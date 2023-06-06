#include "Game.h"

Game::Game() {}

std::shared_ptr<Game> Game::get_instance()
{
	static std::shared_ptr<Game> game_ptr(new Game());
	return game_ptr;
}

void Game::event_occured(GameEvent game_event)
{
	if (game_event == GameEvent::EXIT_GAME)
	{
		exit_flag = true;
	}
}
