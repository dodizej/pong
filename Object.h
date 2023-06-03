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

	int x;
	int y;

	int speed = 10;

	int width  = 10;
	int height = 10;

	int window_size_x;
	int window_size_y;

public:

	std::shared_ptr<Display> display_ptr;

	Object(std::shared_ptr<Display> display_ptr, int x, int y);

	virtual void draw() = 0;

	// TODO: virtual void reset_position() = 0;

	void update_position();

	int get_x();
	int get_y();
	int get_w();
	int get_h();

	virtual ~Object();

};

