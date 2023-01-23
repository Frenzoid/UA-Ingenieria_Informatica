#ifndef POSIX_STREAM_H
#define POSIX_STREAM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <streambuf>
#include <string>
#include <cstddef>

// Customized implementation of Josuttis p673-681.
// It is too brittle to be reusable as is.

class PosixBuf : public std::streambuf {
	const int fd_;
	char outbuffer_[4096];
	static const ptrdiff_t in_back_ = 4;
	char inbuffer_[4096 + in_back_];
public:
	// see open() parameters for constructor
	PosixBuf(const std::string & file_name, int open_flags, int mode = 0);
	virtual ~PosixBuf();
	int FD() const { return fd_; }
	int Lock(short type) const; // type: see fcntl() struct flock l_type
	int Truncate(off_t len = 0) const;
private:
	int_type FlushBuffer();
	virtual int_type overflow(int_type c);
	virtual int_type underflow();
	virtual int sync();
	virtual pos_type seekpos(pos_type, std::ios_base::openmode);
};


#endif
