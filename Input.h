#pragma once
#include <memory>
#include "Key.h"
#include <vector>
#include "InputListener.h"
#include "Object.h"

class Input
{

private:

    typedef std::shared_ptr<InputListener> listener_ptr;

    std::vector<listener_ptr> listeners;

public:

    Input();

    virtual int  check_input();

    virtual int  input_implementation(State & state, Key & key) = 0;

    virtual void add_listener(listener_ptr listener);

    virtual void remove_listener(listener_ptr listener);

};

