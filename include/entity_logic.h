 void entityGameLogic( Game& Game )
{
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for ( int i = 0 ; i < Game.Entities.Enemy.size() ; ++i )
        {
            HandleEnemyMovement( Game.Entities.Enemy[i].Rect , Game.Entities.Tree , Game.Forest );
                // Check if any enemy is collision-ing
            if ( collision ( Game.Player.Rect , Game.Entities.Enemy[i].Rect ) )
            {
                Game.Entities.Enemy.erase(Game.Entities.Enemy.begin() + i);
            }

            for (int j = 0 ; j < Game.Entities.Tree.size() ; j++)
            {
                if ( collision(Game.Entities.Enemy[i].Rect, Game.Entities.Tree[j].Rect) )
                {
                    if ( Game.Entities.Enemy[i].Type == EntityType::Enemy )
                        updateForest( Game.Forest , Game.Entities.Tree[j].Rect , Tile::Brown , 100 );
                    else if ( Game.Entities.Enemy[i].Type == EntityType::FireEnemy )
                        updateForest( Game.Forest , Game.Entities.Tree[j].Rect , Tile::Red , 10 );

                    Game.Entities.Tree.erase(Game.Entities.Tree.begin() + j);
                    --j;
                }
            }

            if ( Game.Entities.Enemy[i].Type == EntityType::Enemy )
                updateForest( Game.Forest , Game.Entities.Enemy[i].Rect , Tile::Brown , 0 );

        }
        for ( int i = 0 ; i < Game.Entities.Allies.size() ; ++i )
        {
            if ( i == Game.controllable )
            {
                playerGameLogic( Game.Entities.Allies[i] , Game.movePlayerBy , Game.Forest );
            }
            else
            {
                HandleAllyMovement( Game.Entities.Allies[i].Rect , Game.Entities.Enemy , 500 , Game.Forest );
            }

            for (int j = 0; j < Game.Entities.Enemy.size(); j++)
                {
                    if (collision(Game.Entities.Allies[i].Rect, Game.Entities.Enemy[j].Rect))
                    {
                        Game.Entities.Enemy.erase(Game.Entities.Enemy.begin() + j);
                        --j;
                    }
                    if (i != j )
                    {
                        moveRectAwayEachother( Game.Entities.Allies[i].Rect , Game.Entities.Allies[j].Rect , constant::PUSH_SPEED * 1.5 ) ;
                    }
                }

                updateForest( Game.Forest , Game.Entities.Allies[i].Rect , Tile::Red , Tile::Brown , 40 );

        }
        for ( int i = 0 ; i < Game.Entities.Tree.size() ; ++i )
        {
            if ( isNotOnTile( Game.Forest , Game.Entities.Tree[i].Rect , Tile::Green ) )
                Game.Entities.Tree.erase( Game.Entities.Tree.begin() + i );
            for ( int j = 0 ; j < Game.Entities.Allies.size() ; ++j )
                moveRectAway( Game.Entities.Allies[j].Rect ,Game.Entities.Tree[i].Rect , constant::PUSH_SPEED );
            moveRectAway( Game.Player.Rect , Game.Entities.Tree[i].Rect , constant::PUSH_SPEED );
        }
}


