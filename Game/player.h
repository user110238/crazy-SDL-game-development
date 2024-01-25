
struct Player{

    SDL_Rect Rect;
    SDL_Texture* Texture;




};

void movePlayer( SDL_Rect &Rect , int Velocityx , int Velocityy )
{
    Rect.x += Velocityx;
    Rect.y += Velocityy;

}
