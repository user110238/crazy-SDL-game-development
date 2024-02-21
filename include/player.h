struct Player
{
    SDL_Rect Rect;
    SDL_Point Velocity;
};

void initPlayer ( Player& player , int x , int y  )
{

    player.Rect.x = x;
    player.Rect.y = y;
    player.Rect.w = constant::ENTITY_SIZE_X;
    player.Rect.h = constant::ENTITY_SIZE_Y;

    player.Velocity.x = 0;
    player.Velocity.y = 0;


}

void movePlayer ( Player& player , int LevelWidth , int LevelHeight )
{
        // lenght of the vector
        // pitagorov zakon po slovensko
    float lenght = std::sqrt(player.Velocity.x * player.Velocity.x + player.Velocity.y * player.Velocity.y);


        // normalize the vector
    float normX = player.Velocity.x / lenght;
    float normY = player.Velocity.y / lenght;

        // scale the normalized vector by velocity
    float scaledX = normX * constant::PLAYER_VELOCITY;
    float scaledY = normY * constant::PLAYER_VELOCITY;

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

