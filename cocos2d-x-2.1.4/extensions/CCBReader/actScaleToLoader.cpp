//
//  actScaleToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actScaleToLoader.h"

void actScaleToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actScaleTo* tmpLayer = (actScaleTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_scale_x") == 0)
    {
        tmpLayer->m_scale_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_scale_y") == 0)
    {
        tmpLayer->m_scale_y = pFloat;
    }
}

