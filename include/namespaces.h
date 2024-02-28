namespace constant
{
    // Entity constants
    const int ENTITY_SIZE_X =       100;
    const int ENTITY_SIZE_Y =       100;

    const int PLAYER_VELOCITY =     10;
    const int ENEMY_VELOCITY =      3;
    const int ALLY_VELOCITY =       5;
    const int ALLY_WANDER_VEL =     3;

    const int CAMP_SPAWN_DISTANCE = 250;
    const int PIXEL_SIZE =          10;
    const int HITBOX_REDUCTION =    10;

    const int EXTRA_RENDER =        10;
}

namespace Resolution
{
    int WindowWidth;
    int WindowHeight;

    int LevelWidth;
    int LevelHeight;
}

namespace Textures
{
    SDL_Texture* Player;

    SDL_Texture* Enemy;
    SDL_Texture* FireEnemy;

    SDL_Texture* Tree;
    SDL_Texture* Ally;
};
