//
//  Ace3DNodeLoader.cpp
//  MLB
//
//  Created by 허정목 on 2014. 2. 26..
//
//

#include "Ace3DNodeLoader.h"

void Ace3DNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    Ace3DNode* tmpLayer = (Ace3DNode*)pNode;
    
    if(strcmp(pPropertyName, "m_object_x") == 0)
    {
        tmpLayer->m_object.x = pFloat;
    }
    else if(strcmp(pPropertyName, "m_object_y") == 0)
    {
        tmpLayer->m_object.y = pFloat;
    }
    else if(strcmp(pPropertyName, "m_object_z") == 0)
    {
        tmpLayer->m_object.z = pFloat;
    }
}