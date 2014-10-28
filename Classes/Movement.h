//
//  Movement.h
//
//
//  Based on chenquanjun's solution (testAStar).
//
//

#ifndef __TowerDefense__Movement__
#define __TowerDefense__Movement__

#include "cocos2d.h"
#include "CCActionInterval.h"
#include "MapGeneral.h"

USING_NS_CC;

class Movement : public ActionInterval
{
    
    public:
    
    static Movement* create(float duration, PointArray* pointArr);

    virtual Movement* clone() const override;
	virtual Movement* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
    protected:
    
    Movement();
    virtual ~Movement();
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, PointArray* pointArr);
    
    void playActionByPos(cocos2d::Point start, cocos2d::Point end, Node *target);
    
    CC_SYNTHESIZE_RETAIN(PointArray*, _pointArr, PointArr);
    
    int _nIndex;
    

    private:
    
    CC_DISALLOW_COPY_AND_ASSIGN(Movement);

};
    

#endif
