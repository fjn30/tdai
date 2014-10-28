//
//  Creep.h
//  Tower Defense
//
//  Created by Georgios Floros on 19/06/2014.
//
//

#ifndef __TowerDefense__Creep__
#define __TowerDefense__Creep__

#include <iostream>
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class Creep : public Unit
{
    
    private:
    time_t prev;
    Label* lblDamageText;

    int coins;
    cocos2d::Layer* _sc;
    double startingHP;
    
    //the latest start and end stored by moveTo
    int lastStart, lastEnd;
    double lastSpeedCoefficient;
    
    ProgressTimer* healthbar;
    
    Label* lblHP;
    
    void update(float delta);
    
    public:
    std::string fileNameFormat;
    Creep(const std::string& fileNameFormat, double healthPoints, double movementSpeed);
    Creep(const std::string& fileNameFormat, cocos2d::Rect rect, double healthPoints, double movementSpeed);
    ~Creep();
    
    void moveTo(MapPath* path, double speedCoefficient, cocos2d::Layer& sc);
    void damageInflict(int dmg);
    int getCoins();
    void setCoins(int coins);
    
    double GetStartingHealthPoints();
    double GetHealthPoints();
    double GetMovementSpeed();
    
    void SetMovementSpeed(double s);
    void SetLastSpeedCoefficient(double s);
    
    void SetHealthPoints(double s);
    
    //base stats
    private:
    
    
    double movementSpeed;
    double healthPoints;
    
    
    public:
    ElementalAffinity element;
    
    
    void invalidatePath();
    
};



#endif 
