#pragma once
#include <SDL2/SDL_events.h>
#include "Input.h"

class KeyboardInput : public Input
{

private:
	SDL_Event sdl_event;

public:

	KeyboardInput();

	int input_implementation(State & state, Key & key);
	
};

