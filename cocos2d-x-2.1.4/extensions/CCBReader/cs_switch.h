//
//  cs_switch.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_switch_h
#define ScrollViewTest_cs_switch_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
    VALUE_TYPE_SWITCH_INT,
    VALUE_TYPE_SWITCH_STRING,
} _ValueType_switch;

class cs_switch
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(cs_switch, create);
  
public:
    _ValueType_switch valueType;
    
    CCNode* selectedChild;
    
    int value_int;
    //CCString* value_string;
    //const char* value_string;
    std::string value_string;
    
    
    //void setValue(int nValue);
    
    void setValue(CCString* nString);
    void setValue(const std::string _string);
    void refresh();
    
    CCNode* getSelectedChild(); // 선택된 child 가져오기
    
// ch - 현재선택된 value값 가져오기
    const std::string getSelectedValue();
};

NS_CC_EXT_END

#endif
