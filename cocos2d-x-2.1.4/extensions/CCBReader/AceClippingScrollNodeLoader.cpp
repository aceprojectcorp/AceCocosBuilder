//
//  AceClippingScrollNodeLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 2..
//
//

#include "AceClippingScrollNodeLoader.h"

void AceClippingScrollNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    AceClippingScrollNode* tmpLayer = (AceClippingScrollNode*)pNode;
    
    if(strcmp(pPropertyName, "m_priority") == 0)
    {
        //tmpLayer->setTouchPriority((int)pFloat);
        tmpLayer->m_touchPriority = (int)pFloat;
    }
    else if(strcmp(pPropertyName, "maxContentSizeW") == 0)
    {
        tmpLayer->maxContentSizeW = pFloat;
    }
    else if(strcmp(pPropertyName, "maxContentSizeH") == 0)
    {
        tmpLayer->maxContentSizeH = pFloat;
    }
    else
    {
        CCLayerLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceClippingScrollNodeLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader)
{
    AceClippingScrollNode* tmpLayer = (AceClippingScrollNode*)pNode;
    
    if(strcmp(pPropertyName, "scrollDir") == 0)
    {
        tmpLayer->scrollDir = (_ScrollDir)pIntegerLabeled;
    }
    else
    {
        CCLayerLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void AceClippingScrollNodeLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceClippingScrollNode* tmpLayer = (AceClippingScrollNode*)pNode;
    
    if(strcmp(pPropertyName, "bMaxContentSizeW") == 0)
    {
        tmpLayer->bMaxContentSizeW = pCheck;
    }
    else if(strcmp(pPropertyName, "bMaxContentSizeH") == 0)
    {
        tmpLayer->bMaxContentSizeH = pCheck;
    }
    else if(strcmp(pPropertyName, "resetPositionLock") == 0)
    {
        tmpLayer->setResetPositionLock(pCheck);
    }
    else
    {
        CCLayerLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}