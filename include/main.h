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

    initPlayer( Game.Player , Resolution::LevelWidth /2 , Resolution::LevelHeight / 2 );

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
        playerGameLogic( Game.Player );
        entityGameLogic( Game.Entities , Game.Forest , Game.Player.Rect );

        // Scrolling
            // Update camera position to center on player
        scrolling( Game.Background.Camera , Game.Player.Rect , Resolution::WindowWidth , Resolution::WindowHeight , Resolution::LevelWidth , Resolution::LevelHeight );

            // Offset everything with camera
            // remake the background texture
        offset( Game.Background );
        updateBackgroundTexture(Game.Forest, Game.Background.Texture, Game.Window.Renderer, Game.Background.Camera );

            // Calculate displayed text
        Game.Text.treeCount = loadTextureFromText( Game.Window.Renderer , std::to_string(calculatePercentage( Game.Forest , Tile::Green )).c_str() , Game.Text.Font );

        // Rendering
        render( Game );

        // Framing
            // Frame delay / limit
        Game.Frames.FrameTime = SDL_GetTicks() - Game.Frames.FrameStart;
        if ( Game.Frames.FrameDelay > Game.Frames.FrameTime )
            SDL_Delay( Game.Frames.FrameDelay - Game.Frames.FrameTime );
        }


}



