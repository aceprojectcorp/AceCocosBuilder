//
//  AceExtRadioButtonLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#include "AceExtRadioButtonLoader.h"

void AceExtRadioButtonLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader) {
    
    AceExtRadioButton* tmpLayer = (AceExtRadioButton*)pNode;
    
    if(strcmp(pPropertyName, "clickEffect") == 0)
    {
        //tmpLayer->m_selectedName = CCString::create(pString);
        tmpLayer->setClickEffect(pString);
    }
    else if(strcmp(pPropertyName, "m_cbFunc") == 0)
    {
        //tmpLayer->m_selectedName = CCString::create(pString);
        //tmpLayer->m_cbFunc = CCString::create(pString);;
        tmpLayer->setCbFunc(pString);
    }
    else
    {
        CCMenuItemLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}

void AceExtRadioButtonLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    AceExtRadioButton* tmpLayer = (AceExtRadioButton*)pNode;
    
    if(strcmp(pPropertyName, "selected") == 0)
    {
        tmpLayer->bSelected = pCheck;
    }
    else
    {
        CCMenuItemLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

