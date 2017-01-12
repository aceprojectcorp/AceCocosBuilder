//
//  AceFrameAnimation.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#ifndef ScrollViewTest_AceFrameAnimation_h
#define ScrollViewTest_AceFrameAnimation_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceFrameAnimation
: public CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceFrameAnimation, create);
    
public:
    float m_fps;
    int nowFrameIdx;
    bool bLoop;
    bool bPlay;
    
    float delay;
    int prevFrameIdx;

    
public:
    void update(float dt);
    void proc(float dt);
    void childReset();
    
public:
    void stop();
    void play();
    bool isPlay();
};

NS_CC_EXT_END

#endif
