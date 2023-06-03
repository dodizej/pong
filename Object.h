#pragma once
#include <memory>
#include "InputListener.h"
#include "Display.h"
#include "Key.h"

class Object : public InputListener
{

protected:
	int velocity_x = 0;
	int velocity_y = 0;

	int x = 100;
	int y = 100;

	int speed = 10;

	int width  = 10;
	int height = 10;

	int window_size_x;
	int window_size_y;

public:

	std::shared_ptr<Display> display_ptr;

	Object(std::shared_ptr<Display> display_ptr, int x, int y);

	virtual void draw() = 0;

	void update_position();

	virtual void buttonPressed(Key k) = 0;
	virtual void buttonReleased(Key k) = 0;

	virtual ~Object();

};

