//
//  AICreepsPlayer.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 04/07/2014.
//
//

#ifndef __TowerDefense_new__AICreepsPlayer__
#define __TowerDefense_new__AICreepsPlayer__

#include "GameScene.h"


USING_NS_CC;
class AICreepsPlayer
{
    private:
    cocos2d::Layer* _sc;
    
    WaveRulesInterface* waveRules;
    
    public:
    AICreepsPlayer(cocos2d::Layer& sc, WaveRules *wr);
    ~AICreepsPlayer();
    
    void ReadyForNextWave();
    
    void BeforeNextWave(void* args);
    void BeforeDeployment();
    void AfterDeployment();
    
    void NotifyAIRecalculate();
    
};




#endif

