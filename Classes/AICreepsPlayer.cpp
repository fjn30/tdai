//
//  AICreepsPlayer.cpp
//  TowerDefense_new
//
//  Created by Georgios Floros on 04/07/2014.
//
//

#include "GameScene.h"

AICreepsPlayer::AICreepsPlayer(cocos2d::Layer& sc, WaveRules* wr)
{
    this->_sc = &sc;
    
    this->waveRules = wr;
    
    //sets up the creeps for the wave
    this->waveRules->WaveRulesInit(this->_sc);
}

AICreepsPlayer::~AICreepsPlayer()
{
    free(waveRules);
}

void AICreepsPlayer::BeforeNextWave(void* args)
{
    GameScene* gs = (GameScene*) _sc;

    this->waveRules->BeforeNextWave(*gs, args);
}

void AICreepsPlayer::ReadyForNextWave()
{
    GameScene* gs = (GameScene*) _sc;
    //before next round
    this->waveRules->BeforeDeployment(*gs);
    gs->InitiateWave(waveRules);
}

void AICreepsPlayer::AfterDeployment()
{
    GameScene* gs = (GameScene*) _sc;
    this->waveRules->AfterDeployment(*gs);
}

void AICreepsPlayer::BeforeDeployment()
{
    GameScene* gs = (GameScene*) _sc;
    this->waveRules->BeforeDeployment(*gs);
}

void AICreepsPlayer::NotifyAIRecalculate()
{
    //if unit path to end point has a point inside tower, recalculate the astar
    GameScene* gs = (GameScene*) _sc;
    
    for ( std::list<Creep*>::iterator creep = gs->creepslist.begin(); creep != gs->creepslist.end(); ++creep )
    {
        Creep* it = *creep;
        it->invalidatePath();
    }
    
}

