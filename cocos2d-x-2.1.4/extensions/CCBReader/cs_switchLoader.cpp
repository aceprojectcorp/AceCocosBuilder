//
//  cs_switchLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_switchLoader.h"

/*
void cs_switchLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader)
{
    cs_switch* tmpLayer = (cs_switch*)pNode;
    
    if(strcmp(pPropertyName, "valueType") == 0)
    {
        tmpLayer->valueType = (_ValueType_switch)pIntegerLabeled;
    }
}
*/

void cs_switchLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    cs_switch* tmpLayer = (cs_switch*)pNode;
    
    if(strcmp(pPropertyName, "value_string") == 0)
    {
        tmpLayer->valueType = VALUE_TYPE_SWITCH_STRING;
        //tmpLayer->value_string = CCString::create(pString);
        //tmpLayer->value_string = CCString::createWithFormat("%s", pString);
        tmpLayer->value_string = pString;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}