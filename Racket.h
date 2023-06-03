#pragma once
#include "Object.h"

class Racket : public Object
{

public:

	Racket(std::shared_ptr<Display> display_ptr, int x, int y) ;

	virtual void draw();

	void update_position();

	virtual void buttonPressed(Key k);
	virtual void buttonReleased(Key k);

};
