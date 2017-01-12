//
//  actSkewToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actSkewToLoader.h"

void actSkewToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actSkewTo* tmpLayer = (actSkewTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_skew_x") == 0)
    {
        tmpLayer->m_skew_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_skew_y") == 0)
    {
        tmpLayer->m_skew_y = pFloat;
    }
}