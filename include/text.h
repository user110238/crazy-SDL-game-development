struct text
{
    TTF_Font* Font;
    SDL_Texture* scoreText;
    SDL_Texture* treeCount;
};

void initText ( text& Text , std::string fontPath )
{
    Text.Font = TTF_OpenFont( fontPath.c_str() , 64 );

}


