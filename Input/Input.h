#pragma once
#include <memory>
#include "Key.h"
#include <vector>
#include "InputListener.h"
#include "../Events/EventGenerator.h"
#include "../Events/Event.h"

class Input : public EventGenerator
{

private:

    typedef std::shared_ptr<InputListener> Listener_ptr;
    
    std::vector<Listener_ptr>       listeners;

public:

    Input();

    virtual void check_input();

    virtual void add_listener(Listener_ptr listener);
    virtual void remove_listener(Listener_ptr listener);
    
    virtual void input_implementation(State& state, Key& key, GameEvent& game_event) = 0;

    virtual void wait_for_any_key(Key& key) = 0;

};

