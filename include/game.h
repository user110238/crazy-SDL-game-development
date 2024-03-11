enum gameState
{
    startUp,

    gameRunning,
    gamePause,

    mainMenuRunning,

    endGame
};

struct Game
{
    gameState State;

    structWindow Window;

    structPlayer Player;
    AllEntities Entities;

    std::vector<std::vector <Tile> > Forest;
    std::vector<std::pair< int , int >> CampCoordinates;
    structFireSpread FireSpread;

    structBackground Background;
    structText Text;

    FrameLimit Frames;

};
