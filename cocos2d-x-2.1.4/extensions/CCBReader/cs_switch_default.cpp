//
//  cs_switch_default.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_switch_default.h"

USING_NS_CC_EXT;

void cs_switch_default::onEnter()
{
    CCNode::onEnter();
    
    value_string = CCString::create("default");
}

CCString* cs_switch_default::getValue()
{
    return this->value_string;
}