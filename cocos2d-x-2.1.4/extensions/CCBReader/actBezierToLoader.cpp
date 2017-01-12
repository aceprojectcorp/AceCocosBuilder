//
//  actBezierToLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actBezierToLoader.h"

void actBezierToLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actBezierTo* tmpLayer = (actBezierTo*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_point1_x") == 0)
    {
        tmpLayer->m_point1_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_point1_y") == 0)
    {
        tmpLayer->m_point1_y = pFloat;
    }
    else if(strcmp(pPropertyName, "m_point2_x") == 0)
    {
        tmpLayer->m_point2_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_point2_y") == 0)
    {
        tmpLayer->m_point2_y = pFloat;
    }
    else if(strcmp(pPropertyName, "m_endPoint_x") == 0)
    {
        tmpLayer->m_endPoint_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_endPoint_y") == 0)
    {
        tmpLayer->m_endPoint_y = pFloat;
    }
}