//
//  AceFlipActionNodeLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 31..
//
//

#include "AceFlipActionNodeLoader.h"

void AceFlipActionNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    AceFlipActionNode* tmpLayer = (AceFlipActionNode*)pNode;
    
    if(strcmp(pPropertyName, "_fTime") == 0)
    {
        tmpLayer->_fTime = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceFlipActionNodeLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceFlipActionNode* tmpLayer = (AceFlipActionNode*)pNode;
    
    if( strcmp( pPropertyName, "left" ) == 0 )
    {
        tmpLayer->_bLeft = pCheck;
    }
    else if( strcmp( pPropertyName, "right" ) == 0 )
    {
        tmpLayer->_bRight = pCheck;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck( pNode, pParent, pPropertyName, pCheck, pCCBReader );
    }
}

void AceFlipActionNodeLoader::onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader)
{
    AceFlipActionNode* tmpLayer = (AceFlipActionNode*)pNode;
    
    if( strcmp( pPropertyName, "_nRepeat" ) == 0 )
    {
        tmpLayer->_nRepeat = pInteger;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeInteger( pNode, pParent, pPropertyName, pInteger, pCCBReader );
    }
}