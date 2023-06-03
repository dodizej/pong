#pragma once
#include "Racket.h"
class PlayerRacket : public Racket
{

public:

	PlayerRacket(std::shared_ptr<Display> _display_ptr, int x, int y);

	void button_pressed(Key k);

	void button_released(Key k);

};

