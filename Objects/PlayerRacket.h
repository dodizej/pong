#pragma once
#include "Racket.h"
#include "../Input/InputListener.h"

class PlayerRacket : public Racket, public InputListener
{

public:

	PlayerRacket(std::shared_ptr<Display> _display_ptr, int x, int y);

	void button_pressed(Key k);

	void button_released(Key k);

};

