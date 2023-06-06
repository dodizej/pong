#pragma once
#include <SDL2/SDL_events.h>
#include "Input.h"
#include <map>

class KeyboardInput : public Input
{

private:
	SDL_Event sdl_event;

	typedef std::map<SDL_Scancode, Key> Key_map;
	Key_map key_mapping =
	{
		  { SDL_SCANCODE_UP     , Key::UP     }
		, { SDL_SCANCODE_DOWN   , Key::DOWN   }
		, { SDL_SCANCODE_LEFT   , Key::LEFT   }
		, { SDL_SCANCODE_RIGHT  , Key::RIGHT  }
		, { SDL_SCANCODE_RETURN , Key::RETURN }
		, { SDL_SCANCODE_ESCAPE , Key::ESC    }
	};

public:

	KeyboardInput();

	void input_implementation(State & state, Key & key, GameEvent & game_event);
	
};

