#include "pix.h"
#include "instance.h"
#include <stdexcept>
#include <string>


/*
 *  Pix
 */

Pix::Pix(const char *const * xpm)
{
	XpmAttributes attrs;
	attrs.valuemask = XpmSize | XpmExactColors | XpmCloseness;
	attrs.exactColors = False;
	attrs.closeness = 65535;
	const int err_code
		(X11::Inst().CreatePixmapFromData(xpm, &pixmap_, &shapemask_, &attrs));
	if (err_code != XpmSuccess) {
		const std::string msg ("Pixmap creation failed: ");
		throw std::runtime_error (msg + XpmGetErrorString(err_code));
	}
	dim_ = Coord(attrs.width, attrs.height);
}


Pix::~Pix()
{
	X11::Inst().FreePixmap(pixmap_);
	X11::Inst().FreePixmap(shapemask_);
}


void Pix::Draw(Coord pos) const
{
	pos -= Dim() / 2;
	X11::Inst().SetClipOrigin(pos);
	X11::Inst().SetClipMask(shapemask_);
	X11::Inst().CopyAreaToWindow(pixmap_, Coord(0,0), Dim(), pos);
}


void Pix::Mask(Coord pos) const
{
	pos -= Dim() / 2;
	X11::Inst().SetClipOrigin(pos);
	X11::Inst().SetClipMask(shapemask_);
	X11::Inst().SetForeground(X11::Inst().GetBlack());
	X11::Inst().FillRectangle(pos, Dim());
}


void Pix::Move(Coord from, Coord to) const
{
	if (from != to) Mask(from);
	Draw(to);
}


/*
 *  PixKeeper
 */

PixKeeper * PixKeeper::singleton_ (0);


PixKeeper::~PixKeeper()
{
	for (PixCtn::const_iterator it (pixes_.begin());
	     it != pixes_.end(); ++it) {
		delete it->second;
	}
}


PixKeeper & PixKeeper::Instance()
{
	if (!singleton_) {
		singleton_ = new PixKeeper;
		InstancesManager::Instance().Push(DestroyInstance);
	}
	return *singleton_;
}


void PixKeeper::DestroyInstance()
{
	delete singleton_;
	singleton_ = 0;
}


const Pix * PixKeeper::Get(const char *const * pix_data)
{
	const PixCtn::const_iterator it (pixes_.find(pix_data));
	if (it != pixes_.end()) return it->second;

	const Pix *const pix (new Pix(pix_data));
	pixes_.insert(PixCtn::value_type(pix_data, pix));
	return pix;
}
