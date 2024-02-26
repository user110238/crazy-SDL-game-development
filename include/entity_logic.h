 void entityGameLogic( AllEntities& Entities , std::vector< std::vector <Tile> >& Forest , const SDL_Rect& Player )
{

        if ( Entities.Enemy.size() == 0 )
            pushRandom( Entities.Enemy , 10 , Resolution::LevelWidth , Resolution::LevelHeight , EntityType::Enemy);


        for ( int i = 0 ; i < Entities.Enemy.size() ; ++i )
        {
            HandleEnemyMovement(Entities.Enemy[i].Rect, Entities.Tree );
                // Check if any enemy is collision-ing
            if ( collision ( Player, Entities.Enemy[i].Rect ) )
            {
                Entities.Enemy.erase(Entities.Enemy.begin() + i);
            }

            for (int j = 0; j < Entities.Tree.size(); j++)
            {
                if (collision(Entities.Enemy[i].Rect, Entities.Tree[j].Rect))
                {
                    if ( Entities.Enemy[i].Type == EntityType::Enemy )
                        updateForest( Forest , Entities.Tree[j].Rect , Tile::Brown , 100 );
                    else if ( Entities.Enemy[i].Type == EntityType::FireEnemy )
                        updateForest( Forest , Entities.Tree[j].Rect , Tile::Red , 10 );

                    Entities.Tree.erase( Entities.Tree.begin() + j);
                    --j;
                }
            }

            if ( Entities.Enemy[i].Type == EntityType::Enemy )
                updateForest( Forest , Entities.Enemy[i].Rect , Tile::Brown , 0 );

        }
        for ( int i = 0 ; i < Entities.Allies.size() ; ++i )
        {
            HandleAllyMovement( Entities.Allies[i].Rect , Entities.Enemy , 500 );

            for (int j = 0; j < Entities.Enemy.size(); j++)
            {
                if (collision(Entities.Allies[i].Rect, Entities.Enemy[j].Rect))
                {
                    Entities.Enemy.erase(Entities.Enemy.begin() + j);
                    --j;
                }
            }
        }
}
