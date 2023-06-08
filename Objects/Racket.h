#pragma once
#include "Object.h"
#include "../Display/Display.h"

class Racket : public Object
{

public:

	Racket(std::shared_ptr<Display> display_ptr, int x, int y);

	void draw();

	virtual void update_position();

	virtual ~Racket();

};

