#pragma once
#include "EventListener.h"
#include <memory>
#include <map>
#include "Menu.h"
#include "Input.h"

class Game : public EventListener
{

public:

    static std::shared_ptr<Game> get_instance();

    void init();
    void main_loop();
    void event_occured(GameEvent game_event);
    void start_main_loop();


    // Event functions
    void set_exit_flag();
    void game_loop();
    void menu();


    bool exit_flag = false;
    int window_size_x = 900;
    int window_size_y = 700;

    std::shared_ptr<Menu>     menu_ptr;
    std::shared_ptr<Input>    input_ptr;
    std::shared_ptr<Display>  display_ptr;

    void (Game::* current_func)();

    std::map<GameEvent, void (Game::*)()> event_mapping =
    {
          { GameEvent::EXIT_GAME , &Game::set_exit_flag }
        , { GameEvent::START_GAME, &Game::game_loop     }
        , { GameEvent::MENU      , &Game::menu          }

    };

private:

    Game();

};

