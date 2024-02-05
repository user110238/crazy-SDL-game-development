
void moveRectTowards(SDL_Rect& srcRect, SDL_Rect& destRect , int detection )
{
        // distance between rectangles
    int DX = destRect.x - srcRect.x;
    int DY = destRect.y - srcRect.y;

        // normalize the vector
        // Pitagorov zakon po slovensko
    double lenght = std::sqrt(DX * DX + DY * DY);
    double normDX = DX / lenght;
    double normDY = DY / lenght;

    if ( lenght <= detection )
    {

            // move src rectangle acording to the normalized vector
        srcRect.x += (int)(normDX * ENEMY_VELOCITY);
        srcRect.y += (int)(normDY * ENEMY_VELOCITY);

    }

}

void HandleEnemyMovement( Entity& Enemy , SDL_Rect& player , int detection )
{

    moveRectTowards( Enemy.Rect , player , detection );


}
