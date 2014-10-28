//
//  InfluenceMap.h
//  TowerDefense_new
//
//  Created by GEO on 29/07/2014.
//
//

#ifndef TowerDefense_new_InfluenceMap_h
#define TowerDefense_new_InfluenceMap_h

#include <map>

#include "GameScene.h"

struct InfluenceMapNode
{
    int cost;
    Tower* pTower;
};

class InfluenceMap : Ref
{
    
    private:
    //the map data container
    std::map < int , InfluenceMapNode > map;
    
    //the mapinfo pointer
    MapInfo* mapInfo;
    
    //the towers vector pointer
    std::list < Tower * >* towers;
    
    int calculateCost(int mapId, int decayLevel, int distance, int strength);
    
    void Propagate();
    void RemoveAllInfluences();
    
    void AddInfluenceAtIndex(int index, InfluenceMapNode node);
    
    public:
    InfluenceMap(MapInfo* mapInfo, std::list < Tower * >* towers);
    ~InfluenceMap();
    
    std::map < int, InfluenceMapNode > * getMap();

    void Invalidate();
    
    InfluenceMapNode* GetNode(int index);
  
    void TestPrintAllInfluences();
    
};

#endif
