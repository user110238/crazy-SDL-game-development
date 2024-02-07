void fillvector( std::vector <std::vector <bool>>& Vector )
{

    for ( int x = 0 ; x < LevelWidth / constant::PIXEL_SIZE ; ++x )
        for (int y = 0; y < LevelHeight / constant::PIXEL_SIZE; ++y)
            if ( getRandomNumber( 0 , 10 ) )
                Vector.at(x).at(y) = 1;

}

SDL_Texture* fillBackground( std::vector <std::vector <bool>>& Vector , SDL_Renderer* Renderer )
{

    SDL_Surface* Surface = SDL_CreateRGBSurface(0, LevelWidth, LevelHeight, 32, 0, 0, 0, 0);

    for (int x = 0; x < LevelWidth / constant::PIXEL_SIZE; ++x) {
        for (int y = 0; y < LevelHeight / constant::PIXEL_SIZE; ++y) {
                if ( Vector.at(x).at(y) )
                {
                    SDL_Rect rect = { x * constant::PIXEL_SIZE, y * constant::PIXEL_SIZE, constant::PIXEL_SIZE, constant::PIXEL_SIZE };
                    SDL_FillRect(Surface, &rect, SDL_MapRGB(Surface->format, 34 , 139 , 34 ));
                }
                else
                {
                    SDL_Rect rect = { x * constant::PIXEL_SIZE, y * constant::PIXEL_SIZE, constant::PIXEL_SIZE, constant::PIXEL_SIZE };
                    SDL_FillRect(Surface, &rect, SDL_MapRGB(Surface->format, 138, 154, 91 ));
                }
        }
    }

    SDL_Texture* Texture = SDL_CreateTextureFromSurface( Renderer , Surface );
    SDL_FreeSurface( Surface );
    return Texture;

}
