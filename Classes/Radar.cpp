//
//  Radar.cpp
//  TowerDefense_new
//
//  Created by GEO on 16/08/2014.
//
//

#include "GameScene.h"

Radar::Radar(cocos2d::Layer & pGS, Point position)
{
    this->_pGs = &pGS;
    
    this->radarBg1 = Sprite::create("radarBG1.png");
    this->radarBg1->setPosition(position);
    
    GameScene* gs = (GameScene*) _pGs;

    gs->addChild(radarBg1);
    
    //populate the vector with the size of the mapinfo
    for ( int i = 0; i < (gs->getMapInfo()->GetTilesPerLine() * gs->getMapInfo()->GetTilesPerColumn()); i++ )
    {
        this->map.push_back(RadarMapNode::Nothing);
    }
    
    
}

Radar::~Radar()
{
    
}


void Radar::invalidate()
{
    GameScene* gs = (GameScene*) _pGs;

    /*
    for ( int i = 0; i < (gs->getMapInfo()->GetTilesPerLine() * gs->getMapInfo()->GetTilesPerColumn()); i++ )
    {
        this->map[i] = RadarMapNode::Nothing;
    }
    
    //the towers
    for ( std::list<Tower*>::iterator tower = gs->towerslist.begin(); tower != gs->towerslist.end(); ++tower )
    {
        Tower* t = *tower;
        this->map[ gs->getMapInfo()->ConvertPointToId(t->getPosition()) ] = RadarMapNode::Tower;
    }

    //the creeps
    for ( std::list<Enemy*>::iterator creep = gs->creepslist.begin(); creep != gs->creepslist.end(); ++creep )
    {
        Enemy* c = *creep;
        this->map[ gs->getMapInfo()->ConvertPointToId(c->getPosition()) ] = RadarMapNode::Creep;
    }
    
    this->radarBg1->removeAllChildrenWithCleanup(true);
    sprites.clear();
     
    
    this->radarBg1->removeAllChildrenWithCleanup(true);
    sprites.clear();
    
    //Sprite* s1 = Sprite::create("towerGreenDot1.png");
    //s1->setPosition(Point ( this->radarBg1->getPosition().x  ,  this->radarBg1->getPosition().y + 300) );
    //gs->addChild(s1);
    //s1->setPosition(Point( 300 , 300 ));
    //this->radarBg1->addChild(s1);
    
    //draw the dots
    for ( int k = 1; k < gs->getMapInfo()->GetTilesPerColumn(); k++ )
    {
        for ( int j = 1; j < gs->getMapInfo()->GetTilesPerLine(); j++ )
        {
            if(map.at(j*k) == RadarMapNode::Tower )
            {
                Sprite* s = Sprite::create("towerGreenDot1.png");
                s->setPosition( Point( j , k ) );
                this->radarBg1->addChild(s);
                sprites.push_back(s);
                std::cout << " tower green \n";
            }
            else if(map.at(j*k) == RadarMapNode::Creep )
            {
                Sprite* s = Sprite::create("creepRedDot1.png");
                s->setPosition( Point( j , k ) );
                this->radarBg1->addChild(s);
                sprites.push_back(s);
                std::cout << " creep red \n";
            }
        }
    }
    */
    
    //first clear any existing dots
    
}