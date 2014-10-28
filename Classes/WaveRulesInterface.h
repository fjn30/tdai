//
//  WaveRulesInterface.h
//  TD1
//
//  Created by Georgios Floros on 05/09/2014.
//
//

#ifndef __TD1__WaveRulesInterface__
#define __TD1__WaveRulesInterface__

#include "GameScene.h"

class WaveRulesInterface : public Ref
{
    public:
    std::string ProfileId;
    virtual void WaveRulesInit(void* args) = 0;
    virtual void BeforeDeployment(cocos2d::Layer& sc) = 0;
    virtual void AfterDeployment(cocos2d::Layer& sc) = 0;
    virtual void BeforeNextWave(cocos2d::Layer& sc, void* args) = 0; // i.e: end of round
    //returns a set of monsters for the current wave
    virtual std::list<Creep*> GetWaveCreeps() = 0;

};



#endif