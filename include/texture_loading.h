SDL_Texture* loadTexture( SDL_Renderer* Renderer , std::string path )
{
    SDL_Texture* Texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    Texture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

    return Texture;
}

SDL_Texture* loadTextureFromText( SDL_Renderer* renderer , std::string text , TTF_Font* font )
{
    SDL_Texture* texture = nullptr;

    SDL_Color textColor = {255, 255, 255};

    SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

    return texture;
}

void rendererAdd( SDL_Renderer* Renderer , SDL_Texture* Texture , SDL_Rect Dest )
{

    SDL_RenderCopy( Renderer, Texture , NULL , &Dest );

}

void rendererAdd( SDL_Renderer* Renderer , SDL_Texture* Texture , SDL_Rect Src , SDL_Rect Dest )
{

    SDL_RenderCopy( Renderer, Texture , &Src , &Dest );

}

void rendererAddFlip( SDL_Renderer* Renderer , SDL_Texture* Texture , SDL_Rect Dest , SDL_RendererFlip Flip )
{

    SDL_RenderCopyEx( Renderer , Texture , NULL , &Dest , 0 , NULL, Flip );

}
