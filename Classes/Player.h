//
//  Player.h
//  TowerDefense
//
//  Created by Georgios Floros on 26/06/2014.
//
//

#ifndef __TowerDefense__Player__
#define __TowerDefense__Player__

#include "GameScene.h"

USING_NS_CC;
class Player : public Ref
{
    
private:
    
    int lifePoints;
    int currency;
    std::string playerName;
    
    //move flags for camera
    bool _bIsMove;
    
    bool _ForwardMove;
    bool _BackMove;
    bool _LeftMove;
    bool _RightMove;
    
    
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    cocos2d::Layer* _sc;
    
    void update(float delta);
    
public:
    
    Player(cocos2d::Layer &ref, std::string name, int lifePoints);
    ~Player();
    
    TowerRules* tw;
    
    void SetCurrency(int coins);
    int GetCurrency();
    void AddCoins(int coins);
    void RemoveCoins(int coins);
    int GetLifePoints();
    void SetLifePoints(int lp);
    void SetPlayerName(std::string name);
    std::string& GetPlayerName();
    void RemoveLifePoints(int i);
    
};



#endif