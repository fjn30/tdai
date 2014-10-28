//
//  MapGeneral.h
//
//
//  Based on chenquanjun's solution (testAStar).
//
//

#ifndef __TowerDefense__MapGeneral__
#define __TowerDefense__MapGeneral__


//defines the type of each tile based on objectid
enum class MapInfoType{
    Invalid   =  0,
    Block     = -1,
    Road      =  1,
    RoadAllowedTower = 2,
    Tower     = 3,
    Planes    = 4,
    End       = 12,
    Start     = 13,
    SimTowerPlace = 20,
};

//defines the possible actions
enum class PlayerActionType{
    Invalid    = 0,
    Down       = 1,
    Left       = 2,
    Right      = 3,
    Up         = 4,
    Max        = 5,
};


#define MAPINFO_ASTAR_DIRECTION_NUM 4
#define MAPINFO_MAX_STEP_NUM 10000
#define MAPINFO_MAX_STORE_PATH_SIZE 10000

#endif
