#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>
#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>

#include "include/main.h"
#include "include/window.h"
#include "include/constants.h"

#include "include/player.h"
#include "include/texture_loading.h"
#include "include/forest.h"
#include "include/entity.h"
#include "include/enemy.h"
#include "include/allies.h"
#include "include/events.h"
#include "include/background.h"
#include "include/text.h"
#include "include/render.h"

struct FrameLimit
{
    int FPS;
    int FrameDelay;
    Uint32 FrameStart;
    int FrameTime;
};

struct AllEntities
{
    std::vector<struct Entity> Enemy;
    std::vector<struct Entity> Allies;
    std::vector<struct Entity> Tree;

};

void setFrameLimit ( FrameLimit& Frames , int x )
{
    Frames.FPS = x;
    Frames.FrameDelay = 1000 / Frames.FPS;
}

namespace Resolution
{
    int WindowWidth;
    int WindowHeight;

    int LevelWidth;
    int LevelHeight;
}

struct Game
{

    structWindow Window;

    //Player Player;
    AllEntities Entities;

    std::vector<std::vector <Tile> > Forest;

    FrameLimit Frames;

};


int main( int argc, char* args[] )
{

            // Enables all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    FrameLimit Frames;
    setFrameLimit( Frames , 60 );
    srand(time(NULL));

            // Window struct
        // window + surf + renderer
    structWindow Window;
    initWindow ( Window , 1600 , 800 , 4800 , 2400 );

            // Create a player struct      x , y
    Player Player;
    initPlayer( Player , 1600 /2 , 800 / 2 , constant::ENTITY_SIZE_X , constant::ENTITY_SIZE_Y );

            // Forest vector
        // Stores background information
        // also makes a texture for thee background
    std::vector<std::vector <Tile> > Forest (
        Window.LevelWidth / constant::PIXEL_SIZE,
        std::vector<Tile> (
            Window.LevelHeight / constant::PIXEL_SIZE , Tile::Green
        ));
        // Number of camps
    Game game;


    fillvector( Forest , 5 );

            // Entity vectors
        // Multinacionalke
    std::vector<struct Entity> Enemy;
    std::vector<struct Entity>::iterator enemyIt = Enemy.begin();
    pushRandom( Enemy , 10 , Window.LevelWidth , Window.LevelHeight , EntityType::Enemy);
        // Trees
    std::vector<struct Entity> Tree;
    std::vector<struct Entity>::iterator treeIt = Tree.begin();
    pushRandom( Tree , 255 , Window.LevelWidth , Window.LevelHeight , EntityType::Tree);
        // Staroselci
    std::vector<struct Entity> Allies;
    std::vector<struct Entity>::iterator allyIt = Allies.begin();
    std::vector<std::pair< int , int >> CampCoordinates = findCamps( Forest );
        // Number of allies + number of allies per camp
    pushToCoords( Allies , 5 , 1 , CampCoordinates , EntityType::Ally);

    struct back Background;
    initBackground( Background , 1600 , 800 , 4800 , 2400 );
    Background.Texture = fillBackground( Forest , Window.Renderer );

        // Textures
    // Set the types in the enum to textures
    Textures::Player = loadTexture( Window.Renderer , "assets/square.png" );
    Textures::Enemy = loadTexture( Window.Renderer , "assets/circle.png" );
    Textures::Tree = loadTexture( Window.Renderer , "assets/triangle.png" );
    Textures::Ally = loadTexture( Window.Renderer , "assets/star.png" );

                // Fonts
        // Path to font + score text
    text Text;
    initText( Text , "assets/ARCADECLASSIC.ttf" );

    while ( endGame() )
    {
            // Used to calculate time per instance of loop
        Frames.FrameStart = SDL_GetTicks();

        // Game logic
            // Update player position
        Player.Velocity = eventHandlerPlayer( Player.Velocity );
        movePlayer( Player , Window.LevelWidth , Window.LevelHeight );

            // Entity logic loop
        if ( Enemy.size() == 0 )
            pushRandom( Enemy , 10 , Window.LevelWidth , Window.LevelHeight , EntityType::Enemy);
        for ( int i = 0 ; i < Enemy.size() ; ++i )
        {
            HandleEnemyMovement(Enemy[i].Rect, Tree );
                // Check if any enemy is collision-ing
            if ( collision ( Player.Rect, Enemy[i].Rect ) )
            {
                Enemy.erase(Enemy.begin() + i);
            }

            for (int j = 0; j < Tree.size(); j++)
            {
                if (collision(Enemy[i].Rect, Tree[j].Rect))
                {
                    updateForest( Forest , Tree[j].Rect , Tile::Brown , 100 );
                    Tree.erase(Tree.begin() + j);
                    --j;
                }
            }

            updateForest( Forest , Enemy[i].Rect , Tile::Brown , 0 );

        }
        for ( int i = 0 ; i < Allies.size() ; ++i )
        {
            HandleAllyMovement( Allies[i].Rect , Enemy , 500 );

            for (int j = 0; j < Enemy.size(); j++)
            {
                if (collision(Allies[i].Rect, Enemy[j].Rect))
                {
                    Enemy.erase(Enemy.begin() + j);
                    --j;
                }
            }
        }

        // Scrolling
            // Update camera position to center on player
        scrolling( Background.Camera , Player.Rect , Window.WindowWidth , Window.WindowHeight , Window.LevelWidth , Window.LevelHeight );

            // Offset everything with camera
            // remake the background texture
        offset( Background );
        updateBackgroundTexture(Forest, Background.Texture, Window.Renderer, Background.Camera );

            // Calculate displayed text
        Text.treeCount = loadTextureFromText( Window.Renderer , std::to_string(calculatePercentage( Forest , Tile::Green )).c_str() , Text.Font );


        // Rendering
        render( Window.Renderer , Background , Player , Enemy , Tree , Allies , Text );

        // Framing
            // Frame delay / limit
        Frames.FrameTime = SDL_GetTicks() - Frames.FrameStart;
        if ( Frames.FrameDelay > Frames.FrameTime )
            SDL_Delay( Frames.FrameDelay - Frames.FrameTime );
        }
    return 0;


}
