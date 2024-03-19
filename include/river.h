#include <cmath>
void generateRiverHorizontal(std::vector<std::vector<Tile>>& vector, int SX, int SY, int RW, int negChange, int posChange)
{
    int RX = SX;
    int RY = SY;

    while (RX < static_cast<int>(vector.size()) && RY < static_cast<int>(vector[0].size()))
    {
        for (int x = RX; x < std::min(RX + RW, static_cast<int>(vector.size())); ++x)
        {
            for (int y = RY; y < std::min(RY + RW, static_cast<int>(vector[0].size())); ++y)
            {
                if (x >= 0 && x < static_cast<int>(vector.size()) && y >= 0 && y < static_cast<int>(vector[0].size()))
                    vector[x][y] = Tile::Blue;
            }
        }
        RX++;
        RY += getRandomNumber(negChange, posChange);
    }
}

void generateRiverVertical(std::vector<std::vector<Tile>>& vector, int SX, int SY, int RW, int negChange, int posChange)
{
    int RX = SX;
    int RY = SY;

    while (RX < static_cast<int>(vector.size()) && RY < static_cast<int>(vector[0].size()))
    {
        for (int x = RX; x < std::min(RX + RW, static_cast<int>(vector.size())); ++x)
        {
            for (int y = RY; y < std::min(RY + RW, static_cast<int>(vector[0].size())); ++y)
            {
                if (x >= 0 && x < static_cast<int>(vector.size()) && y >= 0 && y < static_cast<int>(vector[0].size()))
                    vector[x][y] = Tile::Blue;
            }
        }
        RX += getRandomNumber(negChange, posChange);
        RY++;
    }
}

void riverBanks(std::vector<std::vector<Tile>>& vector, int borderW)
{
    for (int x = 0; x < static_cast<int>(vector.size()); ++x)
    {
        for (int y = 0; y < static_cast<int>(vector[0].size()); ++y)
        {
            if (vector[x][y] == Tile::Green)
            {
                bool isNearBlue = false;

                for (int i = std::max(0, x - borderW); i <= std::min(x + borderW, static_cast<int>(vector.size()) - 1); ++i)
                {
                    for (int j = std::max(0, y - borderW); j <= std::min(y + borderW, static_cast<int>(vector[0].size()) - 1); ++j)
                    {
                        if (vector[i][j] == Tile::Blue)
                        {
                            isNearBlue = true;
                            break;
                        }
                    }
                }
                if (isNearBlue)
                {
                    vector[x][y] = Tile::Sand;
                }
            }
        }
    }
}

void river(std::vector<std::vector<Tile>>& vector)
{
    int RW = getRandomNumber( 8 , 15 );
    int numberOfRivers = getRandomNumber( 1 , 4 );
    int riverStartX, riverStartY;
    bool isHorizontal, isChaotic;

    for (int i = 0; i < numberOfRivers; ++i)
    {
        isHorizontal = rand() % 2;
        isChaotic = rand() % 4;

        if (isHorizontal)
        {
            riverStartX = 0;
            riverStartY = getRandomNumber(RW, static_cast<int>(vector[0].size()) - RW);

            if (!isChaotic)
                generateRiverHorizontal(vector, riverStartX, riverStartY, RW, -4, 4);
            else
                generateRiverHorizontal(vector, riverStartX, riverStartY, RW, -2, 2);
        }
        else
        {
            riverStartX = getRandomNumber(RW, static_cast<int>(vector.size()) - RW);
            riverStartY = 0;

            if (isChaotic)
                generateRiverVertical(vector, riverStartX, riverStartY, RW, -4, 4);
            else
                generateRiverVertical(vector, riverStartX, riverStartY, RW, -2, 2);
        }
    }

    riverBanks(vector, 3);
}
