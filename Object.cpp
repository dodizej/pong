#include "Object.h"


Object::Object(std::shared_ptr<Display> _display_ptr)
{
	this->display_ptr = _display_ptr;
}


void Object::update_position()
{
	int speed = 30;

	int window_size_x;
	int window_size_y;

	this->display_ptr->get_window_size(window_size_x, window_size_y);

	y += speed * velocity_y;

	// right boundary
	if (x + width > window_size_x)
	{
		velocity_x = 0;
		x = window_size_x - width;
	}
	// left boundary
	if (x < 0)
	{
		velocity_x = 0;
		x = 0;
	}
	// bottom boundary
	if (y + height > window_size_y)
	{
		velocity_y = 0;
		y = window_size_y - height;
	}
	// upper boundary
	if (y < 0)
	{
		velocity_y = 0;
		y = 0;
	}

}
