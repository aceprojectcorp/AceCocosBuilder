//
//  actJumpToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actJumpToLoader.h"

void actJumpToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actJumpTo* tmpLayer = (actJumpTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_x") == 0)
    {
        tmpLayer->m_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_y") == 0)
    {
        tmpLayer->m_y = pFloat;
    }
    else if(strcmp(pPropertyName, "m_height") == 0)
    {
        tmpLayer->m_height = pFloat;
    }
    else if(strcmp(pPropertyName, "m_jumps") == 0)
    {
        tmpLayer->m_jumps = pFloat;
    }
}