void render ( SDL_Renderer* Renderer , back Background , Player Player , std::vector<struct Entity> Enemy , std::vector<struct Entity> Tree , text Text )
{
            // Clear current frame
        SDL_RenderClear( Renderer );
            // render background ( level )
        rendererAdd( Renderer , Background.Texture ,  Background.backgroundRect );

            // Render player with camera offset
        SDL_Rect playerRect = {Player.Rect.x - Background.Camera.x, Player.Rect.y - Background.Camera.y, Player.Rect.w, Player.Rect.h};
        rendererAdd( Renderer, Player.Texture, playerRect );

            // render enemies with camera offset
        for ( int i = 0 ; i < Enemy.size() ; i++ )
                rendererAdd( Renderer, Enemy.at(i).Texture, {Enemy.at(i).Rect.x - Background.Camera.x, Enemy.at(i).Rect.y - Background.Camera.y, Enemy.at(i).Rect.w, Enemy.at(i).Rect.h} );
        for ( int i = 0 ; i < Tree.size() ; i++ )
                rendererAdd( Renderer, Tree.at(i).Texture, {Tree.at(i).Rect.x - Background.Camera.x, Tree.at(i).Rect.y - Background.Camera.y, Tree.at(i).Rect.w, Tree.at(i).Rect.h} );

        rendererAdd( Renderer , Text.scoreText , { Background.Camera.w / 2 - 150 / 2 , 0 , 150 , 100 } );
        rendererAdd( Renderer , Text.treeCount , { Background.Camera.w / 2 - 150 / 2 , 100 , 150 , 100 } );

            // Draw Frame
        SDL_RenderPresent( Renderer );

}
