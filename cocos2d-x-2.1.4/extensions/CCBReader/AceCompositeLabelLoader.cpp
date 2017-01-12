//
//  AceCompositeLabelLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#include "AceCompositeLabelLoader.h"


void AceCompositeLabelLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    
    AceCompositeLabel* tmpLayer = (AceCompositeLabel*)pNode;
    
    if(strcmp(pPropertyName, "gapX") == 0)
    {
        tmpLayer->m_gapX = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}


void AceCompositeLabelLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceCompositeLabel* tmpLayer = (AceCompositeLabel*)pNode;
    
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