#pragma once
#include "Key.h"

class InputListener
{

public:

	virtual void button_pressed(Key k) = 0;

	virtual void button_released(Key k) = 0;

};

