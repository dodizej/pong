#include<Windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include <math.h>
#include <memory.h>
#include "Display.h"
#include "Racket.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "Ball.h"
#include "PlayerRacket.h"
#include "ComputerRacket.h"
#include "Menu.h"
#include "Game.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	int window_size_x = 900;
	int window_size_y = 700;

	std::shared_ptr<Game> game_ptr = Game::get_instance();
	game_ptr->start_main_loop();

	return 0;
}
