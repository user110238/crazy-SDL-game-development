void renderGame ( Game Game )
{
            // Clear current frame
        SDL_RenderClear( Game.Window.Renderer );
            // render background ( level )
        rendererAdd( Game.Window.Renderer , Game.Background.Texture , {
            Game.Background.backgroundRect.x ,
            Game.Background.backgroundRect.y ,
            Game.Background.backgroundRect.w ,
            Game.Background.backgroundRect.h  } );

            // Render player with camera offset
        SDL_Rect playerRect =
        { Game.Player.Rect.x - Game.Background.Camera.x,
          Game.Player.Rect.y - Game.Background.Camera.y,
          Game.Player.Rect.w,
          Game.Player.Rect.h };

        rendererAdd( Game.Window.Renderer, Textures::Player, playerRect );

            // render enemies with camera offset
        for ( int i = 0 ; i < Game.Entities.Enemy.size() ; i++ )

            if ( distance( Game.Entities.Allies[Game.controllable].Rect.x , Game.Entities.Allies[Game.controllable].Rect.y ,
                Game.Entities.Enemy.at(i).Rect.x ,  Game.Entities.Enemy.at(i).Rect.y)
                <= std::max( Game.Background.Camera.w , Game.Background.Camera.h ) )

                if ( Game.Entities.Enemy[i].Type == EntityType::Enemy )
                    rendererAdd( Game.Window.Renderer, Textures::Enemy, {
                        Game.Entities.Enemy.at(i).Rect.x - Game.Background.Camera.x,
                        Game.Entities.Enemy.at(i).Rect.y - Game.Background.Camera.y,
                        Game.Entities.Enemy.at(i).Rect.w,
                        Game.Entities.Enemy.at(i).Rect.h} );
                else if ( Game.Entities.Enemy[i].Type == EntityType::FireEnemy )
                    rendererAdd( Game.Window.Renderer, Textures::FireEnemy, {
                        Game.Entities.Enemy.at(i).Rect.x - Game.Background.Camera.x,
                        Game.Entities.Enemy.at(i).Rect.y - Game.Background.Camera.y,
                        Game.Entities.Enemy.at(i).Rect.w,
                        Game.Entities.Enemy.at(i).Rect.h} );

        for ( int i = 0 ; i < Game.Entities.Allies.size() ; i++ )

            if ( distance( Game.Entities.Allies[Game.controllable].Rect.x , Game.Entities.Allies[Game.controllable].Rect.y ,
                Game.Entities.Allies.at(i).Rect.x ,  Game.Entities.Allies.at(i).Rect.y)
                <= std::max( Game.Background.Camera.w , Game.Background.Camera.h ) )

                if ( Game.Entities.Allies[i].Type == EntityType::Ally )
                rendererAdd( Game.Window.Renderer, Textures::Ally, {
                    Game.Entities.Allies.at(i).Rect.x - Game.Background.Camera.x,
                             Game.Entities.Allies.at(i).Rect.y - Game.Background.Camera.y,
                             Game.Entities.Allies.at(i).Rect.w,
                             Game.Entities.Allies.at(i).Rect.h } );

        for ( int i = 0 ; i < Game.Entities.Tree.size() ; i++ )

            if ( distance( Game.Entities.Allies[Game.controllable].Rect.x , Game.Entities.Allies[Game.controllable].Rect.y ,
                Game.Entities.Tree.at(i).Rect.x ,  Game.Entities.Tree.at(i).Rect.y)
                <= std::max( Game.Background.Camera.w , Game.Background.Camera.h ) )
                {
                    if ( Game.Entities.Tree[i].Type == EntityType::Tree1 )
                        rendererAdd( Game.Window.Renderer, Textures::Tree1, {
                             Game.Entities.Tree.at(i).Rect.x - Game.Background.Camera.x,
                             Game.Entities.Tree.at(i).Rect.y - Game.Background.Camera.y,
                             Game.Entities.Tree.at(i).Rect.w,
                             Game.Entities.Tree.at(i).Rect.h } );
                    if ( Game.Entities.Tree[i].Type == EntityType::Tree2 )
                        rendererAdd( Game.Window.Renderer, Textures::Tree2, {
                             Game.Entities.Tree.at(i).Rect.x - Game.Background.Camera.x,
                             Game.Entities.Tree.at(i).Rect.y - Game.Background.Camera.y,
                             Game.Entities.Tree.at(i).Rect.w,
                             Game.Entities.Tree.at(i).Rect.h } );
                    if ( Game.Entities.Tree[i].Type == EntityType::Tree3 )
                        rendererAdd( Game.Window.Renderer, Textures::Tree3, {
                             Game.Entities.Tree.at(i).Rect.x - Game.Background.Camera.x,
                             Game.Entities.Tree.at(i).Rect.y - Game.Background.Camera.y,
                             Game.Entities.Tree.at(i).Rect.w,
                             Game.Entities.Tree.at(i).Rect.h } );

                }



        if( Game.State == gameState::gameRunning )
        {
            rendererAdd( Game.Window.Renderer , Game.Text.scoreText , { Game.Background.Camera.w / 2 - 300 / 2 , 0 , 300 , 100 } );
            rendererAdd( Game.Window.Renderer , Game.Text.treeCount , { Game.Background.Camera.w / 2 - 150 / 2 , 100 , 150 , 100 } );
            if ( Game.Entities.Enemy.size() == 0 && (calculatePercentage( Game.Forest , Tile::Green )) > 30 )
                rendererAdd( Game.Window.Renderer , Game.Text.victory , { Game.Background.Camera.w / 2 - 300 / 2 , 200 , 300 , 100 } );
        } else if ( Game.State == gameState::gamePause ) {

            rendererAdd( Game.Window.Renderer , Game.Text.pause , { Game.Background.Camera.w / 2 - 600 / 2 , Game.Background.Camera.h / 2 - 800 / 2 , 600 , 300 } );

            if ( Game.Button == buttonState::resume )
            {
                rendererAdd( Game.Window.Renderer , Game.Text.resume , { Game.Background.Camera.w / 2 - 300 / 2 , Game.Background.Camera.h / 2 - 300 / 2 , 300 + 25 , 100 + 25 } );
                rendererAdd( Game.Window.Renderer , Game.Text.mainMenu , { Game.Background.Camera.w / 2 - 300 / 2 , Game.Background.Camera.h / 2 - 100 / 2 , 300 , 100 } );

            } else if ( Game.Button == buttonState::menu ) {
                rendererAdd( Game.Window.Renderer , Game.Text.resume , { Game.Background.Camera.w / 2 - 300 / 2 , Game.Background.Camera.h / 2 - 300 / 2 , 300 , 100 } );
                rendererAdd( Game.Window.Renderer , Game.Text.mainMenu , { Game.Background.Camera.w / 2 - 300 / 2 , Game.Background.Camera.h / 2 - 100 / 2 , 300 + 25 , 100 + 25 } );


            }

        }

            // Draw Frame
        SDL_RenderPresent( Game.Window.Renderer );

}

void renderMenu( Game Game )
{
    SDL_RenderClear( Game.Window.Renderer );

    if ( Game.Button == buttonState::play )
    {
        rendererAdd( Game.Window.Renderer , Game.Text.play , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 400 , 300 + 50 , 200 + 50 } );
        rendererAdd( Game.Window.Renderer , Game.Text.save , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 200 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.load , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.quit , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 + 200 , 300 , 200 } );


    } else if ( Game.Button == buttonState::save ) {
        rendererAdd( Game.Window.Renderer , Game.Text.play , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 400 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.save , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 200 , 300 + 50  , 200 + 50  } );
        rendererAdd( Game.Window.Renderer , Game.Text.load , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.quit , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 + 200 , 300 , 200 } );


    } else if ( Game.Button == buttonState::load ) {
        rendererAdd( Game.Window.Renderer , Game.Text.play , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 400 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.save , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 200 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.load , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 , 300 + 50 , 200 + 50 } );
        rendererAdd( Game.Window.Renderer , Game.Text.quit , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 + 200 , 300 , 200 } );



    }  else if ( Game.Button == buttonState::quit ) {
        rendererAdd( Game.Window.Renderer , Game.Text.play , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 400 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.save , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 - 200 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.load , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 , 300 , 200 } );
        rendererAdd( Game.Window.Renderer , Game.Text.quit , { Resolution::WindowWidth / 2 - 300 / 2 , Resolution::WindowHeight / 2 + 200 , 300 + 50 , 200 + 50 } );


    }






    SDL_RenderPresent( Game.Window.Renderer );
}
