//
//  actZNode.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actZNode_h
#define ScrollViewTest_actZNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

enum
{
    E_actMoveTo,
    E_actDelayTime,
    E_actPlace,
    E_actJumpTo,
    E_actBezierTo,
    E_actCardinalSplineTo,
    E_actCatmullRomTo,
    E_actScaleTo,
    E_actSkewTo,
    E_actRotationTo,
    E_actBlink,
    E_actShow,
    E_actHide,
    E_actToggleVisibility,
    E_actFadeIn,
    E_actFadeOut,
    E_actFadeTo,
    E_actTintTo,
    E_actOrbitCamera,
};

class actZNode
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(actZNode, create);
    
    
public:
    void update(float dt);
    void actionStart();
    bool isKindOfClass(CCNode* child, int classNameIdx);
    CCPointArray* parsePoints(CCString* m_points);
    
public:
    
};

NS_CC_EXT_END

#endif
