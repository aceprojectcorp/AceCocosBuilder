//
//  actOrbitCameraLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actOrbitCameraLoader.h"

void actOrbitCameraLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actOrbitCamera* tmpLayer = (actOrbitCamera*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_radius") == 0)
    {
        tmpLayer->m_radius = pFloat;
    }
    else if(strcmp(pPropertyName, "m_deltaRadius") == 0)
    {
        tmpLayer->m_deltaRadius = pFloat;
    }
    else if(strcmp(pPropertyName, "m_angleZ") == 0)
    {
        tmpLayer->m_angleZ = pFloat;
    }
    else if(strcmp(pPropertyName, "m_deltaAngleZ") == 0)
    {
        tmpLayer->m_deltaAngleZ = pFloat;
    }
    else if(strcmp(pPropertyName, "m_angleX") == 0)
    {
        tmpLayer->m_angleX = pFloat;
    }
    else if(strcmp(pPropertyName, "m_deltaAngleX") == 0)
    {
        tmpLayer->m_deltaAngleX = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

