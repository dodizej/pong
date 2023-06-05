#pragma once
#include <memory>
#include <string>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>


class Display
{

public:
    
    static std::shared_ptr<Display> get_instance(int window_size_x, int window_size_y);

    Display(Display const&)        = delete;
    void operator=(Display const&) = delete;


    void draw_rect(int x, int y, int w, int h);
    void draw_text(std::string text);

    void show();
    void clear();

    int get_window_size_x();
    int get_window_size_y();

private:

    int window_size_x;
    int window_size_y;

    Display(int window_size_x, int window_size_y);

    SDL_Window   * win;
    SDL_Renderer * m_window_renderer;

    Uint32 render_flags;

};
