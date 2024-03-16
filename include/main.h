void setup ( Game& Game )
{
    initPlayer( Game.Player , Resolution::LevelWidth / 2 , Resolution::LevelHeight / 2 );

    Game.Forest.resize( Resolution::LevelWidth / constant::PIXEL_SIZE , std::vector<Tile>( Resolution::LevelHeight / constant::PIXEL_SIZE , Tile::Green ) );
    placeCamps( Game.Forest , 5 , Game.CampCoordinates ); // Number of camps
    river( Game.Forest );

    pushRandom( Game.Entities.Enemy , 7 , Resolution::LevelWidth , Resolution::LevelHeight , EntityType::Enemy );
    pushRandom( Game.Entities.Enemy , 3 , Resolution::LevelWidth , Resolution::LevelHeight , EntityType::FireEnemy );
    pushRandomTree( Game.Entities.Tree , 512 , Resolution::LevelWidth , Resolution::LevelHeight , Game.Forest );

    pushToPairCoords( Game.Entities.Allies , 5 , 1 , Game.CampCoordinates , EntityType::Ally ); // Number of allies ; Allies per CampCoordinates

    initBackground( Game.Background );
    Game.Background.Texture = fillBackground( Game.Forest , Game.Window.Renderer );

    Game.FireSpread.lastFireSpreadTime = SDL_GetTicks();
    Game.FireSpread.fireSpreadInterval = 1000;
}

void gameLoop ( Game& Game )
{

            // Used to calculate time per instance of loop
        Game.Frames.FrameStart = SDL_GetTicks();

        // Game logic
        playerGameLogic( Game.Player , Game.Forest );
        entityGameLogic( Game.Entities , Game.Forest , Game.Player.Rect );

        // Scrolling
            // Update camera position to center on player
        scrolling( Game.Background.Camera , Game.Player.Rect , Resolution::WindowWidth , Resolution::WindowHeight , Resolution::LevelWidth , Resolution::LevelHeight );

            // Offset everything with camera
            // remake the background texture
        offset( Game.Background );
        updateBackgroundTexture(Game.Forest, Game.Background.Texture, Game.Window.Renderer, Game.Background.Camera );

            // Calculate Fire spread, every (fireSpreadInterval / 1000) seconds
        if ( Game.Frames.FrameStart - Game.FireSpread.lastFireSpreadTime >= Game.FireSpread.fireSpreadInterval )
        {
            spreadFire( Game.Forest );
            Game.FireSpread.lastFireSpreadTime = Game.Frames.FrameStart;
        }

            // Calculate displayed text
        Game.Text.treeCount = loadTextureFromText( Game.Window.Renderer , std::to_string(calculatePercentage( Game.Forest , Tile::Green )).c_str() , Game.Text.Font );

        // Rendering
        renderGame( Game );

        // Framing
            // Frame delay / limit
        Game.Frames.FrameTime = SDL_GetTicks() - Game.Frames.FrameStart;
        if ( Game.Frames.FrameDelay > Game.Frames.FrameTime )
            SDL_Delay( Game.Frames.FrameDelay - Game.Frames.FrameTime );

}

void startup( Game& Game )
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
    Textures::FireEnemy = loadTexture( Game.Window.Renderer , "assets/red_circle.png" );
    Textures::Tree1 = loadTexture( Game.Window.Renderer , "assets/tree1.png" );
    Textures::Tree2 = loadTexture( Game.Window.Renderer , "assets/tree2.png" );
    Textures::Tree3 = loadTexture( Game.Window.Renderer , "assets/tree3.png" );
    Textures::Ally = loadTexture( Game.Window.Renderer , "assets/star.png" );

    initText( Game.Text , Game.Window.Renderer , "assets/ARCADECLASSIC.ttf" );

}

void mainMenu( Game& Game )
{
    renderMenu( Game );
}

void pauseGame( Game& Game )
{
    renderGame( Game );
}

void GameControl( Game Game )
{
    startup( Game );
    setup( Game );

    Game.State = gameState::mainMenuRunning;
    Game.Button = buttonState::play;

    while ( 1 )
    {
        eventHandler( Game );

        switch( Game.State )
        {
            case gameState::gameRunning:
                gameLoop( Game );
                break;
            case gameState::mainMenuRunning:
                mainMenu( Game );
                break;
            case gameState::gamePause:
                pauseGame( Game );
                break;

            case gameState::endGame:
                cleanUp( Game );
                return;

        }


    }
}
