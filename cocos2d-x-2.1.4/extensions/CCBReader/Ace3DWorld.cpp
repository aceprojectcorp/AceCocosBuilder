//
//  Ace3DWorld.cpp
//  MLB
//
//  Created by 허정목 on 2014. 2. 26..
//
//

#include "Ace3DWorld.h"

USING_NS_CC_EXT;


Ace3DWorld::~Ace3DWorld()
{
//    CCLog("Ace3DWorld 소멸자");
    
    for(int i=0; i<8; i++)
    {
        CC_SAFE_DELETE(gridPoints[i]);
    }
    
    CC_SAFE_DELETE(homeBase);
    CC_SAFE_DELETE(base1);
    CC_SAFE_DELETE(base2);
    CC_SAFE_DELETE(base3);
    
    for(int i=0; i<10; i++)
    {
        CC_SAFE_DELETE(fence[i]);
    }
    
}

Ace3DWorld::Ace3DWorld()
{
    for(int i=0; i<8; i++)
    {
        gridPoints[i] = NULL;
    }
    
    homeBase = NULL;
    base1 = NULL;
    base2 = NULL;
    base3 = NULL;
    
    for(int i=0; i<10; i++)
    {
        fence[i] = NULL;
    }
}

bool Ace3DWorld::init()
{
    if(!CCNode::init()) return false;
    
    return true;
}

void Ace3DWorld::onEnter()
{
    CCNode::onEnter();
    
    
    
    this->initGrid();
    this->calc3DChild();
    this->setGridVisible(false);
}

void Ace3DWorld::visit()
{
    CCNode::visit();
    
    if(bGridVisible)
    {
        kmGLPushMatrix();
        glLineWidth(2);
        
        
        CCPoint pos_0;
        CCPoint pos_1;
        
        //---멀티해상도때문에 추가된 3D월드 좌표 보정
        CCSize designedResolution = CCSize(960, 640);
        CCSize frameSize = CCDirector::sharedDirector()->getOpenGLView()->getFrameSize();
        float fScaleX = (float)frameSize.width / designedResolution.width;
        float fScaleY = (float)frameSize.height / designedResolution.height;
        float ratio;
        if( fScaleX > fScaleY )
        {
            ratio = frameSize.width / designedResolution.width / fScaleY;
            designedResolution.width *= ratio;
        }
        else
        {
            ratio = frameSize.height / designedResolution.height / fScaleX;
            designedResolution.height *= ratio;
        }
        float addWidth = (designedResolution.width - 960) * 0.5;
        float addHeight = (designedResolution.height - 640) * 0.5;
        //---
        
        //---뒷면
        ccDrawColor4B(255, 0, 0, 255);
        //LeftTop ~ RightTop
        pos_0 = CCPointMake(gridPoints[GRID_LeftTop_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftTop_Back]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightTop_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_RightTop_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //LeftTop ~ LeftBottom
        pos_0 = CCPointMake(gridPoints[GRID_LeftTop_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftTop_Back]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_LeftBottom_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftBottom_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //LeftBottom ~ RightBottom
        pos_0 = CCPointMake(gridPoints[GRID_LeftBottom_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftBottom_Back]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightBottom_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_RightBottom_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //RightBottom ~ RightTop
        pos_0 = CCPointMake(gridPoints[GRID_RightBottom_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_RightBottom_Back]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightTop_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_RightTop_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        
        //---앞면
        ccDrawColor4B(0, 255, 0, 255);
        //LeftTop ~ RightTop
        pos_0 = CCPointMake(gridPoints[GRID_LeftTop_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftTop_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightTop_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_RightTop_Front]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //LeftTop ~ LeftBottom
        pos_0 = CCPointMake(gridPoints[GRID_LeftTop_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftTop_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_LeftBottom_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftBottom_Front]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //LeftBottom ~ RightBottom
        pos_0 = CCPointMake(gridPoints[GRID_LeftBottom_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftBottom_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightBottom_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_RightBottom_Front]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //RightBottom ~ RightTop
        pos_0 = CCPointMake(gridPoints[GRID_RightBottom_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_RightBottom_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightTop_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_RightTop_Front]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //---옆면
        ccDrawColor4B(0, 0, 255, 255);
        //LeftTopFront ~ LeftTopBack
        pos_0 = CCPointMake(gridPoints[GRID_LeftTop_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftTop_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_LeftTop_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftTop_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //LeftBottomFront ~ LeftBottomBack
        pos_0 = CCPointMake(gridPoints[GRID_LeftBottom_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftBottom_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_LeftBottom_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_LeftBottom_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //RightBottomFront ~ RightBottomBack
        pos_0 = CCPointMake(gridPoints[GRID_RightBottom_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_RightBottom_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightBottom_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_RightBottom_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        //RightTopFront ~ RightTopBack
        pos_0 = CCPointMake(gridPoints[GRID_RightTop_Front]->m_resultScreen.u + addWidth, gridPoints[GRID_RightTop_Front]->m_resultScreen.v + addHeight);
        pos_1 = CCPointMake(gridPoints[GRID_RightTop_Back]->m_resultScreen.u + addWidth, gridPoints[GRID_RightTop_Back]->m_resultScreen.v + addHeight);
        ccDrawLine(pos_0, pos_1);
        
        kmGLPopMatrix();
    }
}



_Eye Ace3DWorld::getEye()
{
    return m_eye;
}

void Ace3DWorld::setEye(_Eye eye)
{
    m_eye = eye;
}

_Screen Ace3DWorld::getScreen()
{
    return m_screen;
}

void Ace3DWorld::setScreen(_Screen screen)
{
    m_screen = screen;
}

void Ace3DWorld::initGrid()
{
    float tmpPos[] =
    {
        //x                             y                           z
        //뒷면
        -1,                             1,                          1,     //[0] LeftTop_Back
        1,                             1,                          1,      //[1] RightTop_Back
        -1,                             1,                           -1,     //[2] LeftBottom_Back
        1,                             1,                          -1,      //[3] RightBottom_Back
        
        //앞면
        -1,                            -1,                          1,     //[4] LeftTop_Front
        1,                            -1,                          1,      //[5] RightTop_Front
        -1,                            -1,                          -1,     //[6] LeftBottom_Front
        1,                            -1,                          -1,      //[7] RightBottom_Front
    };
    
    float tmpX = 0;
    float tmpY = 0;
    float tmpZ = 0;
//    float sx = 0;
//    float sy = 0;
//    float tmpAngle = 0;
//    float tmpDistance = 0;
    _Translation tmpTranslation;
    _Rotation tmpRotation;
    _Object tmpObject;
    for(int i=0; i<8; i++)
    {
        //gridPoints[i] = [[Ace3DNode alloc] init];
        if(!gridPoints[i])
        {
            gridPoints[i] = new Ace3DNode();
            this->addChild(gridPoints[i]);
//            CCLog("gridPoints[%d] 생성!", i);
        }
        
        tmpX = gridStartX + tmpPos[i * 3 + 0] * gridWidth / 2;
        tmpY = tmpPos[i * 3 + 1] * gridDepth;
        tmpZ = gridStartY + tmpPos[i * 3 + 2] * gridHeight / 2;
        
        tmpTranslation.dx = 0;
        tmpTranslation.dy = 0;
        tmpTranslation.dz = 0;
        gridPoints[i]->set3DTranslation(tmpTranslation);
        
        tmpRotation.x = 0;
        tmpRotation.y = 0;
        tmpRotation.z = 0;
        gridPoints[i]->set3DRotation(tmpRotation);
        
        tmpObject.x = tmpX;
        tmpObject.y = tmpY;
        tmpObject.z = tmpZ;
        gridPoints[i]->set3DObject(tmpObject);
    }
    
    //홈베이스 위치 계산
    if(!homeBase)
    {
        homeBase = new Ace3DNode();
        this->addChild(homeBase);
        //CCSprite* tmpSpr = CCSprite::create("server/test/hjm/images/arrow.png");
        //tmpSpr->setAnchorPoint(CCPointMake(0.5, 0.5));
        //tmpSpr->setScale(0.2);
        //tmpSpr->setOpacity(100);
#if defined(VISIT_DBG)
        //homeBase->addChild(tmpSpr);
#endif
    }
    tmpX = gridPoints[6]->m_object.x + ((gridPoints[7]->m_object.x - gridPoints[6]->m_object.x) / 2);
    tmpY = gridPoints[6]->m_object.y;
    tmpZ = gridPoints[6]->m_object.z;
    tmpTranslation.dx = 0;
    tmpTranslation.dy = 0;
    tmpTranslation.dz = 0;
    homeBase->set3DTranslation(tmpTranslation);
    
    tmpRotation.x = 0;
    tmpRotation.y = 0;
    tmpRotation.z = 0;
    homeBase->set3DRotation(tmpRotation);
    
    tmpObject.x = tmpX;
    tmpObject.y = tmpY;
    tmpObject.z = tmpZ;
    homeBase->set3DObject(tmpObject);
    
    //1루베이스 위치 계산
    if(!base1)
    {
        base1 = new Ace3DNode();
        this->addChild(base1);
        //CCSprite* tmpSpr = CCSprite::create("server/test/hjm/images/arrow.png");
        //tmpSpr->setAnchorPoint(CCPointMake(0.5, 0.5));
        //tmpSpr->setScale(0.2);
        //tmpSpr->setOpacity(100);
#if defined(VISIT_DBG)
        //base1->addChild(tmpSpr);
#endif
    }
    /*
    tmpTranslation.dx = 0;
    tmpTranslation.dy = 0;
    tmpTranslation.dz = 0;
    base1->set3DTranslation(tmpTranslation);
    
    tmpRotation.x = 0;
    tmpRotation.y = 0;
    tmpRotation.z = 0;
    base1->set3DRotation(tmpRotation);
    
    tmpDistance = homeBase->pB3DEngine->getMeterToDistance(GROUND_BASE_TO_BASE_DISTANCE, gridDepth);
    tmpAngle = 45;
    sx = tmpDistance * cosf(DegreeToRadian(tmpAngle)) * 45.5;
    sy = tmpDistance * sinf(DegreeToRadian(tmpAngle));
    tmpObject = homeBase->m_object;
    tmpObject.x += sx;
    tmpObject.y += sy;
    base1->set3DObject(tmpObject);
    */
    
    //2루베이스 위치 계산
    if(!base2)
    {
        base2 = new Ace3DNode();
        this->addChild(base2);
        //CCSprite* tmpSpr = CCSprite::create("server/test/hjm/images/arrow.png");
        //tmpSpr->setAnchorPoint(CCPointMake(0.5, 0.5));
        //tmpSpr->setScale(0.2);
        //tmpSpr->setOpacity(100);
#if defined(VISIT_DBG)
        //base2->addChild(tmpSpr);
#endif
    }
    /*
    tmpTranslation.dx = 0;
    tmpTranslation.dy = 0;
    tmpTranslation.dz = 0;
    base2->set3DTranslation(tmpTranslation);
    
    tmpRotation.x = 0;
    tmpRotation.y = 0;
    tmpRotation.z = 0;
    base2->set3DRotation(tmpRotation);
    
    tmpDistance = homeBase->pB3DEngine->getMeterToDistance(GROUND_BASE_TO_BASE_DIAGONAL_DISTANCE, gridDepth);
    tmpAngle = 90;
    sx = tmpDistance * cosf(DegreeToRadian(tmpAngle)) * 45.5;
    sy = tmpDistance * sinf(DegreeToRadian(tmpAngle));
    tmpObject = homeBase->m_object;
    tmpObject.x += sx;
    tmpObject.y += sy;
    base2->set3DObject(tmpObject);
    */
    
    //3루베이스 위치 계산
    if(!base3)
    {
        base3 = new Ace3DNode();
        this->addChild(base3);
        //CCSprite* tmpSpr = CCSprite::create("server/test/hjm/images/arrow.png");
        //tmpSpr->setAnchorPoint(CCPointMake(0.5, 0.5));
        //tmpSpr->setScale(0.2);
        //tmpSpr->setOpacity(100);
#if defined(VISIT_DBG)
        //base3->addChild(tmpSpr);
#endif
    }
    /*
    tmpTranslation.dx = 0;
    tmpTranslation.dy = 0;
    tmpTranslation.dz = 0;
    base3->set3DTranslation(tmpTranslation);
    
    tmpRotation.x = 0;
    tmpRotation.y = 0;
    tmpRotation.z = 0;
    base3->set3DRotation(tmpRotation);
    
    tmpDistance = homeBase->pB3DEngine->getMeterToDistance(GROUND_BASE_TO_BASE_DISTANCE, gridDepth);
    tmpAngle = 90 + 45;
    sx = tmpDistance * cosf(DegreeToRadian(tmpAngle)) * 45.5;
    sy = tmpDistance * sinf(DegreeToRadian(tmpAngle));
    tmpObject = homeBase->m_object;
    tmpObject.x += sx;
    tmpObject.y += sy;
    base3->set3DObject(tmpObject);
     */
    
    //팬스
    for(int i=0; i<10; i++)
    {
        if(!fence[i])
        {
            fence[i] = new Ace3DNode();
            this->addChild(fence[i]);
            //CCSprite* tmpSpr = CCSprite::create("server/test/hjm/images/arrow.png");
            //tmpSpr->setAnchorPoint(CCPointMake(0.5, 0.5));
            //tmpSpr->setScale(0.15);
            //tmpSpr->setOpacity(100);
#if defined(VISIT_DBG)
            //fence[i]->addChild(tmpSpr);
#endif
        }
    }
}

void Ace3DWorld::calc3DChild()
{
    
    
    CCArray* children = this->getChildren();
    int size = children->count();
    Ace3DNode* pNode = NULL;
    for(int i=0; i<size; i++)
    {
        pNode = dynamic_cast<Ace3DNode*>(children->objectAtIndex(i));
        if(pNode)
        {
            if(pNode->getTag() == 99)
            {
//                CCLog("~~~~~Player Node");
            }
            
            pNode->calc3DPosition(m_eye, m_screen, gridDepth); //jambam 원본
        }
    }
}

void Ace3DWorld::setGridVisible(bool visible)
{
    bGridVisible = visible;
    
    CCArray* children = this->getChildren();
    int size = children->count();
    Ace3DNode* pNode = NULL;
    for(int i=0; i<size; i++)
    {
        pNode = dynamic_cast<Ace3DNode*>(children->objectAtIndex(i));
        if(pNode)
        {
            pNode->setGridVisible(visible);
        }
    }
}

void Ace3DWorld::setBasePosition(CCPoint base1Pos, CCPoint base2Pos, CCPoint base3Pos, CCPoint homebasePos)
{
    basePosition[0] = base1Pos;
    basePosition[1] = base2Pos;
    basePosition[2] = base3Pos;
    basePosition[3] = homebasePos;
}