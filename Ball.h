#pragma once
#include "Object.h"
class Ball : public Object
{

public:

	Ball(std::shared_ptr<Display> display_ptr, int x, int y);

	virtual void draw();

	virtual void buttonPressed(Key k);
	virtual void buttonReleased(Key k);

};

