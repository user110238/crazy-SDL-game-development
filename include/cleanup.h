void cleanUp( Game& Game )
{
    for ( int i = 0 ; i < Game.Forest.size() ; ++ i )
      Game.Forest[i].clear();
    Game.Forest.clear();
    Game.Entities.Enemy.clear();
    Game.Entities.Tree.clear();
    Game.Entities.Allies.clear();

    SDL_DestroyTexture( Textures::Player );
    SDL_DestroyTexture( Textures::Enemy );
    SDL_DestroyTexture( Textures::FireEnemy );
    SDL_DestroyTexture( Textures::Tree );
    SDL_DestroyTexture( Textures::Ally );

    SDL_DestroyTexture( Game.Text.scoreText );
    SDL_DestroyTexture( Game.Text.treeCount );
    SDL_DestroyTexture( Game.Text.victory );
    SDL_DestroyTexture( Game.Text.pause );
    SDL_DestroyTexture( Game.Text.name );
    SDL_DestroyTexture( Game.Text.credits );

    TTF_CloseFont( Game.Text.Font );
    Game.Text.Font = nullptr;

    Textures::Player = nullptr;
    Textures::Enemy = nullptr;
    Textures::FireEnemy = nullptr;
    Textures::Tree = nullptr;
    Textures::Ally = nullptr;

    Game.Text.scoreText = nullptr;
    Game.Text.treeCount = nullptr;
    Game.Text.victory = nullptr;
    Game.Text.pause = nullptr;
    Game.Text.name = nullptr;
    Game.Text.credits = nullptr;

    SDL_DestroyRenderer( Game.Window.Renderer );
    SDL_DestroyWindow( Game.Window.Window );
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
