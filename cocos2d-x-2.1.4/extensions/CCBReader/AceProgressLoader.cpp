//
//  AceProgressLoader.cpp
//  MLB
//
//  Created by 승재 한 on 2014. 7. 21..
//
//

#include "AceProgressLoader.h"

void AceProgressLoader::onHandlePropTypeFloat(CCNode *pNode, CCNode *pParent, const char *pPropertyName, float pFloat, CCBReader *pCCBReader) {
    AceProgress* node = (AceProgress*)pNode;
    
    if(strcmp(pPropertyName, "progressTime") == 0) {
        node->setProgressTime(pFloat);
    } else if(strcmp(pPropertyName, "lastValue") == 0) {
        node->setLastValue(pFloat);
    }
    else
    {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void AceProgressLoader::onHandlePropTypeIntegerLabeled(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader* pCCBReader) {
    AceProgress* node = (AceProgress*)pNode;
    
    if(strcmp(pPropertyName, "startPosition") == 0) {
        node->setStartPosition(pIntegerLabeled);
    }
    else
    {
        CCNodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void AceProgressLoader::onHandlePropTypeString(CCNode *pNode, CCNode *pParent, const char *pPropertyName, const char* pString, CCBReader *pCCBReader) {
    AceProgress* node = (AceProgress*)pNode;
    
    if(strcmp(pPropertyName, "progressCallback") == 0) {
        node->setProgressCallback(pString);
    }
    else
    {
        CCNodeLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}