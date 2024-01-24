#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <iostream>
#include <string>

#include "functions.h"

int main( int argc, char* args[] )
{
    SDL_Init(SDL_INIT_EVERYTHING);

    const int WindowWidth =     1600;
    const int WindowHeight =    800;

    const int PlayerSizex =     100;
    const int PlayerSizey =     100;


    SDL_Window* Window =            nullptr;
    SDL_Renderer* Renderer =        nullptr;
    SDL_Surface* WindowSurface =    nullptr;
    SDL_Texture* PlayerTexture =    nullptr;

    SDL_Rect PlayerRect{ ( WindowWidth / 2 ) - ( PlayerSizex / 2 ) , ( WindowHeight / 2 ) - ( PlayerSizey / 2 ), PlayerSizex , PlayerSizey };

    initialize( &Window , &WindowSurface , &Renderer , WindowWidth , WindowHeight );
    loadMedia( &PlayerTexture , Renderer );

    SDL_Event Event;
    bool Game_Loop = 1;

    while( Game_Loop )
    {
        while ( SDL_PollEvent(&Event) )
        {
            switch ( Event.type )
            {
                case SDL_QUIT:
                    Game_Loop = 0;
                    break;
                case SDL_KEYDOWN:
                    switch ( Event.key.keysym.sym )
                    {
                        case SDLK_RIGHT:
                            PlayerRect.x += 50;
                            break;
                        case SDLK_LEFT:
                            PlayerRect.x -= 50;
                            break;
                    }
            }
        }

        renderTexture( Renderer , PlayerTexture , PlayerRect );
        SDL_SetRenderDrawColor( Renderer, 0 , 0 , 0 , 0 );

    }





}
