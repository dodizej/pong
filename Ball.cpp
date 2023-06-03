#include "Ball.h"
#include <SDL2/SDL.h>
#include <string>

Ball::Ball(std::shared_ptr<Display> display_ptr, int x, int y) : Object(display_ptr, x, y)
{
	this->game_status = 0;
	this->speed       = 7;
	this->velocity_x  = 1;
	this->width       = 15;
	this->height      = 15;
}

void Ball::draw()
{
	this->update_position();
	this->display_ptr->draw_rect(x, y, width, height);
}

void Ball::button_pressed(Key k)  { }

void Ball::button_released(Key k) { }

void Ball::add_collision_obj(std::shared_ptr<Object> object)
{
	this->collision_objects.push_back(object);
}

void Ball::update_position()
{

	x += speed * velocity_x;
	y += speed * velocity_y;

	for (coll_obj_vec::iterator it = collision_objects.begin(); it != collision_objects.end(); ++it)
	{
		std::shared_ptr<Object> obj_ptr = *it;

		if ( x + width  >= obj_ptr->get_x()                    &&
			 y + height > obj_ptr->get_y()                    &&
			 x          <= obj_ptr->get_x() + obj_ptr->get_w() &&
			 y          < obj_ptr->get_y() + obj_ptr->get_h()    )
		{
			velocity_x *= -1;
			break;
		}
	}

	// right boundary
	if (x + width > window_size_x)
	{
		game_status = -1;          // P1 Score +1
		velocity_x  = -1;
		x = window_size_x - width; 
		
	}
	// left boundary
	if (x < 0)
	{
		game_status = 1;          // P2 Score +1
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

int Ball::get_game_status()
{
	return game_status;
}

Ball::~Ball() {}
