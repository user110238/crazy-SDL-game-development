#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

//#include "player.hpp"




int main(int argc, char *argv[]) {

    int windowwidth =           1600;
    int windowheight =          900;

    SDL_Window *window =    SDL_CreateWindow( NULL , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , windowwidth , windowheight , SDL_WINDOW_SHOWN );
    SDL_Renderer *renderer =    SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *surface =  SDL_GetWindowSurface( window );

    bool game_state = 1;

    //init( &window , &renderer , &surface , windowwidth , windowheight );

    const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
    SDL_Event e;
    SDL_PollEvent(&e);

    while ( game_state )
    {

        switch (e.type)
        {
            case SDL_QUIT:
                game_state = 0;
                break;
        }

    }




    return 0;
}
