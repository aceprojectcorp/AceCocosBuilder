//
//  actPlaceLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actPlaceLoader.h"

void actPlaceLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    actPlace* tmpLayer = (actPlace*)pNode;
    
    if(strcmp(pPropertyName, "m_x") == 0)
    {
        tmpLayer->m_x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_y") == 0)
    {
        tmpLayer->m_y = pFloat;
    }
}