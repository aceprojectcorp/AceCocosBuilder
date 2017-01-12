//
//  Ace3DPlayerLoader.cpp
//  MLB
//
//  Created by 허정목 on 2014. 3. 11..
//
//

#include "Ace3DPlayerLoader.h"

void Ace3DPlayerLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    Ace3DPlayer* tmpLayer = (Ace3DPlayer*)pNode;
    
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