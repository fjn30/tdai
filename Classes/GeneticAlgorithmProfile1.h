//
//  DeploymentGeneticAlgorithm.h
//  TD1
//
//  Created by Georgios Floros on 30/08/2014.
//
//

#ifndef __TD1__DeploymentGeneticAlgorithm__
#define __TD1__DeploymentGeneticAlgorithm__


#include "GameScene.h"
#include <pthread.h>


#define MaxChromosomesPopulationSize    10
#define MinCreepMovementSpeed           25
#define MaxCreepMovementSpeed           30
#define MaxHealthPoints                 800
#define MinHealthPoints                 600
#define MaxElementalAffinity            4
#define CreepsPerRound                  10
#define GA1TimeOut                      5000
#define speedBoost                      15.5f
#define MaxGenerations                  10
#define MinNumOfMutations               1
#define MinMutationAddHP                70
#define MinMutationAddMS                0.005
#define MinAcceptableFitness            5

struct CurrentRoundScores
{
    int creepsLeftPercFitness;
    int creepsLeftFitness;
};

struct AdditionalTowers
{
    std::vector<Tower*> additionalTowers;
};

struct Chromosome
{
    double healthPoints[CreepsPerRound];
    double movementSpeed[CreepsPerRound];
    int elementalAffinity[CreepsPerRound];
    
    int fitnessScore;
    double fitnessHPPercentage;
};

class ThreadData
{
    private:
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    CurrentRoundScores pendingRoundScores;
    bool gaInitialized;
    bool isSimulating;
    bool startSimulation;
    int nonGARounds;
    bool gaEnabled;
    
    public:
    
    int crossoverRate;
    int mutationRate;
    int hpMutationImprovement = 1;
    double msMutationImprovement = 0.0f;
    int previouslyPlayedFitness = 0;
    int difficultyLevel = 1;

    
    ///////////////////
    int bkCurrency = 0;    
    struct TStates{
        int attackUpgradesDone;
        int speedUpgradesDone;
        double damage;
        double speed;
    };
    std::map<Tower*,TStates> towerStates;
    //////////////////
    
    cocos2d::Layer* _sc;

    
    //generations
    std::vector<Chromosome*> generation;
    bool first;
    /////////////
    
    std::vector<Creep*> creepsWaveForSimulation;
    std::vector<Creep*> creepsWaveForDeployment;
    
    int GetNonGARounds() {
        int res;
        pthread_mutex_lock(&mutex);
        res = this->nonGARounds;
        pthread_mutex_unlock(&mutex);
        return res;
    }
    void SetNonGARounds(int b) {
        pthread_mutex_lock(&mutex);
        this->nonGARounds = b;
        pthread_mutex_unlock(&mutex);
    }
    void IncrementNonGARoudnds() {
        pthread_mutex_lock(&mutex);
        this->nonGARounds++;
        pthread_mutex_unlock(&mutex);
    }
    
    bool IsGaEnabled() {
        bool res;
        pthread_mutex_lock(&mutex);
        res = this->gaEnabled;
        pthread_mutex_unlock(&mutex);
        return res;
    }
    void SetGaEnabled(bool b) {
        pthread_mutex_lock(&mutex);
        this->gaEnabled = b;
        pthread_mutex_unlock(&mutex);
    }
    
    bool IsSimulationStarted() {
        bool res;
        pthread_mutex_lock(&mutex);
        res = this->startSimulation;
        pthread_mutex_unlock(&mutex);
        return res;
    }
    void SetSimulationStarted(bool b) {
        pthread_mutex_lock(&mutex);
        this->startSimulation = b;
        pthread_mutex_unlock(&mutex);
    }
    
    bool IsSimulating() {
        bool res;
        pthread_mutex_lock(&mutex);
        res = this->isSimulating;
        pthread_mutex_unlock(&mutex);
        return res;
    }
    void SetSimulating(bool b) {
        pthread_mutex_lock(&mutex);
        this->isSimulating = b;
        pthread_mutex_unlock(&mutex);
    }

    bool IsGaInitialized() {
        bool res;
        pthread_mutex_lock(&mutex);
        res = this->gaInitialized;
        pthread_mutex_unlock(&mutex);
        return res;
    }
    void SetGaInitialized(bool b) {
        pthread_mutex_lock(&mutex);
        this->gaInitialized = b;
        pthread_mutex_unlock(&mutex);
    }
    
    CurrentRoundScores GetCurrentRoundScores() {
        CurrentRoundScores csr;
        pthread_mutex_lock(&mutex);
        csr.creepsLeftFitness = this->pendingRoundScores.creepsLeftFitness;
        csr.creepsLeftPercFitness = this->pendingRoundScores.creepsLeftPercFitness;
        pthread_mutex_unlock(&mutex);
        return csr;
    }
    
    void SetCurrentRoundScores(int _numberOfCreepsLeft, int _creepsHPPerc) {
        pthread_mutex_lock(&mutex);
        this->pendingRoundScores.creepsLeftFitness = _numberOfCreepsLeft;
        this->pendingRoundScores.creepsLeftPercFitness = _creepsHPPerc;
        std::cout << "\n NUMBERCREEPSLEFT : " << _numberOfCreepsLeft << " - HPPERC : " << _creepsHPPerc;
        pthread_mutex_unlock(&mutex);
    }
    
    ThreadData()
    {
        this->nonGARounds = 0;
        this->gaEnabled = false;
        this->startSimulation = false;
        this->isSimulating = false;
        this->gaInitialized = false;
        this->first = true;
    }
    
};


struct SelectionPair
{
    Chromosome* parent1;
    Chromosome* parent2;
};


class GeneticAlgorithmProfile1 : public WaveRules
{
    public:
    GeneticAlgorithmProfile1();
    void WaveRulesInit(void* args);
    void BeforeNextWave(cocos2d::Layer& _sc, void* args);
    void BeforeDeployment(cocos2d::Layer& _sc);
    void AfterDeployment(cocos2d::Layer& _sc);
    void RestoreState(cocos2d::Layer& _sc);
    void BackUpState(cocos2d::Layer& _sc);
    
    std::list<Creep*> GetWaveCreeps();
    
    private:
    
    //GENETIC ALGORITHM RELATED
    /********************************************/
    
    //creeps GA
    pthread_t threadsGA[2];
    ThreadData* gaThreadData;
    
    //gets a random integer and applies an exclusion list
    static int GetRandomNumber(std::vector<int>* availableNums);
    
    //randomly generates a population
    static std::vector<Chromosome*> GeneratePopulation(int size, long addHP, long addMS);
        
    static void* Algorithm( void *ptr ); //runs from different threads
    
    static void CalculateFitness(ThreadData* td, Chromosome* population);
    static void Mutate(ThreadData* td, std::vector<Chromosome*>* gen);
    static void Crossover(ThreadData* td, Chromosome* parent1, Chromosome* parent2);
    
    static void DiagnoseLackOfGeneticDiversity(ThreadData* td, std::vector<Chromosome*>* gen);
    static void RatesEvaluation(ThreadData* td);
    
    static void SetWaveForSimulation(ThreadData* td, AdditionalTowers* addT, Chromosome* population);
    static void SetWaveForDeployment(ThreadData* td, Chromosome* population);

    static void SimulationForward(ThreadData* td, AdditionalTowers& at);
    static void SimulationForwardRestore(ThreadData* td, AdditionalTowers& at);
    static void SimulationForwardBackUp(ThreadData* td, AdditionalTowers& at);
    
    /********************************************/
    
    ////////////////////////////
    /* back up gamestate vars */
    GameState gamestateBK;
    int lifePointsBK;
    int currencyBK;
    std::string playerNameBK;
    double creepSpawnDelayBK;
    double nextWaveStartingDelayBK;
    ////////////////////////////
    
    ////////////////////////////
    /* back up wave vars */
    double speedMultiplierBK;
    double hpMultiplierBK;
    int numOfStartingCreepsBK;
    int numOfCreepsMultiplierBK;
    int numOfCreepsAddedPerWaveBK;
    bool specialCreepSetBK;
    double specialCreepSpeedMultiplierBK;
    double specialCreepHPMultiplierBK;
    int specialCreepSpawnFrequencyBK;
    int roundsAfterSpawnBK;
    bool multiplyCreepNumbersPerRoundBK;
    int roundBK;
    ////////////////////////////
    
    
};

#endif