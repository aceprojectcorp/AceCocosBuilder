//
//  Ace3DNode.h
//  MLB
//
//  Created by 허정목 on 2014. 2. 26..
//
//

#ifndef MLB_Ace3DNode_h
#define MLB_Ace3DNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

#define RadianToDegree(x) (x * 57.29577951)
#define DegreeToRadian(x) (x * 0.017453293)

typedef struct
{
    float a;
    float b;
    float c;
}_Eye;

typedef struct
{
    float s;
}_Screen;

typedef struct
{
    float dx;
    float dy;
    float dz;
}_Translation;

typedef struct
{
    float x;
    float y;
    float z;
}_Rotation;

typedef struct
{
    float x;
    float y;
    float z;
}_Object;

typedef struct
{
    float xxx;
    float yyy;
    float zzz;
}_TranslationRotation;

typedef struct
{
    float u;
    float v;
}_ResultScreen;

class Ace3DNode
: public CCNode
{
public:
    virtual bool init();
    virtual void onEnter();
    virtual void visit();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Ace3DNode, create);
    
public:
    _Translation m_translation;
    _Rotation m_rotation;
    _Object m_object;
    _TranslationRotation m_translationRotation;
    _ResultScreen m_resultScreen;
    
    float scale3D; //3D공간의 z값에의해 계산된 scale값 : calc3DPosition()안에서 계산된다.
    bool bGridVisible;
    
    //B3DEngine* pB3DEngine;
public:
    void set3DTranslation(_Translation translation);
    void set3DRotation(_Rotation rotation);
    void set3DObject(_Object object);
    
    void calc3DPosition(_Eye eye, _Screen screen, float gridDepth);
    
private:
    CCLabelTTF* positionLabel;  //3DNode의 공간 좌표를 표시해준다.(디버겅용. 나중에 삭제한다.)
    
public:
    void setGridVisible(bool visible);
    
    //---3D 계산관련
public:
    _TranslationRotation getCalcTranslationRotation(_Object tmpObject, _Translation tmpTranslation, _Rotation tmpRotation);
    _ResultScreen getCalcResultScreen(_TranslationRotation tmpTranslationRotation, _Eye tmpEye, _Screen tmpScreen);
    
    //2d좌표를 입력받아서 3d좌표를 얻는다.(y축 값은 고정이라고 생각한다. x축과 z축만 변한다고 가정)
    _Object get2Dto3DPosition(_Object mObject, float posX2D, float posY2D, _Eye tmpEye, _Screen tmpScreen);
    
    //3d좌표(_Object)를 입력받아서 2d좌표를 얻는다.
    _ResultScreen get3Dto2DPosition(_Object tmpObject, _Eye tmpEye, _Screen tmpScreen, float tmpGridDepth, _Translation tmpTranslation, _Rotation tmpRotation);
    
    //3D공간의 거리단위를 실제거리단위(m)로 바꾼다.
    //float getDistanceToMeter(float distance, float zDepth);
    //---
};

NS_CC_EXT_END

#endif
