//
//  AceTickerLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#include "AceTickerLoader.h"

void AceTickerLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader)
{
    AceTicker* tmpLayer = (AceTicker*)pNode;
    
    if(strcmp(pPropertyName, "moveDir") == 0)
    {
        tmpLayer->moveDir = (_MoveDir)pIntegerLabeled;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void AceTickerLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    AceTicker* tmpLayer = (AceTicker*)pNode;
    
    if(strcmp(pPropertyName, "speed") == 0)
    {
        tmpLayer->m_speed = pFloat;
    }
    else if(strcmp(pPropertyName, "stopDelay") == 0)
    {
        tmpLayer->m_stopDelay = pFloat;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

/*
void AceTickerLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceTicker* tmpLayer = (AceTicker*)pNode;
    
    if(strcmp(pPropertyName, "mode_Short") == 0)
    {
        if(pCheck)
        {
            tmpLayer->m_mode = TICKER_MODE_SHORT;
        }
    }
    else if(strcmp(pPropertyName, "mode_Full") == 0)
    {
        if(pCheck)
        {
            tmpLayer->m_mode = TICKER_MODE_FULL;
        }
    }
    
}
*/