//
//  AceFlowLayerLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#include "AceFlowLayerLoader.h"

void AceFlowLayerLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    AceFlowLayer* tmpLayer = (AceFlowLayer*)pNode;
    
    if(strcmp(pPropertyName, "padingLeft") == 0)
    {
        tmpLayer->m_padding.x = pFloat;
    }
    else if(strcmp(pPropertyName, "padingTop") == 0)
    {
        tmpLayer->m_padding.y = pFloat;
    }
    else if(strcmp(pPropertyName, "gapY") == 0)
    {
        tmpLayer->m_gap = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceFlowLayerLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceFlowLayer* tmpLayer = (AceFlowLayer*)pNode;
    
    if(strcmp(pPropertyName, "m_align_left") == 0)
    {
        if(pCheck)
        {
            tmpLayer->m_align = COMPOSITE_LABEL_ALIGN_LEFT;
        }
    }
    else if(strcmp(pPropertyName, "m_align_center") == 0)
    {
        if(pCheck)
        {
            tmpLayer->m_align = COMPOSITE_LABEL_ALIGN_CENTER;
        }
    }
    else if(strcmp(pPropertyName, "m_align_right") == 0)
    {
        if(pCheck)
        {
            tmpLayer->m_align = COMPOSITE_LABEL_ALIGN_RIGHT;
        }
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

