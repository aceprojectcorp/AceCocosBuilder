//
//  cs_if.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_if_h
#define ScrollViewTest_cs_if_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
    VALUE_TYPE_IF_INT,
    VALUE_TYPE_IF_FLOAT,
    VALUE_TYPE_IF_STRING,
} _ValueType_if;

typedef enum {
    A_EQUAL_B,          //a == b
    A_NOT_EQUAL_B,      //a != b
    A_BIG_B,            //a > b
    A_SMALL_B,          //a < b
    A_BIG_OR_EQUAL_B,   //a >= b
    A_SMALL_OR_EQUAL_B, //a <= b
} _CompareType;

class cs_if
: public cocos2d::CCNode
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(cs_if, create);
    
public:
    _ValueType_if valueType;
    _CompareType compareType;
    int aValue_int;
    int bValue_int;
    float aValue_float;
    float bValue_float;
    CCString* aValue_string;
    CCString* bValue_string;
    
    bool isVisible;
    
public:
    void setCompareType(int nType);
    void setValue(int aValue, int bValue);
    void setValue(float aValue, float bValue);
    void setValue(CCString* aValue, CCString* bValue);
    void refresh();
    bool valueCompare();
    
    void setIsVisible(bool visible);
    void visibleRefresh();
    
};

NS_CC_EXT_END

#endif
