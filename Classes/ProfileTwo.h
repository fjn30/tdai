//
//  ProfileTwo.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 24/08/2014.
//
//

#ifndef __TowerDefense_new__ProfileTwo__
#define __TowerDefense_new__ProfileTwo__

#include "GameScene.h"

class ProfileTwo : public WaveRules {
    
    public:
    
    ProfileTwo();
    //~ProfileTwo();
    
    ElementalAffinity previousEle;
    
    void WaveRulesInit(void* args);
    std::list<Creep*> GetWaveCreeps();
    
};


#endif
