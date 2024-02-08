void render ( SDL_Renderer* Renderer , back Background , Player Player , std::vector<struct Entity> Enemy )
{
            // Clear current frame
        SDL_RenderClear( Renderer );
            // render background ( level )
        rendererAdd( Renderer , Background.Texture , Background.backgroundRect );

            // Render player with camera offset
        SDL_Rect playerRect = {Player.Rect.x - Background.Camera.x, Player.Rect.y - Background.Camera.y, Player.Rect.w, Player.Rect.h};
        rendererAdd( Renderer, Player.Texture, playerRect );

            // render enemies + camera offset
        for ( int i = 0 ; i < Enemy.size() ; i++ )
                rendererAdd( Renderer, Enemy.at(i).Texture, {Enemy.at(i).Rect.x - Background.Camera.x, Enemy.at(i).Rect.y - Background.Camera.y, Enemy.at(i).Rect.w, Enemy.at(i).Rect.h} );

            // Draw Frame
        SDL_RenderPresent( Renderer );

}
