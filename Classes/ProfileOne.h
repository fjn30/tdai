//
//  Profile1.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 24/08/2014.
//
//

#ifndef __TowerDefense_new__Profile1__
#define __TowerDefense_new__Profile1__

#include "GameScene.h"

class ProfileOne : public WaveRules {
    
    public:
    
    ProfileOne();
    
    
    void WaveRulesInit(void* args);
    
    int elementIt;
    int sElementIt;

    std::list<Creep*> GetWaveCreeps();
    
    
    
};

#endif