//
//  actBezierTo.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actBezierTo_h
#define ScrollViewTest_actBezierTo_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class actBezierTo
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actBezierTo, create);
    
    
public:
    float m_time;
    float m_point1_x;
    float m_point1_y;
    float m_point2_x;
    float m_point2_y;
    float m_endPoint_x;
    float m_endPoint_y;
    
public:
    
};

NS_CC_EXT_END

#endif
