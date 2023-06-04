#include "Object.h"


Object::Object(std::shared_ptr<Display> _display_ptr, int x, int y)
{
	this->x = x;
	this->y = y;
	this->init_pos_x = x;
	this->init_pos_y = y;
	this->display_ptr = _display_ptr;
	this->window_size_x = _display_ptr->get_window_size_x();
	this->window_size_y = _display_ptr->get_window_size_y();

}


void Object::update_position()
{

	x += speed * velocity_x;
	y += speed * velocity_y;

	// right boundary
	if (x + width > window_size_x)
	{
		velocity_x = -1;
		x = window_size_x - width;
	}
	// left boundary
	if (x < 0)
	{
		velocity_x = 1;
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

void Object::reset_position()
{
	x = init_pos_x;
	y = init_pos_y;
}

int Object::get_x()
{
	return x;
}

int Object::get_y()
{
	return y;
}

int Object::get_w()
{
	return width;
}

int Object::get_h()
{
	return height;
}

int Object::get_velocity_x()
{
	return velocity_x;
}

int Object::get_velocity_y()
{
	return velocity_y;
}


Object::~Object()
{
}
