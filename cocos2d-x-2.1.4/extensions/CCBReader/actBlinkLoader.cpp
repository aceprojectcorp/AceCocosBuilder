//
//  actBlinkLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actBlinkLoader.h"

void actBlinkLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actBlink* tmpLayer = (actBlink*)pNode;
    
    if(strcmp(pPropertyName, "m_time") == 0)
    {
        tmpLayer->m_time = pFloat;
    }
    else if(strcmp(pPropertyName, "m_blinkCount") == 0)
    {
        tmpLayer->m_blinkCount = pFloat;
    }
}