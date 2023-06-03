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
			(*it)->button_pressed(key);
		}
	}
	else if (state == State::RELEASED)
	{
		for (std::vector<listener_ptr>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->button_released(key);
		}
	}

	return status;
}


void Input::add_listener(listener_ptr listener)
{
	this->listeners.push_back(listener);
}

void Input::remove_listener(listener_ptr listener)
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
