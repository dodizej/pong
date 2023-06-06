#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Display.h"
#include "InputListener.h"
#include "Event.h"

class MenuItem
{

private:

	std::string title;


public:

	MenuItem(std::string title, GameEvent game_event);

	std::string get_title();

	GameEvent game_event;
};

class Menu : public InputListener
{

private:

	Menu(std::shared_ptr<Display> display_ptr);

	std::shared_ptr<Display> display_ptr;

	typedef std::vector<std::shared_ptr<MenuItem> > Menu_items_vector;
	Menu_items_vector menu_items;

	int selected_item = 0;

public:

	Menu(Menu const&) = delete;
	void operator=(Menu const&) = delete;

	static std::shared_ptr<Menu> get_instance(std::shared_ptr<Display> display_ptr);

	void show();

	void button_pressed(Key k);
	void button_released(Key k);

};

