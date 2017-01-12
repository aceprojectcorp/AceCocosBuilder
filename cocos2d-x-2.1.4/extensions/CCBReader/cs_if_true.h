//
//  cs_if_true.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_if_true_h
#define ScrollViewTest_cs_if_true_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class cs_if_true
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(cs_if_true, create);
    
    bool bTrueFalse;
};

NS_CC_EXT_END

#endif
