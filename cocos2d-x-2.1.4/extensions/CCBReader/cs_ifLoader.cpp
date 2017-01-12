//
//  cs_ifLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_ifLoader.h"

/*
void cs_ifLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader)
{
    cs_if* tmpLayer = (cs_if*)pNode;
    
    if(strcmp(pPropertyName, "valueType") == 0)
    {
        tmpLayer->valueType = (_ValueType_if)pIntegerLabeled;
    }
    else if(strcmp(pPropertyName, "compareType") == 0)
    {
        tmpLayer->compareType = (_CompareType)pIntegerLabeled;
    }
}

void cs_ifLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    cs_if* tmpLayer = (cs_if*)pNode;
    
    if(strcmp(pPropertyName, "aValue_int") == 0)
    {
        tmpLayer->aValue_int = (int)pFloat;
    }
    else if(strcmp(pPropertyName, "bValue_int") == 0)
    {
        tmpLayer->bValue_int = (int)pFloat;
    }
    else if(strcmp(pPropertyName, "aValue_float") == 0)
    {
        tmpLayer->aValue_float = pFloat;
    }
    else if(strcmp(pPropertyName, "bValue_float") == 0)
    {
        tmpLayer->bValue_float = pFloat;
    }
}

void cs_ifLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    cs_if* tmpLayer = (cs_if*)pNode;
    
    if(strcmp(pPropertyName, "aValue_string") == 0)
    {
        tmpLayer->aValue_string = CCString::create(pString);
    }
    else if(strcmp(pPropertyName, "bValue_string") == 0)
    {
        tmpLayer->bValue_string = CCString::create(pString);
    }
}
*/

void cs_ifLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    cs_if* tmpLayer = (cs_if*)pNode;
    
    if(strcmp(pPropertyName, "bTrue") == 0)
    {
        if(pCheck)
        {
            tmpLayer->valueType = VALUE_TYPE_IF_INT;
            tmpLayer->aValue_int = 0;
            tmpLayer->bValue_int = 0;
        }
    }
    else if(strcmp(pPropertyName, "bFalse") == 0)
    {
        if(pCheck)
        {
            tmpLayer->valueType = VALUE_TYPE_IF_INT;
            tmpLayer->aValue_int = 0;
            tmpLayer->bValue_int = 1;
        }
    }
}