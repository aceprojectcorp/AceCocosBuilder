//
//  actDelayTime.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actDelayTime_h
#define ScrollViewTest_actDelayTime_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class actDelayTime
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actDelayTime, create);
    
    
public:
    float m_time;
    
public:
    
};

NS_CC_EXT_END

#endif
