//
//  actRotationToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actRotationToLoader.h"

void actRotationToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actRotationTo* tmpLayer = (actRotationTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_angle_x") == 0)
    {
        tmpLayer->m_angle_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_angle_y") == 0)
    {
        tmpLayer->m_angle_y = pFloat;
    }
}