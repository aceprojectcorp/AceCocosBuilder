//
//  AceClippingNodeLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 25..
//
//

#include "AceClippingNodeLoader.h"

void AceClippingNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    AceClippingNode* tmpLayer = (AceClippingNode*)pNode;
    
    if(strcmp(pPropertyName, "m_widthRatio") == 0)
    {
        tmpLayer->setWidthRatio(pFloat);
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}
