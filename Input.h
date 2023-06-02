#pragma once
#include <memory>
#include "Key.h"
#include <vector>
#include "InputListener.h"

class Input
{

private:

    std::vector<InputListener*> listeners;

public:

    Input();

    virtual void check_input();

    virtual void input_implementation(State & state, Key & key) = 0;

    virtual void addListener(InputListener* listener);
    virtual void removeListener(InputListener* listener);

};

