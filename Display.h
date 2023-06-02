#pragma once
#include <memory>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>


class Display
{

public:
    
    static std::shared_ptr<Display> get_instance(int window_size_x, int window_size_y);

    Display(Display const&)        = delete;
    void operator=(Display const&) = delete;


    void drawRect(int x, int y, int w, int h);

    void show();
    void clear();

    void get_window_size(int & x, int & y);

private:

    int window_size_x;
    int window_size_y;

    Display(int window_size_x, int window_size_y);

    SDL_Window   * win;
    SDL_Renderer * m_window_renderer;

    Uint32 render_flags;

};
