 void entityGameLogic( AllEntities& Entities , std::vector< std::vector <Tile> >& Forest , SDL_Rect& Player )
{
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for ( int i = 0 ; i < Entities.Enemy.size() ; ++i )
        {
            HandleEnemyMovement( Entities.Enemy[i].Rect , Entities.Tree );
                // Check if any enemy is collision-ing
            if ( collision ( Player , Entities.Enemy[i].Rect ) )
            {
                Entities.Enemy.erase(Entities.Enemy.begin() + i);
            }

            for (int j = 0 ; j < Entities.Tree.size() ; j++)
            {
                if ( collision(Entities.Enemy[i].Rect, Entities.Tree[j].Rect) )
                {
                    if ( Entities.Enemy[i].Type == EntityType::Enemy )
                        updateForest( Forest , Entities.Tree[j].Rect , Tile::Brown , 100 );
                    else if ( Entities.Enemy[i].Type == EntityType::FireEnemy )
                        updateForest( Forest , Entities.Tree[j].Rect , Tile::Red , 10 );

                    Entities.Tree.erase(Entities.Tree.begin() + j);
                    --j;
                }
            }

            if ( Entities.Enemy[i].Type == EntityType::Enemy )
                updateForest( Forest , Entities.Enemy[i].Rect , Tile::Brown , 0 );

        }
        for ( int i = 0 ; i < Entities.Allies.size() ; ++i )
        {
            HandleAllyMovement( Entities.Allies[i].Rect , Entities.Enemy , 500 , Forest );
            moveRectAway( Entities.Allies[i].Rect , Player , 2) ;

            for (int j = 0; j < Entities.Enemy.size(); j++)
            {
                if (collision(Entities.Allies[i].Rect, Entities.Enemy[j].Rect))
                {
                    Entities.Enemy.erase(Entities.Enemy.begin() + j);
                    --j;
                }
                if (i != j )
                {
                    moveRectAway( Entities.Allies[i].Rect , Entities.Allies[j].Rect , 2) ;
                }
            }

            updateForest( Forest , Entities.Allies[i].Rect , Tile::Red , Tile::Brown , 40 );
        }
        for ( int i = 0 ; i < Entities.Tree.size() ; ++i )
        {
            if ( isTreeCompromised( Forest , Entities.Tree[i].Rect ) )
                Entities.Tree.erase( Entities.Tree.begin() + i );
            for ( int j = 0 ; j < Entities.Allies.size() ; ++j )
                moveRectAway( Entities.Tree[i].Rect , Entities.Allies[j].Rect , 2 );
            moveRectAway( Entities.Tree[i].Rect , Player , 2 );
        }
}


