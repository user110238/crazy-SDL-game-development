struct structText
{
    TTF_Font* Font;

        // Game
    SDL_Texture* areaBurnt;
    SDL_Texture* treeCount;

    SDL_Texture* victory;
    SDL_Texture* defeat;

    SDL_Texture* liveReplay;
        // Pause screen
    SDL_Texture* pause;
    SDL_Texture* resume;
    SDL_Texture* replay;
    SDL_Texture* mainMenu;
        // Main menu
    SDL_Texture* name;

    SDL_Texture* play;

    SDL_Texture* save;
    SDL_Texture* saved;
    SDL_Texture* load;
    SDL_Texture* loaded;

    SDL_Texture* quit;

    SDL_Texture* SessionName;
};

void initText ( structText& Text , SDL_Renderer* Renderer , std::string fontPath )
{
    Text.Font = TTF_OpenFont( fontPath.c_str() , 64 );
    Text.areaBurnt = loadTextureFromText( Renderer , "Area Burnt" , Text.Font );

    Text.victory = loadTextureFromText( Renderer , "Victory!" , Text.Font );
    Text.defeat = loadTextureFromText( Renderer , "Defeat!" , Text.Font );

    Text.liveReplay = loadTextureFromText( Renderer , "Live Replay" , Text.Font );

    Text.pause = loadTextureFromText( Renderer , "Pause" , Text.Font );
    Text.resume = loadTextureFromText( Renderer , "Resume" , Text.Font );
    Text.replay = loadTextureFromText( Renderer , "Replay" , Text.Font );
    Text.mainMenu = loadTextureFromText( Renderer , "Main Menu" , Text.Font );

    Text.name = loadTextureFromText( Renderer , "Amazonka" , Text.Font );
    Text.play = loadTextureFromText( Renderer , "play" , Text.Font );
    Text.quit = loadTextureFromText( Renderer , "quit" , Text.Font );

    Text.save = loadTextureFromText( Renderer , "save" , Text.Font );
    Text.saved = loadTextureFromText( Renderer , "saved" , Text.Font );
    Text.load = loadTextureFromText( Renderer , "load" , Text.Font );
    Text.loaded = loadTextureFromText( Renderer , "loaded" , Text.Font );
}


