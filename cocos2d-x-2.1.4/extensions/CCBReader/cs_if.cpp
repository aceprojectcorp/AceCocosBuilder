//
//  cs_if.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_if.h"
#include "cs_if_true.h"
#include "cs_if_false.h"

USING_NS_CC_EXT;

void cs_if::onEnter()
{
    CCNode::onEnter();
    
    refresh();
}

void cs_if::setCompareType(int nType)
{
    this->compareType = (_CompareType)nType;
    
    refresh();
}

void cs_if::setValue(int aValue, int bValue)
{
    this->aValue_int = aValue;
    this->bValue_int = bValue;
    
    refresh();
}

void cs_if::setValue(float aValue, float bValue)
{
    this->aValue_float = aValue;
    this->bValue_float = bValue;
    
    refresh();
}

void cs_if::setValue(CCString* aValue, CCString* bValue)
{
    this->aValue_string = aValue;
    this->bValue_string = bValue;
    
    refresh();
}

void cs_if::setIsVisible(bool visible) {
    this->isVisible = visible;
    
    visibleRefresh();
}

void cs_if::refresh()
{
    CCArray* children = this->getChildren();
    int size = children->count();
    
    cs_if_true* trueNode = NULL;
    cs_if_false* falseNode = NULL;
    
    for(int i=0; i<size; i++)
    {
        cs_if_true* tmpTrueNode = dynamic_cast<cs_if_true*>(children->objectAtIndex(i));
        cs_if_false* tmpFalseNode = dynamic_cast<cs_if_false*>(children->objectAtIndex(i));
        
        if(tmpTrueNode)
        {
            trueNode = tmpTrueNode;
        }
        
        if(tmpFalseNode)
        {
            falseNode = tmpFalseNode;
        }
    }
    
    bool val = this->valueCompare();
    if(val)
    {
        if(trueNode) trueNode->setVisible(true);
        if(falseNode) falseNode->setVisible(false);
    }
    else
    {
        if(trueNode) trueNode->setVisible(false);
        if(falseNode) falseNode->setVisible(true);
    }
}

void cs_if::visibleRefresh()
{
    CCArray* children = this->getChildren();
    int size = children->count();
    
    cs_if_true* trueNode = NULL;
    cs_if_false* falseNode = NULL;
    
    for(int i=0; i<size; i++)
    {
        cs_if_true* tmpTrueNode = dynamic_cast<cs_if_true*>(children->objectAtIndex(i));
        cs_if_false* tmpFalseNode = dynamic_cast<cs_if_false*>(children->objectAtIndex(i));
        
        if(tmpTrueNode)
        {
            trueNode = tmpTrueNode;
        }
        
        if(tmpFalseNode)
        {
            falseNode = tmpFalseNode;
        }
    }
    
    if(isVisible) {
        trueNode->setVisible(true);
        falseNode->setVisible(false);
    } else {
        trueNode->setVisible(false);
        falseNode->setVisible(true);
    }
}

bool cs_if::valueCompare()
{
    bool val = false;
    
    switch(valueType)
    {
        case VALUE_TYPE_IF_INT :
            switch(compareType)
            {
                case A_EQUAL_B :           //a == b
                    if(aValue_int == bValue_int) val = true;
                    break;
                case A_NOT_EQUAL_B :       //a != b
                    if(aValue_int != bValue_int) val = true;
                    break;
                case A_BIG_B :             //a > b
                    if(aValue_int > bValue_int) val = true;
                    break;
                case A_SMALL_B :           //a < b
                    if(aValue_int < bValue_int) val = true;
                    break;
                case A_BIG_OR_EQUAL_B :    //a >= b
                    if(aValue_int >= bValue_int) val = true;
                    break;
                case A_SMALL_OR_EQUAL_B :  //a <= b
                    if(aValue_int <= bValue_int) val = true;
                    break;
            }
            break;
        case VALUE_TYPE_IF_FLOAT :
            switch(compareType)
            {
                case A_EQUAL_B :           //a == b
                    if(aValue_float == bValue_float) val = true;
                    break;
                case A_NOT_EQUAL_B :       //a != b
                    if(aValue_float != bValue_float) val = true;
                    break;
                case A_BIG_B :             //a > b
                    if(aValue_float > bValue_float) val = true;
                    break;
                case A_SMALL_B :           //a < b
                    if(aValue_float < bValue_float) val = true;
                    break;
                case A_BIG_OR_EQUAL_B :    //a >= b
                    if(aValue_float >= bValue_float) val = true;
                    break;
                case A_SMALL_OR_EQUAL_B :  //a <= b
                    if(aValue_float <= bValue_float) val = true;
                    break;
                default:
                    val = false;
                    break;
            }
            break;
        case VALUE_TYPE_IF_STRING :
            switch(compareType)
            {
                case A_EQUAL_B :           //a == b
                    if(aValue_string->isEqual(bValue_string)) val = true;
                    break;
                case A_NOT_EQUAL_B :       //a != b
                    if(aValue_string->isEqual(bValue_string)) val = true;
                    break;
                default:
                    val = false;
                    break;
            }
            break;
    }
    
    return val;
}