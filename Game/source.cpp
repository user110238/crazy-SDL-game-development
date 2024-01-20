#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>

    // Creates a window and gives ScreenSurface it's surface
bool init( SDL_Window** Window , SDL_Surface** ScreenSurface , const int WindowWidth , const int WindowHeight );
    // Gives a SDL_Surface an image
bool LoadBackground(SDL_Surface** Surface , std::string path);
    // Free-s up window and it's surface memory
void close(SDL_Surface* Background , SDL_Window* Window);


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
    if ( !LoadBackground( &Background , "Images/idk.bmp") )
        std::cout << " Load background fail ";

    SDL_BlitSurface( Background, NULL, ScreenSurface, NULL );
    SDL_UpdateWindowSurface( Window );




    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    close( Background , Window );

    return 0;
}

bool init( SDL_Window** Window , SDL_Surface** ScreenSurface , const int WindowWidth , const int WindowHeight )
{

    *Window = SDL_CreateWindow( "Schizo Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN );
    if( Window == NULL )
    {
        std::cout << " Window not created " << SDL_GetError();
    }
        else
    {
        *ScreenSurface = SDL_GetWindowSurface( *Window );
    }
}

bool LoadBackground(SDL_Surface** Background , std::string path)
{
    bool check = 1;

    *Background = SDL_LoadBMP( path.c_str() );

    return check;
}

void close(SDL_Surface* Background , SDL_Window* Window)
{
        // Free Surface
    SDL_FreeSurface( Background );
    Background = NULL;

        // Free Window
    SDL_DestroyWindow( Window );
    Window = NULL;

    SDL_Quit();
}
