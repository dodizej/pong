#pragma once
#include "Key.h"

class InputListener
{

public:

	virtual void button_pressed(Key k);

	virtual void button_released(Key k);

};

