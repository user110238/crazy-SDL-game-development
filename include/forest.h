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
        for (int y = 0; y < vector.at(0).size(); ++y)
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

    for (size_t x = 0; x < vector.size(); ++x)
    {
        for (size_t y = 0; y < vector[0].size(); ++y)
        {
            rect.x = x * constant::PIXEL_SIZE;
            rect.y = y * constant::PIXEL_SIZE;

            Uint8 r, g, b;
            switch (vector[x][y])
            {
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

void updateBackgroundTexture(std::vector<std::vector<Tile>> vector, SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect camera) {
        // Set renderer to texture
    SDL_SetRenderTarget(renderer, texture);

        // Size of "pixel" or a tile
        // PIXEL_SIZE is 10, probably
    SDL_Rect rect = {0, 0, constant::PIXEL_SIZE, constant::PIXEL_SIZE};

    for (int x = camera.x/constant::PIXEL_SIZE; x < (camera.x + camera.w)/constant::PIXEL_SIZE; ++x)
    {
        for (int y = camera.y/constant::PIXEL_SIZE; y < (camera.y + camera.h)/constant::PIXEL_SIZE; ++y)
        {
            rect.x = x * constant::PIXEL_SIZE;
            rect.y = y * constant::PIXEL_SIZE;

            Uint8 r, g, b;
            switch (vector[x][y])
            {
                case Tile::Brown:
                    r = 79; g = 58; b = 43; // Brown
                    break;
                case Tile::Green:
                    r = 53; g = 94; b = 59; // Green
                    break;
                case Tile::Black:
                    r = 0; g = 0; b = 0; // Black
                    break;
                default:
                    r = 255; g = 255; b = 255; // Default to white
                    break;
            }

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);
}

void updateForest(std::vector<std::vector<Tile>>& vector, SDL_Rect Rect, Tile tile, int clearRadius)
{
    // Center of the rectangle
    int centerX = Rect.x + Rect.w / 2;
    int centerY = Rect.y + Rect.h / 2;
    int extend = clearRadius;

    // Radius == smaller side
    clearRadius += std::min(Rect.w, Rect.h) / 2 - constant::HITBOX_REDUCTION;

    for (int x = std::max(0, Rect.x - extend); x < std::min(static_cast<int>(vector.size() * constant::PIXEL_SIZE), Rect.x + Rect.w + extend); ++x)
    {
        for (int y = std::max(0, Rect.y - extend); y < std::min(static_cast<int>(vector[0].size() * constant::PIXEL_SIZE), Rect.y + Rect.h + extend); ++y)
        {
            // Pitagorov
            int distanceX = x - centerX;
            int distanceY = y - centerY;
            double distance = std::sqrt(std::pow(distanceX, 2) + std::pow(distanceY, 2));
            // If current point is within the circle radius
            if (distance <= clearRadius)
            {
                if (x / constant::PIXEL_SIZE < vector.size() && y / constant::PIXEL_SIZE < vector[0].size())
                {
                    if (vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] != tile)
                        vector[x / constant::PIXEL_SIZE][y / constant::PIXEL_SIZE] = tile;
                }
            }
        }
    }
}

int calculatePercentage(const std::vector<std::vector<Tile>>& vector , Tile tile )
{
    int totalTiles = 0;
    int brownTiles = 0;

    for (int i = 0; i < vector.size(); ++i)
    {
        for (int j = 0; j < vector[i].size(); ++j)
        {
            ++totalTiles;
            if ( vector[i][j] == tile )
                ++brownTiles;
        }
    }

    return static_cast<int>((static_cast<double>(brownTiles) / totalTiles) * 100.0);

}


