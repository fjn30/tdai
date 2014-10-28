
//
//  GameScene.h
//  Tower Defense
//
//  Created by Georgios Floros on 19/06/2014.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <iostream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <random>

#include "cocos2d.h"

#include "StackTrace.h"

#include "Utils.h"
#include "ElementalAffinity.h"
#include "MapGeneral.h"
#include "MapPath.h"
#include "MapInfo.h"
#include "Movement.h"
#include "Unit.h"
#include "Creep.h"
#include "WaveRulesInterface.h"
#include "WaveRules.h"
#include "TowerRules.h"
#include "Tower.h"
#include "Player.h"
#include "InfluenceMap.h"
#include "ProfileOne.h"
#include "ProfileTwo.h"
#include "AICreepsPlayer.h"
#include "ElementalAffinity.h"
#include "MapType.h"
#include "AIStatus.h"
#include "GameState.h"
#include "GUI.h"
#include "Radar.h"
#include "SessionStats.h"

#include "GeneticAlgorithmProfile1.h"

#include "MainMenu.h"
#include "AppDelegate.h"

#include "Settings.h"


class GameScene : public cocos2d::Layer
{
    public:

    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    
	#ifdef defined(_WIN32) || defined(WIN32)
	StackTrace stackTrace;
	#endif

    CurrentRoundScores gaScores;
    
    bool simulationMode;
    
    bool gameEnded;
    bool gamePaused;
    MapType mapType;
    bool imEnabled;
    WaveRulesInterface* waveRules;
    
    SessionStats currSessionStats;
    
    AIStatus* _aiStatus;
    AIStatus* GetAiStatus();
    
    //static pthread_mutex_t mutex;
        
    //delays
    double creepDeploymentDelay;
    double nextWaveStartingDelay;
    
    Layer* getMapLayer();
    MapInfo* getMapInfo();
    TMXTiledMap* getTiledMap();
    InfluenceMap* getInfluenceMap();
    
    GUI* GetGUI();
    
    //general game rules
    GameState gameState;
    
    //wave & creeps
    //start
    void InitiateWave(WaveRulesInterface* wv);
    void nextWave(Ref* ref);
    
    std::list<Tower*> towerslist;
    void InsertTower(Tower* t);
    void DeleteTower(Tower* t);
    
    std::list<Creep*> creepslist;
    void InsertCreep(Creep* e);
    void DeleteCreep(Creep* e);
    
    void SpawnCreep(Ref *cP);
    //end
    
    void BackToMainMenu();
    
    Player* playerHandler;
    AICreepsPlayer* aiPlayerHandler;
    
    
    private:
    bool firstRun;
    
    virtual bool init();
    
    bool browserOpened;
    
    //map data
    MapInfo* _mapInfo;
    Layer* _mapLayer;
    TMXTiledMap* _map;
    InfluenceMap* _im;
    
    //the main loop of the scene
    void update(float delta);
    
    GUI* gui;
    
    //next wave is starting message
    Label* announcements;
    
};


#endif
