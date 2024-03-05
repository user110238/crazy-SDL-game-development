void generateRiver( std::vector<std::vector<Tile>>& vector , int SX , int SY , int RW , int negChange , int posChange )
{
    int RX = SX;
    int RY = SY;

    while ( RX < static_cast<int>(vector.size()) && RY < static_cast<int>(vector[0].size()) )
    {
        for ( int x = RX ; x < std::min( RX + RW  , static_cast<int>(vector.size()) ) ; ++x )
        {
            for ( int y = RY ; y < std::min( RY + RW , static_cast<int>(vector[0].size()) ); ++y )
            {
                vector[x][y] = Tile::Blue;
            }
        }
        RX++;
        RY += getRandomNumber( negChange , posChange );

    }
}

void riverBanks( std::vector<std::vector<Tile>>& vector , int borderW )
{
    for ( int x = 0 ; x < vector.size() ; ++x )
    {
        for ( int y = 0 ; y < vector[0].size() ; ++y )
        {
            if ( vector[x][y] == Tile::Green )
            {
                bool isNearBlue = false;

                for (int i = std::max( 0, x - borderW); i <= std::min(x + borderW, static_cast<int>(vector.size()) - 1); ++i)
                {
                    for (int j = std::max( 0, y - borderW ) ; j <= std::min( y + borderW , static_cast<int>(vector[0].size()) - 1 ) ; ++j )
                    {
                        if ( vector[i][j] == Tile::Blue )
                        {
                            isNearBlue = true;
                            break;
                        }
                    }
                }
                if ( isNearBlue )
                {
                    vector[x][y] = Tile::Sand;
                }
            }
        }
    }
}
void river( std::vector<std::vector<Tile>>& vector )
{

    int RW = 10;
    int riverStartX;
    int riverStartY;

    riverStartX = 100;
    riverStartY = 0;

    generateRiver( vector , riverStartX , riverStartY , RW , -2 , 4 );

    riverStartX = 0;
    riverStartY = getRandomNumber( 50 , vector.size() - RW - 11 );

    generateRiver( vector , riverStartX , riverStartY , RW , -2 , 2 );

    riverBanks( vector , 3 );

}
