//
//  AceClippingNodeLoader.cpp
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#include "AceBarGraphLoader.h"

void AceBarGraphLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader)
{
    AceBarGraph* tmpLayer = (AceBarGraph*)pNode;
    
    if(strcmp(pPropertyName, "m_fSpeed") == 0)
    {
        //tmpLayer->m_fSpeed = pFloat;
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
    else if(strcmp(pPropertyName, "m_fBarA") == 0)
    {
        tmpLayer->m_fBarA = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fCenterLineA") == 0)
    {
        tmpLayer->m_fCenterLineA = pFloat;
    }
    else if(strcmp(pPropertyName, "m_fCenterLineWidth") == 0)
    {
        tmpLayer->m_fCenterLineWidth = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceBarGraphLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceBarGraph* tmpLayer = (AceBarGraph*)pNode;
    
    if( strcmp( pPropertyName, "m_bRight" ) == 0 )
    {
        tmpLayer->m_bRight = pCheck;
       
    }
    else if( strcmp( pPropertyName, "m_bScroll" ) == 0 )
    {
        tmpLayer->m_bScroll = pCheck;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck( pNode, pParent, pPropertyName, pCheck, pCCBReader );
    }
}

void AceBarGraphLoader::onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader)
{
    AceBarGraph* tmpLayer = (AceBarGraph*)pNode;
    
    if( strcmp( pPropertyName, "m_iHeight" ) == 0 )
    {
        tmpLayer->m_iHeight = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iWidth" ) == 0 )
    {
        tmpLayer->m_iWidth = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iCenterHeight" ) == 0 )
    {
        tmpLayer->m_iCenterHeight = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iMargin" ) == 0 )
    {
        tmpLayer->m_iMargin = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iCntPoint" ) == 0 )
    {
        tmpLayer->m_iCntPoint = pInteger;
    }
    else if( strcmp( pPropertyName, "m_iScrollW" ) == 0 )
    {
        tmpLayer->m_iScrollW = pInteger;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeInteger( pNode, pParent, pPropertyName, pInteger, pCCBReader );
    }
}
void AceBarGraphLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader)
{
    AceBarGraph* tmpLayer = (AceBarGraph*)pNode;
    
    if( strcmp( pPropertyName, "m_backColor" ) == 0 )
    {
        tmpLayer->m_backColor = pCCColor3B;
    }
    else if( strcmp( pPropertyName, "m_barColor" ) == 0 )
    {
        tmpLayer->m_barColor = pCCColor3B;
    }
    else if( strcmp( pPropertyName, "m_lineColor" ) == 0 )
    {
        tmpLayer->m_lineColor = pCCColor3B;
    }
    else if( strcmp( pPropertyName, "m_centerLineColor" ) == 0 )
    {
        tmpLayer->m_centerLineColor = pCCColor3B;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeColor3( pNode, pParent, pPropertyName, pCCColor3B, pCCBReader );
    }

}