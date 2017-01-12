//
//  Ace3DBallLoader.cpp
//  MLB
//
//  Created by 허정목 on 2014. 3. 3..
//
//

#include "Ace3DBallLoader.h"

void Ace3DBallLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    Ace3DBall* tmpLayer = (Ace3DBall*)pNode;
    
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
    else if(strcmp(pPropertyName, "tmpPower") == 0)
    {
        tmpLayer->tmpPower = pFloat;
    }
    else if(strcmp(pPropertyName, "tmpAngle") == 0)
    {
        tmpLayer->tmpAngle = pFloat;
    }
    else if(strcmp(pPropertyName, "tmpAngleZ") == 0)
    {
        tmpLayer->tmpAngleZ = pFloat;
    }
    else if(strcmp(pPropertyName, "tmpG") == 0)
    {
        tmpLayer->tmpG = pFloat;
    }
}