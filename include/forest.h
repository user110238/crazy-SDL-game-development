    // Types of tiles
enum class Tile
{
    Green,  // Active forest
    Red,    // Burning
    Brown,  // Burned forest

    Blue,   // Water
    Sand,   // River Bank

    Black,  // Testing
};

struct structFireSpread
{
    Uint32 lastFireSpreadTime;
    int fireSpreadInterval;
};

void placeCamps( std::vector<std::vector<Tile>>& vector , int campCount , std::vector<std::pair< int , int >>& CampCoordinates )
{
    for (int i = 0 ; i < campCount ; ++i)
    {
        int X = getRandomNumber( 0 , vector.size() );
        int Y = getRandomNumber( 0 , vector[i].size() );

        CampCoordinates.push_back(std::make_pair( X , Y ));
    }
}

SDL_Texture* fillBackground( const std::vector<std::vector<Tile>>& vector , SDL_Renderer* Renderer )
{
        // Temporary texture to draw
    SDL_Texture* Texture = SDL_CreateTexture( Renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, vector.size() * constant::PIXEL_SIZE, vector[0].size() * constant::PIXEL_SIZE );

        // Set renderer to texture
    SDL_SetRenderTarget( Renderer, Texture );

        // Size of "pixel" or a tile
        // PIXEL_SIZE is 10, probably
    SDL_Rect rect = {0, 0, constant::PIXEL_SIZE, constant::PIXEL_SIZE};

    for ( int x = 0 ; x < vector.size() ; ++x )
    {
        for ( int y = 0 ; y < vector[0].size() ; ++y )
        {
            rect.x = x * constant::PIXEL_SIZE;
            rect.y = y * constant::PIXEL_SIZE;

            Uint8 r, g, b;
            switch ( vector[x][y] )
            {
                case Tile::Brown:
                    r = 79; g = 58; b = 43; // Brown
                    break;
                case Tile::Green:
                    r = 53; g = 94; b = 60; // Green
                    break;
                case Tile::Blue:
                    r = 0; g = 105; b = 148; // Blue
                    break;
                case Tile::Sand:
                    r = 125; g = 125; b = 0; // Sand grey-ish
                    break;
                case Tile::Red:
                    r = 247; g = 55; b = 24; // Red
                    break;
                case Tile::Black:
                    r = 0; g = 0; b = 0; // Black
                    break;
            }

            SDL_SetRenderDrawColor( Renderer , r , g , b , 255 );
            SDL_RenderFillRect( Renderer , &rect );
        }
    }
    SDL_SetRenderTarget( Renderer , nullptr );
    SDL_SetRenderDrawColor( Renderer , 0 , 0 , 0 , 0 );
    return Texture;
}

void updateBackgroundTexture( const std::vector<std::vector<Tile>>& vector , SDL_Texture* texture , SDL_Renderer* renderer , SDL_Rect camera ) {
    // Set renderer to texture
    SDL_SetRenderTarget( renderer, texture );

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Size of "pixel" or a tile
    // PIXEL_SIZE is 10, probably
    SDL_Rect rect = {0, 0, constant::PIXEL_SIZE, constant::PIXEL_SIZE};

    for ( int x = std::max(0, camera.x / constant::PIXEL_SIZE) ; x < std::min( static_cast<int>( vector.size() ) ,
        (camera.x + camera.w + constant::EXTRA_RENDER ) / constant::PIXEL_SIZE) ; ++x) {
        for ( int y = std::max(0, camera.y / constant::PIXEL_SIZE) ; y < std::min( static_cast<int>( vector[0].size() ) ,
            (camera.y + camera.h + constant::EXTRA_RENDER ) / constant::PIXEL_SIZE) ; ++y) {

            rect.x = x * constant::PIXEL_SIZE;
            rect.y = y * constant::PIXEL_SIZE;

            Uint8 r, g, b;
            switch ( vector[x][y] ) {
                case Tile::Brown:
                    r = 79; g = 58; b = 43; // Brown
                    break;
                case Tile::Green:
                    r = 53; g = 94; b = 60; // Green
                    break;
                case Tile::Blue:
                    r = 0; g = 105; b = 148; // Blue
                    break;
                case Tile::Sand:
                    r = 225; g = 167; b = 80;  // Sand grey-ish
                    break;
                case Tile::Red:
                    r = 247; g = 55; b = 24; // Red
                    break;
                case Tile::Black:
                    r = 0; g = 0; b = 0; // Black
                    break;
            }

            SDL_SetRenderDrawColor( renderer , r , g , b , 255 );
            SDL_RenderFillRect( renderer , &rect );
        }
    }
    SDL_SetRenderTarget( renderer, nullptr );
    SDL_SetRenderDrawColor( renderer , 0 , 0 , 0 , 0 );
}


void updateForest( std::vector<std::vector<Tile>>& vector , const SDL_Rect& Rect , Tile tile , int clearRadius )
{
    int centerX = Rect.x + Rect.w / 2;
    int centerY = Rect.y + Rect.h / 2;
    int extend = clearRadius;

    clearRadius += std::min(Rect.w, Rect.h) / 2 - constant::HITBOX_REDUCTION;
    clearRadius = clearRadius * clearRadius;

    for (int x = std::max(0, Rect.x - extend) ; x < std::min(static_cast<int>(vector.size() * constant::PIXEL_SIZE), Rect.x + Rect.w + extend) ; ++x)
    {
        int DX = x - centerX;
        int squaredDX = DX * DX;

        for (int y = std::max(0, Rect.y - extend) ; y < std::min(static_cast<int>(vector[0].size() * constant::PIXEL_SIZE), Rect.y + Rect.h + extend) ; ++y)
        {
            int DY = y - centerY;
            int distance_squared = squaredDX + DY * DY;

            if ( distance_squared <= clearRadius && x / constant::PIXEL_SIZE < vector.size() && y / constant::PIXEL_SIZE < vector[0].size() )
            {
                if ( vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] == Tile::Green || vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] == Tile::Red )
                    vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] = tile;
            }
        }
    }
}

void updateForest( std::vector<std::vector<Tile>>& vector , SDL_Rect Rect , Tile target , Tile tile , int clearRadius )
{
    int centerX = Rect.x + Rect.w / 2;
    int centerY = Rect.y + Rect.h / 2;
    int extend = clearRadius;

    clearRadius += std::min(Rect.w, Rect.h) / 2 - constant::HITBOX_REDUCTION;
    clearRadius = clearRadius * clearRadius;

    for (int x = std::max(0, Rect.x - extend) ; x < std::min(static_cast<int>(vector.size() * constant::PIXEL_SIZE) , Rect.x + Rect.w + extend) ; ++x)
    {
        int DX = x - centerX;
        int squaredDX = DX * DX;

        for (int y = std::max(0, Rect.y - extend) ; y < std::min(static_cast<int>(vector[0].size() * constant::PIXEL_SIZE), Rect.y + Rect.h + extend) ; ++y)
        {
            int DY = y - centerY;
            int distance_squared = squaredDX + DY * DY;

            if ( distance_squared <= clearRadius && x / constant::PIXEL_SIZE < vector.size() && y / constant::PIXEL_SIZE < vector[0].size() )
            {
                if ( vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] == target )
                    vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] = tile;
            }
        }
    }
}

bool isNotOnTile( const std::vector<std::vector<Tile>>& vector , SDL_Rect Rect , Tile tile )
{
    for (int x = std::max(0, Rect.x / constant::PIXEL_SIZE); x < std::min(static_cast<int>(vector.size()), (Rect.x + Rect.w) / constant::PIXEL_SIZE); ++x)
    {
        for (int y = std::max(0, Rect.y / constant::PIXEL_SIZE) ; y < std::min(static_cast<int>(vector[0].size()), (Rect.y + Rect.h) / constant::PIXEL_SIZE) ; ++y)
        {
            if ( vector[x][y] != tile )
                return true;
        }
    }
    return false;
}

bool isOnTile( const std::vector<std::vector<Tile>>& vector , SDL_Rect Rect , Tile tile )
{
    for (int x = std::max(0, Rect.x / constant::PIXEL_SIZE); x < std::min(static_cast<int>(vector.size()), (Rect.x + Rect.w) / constant::PIXEL_SIZE); ++x)
    {
        for (int y = std::max(0, Rect.y / constant::PIXEL_SIZE) ; y < std::min(static_cast<int>(vector[0].size()), (Rect.y + Rect.h) / constant::PIXEL_SIZE) ; ++y)
        {
            if ( vector[x][y] == tile )
                return true;
        }
    }
    return false;
}

int calculatePercentage( const std::vector<std::vector<Tile>>& vector , Tile tile )
{
    int totalTiles = 0;
    int brownTiles = 0;

    for (int i = 0 ; i < vector.size() ; ++i)
    {
        for (int j = 0 ; j < vector[i].size() ; ++j)
        {
            if ( vector[i][j] != Tile::Blue || vector[i][j] != Tile::Sand )
                ++totalTiles;
            if ( vector[i][j] == tile )
                ++brownTiles;
        }
    }

    return static_cast<int>((static_cast<double>(brownTiles) / totalTiles) * 100.0);

}

void spreadFire( std::vector<std::vector<Tile>>& Forest )
{
    std::vector<std::pair<int, int>> fireSpreadCoords;
    std::vector<std::pair<int, int>> burnedCoords;

    for ( int x = 0 ; x < Forest.size() ; ++x )
    {
        for ( int y = 0 ; y < Forest[0].size() ; ++y )
        {
            if ( Forest[x][y] == Tile::Red )
            {
                int redCount = 0;
                if ( x > 0 && Forest[x - 1][y] != Tile::Green )
                    redCount++;
                if ( x < Forest.size() - 1 && Forest[x + 1][y] != Tile::Green )
                    redCount++;
                if ( y > 0 && Forest[x][y - 1] != Tile::Green )
                    redCount++;
                if ( y < Forest[0].size() - 1 && Forest[x][y + 1] != Tile::Green )
                    redCount++;

                if ( redCount < 4 )
                {
                    if ( x > 0 && Forest[x - 1][y] == Tile::Green )
                        fireSpreadCoords.push_back( {x - 1, y} );
                    if ( x < Forest.size() - 1 && Forest[x + 1][y] == Tile::Green )
                        fireSpreadCoords.push_back( {x + 1, y} );
                    if ( y > 0 && Forest[x][y - 1] == Tile::Green )
                        fireSpreadCoords.push_back( {x, y - 1} );
                    if ( y < Forest[0].size() - 1 && Forest[x][y + 1] == Tile::Green )
                        fireSpreadCoords.push_back( {x, y + 1} );
                }
                else
                {
                    burnedCoords.push_back( {x, y} );
                }
            }
        }
    }

    for ( std::vector<std::pair<int, int>>::iterator IT = fireSpreadCoords.begin() ; IT < fireSpreadCoords.end() ; IT++ )
    {
        int x = IT->first;
        int y = IT->second;

        if ( ( x >= 0 && x < Forest.size() ) && ( y >= 0 && y < Forest[0].size() ) )
        {
            if ( x == 0 || x == Forest.size() - 1 || y == 0 || y == Forest[0].size() - 1 )
                Forest[x][y] = Tile::Brown;
            else
                Forest[x][y] = Tile::Red;
        }
    }

    for ( std::vector<std::pair<int, int>>::iterator IT = burnedCoords.begin() ; IT < burnedCoords.end() ; IT++ )
    {
        int x = IT->first;
        int y = IT->second;

        if ( ( x >= 0 && x < Forest.size() ) && ( y >= 0 && y < Forest[0].size() ) )
            Forest[x][y] = Tile::Brown;
    }
}

std::pair<int, int> findNearestRedTile( const SDL_Rect& allyRect , const std::vector<std::vector<Tile>>& Forest )
{
    std::pair<int, int> nearestRedTile;

    nearestRedTile.first = std::numeric_limits<int>::max();
    nearestRedTile.second = std::numeric_limits<int>::max();

    float minDistance = std::numeric_limits<float>::max();

    for (int x = 0 ; x < Forest.size() ; ++x)
    {
        for (int y = 0 ; y < Forest[0].size() ; ++y)
        {
            if ( Forest[x][y] == Tile::Red )
            {
                float currentDistance = distance( allyRect.x + allyRect.w / 2 , allyRect.y + allyRect.h / 2, x * constant::PIXEL_SIZE, y * constant::PIXEL_SIZE );
                if ( currentDistance <= minDistance )
                {
                    minDistance = currentDistance;
                    nearestRedTile = {x * constant::PIXEL_SIZE , y * constant::PIXEL_SIZE };
                }
            }
        }
    }

    return nearestRedTile;
}

