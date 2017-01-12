//
//  actOrbitCamera.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actOrbitCamera_h
#define ScrollViewTest_actOrbitCamera_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class actOrbitCamera
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actOrbitCamera, create);
    
    
public:
    float m_time;
    float m_radius;
    float m_deltaRadius;
    float m_angleZ;
    float m_deltaAngleZ;
    float m_angleX;
    float m_deltaAngleX;
    
public:
    
};

NS_CC_EXT_END

#endif
