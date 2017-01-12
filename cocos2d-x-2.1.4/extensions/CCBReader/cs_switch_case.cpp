//
//  cs_switch_case.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_switch_case.h"

USING_NS_CC_EXT;

void cs_switch_case::onEnter()
{
    CCNode::onEnter();
    
    
}

/*
CCString* cs_switch_case::getValue()
{
    return this->value_string;
}
*/


const char* cs_switch_case::getValue()
{
    //return this->value_string;
    return this->value_string.c_str();
}