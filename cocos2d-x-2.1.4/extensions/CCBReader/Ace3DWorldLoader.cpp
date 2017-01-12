//
//  Ace3DWorldLoader.cpp
//  MLB
//
//  Created by 허정목 on 2014. 2. 26..
//
//

#include "Ace3DWorldLoader.h"

void Ace3DWorldLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
    //CCLog("pPropertyName = %s", pPropertyName);
    //CCLog("pFloat = %f", pFloat);
    Ace3DWorld* tmpLayer = (Ace3DWorld*)pNode;
    
    if(strcmp(pPropertyName, "m_camera_a") == 0)
    {
        tmpLayer->m_eye.a = pFloat;
        
        //CCSize frameSize = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize();
        //float addWidth = frameSize.width - 960;
        //tmpLayer->m_eye.a += addWidth/2;
        //CCLog("tmpLayer->m_eye.a = %f", tmpLayer->m_eye.a);
    }
    else if(strcmp(pPropertyName, "m_camera_b") == 0)
    {
        tmpLayer->m_eye.b = pFloat;
        //CCLog("tmpLayer->m_eye.b = %f", tmpLayer->m_eye.b);
    }
    else if(strcmp(pPropertyName, "m_camera_c") == 0)
    {
        tmpLayer->m_eye.c = pFloat;
        //CCLog("tmpLayer->m_eye.c = %f", tmpLayer->m_eye.c);
    }
    else if(strcmp(pPropertyName, "m_screen_s") == 0)
    {
        tmpLayer->m_screen.s = pFloat;
        //CCLog("tmpLayer->m_screen.s = %f", tmpLayer->m_screen.s);
    }
    else if(strcmp(pPropertyName, "objMaxScale") == 0)
    {
        tmpLayer->objMaxScale = pFloat;
        //CCLog("tmpLayer->m_screen.s = %f", tmpLayer->m_screen.s);
    }
    else if(strcmp(pPropertyName, "objMinScale") == 0)
    {
        tmpLayer->objMinScale = pFloat;
        //CCLog("tmpLayer->m_screen.s = %f", tmpLayer->m_screen.s);
    }
    else if(strcmp(pPropertyName, "gridStartX") == 0)
    {
        tmpLayer->gridStartX = pFloat;
        
        //CCSize frameSize = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize();
        //float addWidth = frameSize.width - 960;
        //tmpLayer->gridStartX += addWidth/2;
        
        
        
        /*
         CCSize frameSize = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize();
        float addWidth = frameSize.width - 960;
        if(addWidth > 0)
        {
            tmpLayer->gridStartX += addWidth/2;
        }
        else if(addWidth < 0)
        {
            tmpLayer->gridStartX -= addWidth/2;
        }
        */
        
        //CCLog("tmpLayer->gridStartX = %f", tmpLayer->gridStartX);
    }
    else if(strcmp(pPropertyName, "gridStartY") == 0)
    {
        tmpLayer->gridStartY = pFloat;
        //CCLog("tmpLayer->gridStartY = %f", tmpLayer->gridStartY);
    }
    else if(strcmp(pPropertyName, "gridWidth") == 0)
    {
        tmpLayer->gridWidth = pFloat;
        //CCLog("tmpLayer->gridWidth = %f", tmpLayer->gridWidth);
    }
    else if(strcmp(pPropertyName, "gridHeight") == 0)
    {
        tmpLayer->gridHeight = pFloat;
        //CCLog("tmpLayer->gridHeight = %f", tmpLayer->gridHeight);
    }
    else if(strcmp(pPropertyName, "gridDepth") == 0)
    {
        tmpLayer->gridDepth = pFloat;
        //CCLog("tmpLayer->gridDepth = %f", tmpLayer->gridDepth);
    }
}