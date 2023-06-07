#pragma once
#include <memory>
#include <string>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <map>


class Display
{

public:
    
    static std::shared_ptr<Display> get_instance(int window_size_x, int window_size_y);

    void draw_rect(int x, int y, int w, int h);
    void draw_rect_empty(int x, int y, int w, int h);
    void draw_text(std::string text, int x, int y, int font_size = 30);

    void show();
    void clear();

    int get_window_size_x();
    int get_window_size_y();

    std::map<int, TTF_Font*> fonts_by_size;

    void get_text_size(std::string text, int font_size, int& width, int& height);

private:

    int window_size_x;
    int window_size_y;

    Display(int window_size_x, int window_size_y);

    SDL_Window   * win;
    SDL_Renderer * m_window_renderer;

    Uint32 render_flags;

    TTF_Font* get_font(int font_size);

};
