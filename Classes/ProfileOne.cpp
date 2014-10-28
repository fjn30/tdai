//
//  Profile1.cpp
//  TowerDefense_new
//
//  Created by Georgios Floros on 24/08/2014.
//
//

#include "GameScene.h"

ProfileOne::ProfileOne() : WaveRules()
{
}

void ProfileOne::WaveRulesInit(void* args)
{
    this->elementIt = 0;

    ProfileId = "1";
    setCreepsHPMultiplier(5.50f);
    setCreepsSpeedMultiplier(0.0005f);
    setSpecialCreepHPMultiplier(5.5f);
    setNumOfCreepsStarting(10);
    setNumOfCreepsMultiplier(1);
    setNumOfCreepsToBeAddedPerWave(2);
    setMultiplyCreepNumbersPerRound(false);
    setSpecialCreepSpawnFrequency(4);
    double startingHp1 = 150.0f;
    double startingHp2 = 5000.0f;
    double startingSpd1 = 0.25f;
    double startingSpd2 = 0.4f;
    
    Creep * creep1 = new Creep("1creep_simpnone1.png", startingHp1, startingSpd1);
    creep1->setCoins(50);
    creep1->element = ElementalAffinity::None;
    this->addCreep(creep1);
    
    Creep * creep2 = new Creep("1creep_simpfire1.png", startingHp1, startingSpd1);
    creep2->setCoins(50);
    creep2->element = ElementalAffinity::Fire;
    this->addCreep(creep2);
    
    Creep * creep3 = new Creep("1creep_simpwater1.png", startingHp1, startingSpd1);
    creep3->setCoins(50);
    creep3->element = ElementalAffinity::Water;
    this->addCreep(creep3);
    
    Creep * creep4 = new Creep("1creep_simpearth1.png", startingHp1, startingSpd1);
    creep4->setCoins(50);
    creep4->element = ElementalAffinity::Earth;
    this->addCreep(creep4);
    
    Creep * creep5 = new Creep("1creep_simpshock1.png", startingHp1, startingSpd1);
    creep5->setCoins(50);
    creep5->element = ElementalAffinity::Shock;
    this->addCreep(creep5);
    
    Creep * specialCreep1 = new Creep("1creep_specnone1.png", startingHp2, startingSpd2);
    specialCreep1->setCoins(100);
    specialCreep1->element = ElementalAffinity::None;
    this->addSpecialCreep(specialCreep1);
    
    Creep * specialCreep2 = new Creep("1creep_specfire1.png", startingHp2, startingSpd2);
    specialCreep2->setCoins(100);
    specialCreep2->element = ElementalAffinity::Fire;
    this->addSpecialCreep(specialCreep2);
    
    Creep * specialCreep3 = new Creep("1creep_specwater1.png", startingHp2, startingSpd2);
    specialCreep3->setCoins(100);
    specialCreep3->element = ElementalAffinity::Water;
    this->addSpecialCreep(specialCreep3);
    
    Creep * specialCreep4 = new Creep("1creep_specearth1.png", startingHp2, startingSpd2);
    specialCreep4->setCoins(100);
    specialCreep4->element = ElementalAffinity::Earth;
    this->addSpecialCreep(specialCreep4);
    
    Creep * specialCreep5 = new Creep("1creep_specshock1.png", startingHp2, startingSpd2);
    specialCreep5->setCoins(100);
    specialCreep5->element = ElementalAffinity::Shock;
    this->addSpecialCreep(specialCreep5);
}

std::list<Creep*> ProfileOne::GetWaveCreeps()
{
    std::list<Creep*> rules;
    
    std::cout << " Profile 1 wave";
    
    if ( this->elementIt == 4 )
    {
        this->elementIt = 0;
    }
    
    while ( availableCreeps.size() > this->elementIt )
    {
        Creep *it = availableCreeps.at(this->elementIt);
        
        int a = 0;
        if(this->multiplyCreepNumbersPerRound == true) {
            a = (this->numOfStartingCreeps * this->numOfCreepsMultiplier * this->round) + this->numOfCreepsAddedPerWave;
        }
        else {
            a = (this->numOfStartingCreeps * this->numOfCreepsMultiplier) + (this->numOfCreepsAddedPerWave * this->round);
        }
            
        int i = 0;
        while (i < a)
        {
            //Creep units enter as new units (Copy)
            Creep *cP = new Creep(it->fileNameFormat.c_str(), it->GetHealthPoints() * (this->hpMultiplier * this->round), it->GetMovementSpeed() - (this->speedMultiplier * this->round));
            cP->setCoins(it->getCoins());
            cP->element = it->element;
                
            //due to a specific implementation that does number of points * duration the movementspeed
            //coefficient has to be devided, yet by dividing the speed of movement of units radically increases
            //so subtraction is used to make the increase of speed smoother.
                
            rules.push_back(cP);
            i++;
        }
        
        this->elementIt++;
        
        break;
        
    }
    
    if ( this->isSpecialCreepSet() &&  this->roundsAfterSpawn == this->specialCreepSpawnFrequency)
    {
        ElementalAffinity specElement = this->getRandomElement();

        if ( this->sElementIt == 4 )
        {
            this->sElementIt = 0;
        }
        
        while( this->availableSpecialCreeps.size() > this->sElementIt)
        {
            Creep *it = availableSpecialCreeps.at(this->sElementIt);
            
            //Creep units enter as new units (Copy)
            Creep *cP = new Creep(it->fileNameFormat.c_str(), it->GetHealthPoints() * (this->hpMultiplier * this->round), it->GetMovementSpeed() - (this->speedMultiplier * this->round));
            cP->setCoins(it->getCoins());
            cP->element = it->element;

            rules.push_back(cP);
            
            this->sElementIt++;
            break;
        }
        this->roundsAfterSpawn = 0;
    }
    
    this->roundsAfterSpawn++;
    this->round++;
    
    std::cout << "\n test size:  " << rules.size();
    
    return rules;
}