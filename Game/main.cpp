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

    bool quit = false;

        // Window Pointers
    SDL_Window* Window = NULL;
    SDL_Surface* ScreenSurface = NULL;
    SDL_Surface* Background = NULL;
        // Window Renderer
    SDL_Renderer* Renderer = NULL;
        // Event Pointers
    SDL_Event event;

        // Initialization
    if ( !init(&Window , &ScreenSurface , &Renderer , WindowWidth , WindowHeight) )
        std::cout << " Init fail ";
    if ( !LoadMedia( &Background , "Images/idk.bmp") )
        std::cout << " Load background fail ";

        // Game loop
    while ( !quit )
    {
            // Event loop
         while( SDL_PollEvent( &event ) != 0 )
                {
                    //User requests quit
                    switch ( event.type )
                    {
                            // Quit event
                        case SDL_QUIT:
                            quit = true;
                            break;
                            // Detects key
                        case SDL_KEYDOWN:
                                // Key events
                            switch ( event.key.keysym.sym )
                            {
                                case SDLK_w:


                                case SDLK_s:

                                    break;

                            }

                            break;

                        }
                }
        }

        /*SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( gRenderer, &fillRect );*/

    SDL_UpdateWindowSurface( Window );

    close( Window );

    return 0;
}
