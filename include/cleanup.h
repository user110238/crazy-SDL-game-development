void cleanUpGame( Game& Game )
{
    Game.Forest.clear();
    Game.Entities.Enemy.clear();
    Game.Entities.Tree.clear();
    Game.Entities.Allies.clear();
}

void cleanUp( Game& Game )
{
    Game.Forest.clear();
    Game.Entities.Enemy.clear();
    Game.Entities.Tree.clear();
    Game.Entities.Allies.clear();

    SDL_DestroyTexture( Textures::Player );
    SDL_DestroyTexture( Textures::Enemy );
    SDL_DestroyTexture( Textures::FireEnemy );
    SDL_DestroyTexture( Textures::Tree1 );
    SDL_DestroyTexture( Textures::Tree2 );
    SDL_DestroyTexture( Textures::Tree3 );
    SDL_DestroyTexture( Textures::Ally );

    TTF_CloseFont( Game.Text.Font );
    Game.Text.Font = nullptr;

    Textures::Player = nullptr;
    Textures::Enemy = nullptr;
    Textures::FireEnemy = nullptr;
    Textures::Tree1 = nullptr;
    Textures::Tree2 = nullptr;
    Textures::Tree3 = nullptr;
    Textures::Ally = nullptr;

    SDL_DestroyRenderer( Game.Window.Renderer );
    SDL_DestroyWindow( Game.Window.Window );
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
