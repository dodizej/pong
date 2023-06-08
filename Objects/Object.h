#pragma once
#include <memory>
#include "../Display/Display.h"

class Object
{

protected:

	int init_pos_x;
	int init_pos_y;

	int velocity_x = 0;
	int velocity_y = 0;

	int x;
	int y;

	int speed = 10;

	int width  = 10;
	int height = 10;

	int window_size_x;
	int window_size_y;

	std::shared_ptr<Display> display_ptr;

public:

	Object(std::shared_ptr<Display> display_ptr, int x, int y);
	virtual ~Object();

	virtual void reset_position();

	virtual void update_position();

	int get_x();
	int get_y();
	int get_w();
	int get_h();
	int get_velocity_x();
	int get_velocity_y();

	virtual void draw() = 0;



};

