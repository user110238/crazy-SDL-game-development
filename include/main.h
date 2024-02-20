
int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}
float distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/*
     while ( endGame() )
    {
            // Used to calculate time per instance of loop
        Frames.FrameStart = SDL_GetTicks();

        // Game logic
            // Update player position
        Player.Velocity = eventHandlerPlayer( Player.Velocity );
        Player.movePlayer(  Window.LevelWidth , Window.LevelHeight );

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
        }*/




