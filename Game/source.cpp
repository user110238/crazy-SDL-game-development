#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <iostream>
#include <string>

#include "functions.h"
#include "player.h"

int main( int argc, char* args[] )
{
        // Enables all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

        // 60 Framerate
    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    int FrameTime;

        // Resolution
    int WindowWidth =     1600;
    int WindowHeight =    800;

        // Entity values
    const int PlayerSizex =     100;
    const int PlayerSizey =     100;
    const int Velocity =        10;
    int Velocityx =             0;
    int Velocityy =             0;

        // Window and Texture pointers
    SDL_Window* Window =            nullptr;
    SDL_Renderer* Renderer =        nullptr;
    SDL_Surface* WindowSurface =    nullptr;
    //SDL_Texture* PlayerTexture =    nullptr;

    struct Player Player {
            // Player rectangle
        ( WindowWidth / 2 ) - ( PlayerSizex / 2 ) , ( WindowHeight / 2 ) - ( PlayerSizey / 2 ), PlayerSizex , PlayerSizey,
            // Texture
        nullptr
    };

    struct Player Enemy {
        // Player rectangle
        50 , ( WindowHeight / 2 ) - ( PlayerSizey / 2 ), PlayerSizex , PlayerSizey,
            // Texture
        nullptr

    };

        // Setup functions
    initialize( &Window , &WindowSurface , &Renderer , WindowWidth , WindowHeight );
    loadMedia( &Player.Texture , Renderer , "assets/triangle.png" );

    SDL_Event Event;
    bool Game_Loop = 1;


    while( Game_Loop )
    {

        FrameStart = SDL_GetTicks();

        while ( SDL_PollEvent(&Event) )
        {
            switch ( Event.type )
            {
                case SDL_QUIT:
                    Game_Loop = 0;
                    break;
                case SDL_KEYDOWN:
                    if( Event.key.repeat == 0 )
                    {
                        switch( Event.key.keysym.sym )
                        {
                            case SDLK_UP: Velocityy -= Velocity; break;
                            case SDLK_DOWN: Velocityy += Velocity; break;
                            case SDLK_LEFT: Velocityx -= Velocity; break;
                            case SDLK_RIGHT: Velocityx += Velocity; break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if( Event.key.repeat == 0 )
                    {
                        switch( Event.key.keysym.sym )
                        {
                            case SDLK_UP: Velocityy += Velocity; break;
                            case SDLK_DOWN: Velocityy -= Velocity; break;
                            case SDLK_LEFT: Velocityx += Velocity; break;
                            case SDLK_RIGHT: Velocityx -= Velocity; break;
                        }
                    }
                    break;

            }
        }

        movePlayer ( Player.Rect , Velocityx , Velocityy );

        renderTexture( Renderer , Player.Texture , Player.Rect );

        SDL_RenderClear( Renderer );

        FrameTime = SDL_GetTicks() - FrameStart;



        if ( FrameDelay > FrameTime )
            SDL_Delay( FrameDelay - FrameTime );

    }





}
