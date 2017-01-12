//
//  AceProgress.h
//  MLB
//
//  Created by 승재 한 on 2014. 7. 21..
//
//

#ifndef __MLB__AceProgress__
#define __MLB__AceProgress__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN

enum {
    START_LEFT = 0,
    START_RIGHT,
};

class AceProgress
: public CCNode
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceProgress, create);
    
    CC_SYNTHESIZE(CCProgressTimerType, progressType, ProgressType);
    CC_SYNTHESIZE(float, progressTime, ProgressTime);
    CC_SYNTHESIZE(float, beginValue, BeginValue);
    CC_SYNTHESIZE(float, lastValue, LastValue);
    
    CC_SYNTHESIZE(int, startPosition, StartPosition);
    CC_SYNTHESIZE(std::string, progressCallback, ProgressCallback);
    
    CC_SYNTHESIZE(CCCallFunc*, progressCallBackFunc, ProgressCallBackFunc);

    CCProgressTimer* progressTimer;
public:
    AceProgress(): progressType(kCCProgressTimerTypeBar), progressTime(0.0f), beginValue(0.0f), lastValue(0.0f), startPosition(0), progressTimer(NULL), progressCallBackFunc(NULL) {}
    
    
    virtual bool init();
    virtual void onEnter();

    void playProgress();
    void setCallback(SEL_CallFunc selector, CCObject* target, const char* callback);
};

NS_CC_EXT_END

#endif /* defined(__MLB__AceProgress__) */
