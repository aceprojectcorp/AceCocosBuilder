//
//  AceClippingNodeLoader.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceCoverPageScrollLoader.h"

void AceCoverPageScrollLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    AceCoverPageScroll* tmpLayer = (AceCoverPageScroll*)pNode;
    
    if(strcmp(pPropertyName, "m_fAngle") == 0)
    {
        tmpLayer->m_fAngle = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fLen") == 0)
    {
        tmpLayer->m_fLen = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fMaxSize") == 0)
    {
        tmpLayer->m_fMaxSize = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fMinSize") == 0)
    {
        tmpLayer->m_fMinSize = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fScrollSpeed") == 0)
    {
        tmpLayer->m_fScrollSpeed = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fAngleToMove") == 0)
    {
        tmpLayer->m_fAngleToMove = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fMinAlpha") == 0)
    {
        tmpLayer->m_fMinAlpha = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fAutoScrollSpeed") == 0)
    {
        tmpLayer->m_fAutoScrollSpeed = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fMoveY") == 0)
    {
        tmpLayer->m_fMoveY = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceCoverPageScrollLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceCoverPageScroll* tmpLayer = (AceCoverPageScroll*)pNode;
    
    if( strcmp( pPropertyName, "m_bLoop" ) == 0 )
    {
        tmpLayer->m_bLoop = pCheck;
    }
    else if( strcmp( pPropertyName, "m_bAutoScroll" ) == 0 )
    {
        tmpLayer->m_bAutoScroll = pCheck;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck( pNode, pParent, pPropertyName, pCheck, pCCBReader );
    }
}

void AceCoverPageScrollLoader::onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader)
{
    AceCoverPageScroll* tmpLayer = (AceCoverPageScroll*)pNode;
    
    if( strcmp( pPropertyName, "m_iDefaultCur" ) == 0 )
    {
        tmpLayer->m_iDefaultCur = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iShowCnt" ) == 0 )
    {
        tmpLayer->m_iShowCnt = pInteger;
    }
   else
    {
        CCNodeLoader::onHandlePropTypeInteger( pNode, pParent, pPropertyName, pInteger, pCCBReader );
    }
}