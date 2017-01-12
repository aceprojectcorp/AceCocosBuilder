//
//  AcePriorityMenuLoader.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#include "AcePriorityMenuLoader.h"


 void AcePriorityMenuLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
     
     AcePriorityMenu* tmpLayer = (AcePriorityMenu*)pNode;
     
     if(strcmp(pPropertyName, "priority") == 0)
     {
         tmpLayer->m_priority = (int)pFloat;
     }
     else
     {
         CCMenuLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
     }
 }


void AcePriorityMenuLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader)
{
    
    AcePriorityMenu* tmpLayer = (AcePriorityMenu*)pNode;
    
    if(strcmp(pPropertyName, "swallowTouches") == 0)
    {
        tmpLayer->m_swallowTouches = pCheck;
    }
    else if(strcmp(pPropertyName, "checkParent") == 0)
    {
        tmpLayer->setCheckParent(pCheck);
    } else {
        CCLayerLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}