#include "Game.h"
#include "../Input/KeyboardInput.h"

Game::Game() {}

std::shared_ptr<Game> Game::get_instance()
{
	static std::shared_ptr<Game> game_ptr = std::make_shared<Game>(Game());
	game_ptr->init();
	return game_ptr;
}

void Game::init()
{
	this->display_ptr = Display::get_instance(window_size_x, window_size_y);

	this->menu_ptr = Menu::get_instance(display_ptr);
	this->menu_ptr->add_event_listener(this);

	this->input_ptr = std::make_shared<KeyboardInput>(KeyboardInput());
	this->input_ptr->add_listener(menu_ptr);
	this->input_ptr->add_event_listener(this);

	ball_ptr = std::make_shared<Ball>(Ball(display_ptr, window_size_x / 2, window_size_y / 2));

	player_racket_ptr = std::make_shared<PlayerRacket>(PlayerRacket(display_ptr, 50, window_size_y / 2));

	computer_racket_ptr1 = std::make_shared<ComputerRacket>(
		ComputerRacket(display_ptr, window_size_x - 50, window_size_y / 2, ball_ptr));

	objects.push_back(ball_ptr);
	objects.push_back(player_racket_ptr);
	objects.push_back(computer_racket_ptr1);

	ball_ptr->add_collision_obj(player_racket_ptr);
	ball_ptr->add_collision_obj(computer_racket_ptr1);
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


// event functions

void Game::event_occured(GameEvent game_event)
{	
	if (game_event == GameEvent::EXIT_GAME)
	{
		exit_flag = true;
	}
	else if (event_mapping.find(game_event) != event_mapping.end())
	{
		current_func = event_mapping.at(game_event);
	}	
}

void Game::set_exit_flag()
{
	exit_flag = true;
}

void Game::start_game()
{
	player_points   = 0;
	computer_points = 0;

	input_ptr->remove_listener(menu_ptr);
	input_ptr->add_listener(player_racket_ptr);
	
	ball_ptr->add_event_listener(this);

	current_func = &Game::game_loop;
	reset_object_positions();
}

void Game::reset_object_positions()
{
	for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
	{
		(*it)->reset_position();
	}
}

void Game::point_added()
{
	if (player_points >= points_to_win || computer_points >= points_to_win)
	{
		current_func = &Game::game_over_loop;
	}
	else
	{
		current_func = &Game::game_loop;
		reset_object_positions();
		SDL_Delay(200);
	}
}

void Game::point_p1()
{
	++player_points;
	point_added();
}

void Game::point_p2()
{
	++computer_points;
	point_added();
}


// functions for main loop

void Game::game_loop()
{
	/*
	std::string press_space_text = "Press space to play!";
	display_ptr->get_text_size(press_space_text, 20, width, height);
	display_ptr->draw_text(press_space_text, (window_size_x / 2) - (width / 2), window_size_y * 0.7, 20);

	display_ptr->show();
	*/
	//this->input_ptr->wait_for_any_key(key);

	for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
	{
		(*it)->update_position();
		(*it)->draw();
	}
	std::string player_score = std::to_string(player_points);
	std::string compuiter_score = std::to_string(computer_points);

	int width, height;
	display_ptr->get_text_size(player_score, 50, width, height);
	int x_title_pos = (window_size_x/2) - 50 - (width / 2);

	display_ptr->draw_text(player_score, x_title_pos, window_size_y * 0.05, 50);

	width, height;
	display_ptr->get_text_size(compuiter_score, 50, width, height);
	x_title_pos = (window_size_x / 2) + 50 - (width / 2);

	display_ptr->draw_text(compuiter_score, x_title_pos, window_size_y * 0.05, 50);

}

void Game::game_over_loop()
{
	for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
	{
		(*it)->draw();
	}
	std::string text_to_show = "";
	if (player_points >= 3)
	{
		text_to_show = "You win!";
		SDL_Log("Player won!");
	}
	else if (computer_points >= 3)
	{
		text_to_show = "You lose!";
		SDL_Log("Computer won!");
	}

	int width, height; 
	
	// todo - function to draw centered text 
	display_ptr->get_text_size(text_to_show, 30, width, height);
	display_ptr->draw_text(text_to_show, (window_size_x / 2) - (width / 2), window_size_y * 0.2, 30);

	std::string press_space_text = "Press space to restart!";
	display_ptr->get_text_size(press_space_text, 20, width, height);
	display_ptr->draw_text(press_space_text, (window_size_x / 2) - (width / 2), window_size_y * 0.7, 20);

	std::string press_any_text = "Press any other key to return to the menu...";
	display_ptr->get_text_size(press_any_text, 20, width, height);
	display_ptr->draw_text(press_any_text, (window_size_x / 2) - (width / 2), window_size_y * 0.75, 20);

	display_ptr->show();

	Key key;
	this->input_ptr->wait_for_any_key(key);
	if (key == Key::SPACE)
	{
		current_func = event_mapping.at(GameEvent::START_GAME);
	}
	else
	{
		current_func = event_mapping.at(GameEvent::MENU);

		ball_ptr->remove_event_listener(this);
		input_ptr->remove_listener(player_racket_ptr);
		input_ptr->add_listener(menu_ptr);
	}
}

void Game::menu_loop()
{
	menu_ptr->show();
}

