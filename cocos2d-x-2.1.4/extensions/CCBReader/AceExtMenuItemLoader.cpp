//
//  AceExtMenuItemLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#include "AceExtMenuItemLoader.h"

void AceExtMenuItemLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader) {
    
    AceExtMenuItem* tmpLayer = (AceExtMenuItem*)pNode;
    
    if(strcmp(pPropertyName, "btnId") == 0)
    {
        //tmpLayer->m_normalName = CCString::create(pString);
        tmpLayer->setBtnId(pString);
    }
    else if(strcmp(pPropertyName, "clickEffect") == 0)
    {
        //tmpLayer->m_selectedName = CCString::create(pString);
        tmpLayer->setClickEffect(pString);
    }
    else if(strcmp(pPropertyName, "m_selector") == 0)
    {
        //tmpLayer->m_selectedName = CCString::create(pString);
        //tmpLayer->setm_selector(pString);
        //tmpLayer->m_selector = CCString::create(pString);
        tmpLayer->setSelector(pString);
    }
    else
    {
        CCMenuItemLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}