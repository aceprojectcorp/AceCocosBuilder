//
//  actScaleTo.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actScaleTo_h
#define ScrollViewTest_actScaleTo_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class actScaleTo
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actScaleTo, create);
    
    
public:
    float m_time;
    float m_scale_x;
    float m_scale_y;
    
public:
    
};

NS_CC_EXT_END

#endif
