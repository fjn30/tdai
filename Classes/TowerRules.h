//
//  TowerRules.h
//  TowerDefense_new
//
//  Created by Georgios Floros on 09/07/2014.
//
//

#ifndef __TowerDefense_new__TowerUpgradeRules__
#define __TowerDefense_new__TowerUpgradeRules__

#include <iostream>

USING_NS_CC;
class TowerRules : public Ref
{
    //defines the tower upgrading rules
    public:
    TowerRules();
    ~TowerRules();
    
    int GetAttackUpgradeCost(Ref & t);
    int GetSpeedUpgradeCost(Ref & t);
    
    int GetStrength(Ref & t);
    
    double getSameElementPenalty(double num);
    double getElementWeaknessPenalty(double num);
    double getOppositeElementPenalty(double num);
    
    void SetSubAttackSpeed(double num);
    void SetAddAttackDamage(double num);
    
    void SetAttackUpgradeCost(double num);
    void SetSpeedUpgradeCost(double num);
    
    void SetAddFireDamage(double num);
    void SetAddWaterDamage(double num);
    void SetAddEarthDamage(double num);
    void SetAddShockDamage(double num);
    
    bool UpgradeAttackPower(Ref* p, Ref & u);
    bool UpgradeAttackSpeed(Ref* p, Ref & u);
    bool UpgradeToFire(Ref* p, Ref & t);
    bool UpgradeToWater(Ref* p, Ref & t);
    bool UpgradeToShock(Ref* p, Ref & t);
    bool UpgradeToEarth(Ref* p, Ref & t);
    
    void SetElementsAmplifier(double num);
    double GetElementsAmp();
    
    void SetElementWeaknessDamageMultiplier(double num);
    double GetElementWeaknessDamageMultiplier();
    
    double GetWaterDamage(ElementalAffinity creepAff, double num);
    double GetFireDamage(ElementalAffinity creepAff, double num);
    double GetEarthDamage(ElementalAffinity creepAff, double num);
    double GetShockDamage(ElementalAffinity creepAff, double num);
    
    int GetWaterUpgradeCost();
    int GetEarthUpgradeCost();
    int GetShockUpgradeCost();
    int GetFireUpgradeCost();
    
    void SetWaterUpgradeCost(int num);
    void SetFireUpgradeCost(int num);
    void SetEarthUpgradeCost(int num);
    void SetShockUpgradeCost(int num);
    
    private:
    int attackUpgradeCost;
    int speedUpgradeCost;
    
    double attackSpeedSub;
    double attackDamageAdd;
    
    double elementsAmplifier;
    double elementWeaknessDamageMultiplier;
    
    int waterUpgradeCost;
    int addWaterDamage;

    int fireUpgradeCost;
    int addFireDamage;
    
    int earthUpgradeCost;
    int addEarthDamage;
    
    int shockUpgradeCost;
    int addShockDamage;
    
    
};

#endif
