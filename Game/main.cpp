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


        // Window Pointers
    SDL_Window* Window = NULL;
    SDL_Surface* ScreenSurface = NULL;
    SDL_Surface* Background = NULL;

    if ( !init(&Window , &ScreenSurface , WindowWidth , WindowHeight) )
        std::cout << " Init fail ";
    if ( !LoadMedia( &Background , "Images/idk.bmp") )
        std::cout << " Load background fail ";

    SDL_BlitSurface( Background, NULL, ScreenSurface, NULL );
    SDL_UpdateWindowSurface( Window );




    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    close( Background , Window );

    return 0;
}
