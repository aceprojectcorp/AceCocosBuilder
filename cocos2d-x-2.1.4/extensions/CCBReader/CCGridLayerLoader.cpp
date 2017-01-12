//
//  CCGridLayerLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 18..
//
//

#include "CCGridLayerLoader.h"


NS_CC_EXT_BEGIN

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"



void CCGridLayerLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    /*
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((CCLayerColor *)pNode)->setColor(pCCColor3B);
    } else {
        CCGridLayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
     */
}

void CCGridLayerLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    /*
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((CCLayerColor *)pNode)->setOpacity(pByte);
    } else {
        CCGridLayerLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
     */
}

void CCGridLayerLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    /*
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((CCLayerColor *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCGridLayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
     */
}

void CCGridLayerLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    CCLog("pPropertyName = %s", pPropertyName);
    CCLog("pFloat = %f", pFloat);
    
    if(strcmp(pPropertyName, "row") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fRow = pFloat;
    }
    else if(strcmp(pPropertyName, "col") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fCol = pFloat;
    }
    else if(strcmp(pPropertyName, "padingLeft") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fPadingLeft = pFloat;
    }
    else if(strcmp(pPropertyName, "padingTop") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fPadingTop = pFloat;
    }
    else if(strcmp(pPropertyName, "cellWidth") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fCellWidth = pFloat;
    }
    else if(strcmp(pPropertyName, "cellHight") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fCellHight = pFloat;
    }
    else if(strcmp(pPropertyName, "gapX") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fGapX = pFloat;
    }
    else if(strcmp(pPropertyName, "gapY") == 0)
    {
        CCGridLayer* tmpLayer = (CCGridLayer*)pNode;
        tmpLayer->m_fGapY = pFloat;
    }
}






NS_CC_EXT_END