#include "Ball.h"


Ball::Ball(std::shared_ptr<Display> display_ptr, int x, int y) : Object(display_ptr, x, y) 
{
	this->speed      = 5;
	this->velocity_x = 1;
	this->width      = 15;
	this->height     = 15;
}


void Ball::draw()
{
	this->update_position();
	this->display_ptr->drawRect(x, y, width, height);
}


void Ball::buttonPressed(Key k)
{

}


void Ball::buttonReleased(Key k)
{

}
