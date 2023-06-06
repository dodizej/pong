#include "Menu.h"
#include <memory>

// MenuItem

MenuItem::MenuItem(std::string title, GameEvent game_event) : title(title), game_event(game_event) { }

std::string MenuItem::get_title()
{
	return title;
}


// Menu

Menu::Menu(std::shared_ptr<Display> display_ptr)
{
	this->display_ptr = display_ptr;
}

std::shared_ptr<Menu> Menu::get_instance(std::shared_ptr<Display> display_ptr)
{
	static std::shared_ptr<Menu> menu_ptr(new Menu(display_ptr));

	menu_ptr->menu_items.push_back(std::shared_ptr<MenuItem>( new MenuItem("Play"   , GameEvent::START_GAME   )));
	menu_ptr->menu_items.push_back(std::shared_ptr<MenuItem>( new MenuItem("Options", GameEvent::OPEN_OPTIONS )));
	menu_ptr->menu_items.push_back(std::shared_ptr<MenuItem>( new MenuItem("Exit"   , GameEvent::EXIT_GAME    )));

	return menu_ptr;
}


void Menu::show()
{
	int x_window_size = display_ptr->get_window_size_x();
	int y_window_size = display_ptr->get_window_size_y();

	std::string title = "Pong";

	int title_font_size = 80;
	int width, height;
	display_ptr->get_text_size(title, title_font_size, width, height);

	display_ptr->draw_text(title, (x_window_size / 2) - (width / 2), y_window_size * 0.2, title_font_size);

	int font_size = 40;

	int menu_y_margin_top    = display_ptr->get_window_size_y() * 0.50; // start about third of the way down
	int menu_y_margin_bottom = display_ptr->get_window_size_y() * 0.9;

	int one_tile_space = (menu_y_margin_bottom - menu_y_margin_top) / menu_items.size();

	int text_max_width  = 0;
	int text_max_height = 0;
	for (Menu_items_vector::iterator it = menu_items.begin(); it != menu_items.end(); ++it)
	{
		int width, height;
		display_ptr->get_text_size((*it)->get_title(), font_size, width, height);
		if (width > text_max_width)
		{
			text_max_width = width + 150;
		}
		if (height > text_max_height)
		{
			text_max_height = height + 15;
		}
	}

	int item_counter = 0;

	int x_rect_pos = (x_window_size / 2) - (text_max_width / 2);
	int y_rect_pos = menu_y_margin_top;
	for (Menu_items_vector::iterator it = menu_items.begin(); it != menu_items.end(); ++it)
	{

		if (item_counter == selected_item)
		{
			int width, height;
			display_ptr->get_text_size((*it)->get_title(), font_size + 5, width, height);
			int x_title_pos = (x_window_size / 2) - (width / 2);

			display_ptr->draw_text((*it)->get_title(), x_title_pos, y_rect_pos + 4, font_size + 5);
			display_ptr->draw_rect_empty(x_rect_pos - 15, y_rect_pos - 10, text_max_width + 30, text_max_height +20);
		}
		else
		{
			int width, height;
			display_ptr->get_text_size((*it)->get_title(), font_size, width, height);
			int x_title_pos = (x_window_size / 2) - (width / 2);

			display_ptr->draw_text((*it)->get_title(), x_title_pos, y_rect_pos + 4, font_size);
			display_ptr->draw_rect_empty(x_rect_pos, y_rect_pos, text_max_width, text_max_height);
		}
		
		y_rect_pos += text_max_height + 20;
		++item_counter;
	}
}

void Menu::button_pressed(Key k)
{
	if (k == Key::UP && selected_item > 0)
	{
		--selected_item;
	}
	else if (k == Key::DOWN && selected_item < menu_items.size() - 1)
	{
		++selected_item;
	}
	else if (k == Key::RETURN)
	{

	}
	else if (k == Key::ESC)
	{

	}
};

void Menu::button_released(Key k)
{

};

