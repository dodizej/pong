#include "KeyboardInput.h"
#include "Key.h"

KeyboardInput::KeyboardInput()
{
	this->sdl_event = SDL_Event();
}

void KeyboardInput::input_implementation(State & state, Key & key)
{
	while (SDL_PollEvent(&sdl_event)) {

		if (sdl_event.type == SDL_KEYUP || sdl_event.type == SDL_KEYDOWN)
		{
			if (sdl_event.type == SDL_KEYDOWN)
			{
				state = State::PRESSED;
			}
			else // SDL_KEYUP
			{
				state = State::RELEASED;
			}

			if (sdl_event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				key = Key::UP;
			}
			else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				key = Key::DOWN;
			}
			else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				key = Key::LEFT;
			}
			else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				key = Key::RIGHT;
			}
		}
		else if (sdl_event.type == SDL_QUIT)
		{
			// ???
		}
	}

}