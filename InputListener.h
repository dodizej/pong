#pragma once
#include "Key.h"

class InputListener
{

public:

	virtual void buttonPressed(Key k) = 0;

	virtual void buttonReleased(Key k) = 0;

};

