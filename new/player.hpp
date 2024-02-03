class Player
{
    int _position_X, _position_Y;
    int _velocity_X, _velocity_Y;

    public:

    Player();
    ~Player();

    const int WIDTH = 20;
    const int HEIGHT = 20;

    const int VELOCITY = 10;

    void handleEvent( SDL_Event& e );
    void move();

};

Player::Player()
{
    _position_X = 0;
    _position_Y = 0;

    _velocity_X = 0;
    _velocity_Y = 0;

}

void Player::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: _velocity_Y -= VELOCITY; break;
            case SDLK_DOWN: _velocity_Y += VELOCITY; break;
            case SDLK_LEFT: _velocity_X -= VELOCITY; break;
            case SDLK_RIGHT: _velocity_X += VELOCITY; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: _velocity_Y += VELOCITY; break;
            case SDLK_DOWN: _velocity_Y -= VELOCITY; break;
            case SDLK_LEFT: _velocity_X += VELOCITY; break;
            case SDLK_RIGHT: _velocity_X -= VELOCITY; break;
        }
    }
}

void Player::move()
{
    _position_X += _velocity_X;

    /*if( ( _position_X < 0 ) || ( _position_X + DOT_WIDTH > LEVEL_WIDTH ) )
    {
        _position_X -= _velocity_X;
    }*/

    _position_Y += _velocity_Y;

    /*if( ( _position_Y < 0 ) || ( _position_Y + DOT_HEIGHT > LEVEL_HEIGHT ) )
    {
        _position_Y -= _velocity_Y;
    }*/
}
