#include "posix_stream.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include <cstdio>


const ptrdiff_t PosixBuf::in_back_;


PosixBuf::PosixBuf(const std::string & file_name, int open_flags, int mode)
: fd_ (open(file_name.c_str(), open_flags, mode))
{
	// The last table character is used to save the overflow character.
	setp(outbuffer_, outbuffer_ + sizeof outbuffer_ - 1);
	setg(inbuffer_ + in_back_, inbuffer_ + in_back_, inbuffer_ + in_back_);
}


PosixBuf::~PosixBuf()
{
	if (fd_ >= 0) {
		sync();
		close(fd_);
	}
}


int PosixBuf::Lock(short type) const
{
	struct flock lk;
	lk.l_type = type;
	lk.l_whence = SEEK_SET;
	lk.l_start = 0;
	lk.l_len = 0;
	return fcntl(fd_, F_SETLKW, &lk);
}


int PosixBuf::Truncate(off_t len) const
{
	return ftruncate(fd_, len);
}


PosixBuf::int_type PosixBuf::FlushBuffer()
{
	const int total (pptr() - pbase());
	int flushed (0);
	do {
		ssize_t ret;
		while ((ret = write(fd_, outbuffer_ + flushed, total - flushed)) == -1 && errno == EINTR);
		if (ret == -1) return EOF;
		flushed += ret;
	} while (flushed < total);
	pbump(-total);
	return total;
}


// Virtual method called when the output buffer overflows.
PosixBuf::int_type PosixBuf::overflow(int_type c)
{
	if (c != EOF) {
		*pptr() = c;
		pbump(1);
	}
	return FlushBuffer();
}


PosixBuf::int_type PosixBuf::underflow()
{
	if (gptr() < egptr()) return static_cast<unsigned char>(*gptr());
	const ptrdiff_t n_back (std::min(in_back_, gptr() - eback()));
	std::copy(gptr() - n_back, gptr(), inbuffer_ + in_back_ - n_back);
	int ret;
	while ((ret = read(fd_, inbuffer_ + in_back_, sizeof inbuffer_ - in_back_)) == -1 && errno == EINTR);
	if (ret <= 0) return EOF;
	setg(inbuffer_ + in_back_ - n_back, inbuffer_ + in_back_, inbuffer_ + in_back_ + ret);
	return static_cast<unsigned char>(*gptr());
}


// Synchronize stream with file => flush buffer
int PosixBuf::sync()
{
	return FlushBuffer() == EOF ? -1 : 0;
}


PosixBuf::pos_type PosixBuf::seekpos(pos_type pos, std::ios_base::openmode)
{
	if (FlushBuffer() == EOF) return -1;
	return lseek(fd_, pos, SEEK_SET);
}
