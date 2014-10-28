//
//  InfluenceMap.cpp
//  TowerDefense_new
//
//  Created by Georgios Floros on 28/07/2014.
//
//

#include "GameScene.h"

InfluenceMap::InfluenceMap(MapInfo* mapInfo, std::list<Tower*>* towers)
{
    this->mapInfo = mapInfo;
    this->towers = towers;
    
    //populate vector
    for ( int i =0 ; i < (this->mapInfo->GetTilesPerLine() * this->mapInfo->GetTilesPerColumn()); i++)
    {
        std::pair < int , InfluenceMapNode > p;
        p.first = i;
        InfluenceMapNode node;
        node.cost = -1;
        p.second = node;
        this->map.insert(p);
    }
    
}

InfluenceMap::~InfluenceMap()
{
    
}

void InfluenceMap::RemoveAllInfluences()
{
    for( int i = 0; i < this->mapInfo->getMapGridSize().width * this->mapInfo->getMapGridSize().height; i++)
    {
        this->map[i].cost = -1;
    }
}

int InfluenceMap::calculateCost(int mapId, int decayLevel, int distance, int strength)
{
    if( mapId <= 0 ||mapId >=
       this->mapInfo->GetTilesPerLine() * this->mapInfo->GetTilesPerColumn() ) {
        return 0;
    }
    int decayCost = (distance - decayLevel) + strength;
    InfluenceMapNode* node = this->GetNode(mapId);
    if(node->cost < 0) {
        if( this->mapInfo->TypeAtId(mapId) == MapInfoType::Planes ) {
            decayCost = decayCost + 1;
        }
    }
    else {
        if((node->cost ) < 0) {
            decayCost = decayCost + 1;
        }
        else {
            decayCost = decayCost + node->cost;
        }
    }
    return decayCost;
}

void InfluenceMap::Propagate()
{
    for ( std::list<Tower*>::iterator tower = this->towers->begin();
         tower != this->towers->end(); tower++ )
    {
        Tower* t = *tower;
        int strength = t->toweRules->GetStrength(*t);
        int width = this->mapInfo->GetTilesPerLine();
        int index_Center = this->mapInfo->ConvertPointToId(t->getPosition());
        int index_centerLeft = index_Center - 1;
        int index_centerRight = index_Center + 1;
        int index_topLeft = (index_centerLeft + (width*3));
        int index_topRight = (index_centerRight + (width*3));
        int index_bottomLeft = (index_centerLeft - width);
        int distance = t->attackRange-1;
        int num = 2;
        for ( int j = 0; j < distance; j++)
        {
            int indexTopLeft1 = index_topLeft + (width * j) - 1;
            int indexTopRight1 = index_topRight + (width * j) + 1;
            int indexBottomLeft1 = index_bottomLeft - (width * j) -1;
            for ( int k = 1; k < ( num + 2 ) + 1; k++ )
            {
                InfluenceMapNode p5;
                p5.cost = this->calculateCost((indexTopLeft1 - j) + k, j, distance, strength);
                p5.pTower = t;
                this->AddInfluenceAtIndex( (indexTopLeft1 - j) + k, p5);
                InfluenceMapNode p6;
                p6.cost = this->calculateCost((indexBottomLeft1 - j) + (k - 1), j, distance, strength);
                p6.pTower = t;
                this->AddInfluenceAtIndex( (indexBottomLeft1 - j) + (k - 1), p6);
                InfluenceMapNode p7;
                p7.cost = this->calculateCost((indexTopRight1 + j) - (width * k), j, distance, strength);
                p7.pTower = t;
                this->AddInfluenceAtIndex( (indexTopRight1 + j) - (width * k), p7);
                InfluenceMapNode p8;
                p8.cost = this->calculateCost((indexTopLeft1 - j) - (width * (k - 1)), j, distance, strength);
                p8.pTower = t;
                this->AddInfluenceAtIndex( (indexTopLeft1 - j) - (width * (k - 1)), p8);
            }
            num = num + 2;
        }
    }
}

//ensures that the all the indexes are valid

void InfluenceMap::AddInfluenceAtIndex(int index, InfluenceMapNode node)
{
    if( ((this->mapInfo->GetTilesPerLine() * this->mapInfo->GetTilesPerColumn()) > index) && index > 0 )
    {
        this->map[index] = node;
    }
}

void InfluenceMap::Invalidate()
{
    this->RemoveAllInfluences();
    this->Propagate();
}

void InfluenceMap::TestPrintAllInfluences()
{
    std::cout << "\n" << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << "\n";
    for ( int i = 0; i < this->map.size(); i++ )
    {
        if(this->map[i].cost > -1)
        {
            std::cout << "mapid: " << i << " influence: " << this->map[i].cost << "\n";
        }
    }
    std::cout << "\n" << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << "\n";
}


std::map < int, InfluenceMapNode > * InfluenceMap::getMap()
{
    return &this->map;
}

InfluenceMapNode* InfluenceMap::GetNode(int index) {
    int range = this->mapInfo->GetTilesPerLine() * this->mapInfo->GetTilesPerColumn();
    if( index > 0 && index <= range )
    {
        return &this->map.at(index);
    }
    else
    {
        return nullptr;
    }
}
