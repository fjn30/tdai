//
//  Settings.h
//  TD1
//

/**
 *  @Author Georgios Floros
 *
 *  @brief  Holds the settings of the game
 */

#ifndef __TD1__Settings__
#define __TD1__Settings__

#include "GameScene.h"

class Settings
{
    public:
    
    static bool fullyInitialized;
    
    
    static MapType mapType;
    static bool imEnabled;
    static WaveRules* waveRules;

    static int numberOfRounds;
    
    static int playerStartingCurrency;
    static int playerStartingHealthPoints;
    
    
    static double towerAttackRange;
    static int towerAttackPoints;
    static double towerInbetweenAttacksPeriod;
    static int towerCost;
    
    static std::string towerTexture;
    
};

#endif