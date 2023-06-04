#include "KeyboardInput.h"
#include "Key.h"
#include <SDL2/SDL.h>

KeyboardInput::KeyboardInput()
{
	this->sdl_event = SDL_Event();
}

int KeyboardInput::input_implementation(State & state, Key & key)
{
	while (SDL_PollEvent(&sdl_event)) {

		if (sdl_event.type == SDL_KEYUP || sdl_event.type == SDL_KEYDOWN)
		{
			if (sdl_event.type == SDL_KEYDOWN)
			{
				state = State::PRESSED;
				//SDL_Log("PRESSED");
			}
			else // SDL_KEYUP
			{
				state = State::RELEASED;
				//SDL_Log("RELEASED");
			}

			if (sdl_event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				key = Key::UP;
				//SDL_Log("UP");
			}
			else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				key = Key::DOWN;
				//SDL_Log("DOWN");
			}
			else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				key = Key::LEFT;
				//SDL_Log("LEFT");
			}
			else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				key = Key::RIGHT;
				//SDL_Log("RIGHT");
			}
		}
		else if (sdl_event.type == SDL_QUIT)
		{
			return -1;
		}
		return 0;
	}

}
