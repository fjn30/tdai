//
//  WaveRules.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 05/07/2014.
//
//

#ifndef __TowerDefense_new__WaveRules__
#define __TowerDefense_new__WaveRules__

#include "GameScene.h"

class WaveRules : public WaveRulesInterface
{
    
    protected:
    int round;
    
    //Creep related
    std::vector<Creep*> availableCreeps;
    double speedMultiplier;
    double hpMultiplier;
    int numOfStartingCreeps;
    int numOfCreepsMultiplier;
    int numOfCreepsAddedPerWave;
    
    bool specialCreepSet;
    std::vector<Creep*> availableSpecialCreeps;
    double specialCreepSpeedMultiplier;
    double specialCreepHPMultiplier;
    int specialCreepSpawnFrequency;
    int roundsAfterSpawn;
    
    bool multiplyCreepNumbersPerRound;
    
    ElementalAffinity getRandomElement();
    
    public:
    WaveRules(void);
    //~WaveRules(void);
    
    virtual void WaveRulesInit(void* args);
    virtual void BeforeDeployment(cocos2d::Layer& sc);
    virtual void BeforeNextWave(cocos2d::Layer& sc, void* args);
    virtual void AfterDeployment(cocos2d::Layer& sc);
    
    
    std::list<Creep*> GetWaveCreeps();
    
    //normal creeps
    void addCreep(Creep * creep);
    void addFireCreep(Creep * creep);
    void addEarthCreep(Creep * creep);
    void addShockCreep(Creep * creep);
    void addWaterCreep(Creep * creep);
    
    void setCreepsSpeedMultiplier(double multiplier);
    void setCreepsHPMultiplier(double multiplier);
    void setNumOfCreepsStarting(int num);
    void setNumOfCreepsMultiplier(int num);
    void setNumOfCreepsToBeAddedPerWave(int num);
    
    //special creep
    bool isSpecialCreepSet();
    void addSpecialCreep(Creep * creep);
    void addSpecialFireCreep(Creep * creep);
    void addSpecialEarthCreep(Creep * creep);
    void addSpecialShockCreep(Creep * creep);
    void addSpecialWaterCreep(Creep * creep);

    void setSpecialCreepSpawnFrequency(int freq);
    void setSpecialCreepSpeedMultiplier(double multiplier);
    void setSpecialCreepHPMultiplier(double multiplier);
  
    void setMultiplyCreepNumbersPerRound(bool enable);

    
};


#endif
