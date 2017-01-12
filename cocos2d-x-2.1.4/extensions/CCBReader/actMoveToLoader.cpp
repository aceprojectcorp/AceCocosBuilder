//
//  actMoveToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actMoveToLoader.h"

void actMoveToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actMoveTo* tmpLayer = (actMoveTo*)pNode;
    
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
}