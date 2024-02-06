#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "include/main.h"
#include "include/window.h"
#include "include/constants.h"

#include "include/player.h"
#include "include/entity.h"
#include "include/enemy.h"

int main(int argc, char* args[])
{
        // Enables all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

        // Framerate
    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    int FrameTime;

        // Resolution + Level
    int WindowWidth = 1600;
    int WindowHeight = 800;
    int LevelWidth = 3200;
    int LevelHeight = 1900;

        // Random stuff
    srand(time(NULL));
    int Randomx = rand()%(LevelWidth);
    int Randomy = rand()%(LevelHeight);

    structWindow window( WindowWidth , WindowHeight );
    window.init();

        // Create a player struct      x , y
    Player Player ( (LevelWidth / 2) - (constant::ENTITY_SIZE_X / 2) , (LevelHeight / 2) - (constant::ENTITY_SIZE_Y / 2) ,
                                    // w , h
                    constant::ENTITY_SIZE_X , constant::ENTITY_SIZE_Y );

    std::vector<struct Entity> Enemy;
    pushRandom( Enemy , 3 , LevelWidth , LevelHeight );

        // Camera rect is the visible window
        // Background is the whole level
    SDL_Rect camera = {0, 0, WindowWidth, WindowHeight};
    SDL_Rect backgroundRect = {0, 0, LevelWidth, LevelHeight};
    SDL_Texture* Background = nullptr;

        // Textures
    Player.Texture = loadTexture( window.Renderer, "assets/triangle.png");
    Background = loadTexture( window.Renderer, "assets/background.png");

    for ( auto IT = Enemy.begin() ; IT != Enemy.end() ; IT++ )
        (*IT).Texture = loadTexture( window.Renderer, "assets/circle.png");


        // Event variables
        // But are they really variables, hmm
    SDL_Event Event;
    bool Game_Loop = true;

    while (Game_Loop)
    {
            // Used to calculate time per instance of loop
        FrameStart = SDL_GetTicks();

            // Temporary event pool for everything
            // Need to be changed to check keystates for key presses
            // and only use event pool for mouse, quit, ...
        while (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
                case SDL_QUIT:
                    Game_Loop = false;
                    break;
                case SDL_KEYDOWN:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: Player.Velocity.y -= constant::PLAYER_VELOCITY; break;
                            case SDLK_DOWN: Player.Velocity.y += constant::PLAYER_VELOCITY; break;
                            case SDLK_LEFT: Player.Velocity.x -= constant::PLAYER_VELOCITY; break;
                            case SDLK_RIGHT: Player.Velocity.x += constant::PLAYER_VELOCITY; break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: Player.Velocity.y += constant::PLAYER_VELOCITY; break;
                            case SDLK_DOWN: Player.Velocity.y -= constant::PLAYER_VELOCITY; break;
                            case SDLK_LEFT: Player.Velocity.x += constant::PLAYER_VELOCITY; break;
                            case SDLK_RIGHT: Player.Velocity.x -= constant::PLAYER_VELOCITY; break;
                        }
                    }
                    break;
            }
        }

            // Clear Previous frame
        SDL_RenderClear( window.Renderer );

        // Game logic
            // Update player position
        Player.movePlayer(  LevelWidth , LevelHeight );

            // Enemy logic loop
        for ( int i = 0 ; i < Enemy.size() ; i++ )
        {
                // Move enemy towards player
            HandleEnemyMovement( Enemy.at(i) , Player.Rect , 500 );
                // Check if any enemy is collision-ing
            if ( collision (Player.Rect, Enemy.at(i).Rect ) )
                Game_Loop = false;

        }

        // Scrolling
            // Update camera position to center on player
        scrolling( camera , Player.Rect , WindowWidth , WindowHeight , LevelWidth , LevelHeight );

            // Render background with camera offset
        backgroundRect.x = -camera.x;
        backgroundRect.y = -camera.y;
        rendererAdd( window.Renderer , Background , backgroundRect );

        // Rendering
            // Render player with camera offset
        SDL_Rect playerRect = {Player.Rect.x - camera.x, Player.Rect.y - camera.y, Player.Rect.w, Player.Rect.h};
        rendererAdd( window.Renderer, Player.Texture, playerRect );

            // render enemies + camera offset
        for ( int i = 0 ; i < Enemy.size() ; i++ )
                rendererAdd( window.Renderer, Enemy.at(i).Texture, {Enemy.at(i).Rect.x - camera.x, Enemy.at(i).Rect.y - camera.y, Enemy.at(i).Rect.w, Enemy.at(i).Rect.h} );

            // Draw Frame
        SDL_RenderPresent( window.Renderer );

        // Framing
            // Frame delay / limit
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
            SDL_Delay(FrameDelay - FrameTime);
    }

    return 0;
}
