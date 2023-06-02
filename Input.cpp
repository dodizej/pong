#include "Input.h"
#include "Key.h"
#include <SDL2/SDL.h>
#include <string>

Input::Input()
{
}

void Input::check_input()
{
	State state;
	Key   key;

	this->input_implementation(state, key);


	if (state == State::PRESSED)
	{
		for (std::vector<InputListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->buttonPressed(key);
		}
	}
	else if (state == State::RELEASED)
	{
		for (std::vector<InputListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->buttonReleased(key);
		}
	}
}

void Input::addListener(InputListener* listener)
{
	this->listeners.push_back(listener);
}

void Input::removeListener(InputListener* listener)
{
	std::remove_if(listeners.begin(), listeners.end(), [&](InputListener* v_listener) { return listener == v_listener; });
}
