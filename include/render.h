namespace Textures
{
    SDL_Texture* Player;

    SDL_Texture* Enemy;
    SDL_Texture* Tree;
    SDL_Texture* Ally;
};

void render ( SDL_Renderer* Renderer , back Background , Player Player , std::vector<struct Entity> Enemy , std::vector<struct Entity> Tree , std::vector<struct Entity> Allies , text Text )
{
            // Clear current frame
        SDL_RenderClear( Renderer );
            // render background ( level )
        rendererAdd( Renderer , Background.Texture ,  Background.backgroundRect );

            // Render player with camera offset
        SDL_Rect playerRect = {Player.Rect.x - Background.Camera.x, Player.Rect.y - Background.Camera.y, Player.Rect.w, Player.Rect.h};
        rendererAdd( Renderer, Textures::Player, playerRect );

            // render enemies with camera offset
        for ( int i = 0 ; i < Enemy.size() ; i++ )
            if ( distance( Player.Rect.x , Player.Rect.y , Enemy.at(i).Rect.x ,  Enemy.at(i).Rect.y) <= std::max( Background.Camera.w , Background.Camera.h ) )
                if ( Enemy[i].Type == EntityType::Enemy )
                    rendererAdd( Renderer, Textures::Enemy, {Enemy.at(i).Rect.x - Background.Camera.x, Enemy.at(i).Rect.y - Background.Camera.y, Enemy.at(i).Rect.w, Enemy.at(i).Rect.h} );
        for ( int i = 0 ; i < Allies.size() ; i++ )
            if ( distance( Player.Rect.x , Player.Rect.y , Allies.at(i).Rect.x ,  Allies.at(i).Rect.y) <= std::max( Background.Camera.w , Background.Camera.h ) )
                if ( Allies[i].Type == EntityType::Ally )
                rendererAdd( Renderer, Textures::Ally, {Allies.at(i).Rect.x - Background.Camera.x, Allies.at(i).Rect.y - Background.Camera.y, Allies.at(i).Rect.w, Allies.at(i).Rect.h} );
        for ( int i = 0 ; i < Tree.size() ; i++ )
            if ( distance( Player.Rect.x , Player.Rect.y , Tree.at(i).Rect.x ,  Tree.at(i).Rect.y) <= std::max( Background.Camera.w , Background.Camera.h ) )
                if ( Tree[i].Type == EntityType::Tree )
                rendererAdd( Renderer, Textures::Tree, {Tree.at(i).Rect.x - Background.Camera.x, Tree.at(i).Rect.y - Background.Camera.y, Tree.at(i).Rect.w, Tree.at(i).Rect.h} );


        rendererAdd( Renderer , Text.scoreText , { Background.Camera.w / 2 - 150 / 2 , 0 , 150 , 100 } );
        rendererAdd( Renderer , Text.treeCount , { Background.Camera.w / 2 - 150 / 2 , 100 , 150 , 100 } );

            // Draw Frame
        SDL_RenderPresent( Renderer );

}
