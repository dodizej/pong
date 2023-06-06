#pragma once
#include "Event.h"

class EventListener
{
public:
	virtual void event_occured(GameEvent game_event) = 0;
};
