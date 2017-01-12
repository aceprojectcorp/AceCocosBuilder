//
//  cs_switch_default.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_switch_default_h
#define ScrollViewTest_cs_switch_default_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class cs_switch_default
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(cs_switch_default, create);
    
    CCString* value_string;
    
    CCString* getValue();
};

NS_CC_EXT_END

#endif
