//
//  Radar.h
//  TowerDefense_new
//
//  Created by GEO on 16/08/2014.
//
//

#ifndef __TowerDefense_new__Radar__
#define __TowerDefense_new__Radar__

#include "GameScene.h"

enum class RadarMapNode { Creep = 1, Tower = 2, Nothing = 3 };

class Radar {
    
    public:
    Radar(cocos2d::Layer& _gs, cocos2d::Point position);
    ~Radar();
    
    void invalidate();
    
    private:
    cocos2d::Layer* _pGs;
    Sprite* radarBg1;
    std::vector<RadarMapNode> map;
    std::vector<Sprite*> sprites;
    
};




#endif
