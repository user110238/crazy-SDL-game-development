void writeToFile( const char* filename , Game* game )
{
    FILE* file = fopen( filename , "w" );

    fprintf( file , "%d %d %d %d %d\n" , game->Player.Rect.x , game->Player.Rect.y , game->Player.Rect.w , game->Player.Rect.h , game->Player.Type );

    fprintf( file , "%d %d %d %d\n" , game->Background.Camera.x , game->Background.Camera.y , game->Background.Camera.w , game->Background.Camera.h );

    for ( int i = 0 ; i < Resolution::LevelWidth / constant::PIXEL_SIZE ; ++i )
    {
        for ( int j = 0 ; j < Resolution::LevelHeight / constant::PIXEL_SIZE ; ++j )
        {
            fprintf( file , "%d " , game->Forest[i][j] );
        }
        fprintf( file , "\n" );
    }

    fprintf( file , "%zu\n" , game->CampCoordinates.size() );
    for ( size_t i = 0 ; i < game->CampCoordinates.size() ; ++i )
    {
        fprintf( file , "%d %d\n" , game->CampCoordinates[i].first , game->CampCoordinates[i].second );
    }

    fprintf( file , "%zu\n" , game->Entities.Enemy.size() );
    for ( size_t i = 0 ; i < game->Entities.Enemy.size() ; ++i )
    {
        fprintf( file , "%d %d %d %d %d\n" , game->Entities.Enemy[i].Rect.x , game->Entities.Enemy[i].Rect.y , game->Entities.Enemy[i].Rect.w , game->Entities.Enemy[i].Rect.h , game->Entities.Enemy[i].Type );
    }

    fprintf( file , "%zu\n" , game->Entities.Allies.size() );
    for ( size_t i = 0 ; i < game->Entities.Allies.size() ; ++i )
    {
        fprintf( file , "%d %d %d %d %d\n" , game->Entities.Allies[i].Rect.x , game->Entities.Allies[i].Rect.y , game->Entities.Allies[i].Rect.w , game->Entities.Allies[i].Rect.h , game->Entities.Allies[i].Type );
    }

    fprintf( file , "%zu\n" , game->Entities.Tree.size() );
    for ( size_t i = 0 ; i < game->Entities.Tree.size() ; ++i )
    {
        fprintf( file , "%d %d %d %d %d\n" , game->Entities.Tree[i].Rect.x , game->Entities.Tree[i].Rect.y , game->Entities.Tree[i].Rect.w , game->Entities.Tree[i].Rect.h , game->Entities.Tree[i].Type );
    }

    fclose(file);
}

void writeToReplay( const char* filename , Game* game )
{
    FILE* file = fopen( filename , "a" );

    fprintf( file , "%zu\n" , game->Entities.Allies.size() );
    for ( size_t i = 0 ; i < game->Entities.Allies.size() ; ++i )
    {
        fprintf( file , "%d %d %d %d %d\n" , game->Entities.Allies[i].Rect.x , game->Entities.Allies[i].Rect.y , game->Entities.Allies[i].Rect.w , game->Entities.Allies[i].Rect.h , game->Entities.Allies[i].Type );
    }

    fclose(file);
}

void readFromFile( const char* filename , Game* game )
{
    FILE* file = fopen( filename , "r" );

    fscanf( file , "%d %d %d %d %d" , &game->Player.Rect.x , &game->Player.Rect.y , &game->Player.Rect.w , &game->Player.Rect.h , &game->Player.Type );

    fscanf( file, "%d %d %d %d" , &game->Background.Camera.x , &game->Background.Camera.y , &game->Background.Camera.w , &game->Background.Camera.h );

    for ( int i = 0 ; i < Resolution::LevelWidth / constant::PIXEL_SIZE ; ++i )
    {
        for ( int j = 0 ; j < Resolution::LevelHeight / constant::PIXEL_SIZE ; ++j )
        {
            fscanf( file , "%d" , &game->Forest[i][j] );
        }
    }

    size_t numCamps;
    fscanf( file , "%zu" , &numCamps );
    game->CampCoordinates.resize( numCamps );
    for ( size_t i = 0 ; i < numCamps ; ++i )
    {
        fscanf( file , "%d %d" , &game->CampCoordinates[i].first , &game->CampCoordinates[i].second );
    }

    size_t numEnemies;
    fscanf( file , "%zu" , &numEnemies );
    game->Entities.Enemy.resize( numEnemies );
    for ( size_t i = 0 ; i < numEnemies ; ++i )
    {
        fscanf( file , "%d %d %d %d %d" , &game->Entities.Enemy[i].Rect.x , &game->Entities.Enemy[i].Rect.y , &game->Entities.Enemy[i].Rect.w , &game->Entities.Enemy[i].Rect.h , &game->Entities.Enemy[i].Type );
    }

    size_t numAllies;
    fscanf( file , "%zu" , &numAllies );
    game->Entities.Allies.resize( numAllies );
    for ( size_t i = 0 ; i < numAllies ; ++i )
    {
        fscanf( file , "%d %d %d %d %d" , &game->Entities.Allies[i].Rect.x , &game->Entities.Allies[i].Rect.y , &game->Entities.Allies[i].Rect.w , &game->Entities.Allies[i].Rect.h , &game->Entities.Allies[i].Type );
    }

    size_t numTrees;
    fscanf( file , "%zu" , &numTrees );
    game->Entities.Tree.resize( numTrees );
    for ( size_t i = 0 ; i < numTrees ; ++i )
    {
        fscanf( file , "%d %d %d %d %d" , &game->Entities.Tree[i].Rect.x , &game->Entities.Tree[i].Rect.y , &game->Entities.Tree[i].Rect.w , &game->Entities.Tree[i].Rect.h , &game->Entities.Tree[i].Type );
    }

    fclose(file);
}

void readFromReplayOnce( const char* filename , Game* game )
{
    static FILE* file = NULL;
    static bool eof = false;

    if ( file == NULL )
    {
        file = fopen( filename , "r" );
    }

    if ( eof )
    {
        fclose(file);
        file = NULL;
        eof = false;
        game->State = gameState::gameRunning;
        return;
    }

    size_t numAllies;

    if ( fscanf( file , "%zu" , &numAllies ) != 1 )
    {
        eof = true;
        fclose(file);
        file = NULL;
        return;
    }

    game->Entities.Allies.resize( numAllies );
    for ( size_t i = 0 ; i < numAllies ; ++i )
    {
        fscanf( file , "%d %d %d %d %d" , &game->Entities.Allies[i].Rect.x , &game->Entities.Allies[i].Rect.y , &game->Entities.Allies[i].Rect.w , &game->Entities.Allies[i].Rect.h , &game->Entities.Allies[i].Type );
    }

}
