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

	int width = 0, height = 0;

public:

	std::shared_ptr<Display> display_ptr;

	Object(std::shared_ptr<Display> display_ptr);

	virtual void draw() = 0;

	void update_position();

	virtual void buttonPressed(Key k) = 0;
	virtual void buttonReleased(Key k) = 0;

};

