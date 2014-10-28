//
//  DeploymentGeneticAlgorithm.cpp
//  TD1
//
//  Created by Georgios Floros on 30/08/2014.
//
//

#include "GameScene.h"

GeneticAlgorithmProfile1::GeneticAlgorithmProfile1() : WaveRules()
{
    
}

void GeneticAlgorithmProfile1::WaveRulesInit(void* args)
{
    ////GA
    this->gaThreadData = new ThreadData();
    this->gaThreadData->_sc = ((cocos2d::Layer*)args);
    ////
    
    this->ProfileId = "3";
    
    for(int i = 0; i < CreepsPerRound; i++)
    {
        Creep * creep1 = new Creep("1creep_simpnone1.png", 850.0f, 0.25f);
        creep1->setCoins(50);
        creep1->element = ElementalAffinity::None;
        this->gaThreadData->creepsWaveForDeployment.push_back(creep1);
    }
    
}

void GeneticAlgorithmProfile1::BackUpState(cocos2d::Layer& _sc)
{
    GameScene* gs = (GameScene*) & _sc;
    ///////////////////////////////////////////////////////
    //backup everything related to the game state
    this->gamestateBK = gs->gameState;
    this->lifePointsBK = gs->playerHandler->GetLifePoints();
    this->currencyBK = gs->playerHandler->GetCurrency();
    this->playerNameBK = gs->playerHandler->GetPlayerName();
    this->creepSpawnDelayBK = gs->creepDeploymentDelay;
    this->nextWaveStartingDelayBK = gs->nextWaveStartingDelay;
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    //backup everything related to the wave state
    this->speedMultiplierBK = this->speedMultiplier;
    this->hpMultiplierBK = this->hpMultiplier;
    this->numOfStartingCreepsBK = this->numOfStartingCreeps;
    this->numOfCreepsMultiplierBK = this->numOfCreepsMultiplier;
    this->numOfCreepsAddedPerWaveBK = this->numOfCreepsAddedPerWave;
    this->specialCreepSetBK = this->specialCreepSet;
    this->specialCreepSpeedMultiplierBK = this->specialCreepSpeedMultiplier;
    this->specialCreepHPMultiplierBK = this->specialCreepHPMultiplier;
    this->specialCreepSpawnFrequencyBK = this->specialCreepSpawnFrequency;
    this->roundsAfterSpawnBK = this->roundsAfterSpawn;
    this->multiplyCreepNumbersPerRoundBK = this->multiplyCreepNumbersPerRound;
    this->roundBK = this->round;
    ///////////////////////////////////////////////////////
    //apply speed boost to creeps spawn delay timer
    gs->creepDeploymentDelay = gs->creepDeploymentDelay / speedBoost;
    //apply speed boost to next wave starting delay timer
    gs->nextWaveStartingDelay = gs->nextWaveStartingDelay / speedBoost;
    //apply speed boost to tower
    for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
    {
        Tower* t = *tower;
        t->SetInbetweenAttacksPeriod(t->GetInbetweenAttacksPeriod() / speedBoost);
    }
}

void GeneticAlgorithmProfile1::RestoreState(cocos2d::Layer& _sc)
{
    GameScene* gs = (GameScene*) & _sc;
    ///////////////////////////////////////////////////////
    //restore the gamestate
    gs->gameState = this->gamestateBK;
    gs->playerHandler->SetCurrency(this->currencyBK);
    gs->playerHandler->SetLifePoints(this->lifePointsBK);
    gs->playerHandler->SetPlayerName(this->playerNameBK);
    gs->creepDeploymentDelay = this->creepSpawnDelayBK;
    gs->nextWaveStartingDelay = this->nextWaveStartingDelayBK;
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    //restore the wave state
    this->speedMultiplier = this->speedMultiplierBK;
    this->hpMultiplier = this->hpMultiplierBK;
    this->numOfStartingCreeps = this->numOfStartingCreepsBK;
    this->numOfCreepsMultiplier = this->numOfCreepsMultiplierBK;
    this->numOfCreepsAddedPerWave = this->numOfCreepsAddedPerWaveBK;
    this->specialCreepSet = this->specialCreepSetBK;
    this->specialCreepSpeedMultiplier = this->specialCreepSpeedMultiplierBK;
    this->specialCreepHPMultiplier = this->specialCreepHPMultiplierBK;
    this->specialCreepSpawnFrequency = this->specialCreepSpawnFrequencyBK;
    this->roundsAfterSpawn = this->roundsAfterSpawnBK;
    this->multiplyCreepNumbersPerRound = this->multiplyCreepNumbersPerRoundBK;
    this->round = this->roundBK;
    ///////////////////////////////////////////////////////
    //remove speed boost of tower
    for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
    {
        Tower* t = *tower;
        t->SetInbetweenAttacksPeriod(t->GetInbetweenAttacksPeriod() * speedBoost);
    }
}

void GeneticAlgorithmProfile1::BeforeDeployment(cocos2d::Layer& _sc)
{
    GameScene* gs = (GameScene*) &_sc;
    
    if( this->gaThreadData->GetNonGARounds() > 0 && this->gaThreadData->IsGaEnabled() == false)
    {
        int tc = pthread_create(&threadsGA[0], NULL, &GeneticAlgorithmProfile1::Algorithm, this->gaThreadData);
        //wait until need simulating is enabled
        while(!this->gaThreadData->IsGaInitialized() && this->gaThreadData->GetNonGARounds() > 0)
        {
            sleep(1); // wait for ga initialisation
        }
    }
    
    if( this->gaThreadData->IsGaEnabled() == true)
    {
        while(!this->gaThreadData->IsSimulating() && this->gaThreadData->GetNonGARounds() > 0)
        {
            sleep(1); // wait for start simulation to start
        }
        
        if(this->gaThreadData->IsGaEnabled() == true)
        {
            this->BackUpState(_sc);
            gs->GetGUI()->SetGameAlert2("DEPLOYMENT GA SIMULATING : PLEASE WAIT!!!");
            gs->simulationMode = true;
        }
    }
    
}

void GeneticAlgorithmProfile1::AfterDeployment(cocos2d::Layer& _sc)
{
    GameScene* gs = (GameScene*) & _sc;
    if( this->gaThreadData->IsGaEnabled() == true)
    {
        
    }
}


void GeneticAlgorithmProfile1::BeforeNextWave(cocos2d::Layer& _sc, void* args)
{
    GameScene* gs = (GameScene*) & _sc;
    
    if( this->gaThreadData->IsGaEnabled() == true)
    {
        this->RestoreState(_sc);
        gs->GetGUI()->GameAlert2Toggle();
        gs->simulationMode = false;
        this->gaThreadData->SetSimulating(false);
        //set the results
        if(args != NULL)
        {
            this->gaThreadData->SetCurrentRoundScores(((CurrentRoundScores*) args)->creepsLeftFitness, ((CurrentRoundScores*) args)->creepsLeftPercFitness);
        }
    }
}



int GeneticAlgorithmProfile1::GetRandomNumber(std::vector<int>* availableNums)
{
    std::random_device rd;
    std::mt19937 randEng(rd());
    std::shuffle(availableNums->begin(), availableNums->end(), randEng);
    return availableNums->front();
}



std::vector<Chromosome*> GeneticAlgorithmProfile1::GeneratePopulation(int size, long addHP, long addMS)
{
    std::vector<Chromosome*> chromosomes;
    for(int i = 0; i < size; i++)   {
        Chromosome* chromosome = (Chromosome*) malloc( sizeof(Chromosome) );
        std::vector<int> availableElements;
        int j = 0;
        for(int k = 0; k < CreepsPerRound; k++) {
            if(j == CreepsPerRound / 2) {
                j = 0;
            }
            availableElements.push_back(j);
            j++;
        }
        long maxhp = MaxHealthPoints + addHP;
        long minhp = MinHealthPoints + addHP;
        long minms = MinCreepMovementSpeed - addMS;
        long maxms = MaxCreepMovementSpeed - addMS;
        for(int j = 0; j < CreepsPerRound; j++) {
            chromosome->healthPoints[j] = ( ((double)(std::rand() % maxhp + minhp)) );
            chromosome->movementSpeed[j] = ( ((double)(std::rand() % maxms + minms)) / 100.0f );
            chromosome->elementalAffinity[j] = GeneticAlgorithmProfile1::GetRandomNumber(&availableElements);
            for(int w = 0; w < availableElements.size(); w++)   {
                if(availableElements[w] == chromosome->elementalAffinity[j])    {
                    availableElements.erase(availableElements.begin() + (w));
                    break;
                }
            }
        }
        chromosomes.push_back(chromosome);
    }
    return chromosomes;
}

void GeneticAlgorithmProfile1::SetWaveForSimulation(ThreadData* td, AdditionalTowers* addTowerSettings, Chromosome *population)
{

    ///////////////////////////////////////
    
    GameScene* gs = ((GameScene*)td->_sc);
    
    //upgrade existing towers
    
    //apply new towers
    for ( std::vector<Tower*>::iterator tower = addTowerSettings->additionalTowers.begin(); tower != addTowerSettings->additionalTowers.end(); ++tower )
    {
        Tower* t = *tower;
        gs->towerslist.push_back(t);
        gs->getMapLayer()->addChild(t);
    }
    
    ///////////////////////////////////////
    
    td->creepsWaveForSimulation.clear();
    for(int j = 0; j < CreepsPerRound; j++)
    {
        Creep * creep;
        std::string s;
        double hp = population->healthPoints[j];
        double sp = population->movementSpeed[j] / speedBoost ;
        
        ElementalAffinity ef = (ElementalAffinity)population->elementalAffinity[j];
        switch (ef)
        {
            case Earth:
                s = "1creep_simpearth1.png";
                break;
            case Fire:
                s = "1creep_simpfire1.png";
                break;
            case Water:
                s = "1creep_simpwater1.png";
                break;
            case Shock:
                s = "1creep_simpshock1.png";
                break;
            case None:
                s = "1creep_simpnone1.png";
                break;
        }
        creep = new Creep(s, hp, sp);
        creep->setCoins(50);
        creep->element = ef;
        td->creepsWaveForSimulation.push_back(creep);
    }
}


void GeneticAlgorithmProfile1::SetWaveForDeployment(ThreadData* td, Chromosome *population)
{
    td->creepsWaveForDeployment.clear();
    for(int j = 0; j < CreepsPerRound; j++)
    {
        Creep * creep;
        std::string s;
        double hp = population->healthPoints[j];
        double sp = population->movementSpeed[j];
        ElementalAffinity ef = (ElementalAffinity)population->elementalAffinity[j];
        switch (ef)
        {
            case Earth:
                s = "1creep_simpearth1.png";
                break;
            case Fire:
                s = "1creep_simpfire1.png";
                break;
            case Water:
                s = "1creep_simpwater1.png";
                break;
            case Shock:
                s = "1creep_simpshock1.png";
                break;
            case None:
                s = "1creep_simpnone1.png";
                break;
        }
        creep = new Creep(s, hp, sp);
        creep->setCoins(50);
        creep->element = ef;
        td->creepsWaveForDeployment.push_back(creep);
    }
}

void GeneticAlgorithmProfile1::Mutate(ThreadData* td, std::vector<Chromosome*>* generation)
{
    int addHp = MinMutationAddHP * td->hpMutationImprovement;
    double addMs = MinMutationAddMS + td->msMutationImprovement;
    for( int k = 0; k < generation->size(); k++) {
        if(generation->at(k)->fitnessScore == 0) {
            for(int i = 0; i < CreepsPerRound; i++)
            {
                generation->at(k)->healthPoints[i] = generation->at(k)->healthPoints[i] + (addHp * 2);
                generation->at(k)->movementSpeed[i] = generation->at(k)->movementSpeed[i] - (addMs * 2);
                if( generation->at(k)->elementalAffinity[i] == (int)4 ) {
                    generation->at(k)->elementalAffinity[i] = 0;
                }
                else {
                    generation->at(k)->elementalAffinity[i]++;
                }
            }
        }
        else {
            std::vector<int> availableHPIndexes;
            std::vector<int> availableMSIndexes;
            std::vector<int> availableEleIndexes;
            for(int k = 0; k < CreepsPerRound; k++) {
                availableHPIndexes.push_back(k);
                availableMSIndexes.push_back(k);
                availableEleIndexes.push_back(k);
            }
            int hpRngIndexes[MinNumOfMutations + td->mutationRate];
            int msRngIndexes[MinNumOfMutations + td->mutationRate];
            int eleRngIndexes[MinNumOfMutations + td->mutationRate];
            for(int j = 0; j < (MinNumOfMutations + td->mutationRate); j++) {
                hpRngIndexes[j] = GeneticAlgorithmProfile1::GetRandomNumber(&availableHPIndexes);
                msRngIndexes[j] = GeneticAlgorithmProfile1::GetRandomNumber(&availableMSIndexes);
                eleRngIndexes[j] = GeneticAlgorithmProfile1::GetRandomNumber(&availableEleIndexes);
            }
            for(int u = 0; u < (MinNumOfMutations + td->mutationRate); u++) {
                generation->at(k)->healthPoints[hpRngIndexes[u]] = generation->at(k)->healthPoints[hpRngIndexes[u]] + addHp;
                generation->at(k)->movementSpeed[msRngIndexes[u]] = generation->at(k)->movementSpeed[msRngIndexes[u]] - addMs;
                if( generation->at(k)->elementalAffinity[eleRngIndexes[u]] == (int)4 ) {
                    generation->at(k)->elementalAffinity[eleRngIndexes[u]] = 0;
                }
                else {
                    generation->at(k)->elementalAffinity[eleRngIndexes[u]]++;
                }
            }
        }
    }
}


void GeneticAlgorithmProfile1::Crossover(ThreadData* td, Chromosome* parent1, Chromosome* parent2)
{
    for ( int j = 0; j < CreepsPerRound; j ++)
    {
        int ea1 = parent1->elementalAffinity[j];
        int ea2 = parent2->elementalAffinity[j];
        parent1->elementalAffinity[j] = ea2;
        parent2->elementalAffinity[j] = ea1;
    }
}

void GeneticAlgorithmProfile1::SimulationForward(ThreadData* td, AdditionalTowers& at)
{
    GameScene* gs = ((GameScene*)td->_sc);
    
    std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@";
    std::cout << "\nADDITIONAL TOWERS DBG";
    
    td->bkCurrency = gs->playerHandler->GetCurrency();
    
    std::cout << "\nplayerMoney : " << gs->playerHandler->GetCurrency();
    
    //AI -> forward
    for ( int i = 0; i < 20; i++ )
    {
        //FIRST CASE : enough money for placing tower and upgrading it to an element
        if(gs->playerHandler->GetCurrency() >= (50 + 500))
        {
            Tower* n1 = new Tower(*gs, Settings::towerTexture, ((GameScene*)td->_sc)->playerHandler->tw);
            n1->setPosition(gs->getMapInfo()->GetRandomPointMidByType(MapInfoType::SimTowerPlace));
            
            n1->SetHitPositions(gs->getMapInfo());
            n1->SetStartingStats(Settings::towerAttackRange, Settings::towerAttackPoints, Settings::towerInbetweenAttacksPeriod, Settings::towerCost);
            
            at.additionalTowers.push_back(n1);
            
            gs->playerHandler->RemoveCoins(Settings::towerCost);
            
            
            if(gs->playerHandler->GetCurrency() >= 500) //element can be upgraded
            {
                int numOfFire, numOfWater, numOfEarth, numOfShock = 0;
                for(int a = 0; a < at.additionalTowers.size(); a++ )
                {
                    if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Fire)
                    {
                        numOfFire++;
                    }
                    else if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Water)
                    {
                        numOfWater++;
                    }
                    else if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Earth)
                    {
                        numOfEarth++;
                    }
                    else if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Shock)
                    {
                        numOfShock++;
                    }
                }
                for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
                {
                    Tower* t = *tower;
                    if(t->GetElement() == ElementalAffinity::Fire)
                    {
                        numOfFire++;
                    }
                    else if(t->GetElement() == ElementalAffinity::Water)
                    {
                        numOfWater++;
                    }
                    else if(t->GetElement() == ElementalAffinity::Earth)
                    {
                        numOfEarth++;
                    }
                    else if(t->GetElement() == ElementalAffinity::Shock)
                    {
                        numOfShock++;
                    }
                }
                
                
                if(numOfEarth < numOfFire && numOfEarth < numOfWater && numOfEarth < numOfShock)
                {
                    if(n1->UpgradeToEarth(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                    
                }
                else if(numOfFire < numOfEarth && numOfFire < numOfWater && numOfFire < numOfShock)
                {
                    if(n1->UpgradeToFire(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                }
                else if(numOfWater < numOfFire && numOfWater < numOfEarth && numOfWater < numOfShock)
                {
                    if(n1->UpgradeToWater(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                    
                }
                else if(numOfShock < numOfFire && numOfShock < numOfWater && numOfShock < numOfEarth)
                {
                    if(n1->UpgradeToShock(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
        /////////////////////////////////////////
        
        //SECOND CASE : upgrade an existing tower, priortize element upgrades
        if(gs->playerHandler->GetCurrency() >= 500)
        {
            int numOfFire, numOfWater, numOfEarth, numOfShock = 0;
            for(int a = 0; a < at.additionalTowers.size(); a++ )
            {
                if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Fire)
                {
                    numOfFire++;
                }
                else if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Water)
                {
                    numOfWater++;
                }
                else if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Earth)
                {
                    numOfEarth++;
                }
                else if(at.additionalTowers[a]->GetElement() == ElementalAffinity::Shock)
                {
                    numOfShock++;
                }
            }
            for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
            {
                Tower* t = *tower;
                if(t->GetElement() == ElementalAffinity::Fire)
                {
                    numOfFire++;
                }
                else if(t->GetElement() == ElementalAffinity::Water)
                {
                    numOfWater++;
                }
                else if(t->GetElement() == ElementalAffinity::Earth)
                {
                    numOfEarth++;
                }
                else if(t->GetElement() == ElementalAffinity::Shock)
                {
                    numOfShock++;
                }
            }
            
            
            for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
            {
                Tower* n1 = *tower;
                
                if(numOfEarth < numOfFire && numOfEarth < numOfWater && numOfEarth < numOfShock)
                {
                    if(n1->UpgradeToEarth(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                    
                }
                else if(numOfFire < numOfEarth && numOfFire < numOfWater && numOfFire < numOfShock)
                {
                    if(n1->UpgradeToFire(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                }
                else if(numOfWater < numOfFire && numOfWater < numOfEarth && numOfWater < numOfShock)
                {
                    if(n1->UpgradeToWater(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                    
                }
                else if(numOfShock < numOfFire && numOfShock < numOfWater && numOfShock < numOfEarth)
                {
                    if(n1->UpgradeToShock(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetEarthUpgradeCost());
                        //now upgrade atk spd
                        while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                               gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                        {
                            
                            if(n1->UpgradeAttackPower(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                            }
                            
                            if(n1->UpgradeAttackSpeed(gs->playerHandler))
                            {
                                gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                            }
                        }
                        
                    }
                    
                }
                
            }
        }
        
        // THIRD CASE : additional upgrades , attack power and speed
        for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
        {
            Tower* n1 = *tower;
            
            if(n1->GetElement() > 0) //not worth it with out element
            {
                
                while ( gs->playerHandler->GetCurrency() >= n1->toweRules->GetAttackUpgradeCost(*n1) ||
                       gs->playerHandler->GetCurrency() >= n1->toweRules->GetSpeedUpgradeCost(*n1) )
                {
                    
                    if(n1->UpgradeAttackPower(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetAttackUpgradeCost(*n1));
                    }
                    
                    if(n1->UpgradeAttackSpeed(gs->playerHandler))
                    {
                        gs->playerHandler->RemoveCoins(n1->toweRules->GetSpeedUpgradeCost(*n1));
                    }
                }
                
            }
            
        }
    }
    
    gs->playerHandler->SetCurrency(td->bkCurrency);
    
    std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@";

}

void GeneticAlgorithmProfile1::SimulationForwardBackUp(ThreadData* td, AdditionalTowers& at)
{
    GameScene* gs = ((GameScene*)td->_sc);

    //backup tower states
    td->towerStates.clear();
    for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
    {
        Tower* t = *tower;
        ThreadData::TStates ts;
        ts.damage = t->attackPoints;
        ts.speed = t->inbetweenAttacksPeriod;
        ts.attackUpgradesDone = t->GetAttackUpgradesDone();
        ts.speedUpgradesDone = t->GetSpeedUpgradesDone();
        std::pair<Tower*, ThreadData::TStates> p;
        p.first = t;
        p.second = ts;
        td->towerStates.insert(p);
        
    }

}

void GeneticAlgorithmProfile1::SimulationForwardRestore(ThreadData* td, AdditionalTowers& at)
{
    GameScene* gs = ((GameScene*)td->_sc);

    //restore tower states
    for ( std::map<Tower*, ThreadData::TStates>::iterator pair = td->towerStates.begin(); pair != td->towerStates.end(); ++pair )
    {
        Tower* t = pair->first;
        ThreadData::TStates tstates = pair->second;
        t->attackPoints = tstates.damage;
        t->inbetweenAttacksPeriod = tstates.speed;
        t->attackUpgradesDone = tstates.attackUpgradesDone;
        t->speedUpgradesDone = tstates.speedUpgradesDone;
    }

}

void GeneticAlgorithmProfile1::CalculateFitness(ThreadData* td, Chromosome *population)
{
    GameScene* gs = ((GameScene*)td->_sc);
    AdditionalTowers at;
    GeneticAlgorithmProfile1::SimulationForwardBackUp(td, at);
    GeneticAlgorithmProfile1::SimulationForward(td, at);
    GeneticAlgorithmProfile1::SetWaveForSimulation(td, &at, population);
    td->SetSimulating(true);
    while ( td->IsSimulating() == true ) {
        sleep(1);
    }
    CurrentRoundScores crs = td->GetCurrentRoundScores();
    population->fitnessScore = crs.creepsLeftFitness;
    population->fitnessHPPercentage = crs.creepsLeftPercFitness;
    
    GeneticAlgorithmProfile1::SimulationForwardRestore(td, at);
    int siz = at.additionalTowers.size();
    for(int i = 0; i < siz; i++ )
    {
        gs->getMapLayer()->removeChild(at.additionalTowers[i], true);
        gs->towerslist.pop_back();
    }
    GeneticAlgorithmProfile1::RatesEvaluation(td);
}

void GeneticAlgorithmProfile1::RatesEvaluation(ThreadData *td)
{
    if (td->previouslyPlayedFitness <= 1)
    {
        td->mutationRate = 9;
        td->hpMutationImprovement = 10 / td->difficultyLevel;
        td->msMutationImprovement = 0.004 / td->difficultyLevel;
        td->crossoverRate = 0;
    }
    else if (td->previouslyPlayedFitness <= 4)
    {
        td->mutationRate = 6;
        td->hpMutationImprovement = 6 / td->difficultyLevel;
        td->msMutationImprovement = 0.003 / td->difficultyLevel;
        td->crossoverRate = 0;
    }
    else if (td->previouslyPlayedFitness <= 6)
    {
        td->mutationRate = 2;
        td->hpMutationImprovement = 4 / td->difficultyLevel;
        td->msMutationImprovement = 0.002 / td->difficultyLevel;
        td->crossoverRate = 100;
    }
    else if (td->previouslyPlayedFitness <= 8)
    {
        td->mutationRate = 1;
        td->hpMutationImprovement = 2 / td->difficultyLevel;
        td->msMutationImprovement = 0.001 / td->difficultyLevel;
        td->crossoverRate = 100;
    }
}

//not completed, TODO
void GeneticAlgorithmProfile1::DiagnoseLackOfGeneticDiversity(ThreadData* td, std::vector<Chromosome*>* gen)
{
    
    //number of same elements.
    int numberOfNeutralElements = 0, numberOfFireElements = 0, numberOfEarthElements = 0,
    numberOfShockElements = 0, numberOfWaterElements = 0;
    
}


void* GeneticAlgorithmProfile1::Algorithm( void* arg )
{
    srand (static_cast <unsigned> (time(0)));
    ThreadData* td = (ThreadData*)arg;
    if( td->first && td->generation.size() == 0 ) {
        td->generation = GeneticAlgorithmProfile1::GeneratePopulation(MaxChromosomesPopulationSize, 0, 0);
    }
    td->SetSimulating(false);
    td->SetGaInitialized(true);
    td->SetGaEnabled(true);
    if( td->first && td->generation.size() > 0 ) {
        for(int i = 0; i < td->generation.size(); i++) {
            GeneticAlgorithmProfile1::CalculateFitness(td, td->generation.at(i));
        }
        std::sort (td->generation.begin(), td->generation.end(), [](Chromosome * a, Chromosome * b) {
            if (b->fitnessScore == a->fitnessScore) { return b->fitnessHPPercentage < a->fitnessHPPercentage; }
            return b->fitnessScore < a->fitnessScore; });
        td->first = false;
    }

    //DBG - LOG
    std::cout << "\n\n LOG - Generation : INITIAL POP " << " START ";
    for(int k = 0; k < td->generation.size(); k++) {
        std::cout << "\n Chromosome : " << k << " fitness score : " << td->generation.at(k)->fitnessScore;
    }
    std::cout << "\n ---END--- ";
    
    for(int i = 0; i < MaxGenerations; i++) {
        
        std::cout << "\n START OF NEW GENERATION\n";
        
        td->previouslyPlayedFitness = td->generation.at(0)->fitnessScore;
        Chromosome* elite =(Chromosome*) malloc(sizeof(Chromosome));
        for ( int j = 0; j < CreepsPerRound; j ++) {
            elite->healthPoints[j] = td->generation.at(0)->healthPoints[j];
            elite->movementSpeed[j] = td->generation.at(0)->movementSpeed[j];
            elite->elementalAffinity[j] = td->generation.at(0)->elementalAffinity[j];
            elite->fitnessScore = td->generation.at(0)->fitnessScore;
        }
        Chromosome* parent1;
        Chromosome* parent2;
        if(td->crossoverRate == 100) {
            int totalFitness = 0;
            std::vector<double> result(td->generation.size());
            for(int x = 0; x < td->generation.size(); x++) {
                totalFitness =  totalFitness + td->generation.at(x)->fitnessScore;
            }
            for(int p = 0; p < td->generation.size(); p++) {
                result[p] = (((double)td->generation.at(p)->fitnessScore) / ((double)totalFitness)) * 100;
            }
            bool firstSelected = false;
            bool secondSelected = false;
            for(int l = 0 ; l < result.size() ; l++) {
                float roll = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100.0f));
                if( roll <= result.at(l) ) {
                    if(!firstSelected) {
                        parent1 = td->generation.at(l);
                        firstSelected = true;
                    }
                    else if(!secondSelected) {
                        parent2 = td->generation.at(l);
                        secondSelected = true;
                    }
                }
                if(firstSelected && secondSelected) {
                    break;
                }
                else {
                    if( l == result.size()-1 ) {
                        l = 0;
                    }
                }
            }
            GeneticAlgorithmProfile1::Crossover(td, parent1, parent2);
        }
        td->generation.pop_back();
        GeneticAlgorithmProfile1::Mutate(td, &td->generation);
        td->generation.push_back(elite);
        for(int k = 0; k < td->generation.size(); k++) {
            Chromosome* c = td->generation.at(k);
            GeneticAlgorithmProfile1::CalculateFitness(td, c);
        }
        std::sort (td->generation.begin(), td->generation.end(), [](Chromosome * a, Chromosome * b) {
                       if (b->fitnessScore == a->fitnessScore) { return b->fitnessHPPercentage < a->fitnessHPPercentage; }
                       return b->fitnessScore < a->fitnessScore; });
    
        //DBG - LOG
        std::cout << "\n\n LOG - Generation : " << i << " START ";
        for(int k = 0; k < td->generation.size(); k++) {
            std::cout << "\n Chromosome : " << k << " fitness score : " << td->generation.at(k)->fitnessScore;
        }
        std::cout << "\n ---END--- ";
        std::cout << "\n\n GENS PAST " << i;
    
        if ( td->generation.at(0)->fitnessScore == MinAcceptableFitness ) { break; }
    
    }

    std::cout << " \n DEPLOYMENT SETTING --- FITNESS : " << td->generation.at(0)->fitnessScore;
    
    GeneticAlgorithmProfile1::SetWaveForDeployment(td, td->generation.at(0));
    td->SetGaInitialized(false);
    td->SetGaEnabled(false);
    td->SetNonGARounds(0);
    return 0;
}


std::list<Creep*> GeneticAlgorithmProfile1::GetWaveCreeps()
{
    std::list<Creep*> rules;
    std::cout << "\n Profile 3 wave (GENETIC ALGORITHM) ";

    if( this->gaThreadData->IsSimulating() )
    {
        std::cout << "\n SIMULATION DEPLOYMENT : SIZE : " << this->gaThreadData->creepsWaveForSimulation.size() << "";
        for ( std::vector<Creep*>::iterator creep = this->gaThreadData->creepsWaveForSimulation.begin(); creep != this->gaThreadData->creepsWaveForSimulation.end(); ++creep )
        {
            Creep *it = *creep;
            rules.push_back(it);
        }
    }
    else
    {
        std::cout << "\n NON SIMULATION DEPLOYMENT ROUND : " << this->round << "";
        for ( std::vector<Creep*>::iterator creep = this->gaThreadData->creepsWaveForDeployment.begin(); creep != this->gaThreadData->creepsWaveForDeployment.end(); ++creep )
        {
            Creep *it = *creep;
            rules.push_back(it);
        }
        this->gaThreadData->IncrementNonGARoudnds();
    }
    
    this->roundsAfterSpawn++;
    this->round++;
    return rules;

}

