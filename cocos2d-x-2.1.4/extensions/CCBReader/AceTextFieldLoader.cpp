//
//  AceTextFieldLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 29..
//
//

#include "AceTextFieldLoader.h"

void AceTextFieldLoader::onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader) {
    AceTextField* node = (AceTextField*)pNode;
    
    if(strcmp(pPropertyName, "maxLength") == 0) {
        node->setMaxLength(pInteger);
    }
    else
    {
        CCNodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pInteger, pCCBReader);
    }
}
