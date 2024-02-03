#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <iostream>
#include <string>

#include "include/main.h"
#include "include/player.h"

int main(int argc, char* args[])
{
        // Enables all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

        // 60 Framerate
    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    int FrameTime;

        // Resolution
    int WindowWidth = 1600;
    int WindowHeight = 800;
    int LevelWidth = 3200;
    int LevelHeight = 1900;

        // Entity values
    const int PlayerSizex = 100;
    const int PlayerSizey = 100;
    const int Velocity = 10;
    int Velocityx = 0;
    int Velocityy = 0;

        // Random stuff
    srand(time(NULL));
    int Randomx = rand()%(WindowWidth);
    int Randomy = rand()%(WindowHeight);

        // Window and Texture pointers
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    SDL_Surface* WindowSurface = nullptr;


        // Entities
        // Backgrounds and cameras and such

    struct Player Player {
        (WindowWidth / 2) - (PlayerSizex / 2), (WindowHeight / 2) - (PlayerSizey / 2), PlayerSizex, PlayerSizey,
        nullptr
    };

    struct Player Enemy {
        Randomx, Randomy, PlayerSizex, PlayerSizey,
        nullptr
    };

    SDL_Rect camera = {0, 0, WindowWidth, WindowHeight};
    SDL_Rect backgroundRect = {0, 0, LevelWidth, LevelHeight};
    SDL_Texture* Background = nullptr;

        // Setup functions
    initialize(&Window, &WindowSurface, &Renderer, WindowWidth, WindowHeight);
    loadTexture(&Player.Texture, Renderer, "assets/triangle.png");
    loadTexture(&Enemy.Texture, Renderer, "assets/circle.png");
    Background = loadTexture(Renderer, "assets/background.png");

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
                            case SDLK_UP: Velocityy -= Velocity; break;
                            case SDLK_DOWN: Velocityy += Velocity; break;
                            case SDLK_LEFT: Velocityx -= Velocity; break;
                            case SDLK_RIGHT: Velocityx += Velocity; break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if (Event.key.repeat == 0)
                    {
                        switch (Event.key.keysym.sym)
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

            // Clear Previous frame
        SDL_RenderClear(Renderer);

            // Update player position
        movePlayer(Player.Rect, Velocityx, Velocityy);

        if ( collision (Player.Rect, Enemy.Rect) )
            Game_Loop = false;

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

            // Render player with camera offset
        SDL_Rect playerRect = {Player.Rect.x - camera.x, Player.Rect.y - camera.y, Player.Rect.w, Player.Rect.h};
        rendererAdd(Renderer, Player.Texture, playerRect);

            // Render enemy with camera offset
        SDL_Rect enemyRect = {Enemy.Rect.x - camera.x, Enemy.Rect.y - camera.y, Enemy.Rect.w, Enemy.Rect.h};
        rendererAdd(Renderer, Enemy.Texture, enemyRect);

            // Draw Frame
        SDL_RenderPresent(Renderer);

            // Frame delay / limit
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
            SDL_Delay(FrameDelay - FrameTime);
    }

    return 0;
}
