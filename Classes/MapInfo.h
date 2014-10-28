//
//  MapInfo.h
//
//
//  Based on chenquanjun's solution (testAStar).
//
//

#ifndef __TowerDefense__MapInfo__
#define __TowerDefense__MapInfo__


#include "GameScene.h"


USING_NS_CC;
class MapInfo : public Ref {
    
    public:
    static MapInfo* create( const std::string& filename );
    
    MapPath* GetMapPath(int startId, int endId);
    MapPath* GetMapPath(int startId, int endId, Ref * r);
    
    ValueVector GetMapInfoTypeVec(MapInfoType type);
    int GetRandomMapIdByType(MapInfoType type);
    cocos2d::Point GetRandomPointByType(MapInfoType type);
    cocos2d::Point GetRandomPointMidByType(MapInfoType type);

    int ConvertPointToId(cocos2d::Point point);
    cocos2d::Point ConvertIdToPoint(int mapId);
    cocos2d::Point ConvertIdToPointMid(int mapId);
    CC_SYNTHESIZE_READONLY(cocos2d::Size, _mapGridSize, MapGridSize);
    CC_SYNTHESIZE_READONLY(cocos2d::Size, _pointSize, PointSize);
    
    //added
    MapInfoType TypeAtPoint(cocos2d::Point point);
    MapInfoType TypeAtId(int index);
    
    void ChangeTypeForSurroundingIndexes(MapInfoType type, cocos2d::Point loc);
    bool SurroundingTilesAvailable(cocos2d::Point point, int tilesDistance);
    bool TilesForTowerValid(cocos2d::Point point);

    std::vector<MapInfoType> cantPassOverTypes;
    
    ValueMapIntKey GetMapInfoTypeMap();
    
    int GetDistanceInTiles(cocos2d::Point p1, cocos2d::Point p2);
    
    int GetTilesPerLine();
    int GetTilesPerColumn();
    
    void SetTypeToIndex(MapInfoType type, int mapId);
    
    
    void setGScale(int num);
    
    
    private:
    
    //scale G Cost
    int scaleGCost;
    
    
    //IM Related
    //start
    bool imEnabled;
    Ref* _im;
    public:
    void setInfluenceMap(Ref* m);
    //end
    
    private:
    
    struct PointNode
    {
        PointNode()  {nIndex = 0; nG = 0; pParent = NULL;}
        int nIndex;
        int nG;
        PointNode* pParent;
    };
    
    
    MapInfo(void);
    virtual ~MapInfo(void);
    
    TMXTiledMap* map;
    
    virtual bool init(const std::string& filename);
    int GetIndexByDir(int nIndex, int nDir);
    int GetGScore(int nStartIndex, int nEndIndex);
    int GetHScore(int nStartIndex, int nEndIndex);
    PointNode *InTable(int nIndex, std::vector<PointNode*> &vecTbl);
    MapPath *FindPath(int start, int end);

    
    ValueVector _mapInfoTypeVec;
    ValueMapIntKey _mapInfoTypeMap;
    
    int m_nKeyOffset;
    
};


#endif 
