//
//  actTintToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actTintToLoader.h"

void actTintToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actTintTo* tmpLayer = (actTintTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
}

void actTintToLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader)
{
    actTintTo* tmpLayer = (actTintTo*)pNode;
    
    if(strcmp(pPropertyName, "m_r") == 0)
    {
        tmpLayer->m_r = pByte;
    }
    else if(strcmp(pPropertyName, "m_g") == 0)
    {
        tmpLayer->m_g = pByte;
    }
    else if(strcmp(pPropertyName, "m_b") == 0)
    {
        tmpLayer->m_b = pByte;
    }
}