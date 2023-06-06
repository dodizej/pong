#include "Ball.h"
#include <SDL2/SDL.h>
#include <string>

Ball::Ball(std::shared_ptr<Display> display_ptr, int x, int y) : Object(display_ptr, x, y)
{
	this->game_status = 0;
	this->speed       = 4;
	this->velocity_x  = rand() % 5 + 2;
	this->velocity_y  = rand() % 2 + 1;
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

	for (Coll_obj_vec::iterator it = collision_objects.begin(); it != collision_objects.end(); ++it)
	{
		std::shared_ptr<Object> obj_ptr = *it;

		int obj_x = obj_ptr->get_x();
		int obj_y = obj_ptr->get_y();
		int obj_w = obj_ptr->get_w();
		int obj_h = obj_ptr->get_h();

		if ( x + width  > obj_x          &&
			 y + height > obj_y          &&
			 x          < obj_x + obj_w  &&
			 y          < obj_y + obj_h      )
		{

			int x_rnd_vel = rand() % 2 + 4;

			int x_ball_cen = x + width  / 2;
			int y_ball_cen = y + height / 2;

			int x_obj_cen = obj_x + obj_w / 2;
			int y_obj_cen = obj_y + obj_h / 2;

			// minimum distances for the objects to be in collision
			int x_min_dist = width / 2 + obj_w / 2;
			int y_min_dist = height / 2 + obj_h / 2;

			int x_diff = x_ball_cen - x_obj_cen;
			int y_diff = y_ball_cen - y_obj_cen;

			int x_depth = x_min_dist - std::abs(x_diff);
			int y_depth = y_min_dist - std::abs(y_diff);

			if (y_depth < x_depth)
			{
				if (y_diff < 0)
				{
					velocity_y = -1;
				}
				else
				{
					velocity_y = 1;
				}
			}
			else
			{
				if (x_diff < 0)
				{
					velocity_x = -x_rnd_vel;
				}
				else
				{
					velocity_x = x_rnd_vel;
				}
			}

			//SDL_Log("Collision!");
			
			break;
			
		}
	}

	// right side
	if (x + width > window_size_x)
	{
		game_status = -1;              // P1 Score +1
		velocity_x  = -1;
		x = window_size_x - width; 
	}
	// left side
	if (x < 0)
	{
		game_status = 1;               // P2 Score +1
		velocity_x = 1;   
		x = 0;
	}
	// bottom side
	if (y + height > window_size_y)
	{
		velocity_y *= -1;
		y = window_size_y - height;
	}
	// upper side
	if (y < 0)
	{
		velocity_y *= -1;
		y = 0;
	}

}

int Ball::get_game_status()
{
	return game_status;
}

void Ball::reset_position()
{
	game_status = 0;
	Object::reset_position();
	this->velocity_x = rand() % 4 + 1;
	this->velocity_y = rand() % 2 + 1;
}

Ball::~Ball() {}
