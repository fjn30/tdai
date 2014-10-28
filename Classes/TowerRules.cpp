//
//  TowerRules.cpp
//  TowerDefense_new
//
//  Created by Georgios Floros on 09/07/2014.
//
//

#include "GameScene.h"


TowerRules::TowerRules()
{
    this->attackDamageAdd = 0.0f;
    this->attackSpeedSub = 0.0f;
    
    this->attackUpgradeCost = 0;
    this->speedUpgradeCost = 0;
    
    this->elementsAmplifier = 0.0f;
    this->elementWeaknessDamageMultiplier = 0.0f;
    
    this->waterUpgradeCost = 0;
    this->addWaterDamage = 0;
    
    this->fireUpgradeCost = 0;
    this->addFireDamage = 0;
    
    this->earthUpgradeCost = 0;
    this->addEarthDamage = 0;
    
    this->shockUpgradeCost = 0;
    this->addShockDamage = 0;
    
}

TowerRules::~TowerRules()
{
    
}

void TowerRules::SetElementWeaknessDamageMultiplier(double num)
{
    this->elementWeaknessDamageMultiplier = num;
}

void TowerRules::SetAddFireDamage(double num)
{
    this->addFireDamage = num;
}

void TowerRules::SetAddEarthDamage(double num)
{
    this->addEarthDamage = num;
}

void TowerRules::SetAddWaterDamage(double num)
{
    this->addWaterDamage = num;
}

void TowerRules::SetAddShockDamage(double num)
{
    this->addShockDamage = num;
}

void TowerRules::SetElementsAmplifier(double amp)
{
    this->elementsAmplifier = amp;
}

double TowerRules::GetElementsAmp()
{
    return this->elementsAmplifier;
}

void TowerRules::SetAddAttackDamage(double num)
{
    this->attackDamageAdd = num;
}

void TowerRules::SetSubAttackSpeed(double num)
{
    this->attackSpeedSub = num;
}

double TowerRules::getOppositeElementPenalty(double num)
{
    return num / 5;
}

double TowerRules::getSameElementPenalty(double dmg)
{
    return dmg / 2;
}

double TowerRules::getElementWeaknessPenalty(double dmg)
{
    return dmg * elementWeaknessDamageMultiplier;
}

//shows the strength of a tower
int TowerRules::GetStrength(Ref & t)
{
    Tower * to = (Tower*) &t;
    
    int a;
    
    // 1 second / inbetweenAttacksPeriod 
    if(to->GetElement() == ElementalAffinity::Fire)
    {
        //return ((to->attackPoints + this->addFireDamage) * (1/to->inbetweenAttacksPeriod)) / 50;
        a = ((this->elementsAmplifier * to->attackPoints) + this->addFireDamage) + (1/to->inbetweenAttacksPeriod) / 1000;
        //std::cout << "\n\n test strength test: " << a << "\n\n";
        return a;
    }
    else if(to->GetElement() == ElementalAffinity::Earth)
    {
        a = ((this->elementsAmplifier * to->attackPoints) + this->addEarthDamage) + (1/to->inbetweenAttacksPeriod) / 1000;
        //std::cout << "\n\n test strength test: " << a << "\n\n";
        return a;
    }
    else if(to->GetElement() == ElementalAffinity::Water)
    {
        a = ((this->elementsAmplifier * to->attackPoints) + this->addWaterDamage) + (1/to->inbetweenAttacksPeriod) / 1000;
        //std::cout << "\n\n test strength test: " << a << "\n\n";
        return a;
    }
    else if(to->GetElement() == ElementalAffinity::Shock)
    {
        a = ((this->elementsAmplifier * to->attackPoints) + this->addShockDamage) + (1/to->inbetweenAttacksPeriod) / 1000;
        //std::cout << "\n\n test strength test: " << a << "\n\n";
        return a;
    }
    else // element == none
    {
        //return ((to->attackPoints) * (1/to->inbetweenAttacksPeriod)) /50 ;
        a = ((this->elementsAmplifier * to->attackPoints) ) + (1/to->inbetweenAttacksPeriod) / 1000;
        //std::cout << "\n\n test strength test: " << a << "\n\n";
        return a;
    }
}

double TowerRules::GetWaterDamage(ElementalAffinity creepAff, double num)
{
    if(creepAff == ElementalAffinity::Water) // SAME ELE PENALTY
    {
        return this->getSameElementPenalty(this->addWaterDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Fire) // WEAKNESS MULTIPLIER
    {
        return this->getElementWeaknessPenalty(this->addWaterDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Earth)
    {
        return this->addWaterDamage * (this->elementsAmplifier + num);
    }
    else if (creepAff == ElementalAffinity::Shock) // OPPOSITE
    {
        return this->getOppositeElementPenalty(this->addWaterDamage * (this->elementsAmplifier + num));
    }
    else // No element
    {
        return this->addWaterDamage * (this->elementsAmplifier + num);
    }
}

double TowerRules::GetEarthDamage(ElementalAffinity creepAff, double num)
{
    if(creepAff == ElementalAffinity::Water)
    {
        return this->addEarthDamage * (this->elementsAmplifier + num);
    }
    else if (creepAff == ElementalAffinity::Fire) // OPPOSITE
    {
        return this->getOppositeElementPenalty(this->addEarthDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Earth) // SAME ELE PENALTY
    {
        return this->getSameElementPenalty(this->addEarthDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Shock) // WEAKNESS MULTIPLIER
    {
        return this->getElementWeaknessPenalty(this->addEarthDamage * (this->elementsAmplifier + num));
    }
    else // No element
    {
        return this->addEarthDamage * (this->elementsAmplifier + num);
    }
}

double TowerRules::GetShockDamage(ElementalAffinity creepAff, double num)
{
    if(creepAff == ElementalAffinity::Water) // WEAKNESS MULTIPLIER
    {
        return this->getElementWeaknessPenalty(this->addShockDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Fire)
    {
        return this->addShockDamage * (this->elementsAmplifier + num);
    }
    else if (creepAff == ElementalAffinity::Earth)  // OPPOSITE
    {
        return this->getOppositeElementPenalty(this->addShockDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Shock) // SAME ELE PENALTY
    {
        return this->getSameElementPenalty(this->addShockDamage * (this->elementsAmplifier + num));
    }
    else // No element
    {
        return this->addShockDamage * (this->elementsAmplifier + num);
    }
}

double TowerRules::GetFireDamage(ElementalAffinity creepAff, double num)
{
    if(creepAff == ElementalAffinity::Water) // OPPOSITE
    {
        return this->getOppositeElementPenalty(this->addFireDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Fire) // SAME ELE PENALTY
    {
        return this->getSameElementPenalty(this->addFireDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Earth) // WEAKNESS MULTIPLIER
    {
        return this->getElementWeaknessPenalty(this->addFireDamage * (this->elementsAmplifier + num));
    }
    else if (creepAff == ElementalAffinity::Shock)
    {
        return this->addFireDamage * (this->elementsAmplifier + num);
    }
    else // No element
    {
        return this->addFireDamage * (this->elementsAmplifier + num);
    }
}

void TowerRules::SetAttackUpgradeCost(double num)
{
    this->attackUpgradeCost = num;
}

void TowerRules::SetSpeedUpgradeCost(double num)
{
    this->speedUpgradeCost = num;
}

int TowerRules::GetAttackUpgradeCost(Ref & t)
{
    Tower * to = (Tower*) &t;
    return to->GetAttackUpgradesDone() * this->attackUpgradeCost;
}

int TowerRules::GetSpeedUpgradeCost(Ref & t)
{
    Tower * to = (Tower*) &t;
    return to->GetSpeedUpgradesDone() * this->speedUpgradeCost;
}

void TowerRules::SetEarthUpgradeCost(int c)
{
    this->earthUpgradeCost = c;
}

void TowerRules::SetWaterUpgradeCost(int c)
{
    this->waterUpgradeCost = c;
}

void TowerRules::SetFireUpgradeCost(int c)
{
    this->fireUpgradeCost = c;
}

void TowerRules::SetShockUpgradeCost(int c)
{
    this->shockUpgradeCost = c;
}

int TowerRules::GetShockUpgradeCost()
{
    return this->shockUpgradeCost;
}

int TowerRules::GetWaterUpgradeCost()
{
    return this->waterUpgradeCost;
}

int TowerRules::GetFireUpgradeCost()
{
    return this->fireUpgradeCost;
}

int TowerRules::GetEarthUpgradeCost()
{
    return this->earthUpgradeCost;
}

bool TowerRules::UpgradeAttackPower(Ref* p, Ref & u)
{
    Tower *t = (Tower*)&u;
    if( ((Player*)p)->GetCurrency() >= this->GetAttackUpgradeCost(*t) )
    {
        ((Player*)p)->RemoveCoins(this->GetAttackUpgradeCost(*t));
        t->attackPoints = t->attackPoints + this->attackDamageAdd;
        t->IncreaseAttackUpgradesDone();
        return true;
    }
    else
    {
        return false;
    }
}

bool TowerRules::UpgradeAttackSpeed(Ref* p, Ref & u)
{
    Tower *t = (Tower*)&u;
    if( ((Player*)p)->GetCurrency() >= this->GetSpeedUpgradeCost(*t) )
    {
        ((Player*)p)->RemoveCoins(this->GetSpeedUpgradeCost(*t));
        t->inbetweenAttacksPeriod = t->inbetweenAttacksPeriod - this->attackSpeedSub;
        t->IncreaseSpeedUpgradesDone();
        return true;
    }
    else
    {
        return false;
    }
}

bool TowerRules::UpgradeToFire(Ref* p, Ref & u)
{
    Tower *t = (Tower*)&u;
    if( t->GetElement() == ElementalAffinity::None && ((Player*)p)->GetCurrency() >= this->fireUpgradeCost )
    {
        t->SetElement(ElementalAffinity::Fire);
        ((Player*)p)->RemoveCoins(this->fireUpgradeCost);
        return true;
    }
    else
    {
        return false;
    }
}

bool TowerRules::UpgradeToWater(Ref* p, Ref & u)
{
    Tower *t = (Tower*)&u;
    if( t->GetElement() == ElementalAffinity::None && ((Player*)p)->GetCurrency() >= this->waterUpgradeCost )
    {
        t->SetElement(ElementalAffinity::Water);
        ((Player*)p)->RemoveCoins(this->waterUpgradeCost);
        return true;
    }
    else
    {
        return false;
    }
}

bool TowerRules::UpgradeToShock(Ref* p, Ref & u)
{
    Tower *t = (Tower*)&u;
    if( t->GetElement() == ElementalAffinity::None && ((Player*)p)->GetCurrency() >= this->shockUpgradeCost )
    {
        t->SetElement(ElementalAffinity::Shock);
        ((Player*)p)->RemoveCoins(this->shockUpgradeCost);
        return true;
    }
    else
    {
        return false;
    }
}

bool TowerRules::UpgradeToEarth(Ref* p, Ref & u)
{
    Tower *t = (Tower*)&u;
    if( t->GetElement() == ElementalAffinity::None && ((Player*)p)->GetCurrency() >= this->earthUpgradeCost )
    {
        t->SetElement(ElementalAffinity::Earth);
        ((Player*)p)->RemoveCoins(this->earthUpgradeCost);
        return true;
    }
    else
    {
        return false;
    }
}
