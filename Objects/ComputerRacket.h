#pragma once
#include "Racket.h"
#include "Ball.h"
#include <memory>
#include "../Display/Display.h"

class ComputerRacket : public Racket
{
	std::shared_ptr<Ball> ball_ptr;

	int frames = 0;

public:

	ComputerRacket(std::shared_ptr<Display> display_ptr, int x, int y, std::shared_ptr<Ball> ball_ptr);

	void update_position();

};

