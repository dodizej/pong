#pragma once
#include "Object.h"

class Racket : public Object
{

public:

	Racket(std::shared_ptr<Display> display_ptr, int x, int y);

	virtual void draw();

	void update_position();

	virtual void button_pressed(Key k)  = 0;
	virtual void button_released(Key k) = 0;

	virtual ~Racket();

};

