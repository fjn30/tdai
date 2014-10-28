//
//  AIStatus.h
//  TowerDefense_new
//
//  Created by GEO on 02/08/2014.
//
//

#ifndef __TowerDefense_new__AIStatus__
#define __TowerDefense_new__AIStatus__

#include "GameScene.h"

class AIStatus {
    
    public:
    
    AIStatus(cocos2d::Layer& _gs);
    ~AIStatus();
 
    bool enabled;
    
    void IMDraw();
    void ClearIM();
    
    void DrawRoads();
    
    void DrawEnvironment();
    void ClearEnvironment();
    
    private:
    
    //label, color sprite
    std::map< Label*, Sprite* > imNodes;
    std::map< Label*, Sprite* > envNodes;
    
    cocos2d::Layer* _pGs;
    
};

#endif
