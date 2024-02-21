void setup ( Game& Game )
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    setFrameLimit( Game.Frames , 60 );
    srand(time(NULL));

    Resolution::WindowWidth = 1600;
    Resolution::WindowHeight = 800;
    Resolution::LevelWidth = Resolution::WindowWidth * 3;
    Resolution::LevelHeight = Resolution::WindowHeight * 3;

    initWindow ( Game.Window );

    Textures::Player = loadTexture( Game.Window.Renderer , "assets/square.png" );
    Textures::Enemy = loadTexture( Game.Window.Renderer , "assets/circle.png" );
    Textures::Tree = loadTexture( Game.Window.Renderer , "assets/triangle.png" );
    Textures::Ally = loadTexture( Game.Window.Renderer , "assets/star.png" );

    initPlayer( Game.player , Resolution::LevelWidth /2 , Resolution::LevelHeight / 2 );

    Game.Forest.resize( Resolution::LevelWidth / constant::PIXEL_SIZE , std::vector<Tile>( Resolution::LevelHeight / constant::PIXEL_SIZE , Tile::Green ) );
    fillvector( Game.Forest , 5 );

    pushRandom( Game.Entities.Enemy , 10 , Resolution::LevelWidth , Resolution::LevelHeight , EntityType::Enemy);
    pushRandom( Game.Entities.Tree , 255 , Resolution::LevelWidth , Resolution::LevelHeight , EntityType::Tree);

    std::vector<std::pair< int , int >> CampCoordinates = findCamps( Game.Forest );
    pushToPairCoords( Game.Entities.Allies , 5 , 1 , CampCoordinates , EntityType::Ally);

    initBackground( Game.Background );
    Game.Background.Texture = fillBackground( Game.Forest , Game.Window.Renderer );

    initText( Game.Text , Game.Window.Renderer , "assets/ARCADECLASSIC.ttf" );
}

void gameLoop ( Game Game )
{
    while ( endGame() )
    {
            // Used to calculate time per instance of loop
        Game.Frames.FrameStart = SDL_GetTicks();

        // Game logic
            // Update player position
        Game.player.Velocity = eventHandlerPlayer( Game.player.Velocity );
        movePlayer( Game.player , Resolution::LevelWidth , Resolution::LevelHeight );


            // Entity logic loop
        if ( Game.Entities.Enemy.size() == 0 )
            pushRandom( Game.Entities.Enemy , 10 , Resolution::LevelWidth , Resolution::LevelHeight , EntityType::Enemy);
        for ( int i = 0 ; i < Game.Entities.Enemy.size() ; ++i )
        {
            HandleEnemyMovement(Game.Entities.Enemy[i].Rect, Game.Entities.Tree );
                // Check if any enemy is collision-ing
            if ( collision ( Game.player.Rect, Game.Entities.Enemy[i].Rect ) )
            {
                Game.Entities.Enemy.erase(Game.Entities.Enemy.begin() + i);
            }

            for (int j = 0; j < Game.Entities.Tree.size(); j++)
            {
                if (collision(Game.Entities.Enemy[i].Rect, Game.Entities.Tree[j].Rect))
                {
                    updateForest( Game.Forest , Game.Entities.Tree[j].Rect , Tile::Brown , 100 );
                    Game.Entities.Tree.erase(Game.Entities.Tree.begin() + j);
                    --j;
                }
            }

            updateForest( Game.Forest , Game.Entities.Enemy[i].Rect , Tile::Brown , 0 );

        }
        for ( int i = 0 ; i < Game.Entities.Allies.size() ; ++i )
        {
            HandleAllyMovement( Game.Entities.Allies[i].Rect , Game.Entities.Enemy , 500 );

            for (int j = 0; j < Game.Entities.Enemy.size(); j++)
            {
                if (collision(Game.Entities.Allies[i].Rect, Game.Entities.Enemy[j].Rect))
                {
                    Game.Entities.Enemy.erase(Game.Entities.Enemy.begin() + j);
                    --j;
                }
            }
        }

        // Scrolling
            // Update camera position to center on player
        scrolling( Game.Background.Camera , Game.player.Rect , Resolution::WindowWidth , Resolution::WindowHeight , Resolution::LevelWidth , Resolution::LevelHeight );

            // Offset everything with camera
            // remake the background texture
        offset( Game.Background );
        updateBackgroundTexture(Game.Forest, Game.Background.Texture, Game.Window.Renderer, Game.Background.Camera );

            // Calculate displayed text
        Game.Text.treeCount = loadTextureFromText( Game.Window.Renderer , std::to_string(calculatePercentage( Game.Forest , Tile::Green )).c_str() , Game.Text.Font );



        // Rendering
        render( Game.Window.Renderer , Game.Background ,Game.player , Game.Entities.Enemy , Game.Entities.Tree , Game.Entities.Allies , Game.Text );

        // Framing
            // Frame delay / limit
        Game.Frames.FrameTime = SDL_GetTicks() - Game.Frames.FrameStart;
        if ( Game.Frames.FrameDelay > Game.Frames.FrameTime )
            SDL_Delay( Game.Frames.FrameDelay - Game.Frames.FrameTime );
        }


}



