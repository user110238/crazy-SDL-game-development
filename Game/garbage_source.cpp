#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1280;

SDL_Window* Window = NULL;
SDL_Surface* ScreenSurface = NULL;
SDL_Surface* Background = NULL;

bool init()
{
    bool check = 1;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << " Error " << SDL_GetError();
    }
    else
    {
        Window = SDL_CreateWindow( "Schizo Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( Window == NULL )
        {
            std::cout << " Window not created " << SDL_GetError();
        }
         else
        {
            ScreenSurface = SDL_GetWindowSurface( Window );
        }
    }
    return check;
}

bool LoadBackground()
{

    bool check = 1;

    Background = SDL_LoadBMP( "Images/idk.bmp" );
    if( Background == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "images/idk.bmp", SDL_GetError() );
        check = false;
    }

    return check;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( Background );
    Background = NULL;

    //Destroy window
    SDL_DestroyWindow( Window );
    Window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}


int main( int argc, char* args[] )
{

    if ( !init() )
        std::cout << " Init fail ";
    if ( !LoadBackground() )
        std::cout << " Load background fail ";

    SDL_BlitSurface( Background, NULL, ScreenSurface, NULL );

    SDL_UpdateWindowSurface( Window );

    //Hack to get window to stay up
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    close();

    return 0;


}

