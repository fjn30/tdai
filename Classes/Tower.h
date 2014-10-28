//
//  Tower.h
//  Tower Defense
//
//  Created by Georgios Floros on 23/06/2014.
//
//

#ifndef __TowerDefense__Tower__
#define __TowerDefense__Tower__

#include <iostream>
#include "GameScene.h"


USING_NS_CC;
class Tower : public Unit
{
    
    private:
    void ProjectileMoveFinished(Node* sender);
    std::chrono::system_clock::time_point prevAttack;
    bool firstAttack;
    
    Label* lblEleStrength;
    
    public:
    //upgrades
    int attackUpgradesDone;
    int speedUpgradesDone;
    
    private:
    cocos2d::Layer* mainscene;
    
    Sprite* highlight;
    bool isHighlighted;
    std::vector<cocos2d::Point> hitPositions;
    ElementalAffinity element;

    void Init();
    
    public:
    Tower(cocos2d::Layer &ref, const std::string& fileNameFormat, TowerRules* tr);
    Tower(cocos2d::Layer &ref, const std::string& fileNameFormat, cocos2d::Rect rect, TowerRules* tr);
    ~Tower();
        
    void ToggleHighlight(bool activate);
    
    std::vector<cocos2d::Point>& GetHitPosition();
    void AddHitPosition(cocos2d::Point p);
    
    void IncreaseSpeedUpgradesDone();
    void IncreaseAttackUpgradesDone();
    
    int GetSpeedUpgradesDone();
    int GetAttackUpgradesDone();
    
    int GetSpeedUpgradeCost();
    int GetAttackUpgradeCost();
    
    int SpeedsUpgradesDone();
    int AttackUpgradesDone();
    
    bool UpgradeAttackPower(Ref* p);
    bool UpgradeAttackSpeed(Ref* p);
    bool UpgradeToFire(Ref* p);
    bool UpgradeToWater(Ref* p);
    bool UpgradeToEarth(Ref* p);
    bool UpgradeToShock(Ref* p);
    bool UpgradeToPoison(Ref* p);
    
    TowerRules * toweRules;
    
    int GetStrength();
    
    void SetElement(ElementalAffinity ele);
    ElementalAffinity GetElement();
    
    void SetInbetweenAttacksPeriod(double num);
    double GetInbetweenAttacksPeriod();
    
    //base stats
    double attackPoints;
    double attackRange;
    double inbetweenAttacksPeriod;
    double inbetweenAttacksPeriodBoost;
    
    int cost;
    
    void FireProjectile(cocos2d::Point loc);
    void NotifyCreepInRange(Creep* refUnit);
    void Attack(Creep* refUnit);
    
    void SetHitPositions(MapInfo* mi);
    void SetStartingStats(double attackRange, int attackPoints, double inbetweenAttacksPeriod, int cost);
    
};



#endif