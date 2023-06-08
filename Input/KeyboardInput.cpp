#include "KeyboardInput.h"

KeyboardInput::KeyboardInput()
{
	this->sdl_event = SDL_Event();
}

void KeyboardInput::input_implementation(State & state, Key & key, GameEvent & game_event)
{
	while (SDL_PollEvent(&sdl_event)) {
		if (sdl_event.type == SDL_QUIT)
		{
			game_event = GameEvent::EXIT_GAME;
			return;
		}
		else if (sdl_event.type == SDL_KEYUP || sdl_event.type == SDL_KEYDOWN)
		{
			if (sdl_event.type == SDL_KEYDOWN)
			{
				state = State::PRESSED;
			}
			else                                       // SDL_KEYUP - no need to check
			{
				state = State::RELEASED;
			}
			if (key_mapping.find(sdl_event.key.keysym.scancode) != key_mapping.end())
			{
				key = key_mapping.at(sdl_event.key.keysym.scancode);
			}
		}
	}
}

void KeyboardInput::wait_for_any_key(Key & key)
{
	bool no_input = true;
	while (no_input)
	{
		while (SDL_PollEvent(&sdl_event))
		{
			if (sdl_event.type == SDL_KEYDOWN)
			{
				no_input = false;
				if (key_mapping.find(sdl_event.key.keysym.scancode) != key_mapping.end())
				{
					key = key_mapping.at(sdl_event.key.keysym.scancode);
				}
			}
		}
	}
}
