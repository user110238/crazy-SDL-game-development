struct structText
{
    TTF_Font* Font;
    SDL_Texture* scoreText;
    SDL_Texture* treeCount;
};

void initText ( structText& Text , SDL_Renderer* Renderer , std::string fontPath )
{
    Text.Font = TTF_OpenFont( fontPath.c_str() , 64 );
    Text.scoreText = loadTextureFromText( Renderer , "Score" , Text.Font );

}


