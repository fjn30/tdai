//
//  MapPath.h
//
//
//  Based on chenquanjun's solution (testAStar).
//
//

#ifndef __TowerDefense__MapPath__
#define __TowerDefense__MapPath__

#include "cocos2d.h"
#include "MapGeneral.h"
USING_NS_CC;


class MapPath : public Ref{
    
public:
    
    static MapPath* create(int startId, int endId, PointArray* pointArr);
    MapPath* getRevertPath(void);
    MapPath* getCopy();
    
private:
    MapPath(void);
    virtual ~MapPath(void);
    virtual bool init(int startId, int endId, PointArray* pointArr);
    
    CC_SYNTHESIZE_READONLY(int, _startId, StartId);
    CC_SYNTHESIZE_READONLY(int, _endId, EndId);
    CC_SYNTHESIZE_RETAIN(PointArray*, _pointArr, PointArr)
};

#endif 
