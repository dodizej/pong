#include "Input.h"
#include "Key.h"
#include <SDL2/SDL.h>
#include <string>

Input::Input()
{
}

int Input::check_input()
{
	Key   key;
	State state;

	int status = this->input_implementation(state, key);

	if (state == State::PRESSED)
	{
		for (std::vector<listener_ptr>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->buttonPressed(key);
		}
	}
	else if (state == State::RELEASED)
	{
		for (std::vector<listener_ptr>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->buttonReleased(key);
		}
	}

	return status;
}


void Input::addListener(listener_ptr listener)
{
	this->listeners.push_back(listener);
}

void Input::removeListener(listener_ptr listener)
{
	listeners.erase(
		std::remove_if(
			listeners.begin(),
			listeners.end(),
			[&](listener_ptr v_listener) { return listener.get() == v_listener.get(); }
		),
		listeners.end()
	);
}
