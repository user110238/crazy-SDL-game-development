    // Types of tiles
enum class Tile
{
    Green,
    Brown,
    Black,
};

void fillvector( std::vector <std::vector <Tile>>& vector )
{
        // Goes throught the vector and gives it *random* values
    for ( int x = 0 ; x < vector.size() ; ++x )
        for (int y = 0; y < vector[0].size(); ++y)
            if ( getRandomNumber( 0 , 10 ) )
                vector[x][y] = Tile::Green;
            else if ( getRandomNumber( 0 , 10 ) )
                vector[x][y] = Tile::Black;
            else
                vector[x][y] = Tile::Brown;
}

SDL_Texture* fillBackground(std::vector<std::vector<Tile>>& vector, SDL_Renderer* Renderer)
{
        // Temp surface
    SDL_Surface* Surface = SDL_CreateRGBSurfaceWithFormat(0, vector.size() * constant::PIXEL_SIZE, vector[0].size() * constant::PIXEL_SIZE, 24, SDL_PIXELFORMAT_RGB888);
        // Size of a tile
    SDL_Rect rect = {0, 0, constant::PIXEL_SIZE, constant::PIXEL_SIZE};

    for (int x = 0; x < vector.size(); ++x) {
        for (int y = 0; y < vector[0].size(); ++y) {

            rect.x = x * constant::PIXEL_SIZE;
            rect.y = y * constant::PIXEL_SIZE;

            Uint32 color;
            if (vector[x][y] == Tile::Brown)
                color = SDL_MapRGB(Surface->format, 79, 58, 43); // Brown
            else if (vector[x][y] == Tile::Green)
                color = SDL_MapRGB(Surface->format, 53, 94, 59); // Green
            else if (vector[x][y] == Tile::Black)
                color = SDL_MapRGB(Surface->format, 0, 0, 0); // Black

            SDL_FillRect(Surface, &rect, color);
        }
    }

    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
    SDL_FreeSurface(Surface);
    return Texture;
}

void updateForest( std::vector <std::vector <Tile>>& vector ,SDL_Rect Rect )
{
        // Segment the player into grid of smaller
        // points that are 10x10 pixels
    int GridXStart = Rect.x / constant::PIXEL_SIZE;
    int GridXEnd = (Rect.x + Rect.w) / constant::PIXEL_SIZE;
    int GridYStart = Rect.y / constant::PIXEL_SIZE;
    int GridYEnd = (Rect.y + Rect.h) / constant::PIXEL_SIZE;

    for (int gridX = GridXStart; gridX <= GridXEnd; ++gridX)
    {
        for (int gridY = GridYStart; gridY <= GridYEnd; ++gridY)
        {
            if (gridX >= 0 && gridX < vector.size() && gridY >= 0 && gridY < vector[0].size())
            {
                if ( vector[gridX][gridY] == Tile::Brown || vector[gridX][gridY] == Tile::Black )
                    vector[gridX][gridY] = Tile::Green;
            }
        }
    }
}

