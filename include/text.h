struct structText
{
    TTF_Font* Font;

    SDL_Texture* scoreText;
    SDL_Texture* treeCount;
    SDL_Texture* victory;

    SDL_Texture* name;
    SDL_Texture* credits;
};

void initText ( structText& Text , SDL_Renderer* Renderer , std::string fontPath )
{
    Text.Font = TTF_OpenFont( fontPath.c_str() , 64 );
    Text.scoreText = loadTextureFromText( Renderer , "Score" , Text.Font );
    Text.victory = loadTextureFromText( Renderer , "Victory!" , Text.Font );

    Text.name = loadTextureFromText( Renderer , "Amazonka" , Text.Font );
    Text.credits = loadTextureFromText( Renderer , "By Microsoft" , Text.Font );
}


