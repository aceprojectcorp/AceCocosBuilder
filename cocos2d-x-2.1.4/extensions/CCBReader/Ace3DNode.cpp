//
//  Ace3DNode.cpp
//  MLB
//
//  Created by 허정목 on 2014. 2. 26..
//
//

#include "Ace3DNode.h"
#include "Ace3DWorld.h"

USING_NS_CC_EXT;

bool Ace3DNode::init()
{
    if(!CCNode::init()) return false;
    
    return true;
}

void Ace3DNode::onEnter()
{
    CCNode::onEnter();
    
    
    
    positionLabel = CCLabelTTF::create("", "Thonburi", 24);
    positionLabel->setString("(0, 0, 0)");
    positionLabel->setAnchorPoint(CCPointMake(0, 1));
    this->addChild(positionLabel);
    
    setGridVisible(false);
}

void Ace3DNode::visit()
{
    CCNode::visit();
    
    /*
    if(bGridVisible)
    {
        kmGLPushMatrix();
        glLineWidth(2);
        
        CCPoint tmpPoints[4];
        Ace3DWorld* tmpWorld = (Ace3DWorld*)this->getParent();
        _Object tmpObject;
        _TranslationRotation tmpTranslationRotation;
        _ResultScreen tmpResultScreen;
        
        //leftBack
        tmpObject.x = m_object.x - 10;
        tmpObject.y = m_object.y + 0.1;
        tmpObject.z = m_object.z;
        tmpTranslationRotation = this->getCalcTranslationRotation(tmpObject, m_translation, m_rotation);
        tmpResultScreen = this->getCalcResultScreen(tmpTranslationRotation, tmpWorld->getEye(), tmpWorld->getScreen());
        tmpPoints[0] = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
        
        //leftFront
        tmpObject.x = m_object.x - 10;
        tmpObject.y = m_object.y - 0.1;
        tmpObject.z = m_object.z;
        tmpTranslationRotation = this->getCalcTranslationRotation(tmpObject, m_translation, m_rotation);
        tmpResultScreen = this->getCalcResultScreen(tmpTranslationRotation, tmpWorld->getEye(), tmpWorld->getScreen());
        tmpPoints[1] = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
        
        //rightFront
        tmpObject.x = m_object.x + 10;
        tmpObject.y = m_object.y - 0.1;
        tmpObject.z = m_object.z;
        tmpTranslationRotation = this->getCalcTranslationRotation(tmpObject, m_translation, m_rotation);
        tmpResultScreen = this->getCalcResultScreen(tmpTranslationRotation, tmpWorld->getEye(), tmpWorld->getScreen());
        tmpPoints[2] = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
        
        //rightBack
        tmpObject.x = m_object.x + 10;
        tmpObject.y = m_object.y + 0.1;
        tmpObject.z = m_object.z;
        tmpTranslationRotation = this->getCalcTranslationRotation(tmpObject, m_translation, m_rotation);
        tmpResultScreen = this->getCalcResultScreen(tmpTranslationRotation, tmpWorld->getEye(), tmpWorld->getScreen());
        tmpPoints[3] = CCPointMake(tmpResultScreen.u, tmpResultScreen.v);
        
        ccDrawSolidPoly(tmpPoints, 4, ccc4f(0, 0, 0, 0.7));
        
        kmGLPopMatrix();
    }
     */
}

void Ace3DNode::set3DTranslation(_Translation translation)
{
    m_translation = translation;
}

void Ace3DNode::set3DRotation(_Rotation rotation)
{
    m_rotation = rotation;
}

void Ace3DNode::set3DObject(_Object object)
{
    m_object = object;
}

void Ace3DNode::calc3DPosition(_Eye eye, _Screen screen, float gridDepth)
{
    m_translationRotation = this->getCalcTranslationRotation(m_object, m_translation, m_rotation);
    m_resultScreen = this->getCalcResultScreen(m_translationRotation, eye, screen);
    
    Ace3DWorld* tmpWorld = (Ace3DWorld*)this->getParent();
    float maxScale = tmpWorld->objMaxScale;
    float minScale = tmpWorld->objMinScale;
    float nowZ = (m_object.y - gridDepth) * -1;
    float maxZ = gridDepth * 2;
    scale3D = (nowZ / maxZ) * maxScale;
    if(scale3D < minScale)
    {
        scale3D = minScale;
    }
    if(scale3D > maxScale)
    {
        scale3D = maxScale;
    }
    
    this->setScale(scale3D);
    
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
    
    this->setPosition(CCPointMake(m_resultScreen.u + addWidth, m_resultScreen.v + addHeight));
    
    //---디버깅용
    //char buf[256];
    //sprintf(buf, "(%.1f, %.1f, %.1f)", m_object.x, m_object.y, m_object.z);
    //positionLabel->setString(buf);
    //---
}

void Ace3DNode::setGridVisible(bool visible)
{
    bGridVisible = visible;
    
    positionLabel->setVisible(visible);
}

//----------------------------------------------------------------------------------------------------------------임시
_TranslationRotation Ace3DNode::getCalcTranslationRotation(_Object tmpObject, _Translation tmpTranslation, _Rotation tmpRotation)
{
    _TranslationRotation tmpTranslationRotation;
    
    //cos@x
    //cos@y
    //cos@z
    //sin@x
    //sin@y
    //sin@z
   
    float radianX = DegreeToRadian(tmpRotation.x);
    float radianY = DegreeToRadian(tmpRotation.y);
    float radianZ = DegreeToRadian(tmpRotation.z);
    
    float cosXvalue = cosf(radianX);
    float cosYvalue = cosf(radianY);
    float cosZvalue = cosf(radianZ);
    
    float sinXvalue = sinf(radianX);
    float sinYvalue = sinf(radianY);
    float sinZvalue = sinf(radianZ);
    
    //xxx = x(cos@y cos@z) + y(sin@x sin@y cos@z - cos@x sin@z) + z(cos@x sin@y cos@z + sin@x sin@z)
    tmpTranslationRotation.xxx = (tmpObject.x + tmpTranslation.dx) *
    (cosYvalue *
     cosZvalue) +
    (tmpObject.y + tmpTranslation.dy) *
    (sinXvalue *
     sinYvalue *
     cosZvalue -
     cosXvalue *
     sinZvalue) +
    (tmpObject.z + tmpTranslation.dz) *
    (cosXvalue *
     sinYvalue *
     cosZvalue +
     sinXvalue *
     sinZvalue);
    
    //yyy = x(cos@y sin@z) + y(sin@x sin@y sin@z + cos@x cos@z) + z(cos@x sin@y sin@z - sin@x cos@z)
    tmpTranslationRotation.yyy = (tmpObject.x + tmpTranslation.dx) *
    (cosYvalue *
     sinZvalue) +
    (tmpObject.y + tmpTranslation.dy) *
    (sinXvalue *
     sinYvalue *
     sinZvalue +
     cosXvalue *
     cosZvalue) +
    (tmpObject.z + tmpTranslation.dz) *
    (cosXvalue *
     sinYvalue *
     sinZvalue -
     sinXvalue *
     cosZvalue);
    
    //zzz = -x sin@y + y(sin@x cos@y) + z(cos@x cos@y)
    tmpTranslationRotation.zzz = -(tmpObject.x + tmpTranslation.dx) *
    sinYvalue +
    (tmpObject.y + tmpTranslation.dy) *
    (sinXvalue *
     cosYvalue) +
    (tmpObject.z + tmpTranslation.dz) *
    (cosXvalue *
     cosYvalue);
    
    
    /*
     //xxx = x(cos@y cos@z) + y(sin@x sin@y cos@z - cos@x sin@z) + z(cos@x sin@y cos@z + sin@x sin@z)
     tmpTranslationRotation.xxx = (tmpObject.x + tmpTranslation.dx) *
     (cosf(DegreeToRadian(tmpRotation.y)) *
     cosf(DegreeToRadian(tmpRotation.z))) +
     (tmpObject.y + tmpTranslation.dy) *
     (sinf(DegreeToRadian(tmpRotation.x)) *
     sinf(DegreeToRadian(tmpRotation.y)) *
     cosf(DegreeToRadian(tmpRotation.z)) -
     cosf(DegreeToRadian(tmpRotation.x)) *
     sinf(DegreeToRadian(tmpRotation.z))) +
     (tmpObject.z + tmpTranslation.dz) *
     (cosf(DegreeToRadian(tmpRotation.x)) *
     sinf(DegreeToRadian(tmpRotation.y)) *
     cosf(DegreeToRadian(tmpRotation.z)) +
     sinf(DegreeToRadian(tmpRotation.x)) *
     sinf(DegreeToRadian(tmpRotation.z)));
     
     //yyy = x(cos@y sin@z) + y(sin@x sin@y sin@z + cos@x cos@z) + z(cos@x sin@y sin@z - sin@x cos@z)
     tmpTranslationRotation.yyy = (tmpObject.x + tmpTranslation.dx) *
     (cosf(DegreeToRadian(tmpRotation.y)) *
     sinf(DegreeToRadian(tmpRotation.z))) +
     (tmpObject.y + tmpTranslation.dy) *
     (sinf(DegreeToRadian(tmpRotation.x)) *
     sinf(DegreeToRadian(tmpRotation.y)) *
     sinf(DegreeToRadian(tmpRotation.z)) +
     cosf(DegreeToRadian(tmpRotation.x)) *
     cosf(DegreeToRadian(tmpRotation.z))) +
     (tmpObject.z + tmpTranslation.dz) *
     (cosf(DegreeToRadian(tmpRotation.x)) *
     sinf(DegreeToRadian(tmpRotation.y)) *
     sinf(DegreeToRadian(tmpRotation.z)) -
     sinf(DegreeToRadian(tmpRotation.x)) *
     cosf(DegreeToRadian(tmpRotation.z)));
     
     //zzz = -x sin@y + y(sin@x cos@y) + z(cos@x cos@y)
     tmpTranslationRotation.zzz = -(tmpObject.x + tmpTranslation.dx) *
     sinf(DegreeToRadian(tmpRotation.y)) +
     (tmpObject.y + tmpTranslation.dy) *
     (sinf(DegreeToRadian(tmpRotation.x)) *
     cosf(DegreeToRadian(tmpRotation.y))) +
     (tmpObject.z + tmpTranslation.dz) *
     (cosf(DegreeToRadian(tmpRotation.x)) *
     cosf(DegreeToRadian(tmpRotation.y)));
     */
    
    tmpTranslationRotation.xxx = tmpObject.x;
    tmpTranslationRotation.yyy = tmpObject.y;
    tmpTranslationRotation.zzz = tmpObject.z;
    
    return tmpTranslationRotation;
}

_ResultScreen Ace3DNode::getCalcResultScreen(_TranslationRotation tmpTranslationRotation, _Eye tmpEye, _Screen tmpScreen)
{
    _ResultScreen tmpResultScreen;
    
    //u = x - (x-a)(y-s) / (y-b)
    if((tmpTranslationRotation.yyy - tmpEye.b) !=0)
    {
        tmpResultScreen.u = tmpTranslationRotation.xxx - (tmpTranslationRotation.xxx - tmpEye.a) * (tmpTranslationRotation.yyy - tmpScreen.s) / (tmpTranslationRotation.yyy - tmpEye.b);
    }
    
    //v = z - (z-c)(y-s) / (y-b)
    if((tmpTranslationRotation.yyy - tmpEye.b) != 0)
    {
        tmpResultScreen.v = tmpTranslationRotation.zzz - (tmpTranslationRotation.zzz - tmpEye.c) * (tmpTranslationRotation.yyy - tmpScreen.s) / (tmpTranslationRotation.yyy - tmpEye.b);
    }
    
    return tmpResultScreen;
}

_ResultScreen Ace3DNode::get3Dto2DPosition(_Object tmpObject, _Eye tmpEye, _Screen tmpScreen, float tmpGridDepth, _Translation tmpTranslation, _Rotation tmpRotation)
{
    _ResultScreen tmpResultScreen;
    
    _TranslationRotation tmpTranslationRotation = this->getCalcTranslationRotation(tmpObject, tmpTranslation, tmpRotation);
    tmpResultScreen = this->getCalcResultScreen(tmpTranslationRotation, tmpEye, tmpScreen);
    
    return tmpResultScreen;
}

_Object Ace3DNode::get2Dto3DPosition(_Object mObject, float posX2D, float posY2D, _Eye tmpEye, _Screen tmpScreen)
{
    _Object tmpObject;
    
    float tmpX;
    float tmpY;
    float tmpZ = mObject.z;
    
    /*
     //posY2D = tmpZ - (tmpZ - tmpEye.c) * (tmpY - tmpScreen.s) / (tmpY - tmpEye.b);
     시작 : v = z - (z-c)(y-s) / (y-b)
     v = z - (z-c)(y-s)
     --------------
     (y-b)
     v(y-b) = z(y-b) - (z-c)(y-s)
     vy - vb = zy - zb - (zy - zs - cy + cs)
     = zy - zb - zy + zs + cy - cs
     = -zb + zs + cy - cs
     vy - cy = -zb + zs - cs + vb
     y(v-c) = zs - cs - zb  + vb
     = s(z-c) - zb + vb
     = s(z-c) + b(v-z)
     y = s(z-c) + b(v-z)
     ----------------
     (v-c)
     y = (s(z-c) + b(v-z)) / (v-c)
     
     v : posY2D
     z : tmpZ
     c : tmpEye.c
     y : tmpY
     s : tmpScreen.s
     b = tmpEye.b
     
     결과 : y = (s(z-c) + b(v-z)) / (v - c)
     */
    tmpY = (tmpScreen.s * (tmpZ - tmpEye.c) + tmpEye.b * (posY2D - tmpZ)) / (posY2D - tmpEye.c);
    
    /*
     //posX2D = tmpX - (tmpX - tmpEye.a) * (tmpY - tmpScreen.s) / (tmpY - tmpEye.b);
     시작 : u = x - (x-a)(y-s) / (y-b)
     u = x - (x-a)(y-s)
     ----------
     (y-b)
     u(y-b) = x(y-b) - (x-a)(y-s)
     uy - ub = xy - xb - (xy - xs - ay + as)
     = xy - xb - xy + xs + ay - as
     = -xb + xs + ay - as
     = x(s-b) + ay - as
     x(s-b) = uy - ub - ay + as
     x = uy - ub - ay + as
     -----------------
     (s-b)
     x = u(y-b) - a(y-s)
     ---------------
     (s-b)
     x = (u(y-b) - a(y-s)) / (s-b)
     
     u : posX2D
     x = tmpX
     a = tmpEye.a
     y = tmpY
     s = tmpScreen.s
     b = tmpEye.b
     
     결과 : x = (u(y-b) - a(y-s)) / (s - b)
     */
    tmpX = (posX2D * (tmpY - tmpEye.b) - tmpEye.a * (tmpY - tmpScreen.s)) / (tmpScreen.s - tmpEye.b);
    
    tmpObject.x = tmpX;
    tmpObject.y = tmpY;
    tmpObject.z = tmpZ;
    
    return tmpObject;
}
//----------------------------------------------------------------------------------------------------------------









