#include<SDL2/SDL.h>

#include <string>


class SDLInter {


    public:

        const int SCREEN_WIDTH = 640;
        const int SCREEN_HEIGHT = 480;

        bool init();

        void close();

        SDL_Window* gameWindow = NULL;
        SDL_Renderer* gameRenderer = NULL;


};




