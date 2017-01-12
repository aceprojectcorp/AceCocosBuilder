//
//  actJumpTo.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actJumpTo_h
#define ScrollViewTest_actJumpTo_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class actJumpTo
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actJumpTo, create);
    
    
public:
    float m_time;
    float m_x;
    float m_y;
    float m_height;
    float m_jumps;
    
public:
    
};

NS_CC_EXT_END

#endif
