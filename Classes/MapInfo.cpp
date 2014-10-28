//
//  MapInfo.cpp
//
//
//  Based on chenquanjun on 14-3-14 (testAStar).
//
//

#include "GameScene.h"
#include <iostream>
#include <array>

MapInfo::MapInfo(void) {
    this->_mapGridSize = Size(0, 0);
    this->_pointSize = Size(0, 0);
    this->m_nKeyOffset = 10000;
    srand((unsigned)time(NULL));
    this->scaleGCost = 1;
}

MapInfo::~MapInfo(void) {
    
}

bool MapInfo::init(const std::string& filename) {
    
    map = TMXTiledMap::create(filename);
    auto objectGrp = map->getObjectGroup("object");
    auto layer = map->getLayer("background");
    _mapGridSize = layer->getLayerSize();
    auto& objects = objectGrp->getObjects();
	int capacity = 1;
	capacity = _mapGridSize.width * _mapGridSize.height;
    ValueMap& dict = objects.at(0).asValueMap();
    _pointSize = Size(dict["width"].asFloat(), dict["height"].asFloat());
    
	//windows doesn't support variable sized arrays
	int mapType[capacity]; //<- mac
    
    /*
	//windows fix, declare and populate the vector
	std::vector<int> mapType;
	for (int i = 0; i < capacity; i++)
	{
		mapType.push_back(0);
	}
    */

    for (auto& obj : objects) {
        ValueMap& dict = obj.asValueMap();
        
        float x = dict["x"].asFloat() / _pointSize.width;
        float y = dict["y"].asFloat() / _pointSize.height;
        
        int objectId = dict["objectid"].asInt();
        int mapId = x + y * _mapGridSize.width;
        mapType[mapId] = objectId;
    }
    

    for (int i = 0; i < capacity; i++) {
        int num = mapType[i];
        //CCASSERT(num != 0, "objectId not set");
        Value pNum = Value(num);
        _mapInfoTypeVec.push_back(pNum);
    }
    
    return true;
}

#pragma -mark- ------Public Method------


void MapInfo::setInfluenceMap(cocos2d::Ref *m)
{
    if(m != nullptr)
    {
        this->_im = m;
        this->imEnabled = true;
    }
    else
    {
        this->imEnabled = false;
    }
}

void MapInfo::setGScale(int num)
{
    this->scaleGCost = num;
}

//through euclidean distance
int MapInfo::GetDistanceInTiles(cocos2d::Point p1, cocos2d::Point p2)
{
    int nIndex = this->ConvertPointToId(p1);
    int nEndIndex = this->ConvertPointToId(p2);
    
    int nRow = nIndex / _mapGridSize.width;
    int nCol = nIndex % (int)_mapGridSize.width;
    
    int nEndRow = nEndIndex / _mapGridSize.width;
    int nEndCol = nEndIndex % (int)_mapGridSize.width;
    
    int x = abs(nEndRow - nRow);
    int y = abs(nEndCol - nCol);
    
    return sqrt((x * x) + (y * y));
}

bool MapInfo::TilesForTowerValid(Point point)
{
    int mapId = this->ConvertPointToId(point);
    bool result = false;
    
    if(

       //_mapInfoTypeVec[ mapId + 3 ].asInt() != (int) MapInfoType::Tower &&
       //_mapInfoTypeVec[ mapId - 3 ].asInt() != (int) MapInfoType::Tower &&
       //_mapInfoTypeVec[ mapId + 3 ].asInt() != (int) MapInfoType::Road &&
       //_mapInfoTypeVec[ mapId - 3 ].asInt() != (int) MapInfoType::Road &&
       
       _mapInfoTypeVec[ mapId + 2 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ mapId - 2 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ mapId + 2 ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ mapId - 2 ].asInt() != (int) MapInfoType::Road &&
       
       _mapInfoTypeVec[ (mapId + (this->GetTilesPerLine() * 2)) + 1 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId + (this->GetTilesPerLine() * 2)) ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId + (this->GetTilesPerLine() * 2)) - 1 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId + (this->GetTilesPerLine() * 2)) + 1 ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ (mapId + (this->GetTilesPerLine() * 2)) ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ (mapId + (this->GetTilesPerLine() * 2)) - 1 ].asInt() != (int) MapInfoType::Road &&
       
       //_mapInfoTypeVec[ (mapId - (this->GetTilesPerLine() * 2)) + 1 ].asInt() != (int) MapInfoType::Tower &&
       //_mapInfoTypeVec[ (mapId - (this->GetTilesPerLine() * 2)) ].asInt() != (int) MapInfoType::Tower &&
       //_mapInfoTypeVec[ (mapId - (this->GetTilesPerLine() * 2)) - 1 ].asInt() != (int) MapInfoType::Tower &&
       //_mapInfoTypeVec[ (mapId - (this->GetTilesPerLine() * 2)) + 1 ].asInt() != (int) MapInfoType::Road &&
       //_mapInfoTypeVec[ (mapId - (this->GetTilesPerLine() * 2)) ].asInt() != (int) MapInfoType::Road &&
       //_mapInfoTypeVec[ (mapId - (this->GetTilesPerLine() * 2)) - 1 ].asInt() != (int) MapInfoType::Road &&
       
       _mapInfoTypeVec[ mapId + 1 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ mapId ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ mapId - 1 ].asInt() != (int) MapInfoType::Tower &&
       
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) + 1 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) - 1 ].asInt() != (int) MapInfoType::Tower &&
       
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) + 1 ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) ].asInt() != (int) MapInfoType::Tower &&
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) - 1 ].asInt() != (int) MapInfoType::Tower &&
       
       _mapInfoTypeVec[ mapId + 1 ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ mapId ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ mapId - 1 ].asInt() != (int) MapInfoType::Road &&
       
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) + 1 ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) - 1 ].asInt() != (int) MapInfoType::Road &&
       
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) + 1 ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) ].asInt() != (int) MapInfoType::Road &&
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) - 1 ].asInt() != (int) MapInfoType::Road &&
       
       _mapInfoTypeVec[ mapId + 1 ].asInt() != (int) MapInfoType::Invalid &&
       _mapInfoTypeVec[ mapId ].asInt() != (int) MapInfoType::Invalid &&
       _mapInfoTypeVec[ mapId - 1 ].asInt() != (int) MapInfoType::Invalid &&
       
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) + 1 ].asInt() != (int) MapInfoType::Invalid &&
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) ].asInt() != (int) MapInfoType::Invalid &&
       _mapInfoTypeVec[ (mapId + this->GetTilesPerLine()) - 1 ].asInt() != (int) MapInfoType::Invalid &&
       
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) + 1 ].asInt() != (int) MapInfoType::Invalid &&
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) ].asInt() != (int) MapInfoType::Invalid &&
       _mapInfoTypeVec[ (mapId - this->GetTilesPerLine()) - 1 ].asInt() != (int) MapInfoType::Invalid
       
    )
    {
        result = true;
    }
    
    
    return result;
}

bool MapInfo::SurroundingTilesAvailable(Point point, int tilesDistance)
{
    int mapId = this->ConvertPointToId(point);
    int elementsPerLine = _mapGridSize.width;

    bool result = false;
    int unavailableInts = 0;
    
    for( int i = 0; i < tilesDistance; i++)
    {
        if( ((mapId - elementsPerLine  * i) / elementsPerLine) > this->GetTilesPerColumn() || ((mapId - elementsPerLine  * i) / elementsPerLine) <= 0 )
        {
            unavailableInts++;
            break;
        }
        
        if (
            
            _mapInfoTypeVec[ (mapId + (2 * i))  ].asInt() != (int) MapInfoType::Tower &&
            _mapInfoTypeVec[ (mapId - (2 * i)) ].asInt() != (int) MapInfoType::Tower &&
            
            _mapInfoTypeVec[ (mapId + elementsPerLine + (2 * i)) ].asInt() != (int) MapInfoType::Road &&
            _mapInfoTypeVec[ (mapId + elementsPerLine - (2 * i)) ].asInt() != (int) MapInfoType::Road &&
            _mapInfoTypeVec[ (mapId - elementsPerLine + (2 * i)) ].asInt() != (int) MapInfoType::Road &&
            _mapInfoTypeVec[ (mapId - elementsPerLine - (2 * i)) ].asInt() != (int) MapInfoType::Road &&
            
            _mapInfoTypeVec[ (mapId + elementsPerLine + (2 * i)) ].asInt() != (int) MapInfoType::Tower &&
            _mapInfoTypeVec[ (mapId + elementsPerLine - (2 * i)) ].asInt() != (int) MapInfoType::Tower &&
            _mapInfoTypeVec[ (mapId - elementsPerLine + (2 * i)) ].asInt() != (int) MapInfoType::Tower &&
            _mapInfoTypeVec[ (mapId - elementsPerLine - (2 * i)) ].asInt() != (int) MapInfoType::Tower &&
            
            _mapInfoTypeVec[ (mapId + (elementsPerLine * i))  ].asInt() != (int) MapInfoType::Tower &&
            _mapInfoTypeVec[ (mapId - (elementsPerLine * i)) ].asInt() != (int) MapInfoType::Tower &&
            
            _mapInfoTypeVec[ (mapId + (elementsPerLine * i))  ].asInt() != (int) MapInfoType::Road &&
            _mapInfoTypeVec[ (mapId - (elementsPerLine * i)) ].asInt() != (int) MapInfoType::Road
            
            )
        {
            
        }
        else
        {
            unavailableInts++;
        }
        
    }
    
    
    if(unavailableInts > 0)
    {
        result = true;
    }
    
    return result;
}

//changes the surrounding indexes to the given type
//( line above, line under, current line and -1 + 1 on all 3 lines )
//line as in GridMap line
void MapInfo::ChangeTypeForSurroundingIndexes(MapInfoType type, Point point)
{
    int mapId = this->ConvertPointToId(point);
    int elementsPerLine = _mapGridSize.width;

    _mapInfoTypeVec[ (mapId + (elementsPerLine*2)) + 1 ] = (int) type;
    _mapInfoTypeVec[ mapId + (elementsPerLine*2) ] = (int) type;
    _mapInfoTypeVec[ (mapId + (elementsPerLine*2)) - 1 ] = (int) type;

    _mapInfoTypeVec[ (mapId + elementsPerLine) + 1 ] = (int) type;
    _mapInfoTypeVec[ (mapId + elementsPerLine) ] = (int) type;
    _mapInfoTypeVec[ (mapId + elementsPerLine) - 1 ] = (int) type;
    
    _mapInfoTypeVec[ (mapId ) + 1 ] = (int) type;
    _mapInfoTypeVec[ (mapId ) ] = (int) type;
    _mapInfoTypeVec[ (mapId ) - 1 ] = (int) type;
    
}

int MapInfo::GetTilesPerLine()
{
    return this->_mapGridSize.width;
}

int MapInfo::GetTilesPerColumn()
{
    return this->_mapGridSize.height;
}

MapInfoType MapInfo::TypeAtPoint(Point point)
{
    int mapId = this->ConvertPointToId(point);
    return (MapInfoType)_mapInfoTypeVec.at(mapId).asInt();
}


MapInfo* MapInfo::create(const std::string& filename) {
    
    MapInfo *pMapInfo = new MapInfo();
    
    if (pMapInfo && pMapInfo->init(filename))
    {
        pMapInfo->autorelease();
        return pMapInfo;
    }
    CC_SAFE_DELETE(pMapInfo);
    return nullptr;
}

#pragma -mark- Get Method

MapPath* MapInfo::GetMapPath(int startId, int endId){
    MapPath* path = this->FindPath(startId, endId);
    return path;
}

ValueMapIntKey MapInfo::GetMapInfoTypeMap()
{
    return this->_mapInfoTypeMap;
}

MapInfoType MapInfo::TypeAtId(int mapId)
{
    MapInfoType result = MapInfoType::Invalid;
    if( mapId <= (this->GetTilesPerColumn() * this->GetTilesPerLine()) && mapId > 0 )
    {
        result = (MapInfoType)_mapInfoTypeVec.at(mapId).asInt();
    }
    return result;
}

ValueVector MapInfo::GetMapInfoTypeVec(MapInfoType type){
    int typeNum = (int)type;
    ValueVector typeVec;
    int i = 0;
    for (auto& value: _mapInfoTypeVec) {
        int num = value.asInt();
        if (num == typeNum) {
            typeVec.push_back(Value(i));
        }
        i++;
    }
    return typeVec;
}

int MapInfo::GetRandomMapIdByType(MapInfoType type){
    int mapId = -1;
    auto roadVec = this->GetMapInfoTypeVec(type);
    if (!roadVec.empty()) {
        int count = roadVec.size();
        float r = CCRANDOM_0_1();
        if (r == 1) // to prevent from accessing data-arr[data->num], out of range.
        {
            r = 0;
        }
        
        int randomTarget = r * count;
        auto value = roadVec.at(randomTarget);
        mapId = value.asInt();
    } else {
        log("Warning: map id invalid, error type or type didnot exist");
    }
    
    return mapId;
}

Point MapInfo::GetRandomPointByType(MapInfoType type){
    int mapId = GetRandomMapIdByType(type);
    return ConvertIdToPoint(mapId);
}

Point MapInfo::GetRandomPointMidByType(MapInfoType type){
    int mapId = GetRandomMapIdByType(type);
    return ConvertIdToPointMid(mapId);
}

#pragma -mark- Convert Method

int MapInfo::ConvertPointToId(Point point){
    int mapId = -1;
    // 8 9 ...
    // 4 5 6 7
    // 0 1 2 3
    if (Rect(0, 0, _mapGridSize.width * _pointSize.width, _mapGridSize.height * _pointSize.height).containsPoint(point)) {
        int x = point.x / _pointSize.width;
        int y = point.y / _pointSize.height;
        mapId = x + y * _mapGridSize.width;
    }
    return mapId;
}

Point MapInfo::ConvertIdToPoint(int mapId){
    Point point = Point(0, 0);
    if (mapId >= 0 && mapId < _mapInfoTypeVec.size()) {
        int y = (mapId / (int)_mapGridSize.width);
        int x = (mapId - y * _mapGridSize.width) ;
        
        point = Point(x  * _pointSize.width, y * _pointSize.height);
    }
    return point;
}

Point MapInfo::ConvertIdToPointMid(int mapId){
    Point point = ConvertIdToPoint(mapId);
    return Point(point.x + _pointSize.width * 0.5f, point.y + _pointSize.height * 0.5f);
}


void MapInfo::SetTypeToIndex(MapInfoType type, int mapId)
{
    _mapInfoTypeVec[mapId] = (int)type;
}


#pragma -mark- ------Private Method------

#pragma -mark- find Path Method

//the actual astar algo
MapPath* MapInfo::FindPath(int start, int end) {
    
    std::vector<PointNode*> vecClose;
    std::vector<PointNode*> vecOpen;
    
    if (start == -1 || end == -1)
    {
        return nullptr;
    }
    
    auto &pointTypeStart = _mapInfoTypeVec.at(start);
    if (pointTypeStart.asInt() == (int)MapInfoType::Block)
    {
        return nullptr;
    }
    
    auto &pointTypeEnd = _mapInfoTypeVec.at(end);
    if (pointTypeEnd.asInt() == (int)MapInfoType::Block)
    {
        return nullptr;
    }
    
    PointNode* pNode = new PointNode();
    pNode->nIndex = start;
    vecClose.push_back(pNode);
    
    int nStep = 0;
    while(true)
    {
        if (nStep++ >= MAPINFO_MAX_STEP_NUM)
        {
            break;
        }
        PointNode* pNextNode = vecClose[vecClose.size() - 1];
        if (!pNextNode)
        {
            break;
        }
        if (pNextNode->nIndex == end)
        {
            break;
        }
        
        for (int i = 0; i < MAPINFO_ASTAR_DIRECTION_NUM; i++)
        {
            int nIndex = GetIndexByDir(pNextNode->nIndex, i);
            if (-1 == nIndex) //illegal index
            {
                continue;
            }

            //if the type of the particular index is contained in the vector
            //then the node is ignored
            bool cont = true;
            for( std::vector<MapInfoType>::iterator it = this->cantPassOverTypes.begin(); it != this->cantPassOverTypes.end(); ++it)
            {
                auto &pointType = _mapInfoTypeVec.at(nIndex);
                MapInfoType type = *it;
                if (pointType.asInt() == (int)type)
                {
                    cont = false;
                    break;
                }
            }
            
            if(!cont)
            {
                continue;
            }
            
            
            if (InTable(nIndex, vecClose) != nullptr)
            {
                continue;
            }
            
            PointNode* pNode = InTable(nIndex, vecOpen);
            if (pNode)
            {
                int nNewG = pNextNode->nG + GetGScore(pNextNode->nIndex, pNode->nIndex);
                if (pNode->nG > nNewG)
                {
                    pNode->nG = nNewG;
                    pNode->pParent = pNextNode;
                }
                continue;
            }
            
            pNode = new PointNode;
            pNode->nIndex = nIndex;
            pNode->nG = pNextNode->nG + GetGScore(pNextNode->nIndex, pNode->nIndex);
            pNode->pParent = pNextNode;
            
            vecOpen.push_back(pNode);
    
        }
        
        int nMinF = 0xFFFFFF;
        pNextNode = nullptr;
        int nNextNodeIndex = 0;
        for (int i = 0; i < (int)vecOpen.size(); i++)
        {
            PointNode* pNode2 = vecOpen[i];
            if (!pNode2)
            {
                continue;
            }
            int nH = GetHScore(pNode2->nIndex, end);
            int nF = nH + pNode2->nG;
            if (nF < nMinF)
            {
                nMinF = nF;
                pNextNode = pNode2;
                nNextNodeIndex = i;
            }
        }
        if (nNextNodeIndex >= 0 && nNextNodeIndex < (int)vecOpen.size())
        {
            vecClose.push_back(pNextNode);
            vecOpen.erase(vecOpen.begin() + nNextNodeIndex);
        }
    }
    
    PointArray *pathArr = PointArray::create(0);
    
    pNode = vecClose[vecClose.size() - 1];
    
    while (pNode)
    {
        int mapId = pNode->nIndex;
        Point point = this->ConvertIdToPointMid(mapId); //map id
        pathArr->addControlPoint(point);
        pNode = pNode->pParent;
    }
    
    MapPath* pathRevert = MapPath::create(end, start , pathArr);
    MapPath* path = pathRevert->getRevertPath();
    
    do {
        for (std::vector<PointNode *>::iterator it = vecClose.begin(); it != vecClose.end(); it ++)
            if (NULL != *it)
            {
                delete *it;
                *it = NULL;
            }
        vecClose.clear();
    } while (0);
    
    do {
        for (std::vector<PointNode *>::iterator it = vecOpen.begin(); it != vecOpen.end(); it ++)
            if (NULL != *it)
            {
                delete *it;
                *it = NULL;
            }
        vecOpen.clear();
    } while (0);
    
    start = -1;
    end = -1;
    
    return path->getCopy();
}
 
#pragma -mark- A Star Method

int MapInfo::GetIndexByDir(int nIndex, int nDir)
{
    if (nIndex < 0 || nIndex >= (int)_mapGridSize.width * _mapGridSize.height)
    {
        return -1;
    }
    
    int nRow = nIndex / _mapGridSize.width;
    int nCol = nIndex % (int)_mapGridSize.width;
    
    switch(nDir)
    {
        case 0:
            nRow += 1;
            break;
        case 1:
            nCol += 1;
            break;
        case 2:
            nRow -= 1;
            break;
        case 3:
            nCol -= 1;
            break;
        case 4:
            nRow += 1;
            nCol +=1;
            break;
        case 5:
            nRow -= 1;
            nCol += 1;
            break;
        case 6:
            nRow -= 1;
            nCol -= 1;
            break;
        case 7:
            nRow += 1;
            nCol -= 1;
            break;
        default:
            break;
    }
    if (nRow < 0 || nRow >= _mapGridSize.height
        || nCol < 0 || nCol >= _mapGridSize.width)
    {
        return -1;
    }
    return nRow * _mapGridSize.width + nCol;
}

int MapInfo::GetGScore(int start, int end) {
    int nStartRow = start / _mapGridSize.width;
    int nStartCol = start %  (int)_mapGridSize.width;
    int nEndRow = end /  _mapGridSize.width;
    int nEndCol = end % (int)_mapGridSize.width;
    int envCost = 1;
    if(this->TypeAtId(start) == MapInfoType::Planes) {
        envCost = 10;
    }
    if(this->imEnabled == true) {
        InfluenceMapNode* imn = ((InfluenceMap*)this->_im)->GetNode(start);
        if( imn )  {
            if( imn->cost == -1) {
                if (nStartRow == nEndRow || nStartCol == nEndCol) {
                    return (2 * scaleGCost) + (envCost * 10);
                }
                return (5 * scaleGCost) + (envCost * 10);
            }
            else {
                Tower * t = imn->pTower;
                if (nStartRow == nEndRow || nStartCol == nEndCol) {
                    return (( (imn->cost + t->GetStrength()) ) * scaleGCost) + (envCost);
                }
                return (( (imn->cost + t->GetStrength()) ) * scaleGCost) + (envCost);
            }
        }
    }
    else {
        if (nStartRow == nEndRow || nStartCol == nEndCol) {
            return 10 + (envCost * 10);
        }
        return 20 + (envCost * 10);
    }
}

int MapInfo::GetHScore(int nStartIndex, int nEndIndex)
{
    int nRow = nStartIndex / _mapGridSize.width;
    int nCol = nStartIndex % (int)_mapGridSize.width;
    
    int nEndRow = nEndIndex / _mapGridSize.width;
    int nEndCol = nEndIndex % (int)_mapGridSize.width;
    
    return (abs(nEndRow - nRow) + abs(nEndCol - nCol)) * 10;
}

MapInfo::PointNode *MapInfo::InTable(int nIndex, std::vector<PointNode*> &vecTbl)
{
    for (int i = 0; i < (int)vecTbl.size(); i++)
    {
        if (nIndex == vecTbl[i]->nIndex)
        {
            return vecTbl[i];
        }
    }
    return nullptr;
}

