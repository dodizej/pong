#pragma once
#include "Object.h"

class Racket : public Object
{

private:
	int x = 100;
	int y = 100;

	int width  = 20;
	int height = 70;

public:

	Racket(std::shared_ptr<Display> display_ptr, int x, int y) ;

	virtual void draw();

	virtual void buttonPressed(Key k);
	virtual void buttonReleased(Key k);

};

