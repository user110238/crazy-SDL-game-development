    // Types of tiles
enum class Tile
{
    Green,  // Active forest
    Brown,  // Burned forest

    Black,  // idk
};

void fillvector( std::vector <std::vector <Tile>>& vector )
{
        // Goes throught the vector and gives it *random* values
    for ( int x = 0 ; x < vector.size() ; ++x )
        for (int y = 0; y < vector[0].size(); ++y)
            if ( getRandomNumber( 0 , 10 ) ) // 90 will be green
                vector[x][y] = Tile::Green;
            else if ( getRandomNumber( 0 , 1 ) )
                vector[x][y] = Tile::Brown;
            else
                vector[x][y] = Tile::Black;
}

SDL_Texture* fillBackground(std::vector<std::vector<Tile>>& vector, SDL_Renderer* Renderer) {
        // Temporary texture to draw
    SDL_Texture* Texture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, vector.size() * constant::PIXEL_SIZE, vector[0].size() * constant::PIXEL_SIZE);

        // Set renderer to texture
    SDL_SetRenderTarget(Renderer, Texture);

        // Size of "pixel" or a tile
        // PIXEL_SIZE is 10, probably
    SDL_Rect rect = {0, 0, constant::PIXEL_SIZE, constant::PIXEL_SIZE};

    for (size_t x = 0; x < vector.size(); ++x) {
        for (size_t y = 0; y < vector[0].size(); ++y) {
            rect.x = x * constant::PIXEL_SIZE;
            rect.y = y * constant::PIXEL_SIZE;

            Uint8 r, g, b;
            switch (vector[x][y]) {
                case Tile::Brown:
                    r = 79; g = 58; b = 43; // Brown
                    break;
                case Tile::Green:
                    r = 53; g = 94; b = 59; // Green
                    break;
                case Tile::Black:
                    r = 0; g = 0; b = 0; // Black
                    break;
            }
            SDL_SetRenderDrawColor(Renderer, r, g, b, 255);
            SDL_RenderFillRect(Renderer, &rect);
        }
    }
    SDL_SetRenderTarget(Renderer, nullptr);

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

