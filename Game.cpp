#include "Game.h"
#include "Display.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "Ball.h"
#include "PlayerRacket.h"
#include "ComputerRacket.h"


Game::Game() {}

std::shared_ptr<Game> Game::get_instance()
{
	static std::shared_ptr<Game> game_ptr(new Game());
	game_ptr->init();
	return game_ptr;
}

void Game::event_occured(GameEvent game_event)
{	
	if (game_event == GameEvent::EXIT_GAME)
	{
		exit_flag = true;
	}
	else if (event_mapping.find(game_event) != event_mapping.end())
	{
		current_func = event_mapping[game_event];
	}	
}

void Game::init()
{
	this->display_ptr = Display::get_instance(window_size_x, window_size_y);

	this->menu_ptr = Menu::get_instance(display_ptr);
	this->menu_ptr->add_event_listener(this);

	this->input_ptr = std::make_shared<KeyboardInput>(KeyboardInput());
	this->input_ptr->add_listener(menu_ptr);
	this->input_ptr->add_event_listener(this);

	this->current_func = event_mapping[GameEvent::MENU];
}

void Game::start_main_loop()
{
	this->main_loop();
}

void Game::main_loop()
{
	while (!exit_flag)
	{
		display_ptr->clear();
		input_ptr->check_input();
		
		(*this.*current_func)();

		display_ptr->show();
	}
}

void Game::menu()
{
	menu_ptr->show();
}

void Game::game_loop()
{
	this->input_ptr->remove_listener(menu_ptr);

	std::shared_ptr<Ball> ball_ptr = std::make_shared<Ball>(Ball(display_ptr, window_size_x / 2, window_size_y / 2));

	std::shared_ptr<PlayerRacket> player_racket_ptr = std::make_shared<PlayerRacket>(
		PlayerRacket(display_ptr, 50, window_size_y / 2)
	);

	std::shared_ptr<ComputerRacket> computer_racket_ptr1 = std::make_shared<ComputerRacket>(
		ComputerRacket(display_ptr, window_size_x - 50, window_size_y / 2, ball_ptr)
	);

	//std::shared_ptr<ComputerRacket> computer_racket_ptr1(new ComputerRacket(display_ptr, 50, window_size_y / 2, ball_ptr));
	//std::shared_ptr<ComputerRacket> computer_racket_ptr2(new ComputerRacket(display_ptr, window_size_x - 50, window_size_y / 2, ball_ptr));

	// Add player racket as listener to keyboard input
	input_ptr->add_listener(player_racket_ptr);

	// Add collision objects
	ball_ptr->add_collision_obj(player_racket_ptr);
	ball_ptr->add_collision_obj(computer_racket_ptr1);
	//ball_ptr->add_collision_obj(computer_racket_ptr2);


	std::vector<std::shared_ptr<Object>> objects;
	objects.push_back(ball_ptr);
	objects.push_back(player_racket_ptr);
	objects.push_back(computer_racket_ptr1);
	//objects.push_back(computer_racket_ptr2);

	int game_status = 0;
	int player_points = 0;
	int computer_points = 0;

	while (!exit_flag)
	{
		display_ptr->clear();
		input_ptr->check_input();
		for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
		{
			(*it)->draw();
		}
		display_ptr->show();

		game_status = ball_ptr->get_game_status();
		if (game_status != 0)
		{
			if (game_status > 0)
			{
				++computer_points;
				SDL_Log("Computer +1");
			}
			else
			{
				++player_points;
				SDL_Log("Player +1");
			}

			if (player_points >= 3 || computer_points >= 3)
			{
				std::string text_to_show = "";
				if (player_points >= 3)
				{
					text_to_show = "Player won!";
					SDL_Log("Player won!");
				}
				else if (computer_points >= 3)
				{
					text_to_show = "Computer won!";
					SDL_Log("Computer won!");
					
				}
				int width, height;
				display_ptr->get_text_size(text_to_show, 30, width, height);
				display_ptr->draw_text("Player won!", (window_size_x / 2) - (width / 2), window_size_y * 0.2, 30);

				std::string press_space_text = "Press space to restart";
				display_ptr->get_text_size(press_space_text, 20, width, height);
				display_ptr->draw_text(press_space_text, (window_size_x / 2) - (width / 2), window_size_y * 0.7, 20);

				std::string press_any_text = "Press any other key to return to the menu";
				display_ptr->get_text_size(press_any_text, 20, width, height);
				display_ptr->draw_text(press_any_text, (window_size_x / 2) - (width / 2), window_size_y * 0.75, 20);

				display_ptr->show();
				break;
			}

			for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
			{
				(*it)->reset_position();
			}
			SDL_Delay(200);
		}
	}

	Key key;
	this->input_ptr->wait_for_any_key(key);

	if (key != Key::SPACE)
	{
		current_func = event_mapping[GameEvent::MENU];
		this->input_ptr->remove_listener(player_racket_ptr);
		this->input_ptr->add_listener(menu_ptr);
	}
	
}

void Game::set_exit_flag()
{
	exit_flag = true;
}
