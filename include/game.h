enum gameState
{
    startUp,
    reSetupRandom,
    reSetupBeforeReplay,

    gameRunning,
    gameReplaying,
    gamePause,

    gameCompleted,
    gameFailed,

    mainMenuRunning,

    saved,
    loaded,

    endGame
};

enum buttonState
{
    play,

    resume,
    replay,
    menu,

    save,
    load,

    quit,

    nothing
};

struct Game
{
    gameState State;
    buttonState Button;

    structWindow Window;

    Entity Player;
    SDL_Point movePlayerBy;
    int controllable = 0;

    AllEntities Entities;

    std::vector<std::vector <Tile> > Forest;
    std::vector<std::pair< int , int >> CampCoordinates;
    structFireSpread FireSpread;

    structBackground Background;
    structText Text;

    std::string SessionName = "";

    FrameLimit Frames;

    double seed;
    int Level = 1;

};
