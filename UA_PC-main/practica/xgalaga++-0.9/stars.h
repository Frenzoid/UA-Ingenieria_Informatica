#ifndef STARS_H
#define STARS_H

#include "gfxinterface.h"
#include "vectordeque.t.h"
#include <list>


class StarsFields {

	// A stars field contains stars scrolling together at a given speed,
	// all the same color (computed from speed).
	class StarsField {
		typedef VectorDeque<Coord> FieldCtn;
		FieldCtn field_;
		int speed_;
		XColor color_;

		StarsField(const StarsField&); // no copy
		StarsField & operator=(const StarsField&); // no copy	
	public:
		StarsField(int speed);
		void Scroll();
	private:
		void DrawAll() const;
	};

	static StarsFields * singleton_;
	static const int max_star_speed_ = 3;

	typedef std::list<StarsField*> Ctn;
	Ctn stars_fields_;

	StarsFields();
	~StarsFields();	
	StarsFields(const StarsFields&); // no copy
	StarsFields & operator=(const StarsFields&); // no copy	
public:
	static StarsFields & Instance();
	static void DestroyInstance();

	void Scroll();
};


#endif
