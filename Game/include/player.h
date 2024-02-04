
struct Player
{

    SDL_Rect Rect;
    SDL_Texture* Texture;
    SDL_Renderer* Renderer;

    SDL_Point Velocity;

};


void movePlayer(Player& player, int LevelWidth, int LevelHeight)
{
        // lenght of the vector
        // pitagorov zakon po slovensko
    float lenght = std::sqrt(player.Velocity.x * player.Velocity.x + player.Velocity.y * player.Velocity.y);


        // normalize the vector
    float normX = player.Velocity.x / lenght;
    float normY = player.Velocity.y / lenght;

        // scale the normalized vector by velocity
    float scaledX = normX * VELOCITY;
    float scaledY = normY * VELOCITY;

        // create the new postion
    int newX = player.Rect.x + static_cast<int>(scaledX);
    int newY = player.Rect.y + static_cast<int>(scaledY);

        // move back if out of bounds
    if (newX >= 0 && newX + player.Rect.w <= LevelWidth)
    {
        player.Rect.x = newX;
    }
    if (newY >= 0 && newY + player.Rect.h <= LevelHeight)
    {
        player.Rect.y = newY;
    }
}

void moveRectTowards(SDL_Rect& srcRect, SDL_Rect& destRect)
{
        // distance between rectangles
    int DX = destRect.x - srcRect.x;
    int DY = destRect.y - srcRect.y;

        // normalize the vector
        // Pitagorov zakon po slovensko
    double lenght = std::sqrt(DX * DX + DY * DY);
    double normDX = DX / lenght;
    double normDY = DY / lenght;

        // move src rectangle acording to the normalized vector
    srcRect.x += (int)(normDX * VELOCITY);
    srcRect.y += (int)(normDY * VELOCITY);

}
