#include "input.h"
#include "gfxinterface.h"
#include <X11/keysym.h>


Input::Input()
: quit_ (false)
, move_ (0)
, left_ (false), right_ (false), last_is_left_(false)
, up_ (false), down_ (false), last_is_up_(false)
, fire_ (false), firing_(false)
, start_ (false)
, pause_ (false)
, cheat_ (false)
, details_ (0)
, window_size_ (0)
, inc_refresh_rate_(false)
{}


void Input::Update()
{
	fire_ = false;
	move_ = 0;
	vmove_ = 0;
	start_ = false;
	cheat_ = false;
	highscores_ = false;
	details_ = 0;
	window_size_ = 0;
	inc_refresh_rate_ = false;

	while (X11::Inst().Pending()) {
		XEvent e;
		X11::Inst().NextEvent(&e);
		
		switch (e.type) {
		case KeyPress:
			switch (XLookupKeysym(&e.xkey, 0)) {
			case XK_Left:
				left_ = true;
				last_is_left_ = true;
				break;
			case XK_Right:
				right_ = true;
				last_is_left_ = false;
				break;
			case XK_Up:
				up_ = true;
				last_is_up_ = true;
				break;
			case XK_Down:
				down_ = true;
				last_is_up_ = false;
				break;
			case XK_space:
				fire_ = firing_ = true;
				break;
			default:
				char c (0);
				XLookupString(&e.xkey, &c, 1, 0, 0);
				switch (c) {
				case '+':
					details_ = 1;
					break;
				case '-':
					details_ = -1;
					break;
				case 'r':
					inc_refresh_rate_ = true;
					break;
				case '1':
					window_size_ = 1;
					break;
				case '2':
					window_size_ = 2;
					break;
				case '3':
					window_size_ = 3;
					break;
				case '4':
					window_size_ = 4;
					break;
				case '5':
					window_size_ = 5;
					break;
				case 'h':
					highscores_ = true;
					break;
				case 'p':
					pause_ = !pause_;
					break;
				case 'q':
					quit_ = true;
					return;
				case 's':
					start_ = true;
					return;
				case 'C':
					cheat_ = true;
					return;
				}
			}
			break;
		case KeyRelease:
			switch (XLookupKeysym(&e.xkey, 0)) {
			case XK_Left:
				left_ = false;
				break;
			case XK_Right:
				right_ = false;
				break;
			case XK_Up:
				up_ = false;
				break;
			case XK_Down:
				down_ = false;
				break;
			case XK_space:
				firing_ = false;
				break;
			}
			break;
		}
	}

	fire_ |= firing_;

	if      (!left_ && !right_) move_ =  0;
	else if ( left_ && !right_) move_ = -1;
	else if (!left_ &&  right_) move_ =  1;
	else if (last_is_left_)     move_ = -1;
	else                        move_ =  1;

	if      (!up_ && !down_) vmove_ =  0;
	else if ( up_ && !down_) vmove_ = -1;
	else if (!up_ &&  down_) vmove_ =  1;
	else if (last_is_up_)    vmove_ = -1;
	else                     vmove_ =  1;
}
