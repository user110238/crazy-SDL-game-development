void fillvector( std::vector <std::vector <Tile>>& vector )
{

    for ( int x = 0 ; x < LevelWidth / constant::PIXEL_SIZE ; ++x )
        for (int y = 0; y < LevelHeight / constant::PIXEL_SIZE; ++y)
            if ( getRandomNumber( 0 , 10 ) )
                vector.at(x).at(y) = Tile::Green;
            else if ( getRandomNumber( 0 , 10 ) )
                vector.at(x).at(y) = Tile::Black;
            else
                vector.at(x).at(y) = Tile::Brown;
}

SDL_Texture* fillBackground( std::vector <std::vector <Tile>>& vector , SDL_Renderer* Renderer )
{

    SDL_Surface* Surface = SDL_CreateRGBSurface(0, vector.size() * constant::PIXEL_SIZE, vector[0].size() * constant::PIXEL_SIZE, 32, 0, 0, 0, 0);

    for (size_t x = 0; x < vector.size(); ++x) {
        for (size_t y = 0; y < vector[0].size(); ++y) {
                if ( vector.at(x).at(y) == Tile::Brown )
                {
                    SDL_Rect rect = { static_cast<int>(x) * constant::PIXEL_SIZE, static_cast<int>(y) * constant::PIXEL_SIZE, constant::PIXEL_SIZE, constant::PIXEL_SIZE };
                    SDL_FillRect(Surface, &rect, SDL_MapRGB(Surface->format, 79,58,43 ));
                }
                else if ( vector.at(x).at(y) == Tile::Green)
                {
                    SDL_Rect rect = { static_cast<int>(x) * constant::PIXEL_SIZE, static_cast<int>(y) * constant::PIXEL_SIZE, constant::PIXEL_SIZE, constant::PIXEL_SIZE };
                    SDL_FillRect(Surface, &rect, SDL_MapRGB(Surface->format, 53, 94, 59 ));
                }
                else if ( vector.at(x).at(y) == Tile::Black )
                {
                    SDL_Rect rect = { static_cast<int>(x) * constant::PIXEL_SIZE, static_cast<int>(y) * constant::PIXEL_SIZE, constant::PIXEL_SIZE, constant::PIXEL_SIZE };
                    SDL_FillRect(Surface, &rect, SDL_MapRGB(Surface->format, 0, 0, 0 ));

                }
        }
    }

    SDL_Texture* Texture = SDL_CreateTextureFromSurface( Renderer , Surface );
    SDL_FreeSurface( Surface );

    return Texture;

}

void updateForest( std::vector <std::vector <Tile>>& vector ,SDL_Rect Rect )
{
    int playerGridXStart = Rect.x / constant::PIXEL_SIZE;
    int playerGridXEnd = (Rect.x + Rect.w) / constant::PIXEL_SIZE;
    int playerGridYStart = Rect.y / constant::PIXEL_SIZE;
    int playerGridYEnd = (Rect.y + Rect.h) / constant::PIXEL_SIZE;

    for (int gridX = playerGridXStart; gridX <= playerGridXEnd; ++gridX)
    {
        for (int gridY = playerGridYStart; gridY <= playerGridYEnd; ++gridY)
        {
            if (gridX >= 0 && gridX < vector.size() && gridY >= 0 && gridY < vector[0].size())
            {
                if ( vector[gridX][gridY] == Tile::Brown || vector[gridX][gridY] == Tile::Black )
                    vector[gridX][gridY] = Tile::Green;
            }
        }
    }




}

