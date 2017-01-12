//
//  actFadeToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actFadeToLoader.h"

void actFadeToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actFadeTo* tmpLayer = (actFadeTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
}

void actFadeToLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader)
{
    actFadeTo* tmpLayer = (actFadeTo*)pNode;
    
    if(strcmp(pPropertyName, "m_opacity") == 0)
    {
        tmpLayer->m_opacity = pByte;
    }
}