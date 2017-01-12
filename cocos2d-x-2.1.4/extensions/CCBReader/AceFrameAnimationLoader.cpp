//
//  AceFrameAnimationLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#include "AceFrameAnimationLoader.h"

void AceFrameAnimationLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    AceFrameAnimation* tmpLayer = (AceFrameAnimation*)pNode;
    
    if(strcmp(pPropertyName, "m_fps") == 0)
    {
        tmpLayer->m_fps = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceFrameAnimationLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceFrameAnimation* tmpLayer = (AceFrameAnimation*)pNode;
    
    if(strcmp(pPropertyName, "bLoop") == 0)
    {
        tmpLayer->bLoop = pCheck;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}