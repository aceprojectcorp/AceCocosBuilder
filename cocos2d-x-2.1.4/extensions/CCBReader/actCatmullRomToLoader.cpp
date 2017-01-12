//
//  actCatmullRomToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actCatmullRomToLoader.h"

void actCatmullRomToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actCatmullRomTo* tmpLayer = (actCatmullRomTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_tension") == 0)
    {
        tmpLayer->m_tension = pFloat;
    }
}

void actCatmullRomToLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    actCatmullRomTo* tmpLayer = (actCatmullRomTo*)pNode;
    
    if(strcmp(pPropertyName, "m_points") == 0)
    {
        tmpLayer->m_points = CCString::create(pString);
    }
}