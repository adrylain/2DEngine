#pragma once

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


class Game {

    public:

    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }



    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;

    private:

    SDL_Window *window;

};










