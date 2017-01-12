//
//  AceClippingNodeLoader.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceAreaGraphLoader.h"

void AceAreaGraphLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    AceAreaGraph* tmpLayer = (AceAreaGraph*)pNode;
    
    if(strcmp(pPropertyName, "m_fSpeed") == 0)
    {
        tmpLayer->m_fSpeed = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fBackA") == 0)
    {
        tmpLayer->m_fBackA = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fLineA") == 0)
    {
       tmpLayer->m_fLineA = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fLineWidth") == 0)
    {
        tmpLayer->m_fLineWidth = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fPointA") == 0)
    {
        tmpLayer->m_fPointA = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fPointSize") == 0)
    {
        tmpLayer->m_fPointSize = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceAreaGraphLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    //AceAreaGraph* tmpLayer = (AceAreaGraph*)pNode;
    
    if( strcmp( pPropertyName, "m_bLoop" ) == 0 )
    {
       
    }
    else if( strcmp( pPropertyName, "m_bAutoScroll" ) == 0 )
    {
        
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck( pNode, pParent, pPropertyName, pCheck, pCCBReader );
    }
}

void AceAreaGraphLoader::onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader)
{
    AceAreaGraph* tmpLayer = (AceAreaGraph*)pNode;
    
    if( strcmp( pPropertyName, "m_iHeight" ) == 0 )
    {
        tmpLayer->m_iHeight = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iMarginUp" ) == 0 )
    {
        tmpLayer->m_iMarginUp = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iMarginDown" ) == 0 )
    {
        tmpLayer->m_iMarginDown = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iLenPointToPoint" ) == 0 )
    {
        tmpLayer->m_iLenPointToPoint = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iCntPoint" ) == 0 )
    {
        tmpLayer->m_iCntPoint = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iPointSegs" ) == 0 )
    {
        tmpLayer->m_iPointSegs = pInteger;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeInteger( pNode, pParent, pPropertyName, pInteger, pCCBReader );
    }
}
void AceAreaGraphLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader)
{
    AceAreaGraph* tmpLayer = (AceAreaGraph*)pNode;
    
    if( strcmp( pPropertyName, "m_backColor" ) == 0 )
    {
        tmpLayer->m_backColor = pCCColor3B;
    }
    else if( strcmp( pPropertyName, "m_pointColor" ) == 0 )
    {
        tmpLayer->m_pointColor = pCCColor3B;
    }
    else if( strcmp( pPropertyName, "m_lineColor" ) == 0 )
    {
        tmpLayer->m_lineColor = pCCColor3B;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeColor3( pNode, pParent, pPropertyName, pCCColor3B, pCCBReader );
    }

}