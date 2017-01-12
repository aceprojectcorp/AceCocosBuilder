//
//  Ace3DPlayer.cpp
//  MLB
//
//  Created by 허정목 on 2014. 3. 11..
//
//

#include "Ace3DPlayer.h"
#include "Ace3DWorld.h"

USING_NS_CC_EXT;

Ace3DWorld* tmpWorld3D;

bool Ace3DPlayer::init()
{
    if(!Ace3DNode::init()) return false;
    
    return true;
}

void Ace3DPlayer::onEnter()
{
    Ace3DNode::onEnter();
    
    
    tmpWorld3D = NULL;

    
    /*
    collision.h = PLAYER_COLLISION_HEIGHT * 12.0f;
    collision.radiusMeter = PLAYER_COLLISION_RADIUS;
    */
     
    
    tmpWorld3D = (Ace3DWorld*)this->getParent();
    mEye = tmpWorld3D->getEye();
    mScreen = tmpWorld3D->getScreen();
    fGridDepth = tmpWorld3D->gridDepth;
    
    
    this->scheduleUpdate();
}

void Ace3DPlayer::visit()
{
    CCNode::visit();
    
    kmGLPushMatrix();
    glLineWidth(1);
    
    //---test
    /*
    CCPoint pos_0;
    CCPoint pos_1;
    
    if(tmpWorld3D != NULL && isVisible())
    {
        _Object tmpDstobject;
        float sx;
        float sy;
        CCPoint tmpDstPoint;
        _ResultScreen tmpResultScreen;
        
        
        //시야
        sx = pB3DEngine->getMeterToDistance(PLAYER_COLLISION_RADIUS, tmpWorld3D->gridDepth) * cosf(DegreeToRadian(dstAngle)) * 45.5;
        sy = pB3DEngine->getMeterToDistance(PLAYER_COLLISION_RADIUS, tmpWorld3D->gridDepth) * sinf(DegreeToRadian(dstAngle));
        
        tmpDstobject = m_object;
        tmpDstobject.x += sx;
        tmpDstobject.y += sy;
        tmpResultScreen = pB3DEngine->get3Dto2DPosition(tmpDstobject, mEye, mScreen, fGridDepth, m_translation, m_rotation);
        tmpDstPoint = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
        
        pos_0 = this->getPosition();
        pos_1 = tmpDstPoint;
        glLineWidth(2);
        ccDrawColor4B(255, 0, 0, 255);
        ccDrawLine(pos_0, pos_1);
        \
        
        //키
        tmpDstobject = m_object;
        tmpDstobject.z += collision.h;
        tmpResultScreen = pB3DEngine->get3Dto2DPosition(tmpDstobject, mEye, mScreen, fGridDepth, m_translation, m_rotation);
        tmpDstPoint = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
        
        pos_0 = this->getPosition();
        pos_1 = tmpDstPoint;
        glLineWidth(2);
        ccDrawColor4B(0, 255, 0, 255);
        ccDrawLine(pos_0, pos_1);
        
        //충돌영역
        CCPoint tmpCollisionPoints[36];
        for(int i=0; i<36; i++)
        {
            sx = pB3DEngine->getMeterToDistance(collision.radiusMeter, tmpWorld3D->gridDepth) * cosf(DegreeToRadian(i * 10)) * 45.5;
            sy = pB3DEngine->getMeterToDistance(collision.radiusMeter, tmpWorld3D->gridDepth) * sinf(DegreeToRadian(i * 10));
            
            tmpDstobject = m_object;
            tmpDstobject.x += sx;
            tmpDstobject.y += sy;
            tmpResultScreen = pB3DEngine->get3Dto2DPosition(tmpDstobject, mEye, mScreen, fGridDepth, m_translation, m_rotation);
            tmpDstPoint = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
            
            tmpCollisionPoints[i] = tmpDstPoint;
        }
        ccDrawSolidPoly(tmpCollisionPoints, 36, ccc4f(0, 0, 0, 0.3));
    }
     */
    //---
    
    kmGLPopMatrix();
}