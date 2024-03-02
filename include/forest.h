    // Types of tiles
#include <math.h>
enum class Tile
{
    Green,  // Active forest
    Red,    // Burning
    Brown,  // Burned forest

    Black,  // Testing, camp center right now
};

struct structFireSpread
{
    Uint32 lastFireSpreadTime;
    int fireSpreadInterval;
};

void fillvector( std::vector<std::vector<Tile>>& vector , int campCount )
{
    for (int i = 0 ; i < campCount ; ++i)
    {
        int startX = getRandomNumber(0, vector.size());
        int startY = getRandomNumber(0, vector.at(0).size());

        for (int x = startX; x < startX + 5; ++x)
        {
            for (int y = startY; y < startY + 5; ++y)
            {
                vector[x][y] = Tile::Black;
            }
        }
    }

    for ( int x = 0 ; x < vector.size() ; ++x )
    {
        for ( int y = 0 ; y < vector[0].size() ; ++y )
        {
            if ( vector[x][y] != Tile::Black )
                vector[x][y] = Tile::Green;
        }
    }
}

SDL_Texture* fillBackground( std::vector<std::vector<Tile>>& vector , SDL_Renderer* Renderer )
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
                case Tile::Red:
                    r = 255; g = getRandomNumber( 0 , 50 ); b = 25; // Shifting Red
                    break;
                case Tile::Black:
                    r = 0; g = 0; b = 0; // Black
                    break;
            }

            SDL_SetRenderDrawColor( Renderer, r, g, b, 255 );
            SDL_RenderFillRect( Renderer, &rect );
        }
    }
    SDL_SetRenderTarget( Renderer, nullptr );
    return Texture;
}

void updateBackgroundTexture( std::vector<std::vector<Tile>> vector , SDL_Texture* texture , SDL_Renderer* renderer , SDL_Rect camera ) {
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
                case Tile::Red:
                    r = 255; g = getRandomNumber(0, 50); b = 25; // Shifting Red
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
}


void updateForest( std::vector<std::vector<Tile>>& vector , SDL_Rect Rect , Tile tile , int clearRadius )
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

bool isTreeCompromised( const std::vector<std::vector<Tile>>& vector , SDL_Rect Rect )
{
    for (int x = std::max(0, Rect.x / constant::PIXEL_SIZE); x < std::min(static_cast<int>(vector.size()), (Rect.x + Rect.w) / constant::PIXEL_SIZE); ++x)
    {
        for (int y = std::max(0, Rect.y / constant::PIXEL_SIZE) ; y < std::min(static_cast<int>(vector[0].size()), (Rect.y + Rect.h) / constant::PIXEL_SIZE) ; ++y)
        {
            if ( vector[x][y] != Tile::Green )
                return true;
        }
    }
    return false;
}

void updateForestRandom( std::vector<std::vector<Tile>>& vector , SDL_Rect Rect , Tile tile , int clearRadius )
{
       // Center of the rectangle
    int centerX = Rect.x + Rect.w / 2;
    int centerY = Rect.y + Rect.h / 2;
    int extend = clearRadius;

    // Radius == smaller side
    clearRadius += std::min(Rect.w, Rect.h) / 2 - constant::HITBOX_REDUCTION;

    for ( int x = std::max(0, Rect.x - extend) ; x < std::min(static_cast<int>(vector.size() * constant::PIXEL_SIZE), Rect.x + Rect.w + extend) ; ++x )
    {
        for ( int y = std::max(0, Rect.y - extend) ; y < std::min(static_cast<int>(vector[0].size() * constant::PIXEL_SIZE), Rect.y + Rect.h + extend) ; ++y )
        {
            // Pitagorov
            int distanceX = x - centerX;
            int distanceY = y - centerY;
            double distance = std::sqrt(std::pow(distanceX, 2) + std::pow(distanceY, 2));
            // If current point is within the circle radius
            if ( distance <= clearRadius )
            {
                if ( x / constant::PIXEL_SIZE < vector.size() && y / constant::PIXEL_SIZE < vector[0].size() )
                {
                    if ( vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] == Tile::Green )
                        vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] = tile;
                }
            }
        }
    }
}


int calculatePercentage( const std::vector<std::vector<Tile>>& vector , Tile tile )
{
    int totalTiles = 0;
    int brownTiles = 0;

    for (int i = 0 ; i < vector.size() ; ++i)
    {
        for (int j = 0 ; j < vector[i].size() ; ++j)
        {
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
                if (x > 0 && (Forest[x - 1][y] == Tile::Red || Forest[x - 1][y] == Tile::Black || Forest[x - 1][y] == Tile::Brown))
                    redCount++;
                if (x < Forest.size() - 1 && (Forest[x + 1][y] == Tile::Red || Forest[x + 1][y] == Tile::Black || Forest[x + 1][y] == Tile::Brown))
                    redCount++;
                if (y > 0 && (Forest[x][y - 1] == Tile::Red || Forest[x][y - 1] == Tile::Black || Forest[x][y - 1] == Tile::Brown))
                    redCount++;
                if (y < Forest[0].size() - 1 && (Forest[x][y + 1] == Tile::Red || Forest[x][y + 1] == Tile::Black || Forest[x][y + 1] == Tile::Brown))
                    redCount++;

                if ( redCount < 4 )
                {
                    if (x > 0 && Forest[x - 1][y] == Tile::Green)
                        fireSpreadCoords.emplace_back(x - 1, y);
                    if (x < Forest.size() - 1 && Forest[x + 1][y] == Tile::Green)
                        fireSpreadCoords.emplace_back(x + 1, y);
                    if (y > 0 && Forest[x][y - 1] == Tile::Green)
                        fireSpreadCoords.emplace_back(x, y - 1);
                    if (y < Forest[0].size() - 1 && Forest[x][y + 1] == Tile::Green)
                        fireSpreadCoords.emplace_back(x, y + 1);
                }
                else
                {
                    burnedCoords.emplace_back(x, y);
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

