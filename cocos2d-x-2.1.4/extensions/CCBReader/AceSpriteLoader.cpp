//
//  AceSpriteLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#include "AceSpriteLoader.h"

void AceSpriteLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader)
{
    AceSprite* tmpLayer = (AceSprite*)pNode;
    
    if(strcmp(pPropertyName, "blendType") == 0)
    {
        tmpLayer->blendType  = (_BlendType)pIntegerLabeled;
    }
    else
    {
        CCSpriteLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}