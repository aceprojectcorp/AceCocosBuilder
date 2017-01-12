//
//  actFadeTo.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actFadeTo_h
#define ScrollViewTest_actFadeTo_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class actFadeTo
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actFadeTo, create);
    
    
public:
    float m_time;
    GLubyte m_opacity;
    
public:
    
};

NS_CC_EXT_END

#endif
