struct structText
{
    TTF_Font* Font;

        // Game
    SDL_Texture* scoreText;
    SDL_Texture* treeCount;
    SDL_Texture* victory;
        // Pause screen
    SDL_Texture* pause;
    SDL_Texture* resume;
    SDL_Texture* mainMenu;
        // Main menu
    SDL_Texture* name;
    SDL_Texture* play;
    SDL_Texture* save;
    SDL_Texture* quit;
    SDL_Texture* credits;
};

void initText ( structText& Text , SDL_Renderer* Renderer , std::string fontPath )
{
    Text.Font = TTF_OpenFont( fontPath.c_str() , 64 );
    Text.scoreText = loadTextureFromText( Renderer , "Score" , Text.Font );
    Text.victory = loadTextureFromText( Renderer , "Victory!" , Text.Font );

    Text.pause = loadTextureFromText( Renderer , "Pause" , Text.Font );
    Text.resume = loadTextureFromText( Renderer , "Resume" , Text.Font );
    Text.mainMenu = loadTextureFromText( Renderer , "Main Menu" , Text.Font );

    Text.name = loadTextureFromText( Renderer , "Amazonka" , Text.Font );
    Text.play = loadTextureFromText( Renderer , "play" , Text.Font );
    Text.quit = loadTextureFromText( Renderer , "quit" , Text.Font );
    Text.save = loadTextureFromText( Renderer , "save" , Text.Font );
    Text.credits = loadTextureFromText( Renderer , "By Microsoft" , Text.Font );
}


