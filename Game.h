#pragma once
#include "EventListener.h"
#include <memory>

class Game : public EventListener
{

    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

    static std::shared_ptr<Game> get_instance();

    void event_occured(GameEvent game_event);

    bool exit_flag = false;

private:

    Game();

};

