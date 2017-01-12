//
//  cs_switch_case.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_switch_case_h
#define ScrollViewTest_cs_switch_case_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

class cs_switch_case
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(cs_switch_case, create);
    
    //CCString* value_string;
    //const char* value_string;
    std::string value_string;
    
    //CCString* getValue();
    const char* getValue();
};

NS_CC_EXT_END

#endif
