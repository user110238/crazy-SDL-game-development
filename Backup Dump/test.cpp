#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <iostream>
#include <string>


int main( int argc, char* args[] )
{
    const int WindowWidth = 1600;
    const int WindowHeight = 800;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

    SDL_Texture* PlayerTexture = nullptr;

    SDL_Surface* tmpSurface = IMG_Load("assets/idk.png");
    PlayerTexture = SDL_CreateTextureFromSurface( Renderer , tmpSurface );
    SDL_FreeSurface( tmpSurface );

    SDL_CreateWindowAndRenderer( 1600 , 900 , 0 , &Window , &Renderer );

    SDL_Event Event;
    bool running = 1;

    SDL_Rect Rect{ 10 , 10 , 100 , 100 };



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

        SDL_RenderCopy( Renderer , PlayerTexture , NULL , &Rect );

        SDL_RenderPresent(Renderer);

    }

    SDL_DestroyWindow( Window );
    Window = NULL;

    SDL_Quit();

    return 0;

}
