//
//  cs_switch_caseLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#include "cs_switch_caseLoader.h"

void cs_switch_caseLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    cs_switch_case* tmpLayer = (cs_switch_case*)pNode;
    
    if(strcmp(pPropertyName, "value_string") == 0)
    {
        //tmpLayer->value_string = CCString::create(pString);
        //tmpLayer->value_string = CCString::createWithFormat("%s", pString);
        tmpLayer->value_string = pString;
    }
    else
    {
        CCNodeLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}