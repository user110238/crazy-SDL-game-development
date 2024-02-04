#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

    // Entity constants
const int ENTITY_SIZE_X =   100;
const int ENTITY_SIZE_Y =   100;
const int VELOCITY = 10;

#include "include/main.h"
#include "include/player.h"

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

    int Velocityx = 0;
    int Velocityy = 0;

        // Random stuff
    srand(time(NULL));
    int Randomx = rand()%(LevelWidth);
    int Randomy = rand()%(LevelHeight);

        // Window and Texture pointers
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    SDL_Surface* WindowSurface = nullptr;

        // Entities
        // backgrounds and cameras and such
    struct Player Player {
        (WindowWidth / 2) - (ENTITY_SIZE_X / 2), (WindowHeight / 2) - (ENTITY_SIZE_Y / 2), ENTITY_SIZE_X, ENTITY_SIZE_Y,
        nullptr
    };

    std::vector<struct Player> Enemy;

    for ( int i = 0 ; i < 3 ; i++ )
    {
        Enemy.push_back( { Randomx, Randomy, ENTITY_SIZE_X, ENTITY_SIZE_Y, nullptr } );
        Randomx = rand()%(LevelWidth);
        Randomy = rand()%(LevelHeight);
    }

        // Camera rect is the visible window
        // Background is the whole level
    SDL_Rect camera = {0, 0, WindowWidth, WindowHeight};
    SDL_Rect backgroundRect = {0, 0, LevelWidth, LevelHeight};
    SDL_Texture* Background = nullptr;

        // Setup functions
    initialize(&Window, &WindowSurface, &Renderer, WindowWidth, WindowHeight);
        // Textures
    Player.Texture = loadTexture( Renderer, "assets/triangle.png");
    Background = loadTexture( Renderer, "assets/background.png");

    for ( auto IT = Enemy.begin() ; IT != Enemy.end() ; IT++ )
        (*IT).Texture = loadTexture( Renderer, "assets/circle.png");


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
                            case SDLK_UP: Player.Velocity.y -= VELOCITY; break;
                            case SDLK_DOWN: Player.Velocity.y += VELOCITY; break;
                            case SDLK_LEFT: Player.Velocity.x -= VELOCITY; break;
                            case SDLK_RIGHT: Player.Velocity.x += VELOCITY; break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
                        {
                            case SDLK_UP: Player.Velocity.y += VELOCITY; break;
                            case SDLK_DOWN: Player.Velocity.y -= VELOCITY; break;
                            case SDLK_LEFT: Player.Velocity.x += VELOCITY; break;
                            case SDLK_RIGHT: Player.Velocity.x -= VELOCITY; break;
                        }
                    }
                    break;
            }
        }

            // Clear Previous frame
        SDL_RenderClear(Renderer);

        // Game logic
            // Update player position
        movePlayer( Player ,  LevelWidth , LevelHeight );

            // Enemy logic loop
        for ( int i = 0 ; i < Enemy.size() ; i++ )
        {
                // Move enemy towards player
            moveRectTowards(Enemy.at(i).Rect, Player.Rect);
                // Check if any enemy is collision-ing
            if ( collision (Player.Rect, Enemy.at(i).Rect ) )
                Game_Loop = false;

        }

        // Scrolling
            // Update camera position to center on player
        camera.x = Player.Rect.x + Player.Rect.w / 2 - WindowWidth / 2;
        camera.y = Player.Rect.y + Player.Rect.h / 2 - WindowHeight / 2;

            // Keep the camera within the bounds of the level
        if (camera.x < 0)
            camera.x = 0;
        if (camera.y < 0)
            camera.y = 0;
        if (camera.x > LevelWidth - camera.w)
            camera.x = LevelWidth - camera.w;
        if (camera.y > LevelHeight - camera.h)
            camera.y = LevelHeight - camera.h;

            // Render background with camera offset
        backgroundRect.x = -camera.x;
        backgroundRect.y = -camera.y;
        rendererAdd( Renderer , Background , backgroundRect );

        // Rendering
            // Render player with camera offset
        SDL_Rect playerRect = {Player.Rect.x - camera.x, Player.Rect.y - camera.y, Player.Rect.w, Player.Rect.h};
        rendererAdd(Renderer, Player.Texture, playerRect);

            // render enemies + camera offset
        for ( int i = 0 ; i < Enemy.size() ; i++ )
                rendererAdd(Renderer, Enemy.at(i).Texture, {Enemy.at(i).Rect.x - camera.x, Enemy.at(i).Rect.y - camera.y, Enemy.at(i).Rect.w, Enemy.at(i).Rect.h});

            // Draw Frame
        SDL_RenderPresent(Renderer);

        // Framing
            // Frame delay / limit
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
            SDL_Delay(FrameDelay - FrameTime);
    }

    return 0;
}
