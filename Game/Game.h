#pragma once
#include "../Events/EventListener.h"
#include <memory>
#include <map>
#include "../Menu/Menu.h"
#include "../Input/Input.h"
#include "../Objects/PlayerRacket.h"
#include "../Objects/ComputerRacket.h"


class Game : public EventListener
{

public:

    static std::shared_ptr<Game> get_instance();

    void main_loop();

private:

    void init();

    void event_occured(GameEvent game_event);
    void reset_object_positions();
    void point_added();


    // Event functions
    void set_exit_flag();
    void start_game();
    void point_p1();
    void point_p2();

    // loop functions
    void game_loop();
    void game_over_loop();
    void menu_loop();


    bool exit_flag    = false;
    int window_size_x = 900;
    int window_size_y = 700;

    const int points_to_win = 3;

    std::shared_ptr<Menu>     menu_ptr;
    std::shared_ptr<Input>    input_ptr;
    std::shared_ptr<Display>  display_ptr;

    void (Game::* current_func)() = &Game::menu_loop;

    const std::map<GameEvent, void (Game::*)()> event_mapping =
    {
          { GameEvent::EXIT_GAME , &Game::set_exit_flag }
        , { GameEvent::START_GAME, &Game::start_game    }
        , { GameEvent::MENU      , &Game::menu_loop     }
        , { GameEvent::POINT_P1  , &Game::point_p1      }
        , { GameEvent::POINT_P2  , &Game::point_p2      }
    };


    int player_points = 0, computer_points = 0;

    std::vector<std::shared_ptr<Object>> objects;

    std::shared_ptr<Ball>                ball_ptr;
    std::shared_ptr<PlayerRacket>        player_racket_ptr;
    std::shared_ptr<ComputerRacket>      computer_racket_ptr1;

    Game();

};

