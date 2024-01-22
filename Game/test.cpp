#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
    // Init , LoadMedia , close
#include "game.h"


int main( int argc, char* args[] )
{
    const int WindowWidth = 1600;
    const int WindowHeight = 800;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

    SDL_Event Event;
    bool running = 1;

    SDL_Rect Rect{ 10 , 10 , 100 , 100 };

    SDL_CreateWindowAndRenderer( 1600 , 900 , 0 , &Window , &Renderer );

    while ( running )
    {
        while ( SDL_PollEvent(&Event))
        {

        switch ( Event.type )
        {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch ( Event.key.keysym.sym )
                {
                    case SDLK_RIGHT:
                        Rect.x += 50;
                        break;
                    case SDLK_LEFT:
                        Rect.x -= 50;
                        break;
                }
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&Rect.x , &Rect.y );
                Rect.x -=50;
                Rect.y -=50;


        }

        }
        SDL_SetRenderDrawColor(Renderer, 255 , 255 , 255 , 255 );
        SDL_RenderClear(Renderer);

        SDL_SetRenderDrawColor(Renderer, 255 , 0 , 0 , 255 );
        SDL_RenderFillRect(Renderer , &Rect );

        SDL_RenderPresent(Renderer);

    }

    SDL_DestroyWindow( Window );
    Window = NULL;

    SDL_Quit();

    return 0;

}
