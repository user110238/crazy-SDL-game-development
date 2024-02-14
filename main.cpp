#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>

#include "include/main.h"
#include "include/window.h"
#include "include/constants.h"

#include "include/player.h"
#include "include/entity.h"
#include "include/enemy.h"
#include "include/events.h"
#include "include/forest.h"
#include "include/background.h"
#include "include/render.h"

int main(int argc, char* args[])
{
        // Enables all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

        // Framerate
    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    int FrameTime;
    int frameCounter = 0;
    srand(time(NULL));

        // Resolution + Level
    int WindowWidth = 1600;
    int WindowHeight = 800;
    int LevelWidth = WindowWidth * 3;
    int LevelHeight = WindowHeight * 3;

        // Window struct
        // window + surf + renderer
    structWindow window( WindowWidth , WindowHeight );
    window.init();


        // Create a player struct      x , y
    Player Player ( (LevelWidth / 2) - (constant::ENTITY_SIZE_X / 2) , (LevelHeight / 2) - (constant::ENTITY_SIZE_Y / 2) ,
                                    // w , h
                    constant::ENTITY_SIZE_X , constant::ENTITY_SIZE_Y );

        // Enemies vector
        // Multinacionalke
    std::vector<struct Entity> Enemy;
    std::vector<struct Entity>::iterator enemyIt = Enemy.begin();
    pushRandom( Enemy , 3 , LevelWidth , LevelHeight );
    std::vector<struct Entity> Tree;
    std::vector<struct Entity>::iterator treeIt = Tree.begin();
    pushRandom( Tree , 3 , LevelWidth , LevelHeight );

        // Forest vector
        // Stores background information
        // also makes a texture for thee background
    std::vector<std::vector <Tile> > Forest (
        LevelWidth / constant::PIXEL_SIZE,
        std::vector<Tile> (
            LevelHeight / constant::PIXEL_SIZE , Tile::Green
        ));
    fillvector( Forest );

    struct back Background ( WindowWidth , WindowHeight , LevelWidth , LevelHeight );
    Background.Texture = fillBackground( Forest , window.Renderer );

        // Textures
    Player.Texture = loadTexture( window.Renderer, "assets/square.png");
    for ( std::vector<Entity>::iterator IT = Enemy.begin() ; IT != Enemy.end() ; IT++ )
        (*IT).Texture = loadTexture( window.Renderer, "assets/circle.png");
    for ( std::vector<Entity>::iterator IT = Tree.begin() ; IT != Tree.end() ; IT++ )
        (*IT).Texture = loadTexture( window.Renderer, "assets/triangle.png");

    bool state = true;

    while ( endGame() )

    {
            // Used to calculate time per instance of loop
        FrameStart = SDL_GetTicks();

        // Game logic
            // Update player position
        Player.Velocity = eventHandlerPlayer( Player.Velocity );
        Player.movePlayer(  LevelWidth , LevelHeight );

        updateForest( Forest , Player.Rect , Tile::Green );

            // Entity logic loop
        for ( int i = 0 ; i < Enemy.size() ; i++ )
        {
            HandleEnemyMovement(Enemy[i], Player.Rect, Tree , 500 );
                // Check if any enemy is collision-ing
            if ( collision ( Player.Rect, Enemy[i].Rect ) )
            {
                state = false;
            }

            for (int j = 0; j < Tree.size(); j++)
            {
                if (collision(Enemy[i].Rect, Tree[j].Rect))
                {
                    Tree.erase(Tree.begin() + j);
                    --j;
                }
            }

            updateForest( Forest , Enemy[i].Rect , Tile::Brown);

        }

        // Scrolling
            // Update camera position to center on player
        scrolling( Background.Camera , Player.Rect , WindowWidth , WindowHeight , LevelWidth , LevelHeight );

            // Offset everything with camera
            // remake the background texture
        Background.offset();
        updateBackgroundTexture(Forest, Background.Texture, window.Renderer, Background.Camera );

        // Rendering
        render( window.Renderer , Background , Player , Enemy , Tree );

        // Framing
            // Frame delay / limit
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
            SDL_Delay(FrameDelay - FrameTime);
    }

    return 0;
}