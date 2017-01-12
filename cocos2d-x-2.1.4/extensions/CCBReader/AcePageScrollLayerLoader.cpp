//
//  AcePageScrollLayerLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#include "AcePageScrollLayerLoader.h"

void AcePageScrollLayerLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    AcePageScrollLayer* tmpLayer = (AcePageScrollLayer*)pNode;
    
    if(strcmp(pPropertyName, "priority") == 0)
    {
        tmpLayer->m_fPriority = pFloat;
    }
    else
    {
        CCLayerLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}