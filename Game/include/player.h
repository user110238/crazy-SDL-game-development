
struct Player
{

    SDL_Rect Rect;
    SDL_Texture* Texture;

    SDL_Point Velocity;

    Player( int , int , int , int );
    void movePlayer( int , int  );

};

Player::Player( int x , int y , int w , int h )
{
    Rect.x = x;
    Rect.y = y;
    Rect.w = w;
    Rect.h = h;

    Texture = nullptr;
    Velocity.x = 0;
    Velocity.y = 0;

}

void Player::movePlayer( int LevelWidth, int LevelHeight )
{
        // lenght of the vector
        // pitagorov zakon po slovensko
    float lenght = std::sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);


        // normalize the vector
    float normX = Velocity.x / lenght;
    float normY = Velocity.y / lenght;

        // scale the normalized vector by velocity
    float scaledX = normX * constant::PLAYER_VELOCITY;
    float scaledY = normY * constant::PLAYER_VELOCITY;

        // create the new postion
    int newX = Rect.x + static_cast<int>(scaledX);
    int newY = Rect.y + static_cast<int>(scaledY);

        // move back if out of bounds
    if (newX >= 0 && newX + Rect.w <= LevelWidth)
    {
        Rect.x = newX;
    }
    if (newY >= 0 && newY + Rect.h <= LevelHeight)
    {
        Rect.y = newY;
    }


}

