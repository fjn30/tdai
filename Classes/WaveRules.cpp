//
//  WaveRules.cpp
//  TowerDefense_new
//
//  Created by Georgios Floros on 05/07/2014.
//
//

#include "GameScene.h"

WaveRules::WaveRules() : WaveRulesInterface()
{
    this->specialCreepSet = false;
    
    this->round = 1;
    
    this->multiplyCreepNumbersPerRound = false;
    this->speedMultiplier = 1;
    this->hpMultiplier = 1;
    this->numOfStartingCreeps = 1;
    this->numOfCreepsMultiplier = 1;
    this->numOfCreepsAddedPerWave = 2;
    
    this->specialCreepSet = false;
    this->specialCreepSpeedMultiplier = 1;
    this->specialCreepHPMultiplier = 1;
    this->specialCreepSpawnFrequency = 0;
    this->roundsAfterSpawn = 0;
}


void WaveRules::WaveRulesInit(void* args)
{
    
}

void WaveRules::BeforeDeployment(cocos2d::Layer& sc)
{
    
}

void WaveRules::BeforeNextWave(cocos2d::Layer& sc, void* args)
{
    
}

void WaveRules::AfterDeployment(cocos2d::Layer& sc)
{
    
}


void WaveRules::setNumOfCreepsStarting(int num)
{
    this->numOfStartingCreeps = num;
}

void WaveRules::setNumOfCreepsMultiplier(int num)
{
    this->numOfCreepsMultiplier = num;
}

void WaveRules::addCreep(Creep * const creep)
{
    this->availableCreeps.push_back(creep);
}

void WaveRules::setNumOfCreepsToBeAddedPerWave(int num)
{
    this->numOfCreepsAddedPerWave = num;
}

void WaveRules::setCreepsSpeedMultiplier(double multiplier)
{
    this->speedMultiplier = multiplier;
}

void WaveRules::setCreepsHPMultiplier(double multiplier)
{
    this->hpMultiplier = multiplier;
}

void WaveRules::addSpecialCreep(Creep * creep)
{
    this->specialCreepSet = true;
    this->availableSpecialCreeps.push_back(creep);
}
 
void WaveRules::setSpecialCreepSpawnFrequency(int freq)
{
    this->specialCreepSpawnFrequency = freq;
}

void WaveRules::setSpecialCreepSpeedMultiplier(double multiplier)
{
    this->specialCreepSpeedMultiplier = multiplier;
}

void WaveRules::setSpecialCreepHPMultiplier(double multiplier)
{
    this->specialCreepHPMultiplier = multiplier;
}

bool WaveRules::isSpecialCreepSet()
{
    return this->specialCreepSet;
}

void WaveRules::setMultiplyCreepNumbersPerRound(bool enable)
{
    this->multiplyCreepNumbersPerRound = enable;
}

ElementalAffinity WaveRules::getRandomElement()
{
    // 0 - 5 :: 0,1,2,3,4
    return (ElementalAffinity) (std::rand() % 5);
}


std::list<Creep*> WaveRules::GetWaveCreeps()
{
    std::list<Creep*> rules;
    
    
    return rules;
}


//the actual
/*
 
 
 std::list<Creep*> WaveRules::GetWaveCreeps()
 {
 std::list<Creep*> rules;
 ElementalAffinity simpElement = this->getRandomElement();
 ElementalAffinity specElement = this->getRandomElement();
 
 for ( std::list<Creep*>::iterator creep = availableCreeps.begin(); creep != availableCreeps.end(); ++creep )
 {
 Creep *it = *creep;
 if(simpElement == it->element)
 {
 int a = 0;
 
 if(this->multiplyCreepNumbersPerRound == true)
 {
 a = (this->numOfStartingCreeps * this->numOfCreepsMultiplier * this->round) + this->numOfCreepsAddedPerWave;
 }
 else
 {
 a = (this->numOfStartingCreeps * this->numOfCreepsMultiplier) + (this->numOfCreepsAddedPerWave * this->round);
 }
 
 int i = 0;
 while (i < a)
 {
 
 //Creep units enter as new units (Copy)
 Creep *cP = new Creep(it->fileNameFormat.c_str(), it->GetHealthPoints() * (this->hpMultiplier * this->round), it->GetMovementSpeed() - (this->speedMultiplier * this->round));
 cP->setCoins(it->getCoins());
 
 //due to a specific implementation that does number of points * duration the movementspeed
 //coefficient has to be devided, yet by dividing the speed of movement of units radically increases
 //so subtraction is used to make the increase of speed smoother.
 
 rules.push_back(cP);
 i++;
 }
 break;
 }
 }
 
 if ( this->isSpecialCreepSet() &&  this->roundsAfterSpawn == this->specialCreepSpawnFrequency)
 {
 for ( std::list<Creep*>::iterator sCreep = availableSpecialCreeps.begin(); sCreep != availableSpecialCreeps.end(); ++sCreep )
 {
 Creep *it = *sCreep;
 if(specElement == it->element)
 {
 //Creep units enter as new units (Copy)
 Creep *cP = new Creep(it->fileNameFormat.c_str(), it->GetHealthPoints() * (this->hpMultiplier * this->round), it->GetMovementSpeed() - (this->speedMultiplier * this->round));
 cP->setCoins(it->getCoins());
 
 rules.push_back(cP);
 }
 break;
 }
 this->roundsAfterSpawn = 0;
 }
 
 this->roundsAfterSpawn++;
 this->round++;
 
 return rules;
 }
 
*/


/*

std::list<Creep*> WaveRules::GetWaveCreeps()
{
    std::list<Creep*> rules;
 
    for ( std::list<Creep* const>::iterator creep = availableCreeps.begin(); creep != availableCreeps.end(); ++creep )
    {
        int i = 0, a = this->numOfStartingCreeps * this->numOfCreepsMultiplier * round;
        while (i < a)
        {
            Creep *it = *creep;
            //Creep units enter as new units (Copy)
            Creep *cP = new Creep(it->fileNameFormat.c_str(), it->GetHealthPoints() * (this->hpMultiplier * this->round), it->GetMovementSpeed() - (this->speedMultiplier * this->round));
            cP->setCoins(it->getCoins());
            
            //due to a specific implementation that does number of points * duration the movementspeed
            //coefficient has to be devided, yet by dividing the speed of movement of units radically increases
            //so subtraction is used to make the increase of speed smoother.
            
            rules.push_back(cP);
            i++;
        }
    }
    
    if ( this->isSpecialCreepSet() &&  this->roundsAfterSpawn == this->specialCreepSpawnFrequency)
    {
        for ( std::list<Creep*>::iterator sCreep = availableSpecialCreeps.begin(); sCreep != availableSpecialCreeps.end(); ++sCreep )
        {
            Creep *it = *sCreep;
            //Creep units enter as new units (Copy)
            Creep *cP = new Creep(it->fileNameFormat.c_str(), it->GetHealthPoints() * (this->hpMultiplier * this->round), it->GetMovementSpeed() - (this->speedMultiplier * this->round));
            cP->setCoins(it->getCoins());
            
            rules.push_back(cP);
        }
        this->roundsAfterSpawn = 0;
    }
    
    this->roundsAfterSpawn++;
    this->round++;
    
    return rules;
}

*/