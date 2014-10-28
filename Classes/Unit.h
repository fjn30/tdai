//
//  Unit.h
//  Tower Defense
//
//  Created by Georgios Floros on 16/06/2014.
//
//

#ifndef __TowerDefense__Unit__
#define __TowerDefense__Unit__

#include <iostream>
#include "cocos2d.h"
#include "MapGeneral.h"


USING_NS_CC;
class Unit : public cocos2d::Sprite
{
    
private:
    
    bool init(const std::string& fileNameFormat);
    bool initWithRect(const std::string & fileNameFormat, cocos2d::Rect r);
    
    cocos2d::Map<int, cocos2d::Animation*> _playerAnimMap;
    
    Sprite* _animationSprite;
    PlayerActionType _lastActionType;
    
public:
    Unit();
    Unit(const std::string& fileNameFormat, cocos2d::Rect rect);
    Unit(const std::string& fileNameFormat);

    ~Unit();
    
    static Unit& create(const std::string & fileNameFormat);
    static Unit& createWithSize(const std::string& fileNameFormat, cocos2d::Rect rect);

    bool isInitialized();
    
    void playAction(PlayerActionType actionType);
    
};

    
#endif
