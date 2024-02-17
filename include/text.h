struct text
{
    TTF_Font* Font;
    SDL_Texture* scoreText;
    SDL_Texture* treeCount;

    text( SDL_Renderer* , std::string , std::string , int );
};

text::text( SDL_Renderer* Renderer , std::string fontPath , std::string pscoreText , int ptreeCount )
{
    Font = TTF_OpenFont( fontPath.c_str() , 64 );

    scoreText = loadTextureFromText( Renderer , pscoreText.c_str() , Font );

    treeCount = loadTextureFromText( Renderer , std::to_string(ptreeCount).c_str() , Font );

}
