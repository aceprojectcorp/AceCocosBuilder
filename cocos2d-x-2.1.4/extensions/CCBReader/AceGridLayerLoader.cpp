//
//  AceGridLayerLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#include "AceGridLayerLoader.h"

void AceGridLayerLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    AceGridLayer* tmpLayer = (AceGridLayer*)pNode;
    
    if(strcmp(pPropertyName, "row") == 0)
    {
        tmpLayer->setRow((int)pFloat);
    }
    else if(strcmp(pPropertyName, "col") == 0)
    {
        tmpLayer->setCol((int)pFloat);
    }
    else if(strcmp(pPropertyName, "padingLeft") == 0)
    {
        CCPoint tmpPoint = tmpLayer->getPadding();
        tmpPoint.x = pFloat;
        tmpLayer->setPadding(tmpPoint);
    }
    else if(strcmp(pPropertyName, "padingTop") == 0)
    {
        CCPoint tmpPoint = tmpLayer->getPadding();
        tmpPoint.y = pFloat;
        tmpLayer->setPadding(tmpPoint);
    }
    else if(strcmp(pPropertyName, "cellWidth") == 0)
    {
        CCSize tmpSize = tmpLayer->getItemSize();
        tmpSize.width = pFloat;
        tmpLayer->setItemSize(tmpSize);
    }
    else if(strcmp(pPropertyName, "cellHight") == 0)
    {
        CCSize tmpSize = tmpLayer->getItemSize();
        tmpSize.height = pFloat;
        tmpLayer->setItemSize(tmpSize);
    }
    else if(strcmp(pPropertyName, "gapX") == 0)
    {
        CCSize tmpSize = tmpLayer->getGap();
        tmpSize.width = pFloat;
        tmpLayer->setGap(tmpSize);
    }
    else if(strcmp(pPropertyName, "gapY") == 0)
    {
        CCSize tmpSize = tmpLayer->getGap();
        tmpSize.height = pFloat;
        tmpLayer->setGap(tmpSize);
    }
    else if(strcmp(pPropertyName, "maxContentSizeW") == 0)
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

void AceGridLayerLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceGridLayer* tmpLayer = (AceGridLayer*)pNode;
    
    if(strcmp(pPropertyName, "autoResize") == 0)
    {
        tmpLayer->setIsAutoResize(pCheck);
    }
    else if(strcmp(pPropertyName, "bMaxContentSizeW") == 0)
    {
        tmpLayer->bMaxContentSizeW = pCheck;
    }
    else if(strcmp(pPropertyName, "bMaxContentSizeH") == 0)
    {
        tmpLayer->bMaxContentSizeH = pCheck;
    }
    else if(strcmp(pPropertyName, "bAddWidth") == 0)
    {
        tmpLayer->bAddWidth = pCheck;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

/*
void AceGridLayerLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader) {
    
    AceGridLayer* tmpLayer = (AceGridLayer*)pNode;
    
    if(strcmp(pPropertyName, "cellNodeName") == 0)
    {
        tmpLayer->m_cellNodeName = CCString::create(pString);
    }
}
*/