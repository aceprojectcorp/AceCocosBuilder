//
//  cs_switch.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_switch.h"
#include "cs_switch_case.h"
#include "cs_switch_default.h"

USING_NS_CC_EXT;

void cs_switch::onEnter()
{
    CCNode::onEnter();
    
    //value_int = value_string->intValue();
    
    refresh();
}

/*
void cs_switch::setValue(int nValue)
{
    this->value_int = nValue;
    
    refresh();
}
*/

void cs_switch::setValue(CCString* nString)
{
    this->value_string = nString->getCString();
    
    refresh();
}

void cs_switch::setValue(const std::string _string)
{
    this->value_string = _string;
    
    refresh();
}

void cs_switch::refresh()
{
    CCArray* children = this->getChildren();
    int size = children->count();
    
    cs_switch_case* caseNode = NULL;
    cs_switch_default* defaultNode = NULL;

    int defaultPos = -1;
    bool bDefaultView = true;
    for(int i=0; i<size; i++)
    {
        caseNode = dynamic_cast<cs_switch_case*>(children->objectAtIndex(i));
        defaultNode = dynamic_cast<cs_switch_default*>(children->objectAtIndex(i));
        
        if(defaultNode)
        {
            defaultNode->setVisible(false);
            defaultPos = i;
        }
        
        if(caseNode)
        {
            caseNode->setVisible(false);
            
            if(valueType == VALUE_TYPE_SWITCH_INT)
            {
                /*
                int childValue = caseNode->getValue()->intValue();
                if(value_int == childValue)
                {
                    caseNode->setVisible(true);
                    bDefaultView = false;
                }
                 */
            }
            else
            {
                //CCString* childValue = CCString::createWithFormat("%s", caseNode->getValue());
                std::string childValue = caseNode->getValue();
                
                //if(childValue)
                if(strcmp(childValue.c_str(), "") != 0)
                {
                    //if(strcmp(value_string.c_str(), childValue->getCString()) == 0)
                    if(strcmp(value_string.c_str(), childValue.c_str()) == 0)
                    {
                        caseNode->setVisible(true);
                        bDefaultView = false;
                        
                        selectedChild = caseNode;
                    }
                }
            }
        }
    }
    
    if(bDefaultView && defaultPos != -1)
    {
        defaultNode = dynamic_cast<cs_switch_default*>(children->objectAtIndex(defaultPos));
        defaultNode->setVisible(true);
        
        selectedChild = defaultNode;
    }
}

CCNode* cs_switch::getSelectedChild() {
    return selectedChild;
}

const std::string cs_switch::getSelectedValue() {
    return value_string;
}




