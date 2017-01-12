//
//  AceMultiNodeLoader.cpp
//  MLB
//
//  Created by 허정목 on 2014. 8. 11..
//
//

#include "AceMultiNodeLoader.h"

void AceMultiNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    
    AceMultiNode* tmpLayer = (AceMultiNode*)pNode;
    
    if(strcmp(pPropertyName, "maxContentSizeW") == 0)
    {
        tmpLayer->maxContentSizeW = pFloat;
    }
    else if(strcmp(pPropertyName, "maxContentSizeH") == 0)
    {
        tmpLayer->maxContentSizeH = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceMultiNodeLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceMultiNode* tmpLayer = (AceMultiNode*)pNode;
    
    if(strcmp(pPropertyName, "bMaxContentSizeW") == 0)
    {
        tmpLayer->bMaxContentSizeW = pCheck;
    }
    else if(strcmp(pPropertyName, "bMaxContentSizeH") == 0)
    {
        tmpLayer->bMaxContentSizeH = pCheck;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}
