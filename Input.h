#pragma once
#include <memory>
#include "Key.h"
#include <vector>
#include "InputListener.h"
#include "Object.h"
#include "EventListener.h"

class Input
{

private:

    typedef std::shared_ptr<InputListener> Listener_ptr;
    typedef std::shared_ptr<EventListener> Event_listener_ptr;
    
    std::vector<Listener_ptr>       listeners;
    std::vector<Event_listener_ptr> event_listeners;

public:

    Input();

    virtual void check_input();

    virtual void add_listener(Listener_ptr listener);
    virtual void remove_listener(Listener_ptr listener);

    virtual void add_event_listener(Event_listener_ptr listener);
    virtual void remove_event_listener(Event_listener_ptr listener);
    
    virtual void input_implementation(State& state, Key& key, GameEvent& game_event) = 0;

};

