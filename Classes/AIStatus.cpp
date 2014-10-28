//
//  AIStatus.cpp
//  TowerDefense_new
//
//  Created by GEO on 02/08/2014.
//
//

#include "GameScene.h"


AIStatus::AIStatus(cocos2d::Layer & pGS)
{
    this->_pGs = &pGS;
    this->enabled = false;
}

AIStatus::~AIStatus()
{
    this->envNodes.clear();
    this->imNodes.clear();
}

void AIStatus::ClearIM()
{
    if(this->enabled == true)
    {
        GameScene* sc = (GameScene*) this->_pGs;
        //delete existing labels and sprites first
        for( std::pair<Label*, Sprite*> p : this->imNodes )
        {
            //remove label
            sc->getMapLayer()->removeChild(p.first);
            sc->getMapLayer()->removeChild(p.second);
        }
        this->imNodes.clear();
    }
}

void AIStatus::IMDraw()
{
    if(this->enabled == true)
    {
        GameScene* sc = (GameScene*) this->_pGs;
        //im cost numbers
        for(std::map<int, InfluenceMapNode>::iterator node = sc->getInfluenceMap()->getMap()->begin(); node != sc->getInfluenceMap()->getMap()->end(); ++node)
        {
            if(((InfluenceMapNode)node->second).cost > -1)
            {
                std::stringstream ss1;
                ss1 << ((InfluenceMapNode)node->second).cost; //+ ((InfluenceMapNode)node->second).pTower->GetStrength() ;
                Label * lbl = Label::create(ss1.str(), "Arial", 12, CCSizeMake(sc->getTiledMap()->getTileSize().width, sc->getTiledMap()->getTileSize().height), kCCTextAlignmentCenter);
                lbl->setPosition(sc->getMapInfo()->ConvertIdToPoint(node->first));
            
                Rect r = lbl->getBoundingBox();
                Sprite * spr = Sprite::create("sprite_Blue_10x10.png", r);
                spr->setPosition(sc->getMapInfo()->ConvertIdToPoint(node->first));
                spr->setOpacityModifyRGB(true);
                spr->setOpacity( 80 + (((InfluenceMapNode)node->second).cost / 10) );
            
                sc->getMapLayer()->addChild(spr);
                sc->getMapLayer()->addChild(lbl);
            
                //add it to the local pointers holder
                std::pair< Label*, Sprite* > p;
                p.first = lbl;
                p.second = spr;
                this->imNodes.insert(p);
            }
        }
    }
}

void AIStatus::ClearEnvironment()
{
    GameScene* sc = (GameScene*) this->_pGs;
    
    //delete existing labels and sprites first
    for( std::pair<Label*, Sprite*> p : this->envNodes )
    {
        //remove label
        sc->getMapLayer()->removeChild(p.first);
    }
    
    this->envNodes.clear();
}


void AIStatus::DrawRoads()
{
    GameScene* sc = (GameScene*) this->_pGs;

    if(this->enabled == true)
    {
        //draw all roads
        ValueVector idd = sc->getMapInfo()->GetMapInfoTypeVec(MapInfoType::Road);
        for (auto& index: idd) {
            Label * lbl = Label::create("R", "Arial", 12, CCSizeMake(sc->getTiledMap()->getTileSize().width, sc->getTiledMap()->getTileSize().height), kCCTextAlignmentCenter);
            lbl->setPosition(sc->getMapInfo()->ConvertIdToPoint(index.asInt()));
            sc->getMapLayer()->addChild(lbl);
        
            std::pair < Label*, Sprite* > p;
            p.first = lbl;
            this->envNodes.insert(p);
        }
    }
}

void AIStatus::DrawEnvironment()
{
    GameScene* sc = (GameScene*) this->_pGs;
    
    if(this->enabled == true)
    {
        //DEBUG ONLY DRAW tower
        ValueVector ids = sc->getMapInfo()->GetMapInfoTypeVec(MapInfoType::Tower);
        for (auto& index: ids) {
            Label * lbl = Label::create("T", "Arial", 12, CCSizeMake(sc->getTiledMap()->getTileSize().width, sc->getTiledMap()->getTileSize().height), kCCTextAlignmentCenter);
            lbl->setPosition(sc->getMapInfo()->ConvertIdToPoint(index.asInt()));
            sc->getMapLayer()->addChild(lbl);
     
            std::pair < Label*, Sprite* > p;
            p.first = lbl;
            this->envNodes.insert(p);
        }

    }
    
}