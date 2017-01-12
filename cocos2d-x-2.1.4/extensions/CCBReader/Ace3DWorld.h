//
//  Ace3DWorld.h
//  MLB
//
//  Created by 허정목 on 2014. 2. 26..
//
//

#ifndef MLB_Ace3DWorld_h
#define MLB_Ace3DWorld_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Ace3DNode.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;

enum
{
    //뒷면
    GRID_LeftTop_Back,
    GRID_RightTop_Back,
    GRID_LeftBottom_Back,
    GRID_RightBottom_Back,
    
    //앞면
    GRID_LeftTop_Front,
    GRID_RightTop_Front,
    GRID_LeftBottom_Front,
    GRID_RightBottom_Front,
};

class Ace3DWorld
: public CCNode
{
public:
    Ace3DWorld();
    ~Ace3DWorld();
    virtual bool init();
    virtual void onEnter();
    virtual void visit();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Ace3DWorld, create);
    
public:
    _Eye m_eye;
    _Screen m_screen;
    
    Ace3DNode* base1;
    Ace3DNode* base2;
    Ace3DNode* base3;
    Ace3DNode* homeBase;
    
    Ace3DNode* fence[10];
    
    
    
    Ace3DNode* gridPoints[8];

    float objMaxScale;
    float objMinScale;
    
    float gridStartX;
    float gridStartY;
    float gridWidth;
    float gridHeight;
    float gridDepth;
    
    CCPoint basePosition[4];
    
private:
    bool bGridVisible;
    
public:
    _Eye getEye();
    void setEye(_Eye eye);
    _Screen getScreen();
    void setScreen(_Screen screen);
    
    void initGrid();
    void calc3DChild();
    void setGridVisible(bool visible);
    void setBasePosition(CCPoint base1Pos, CCPoint base2Pos, CCPoint base3Pos, CCPoint homebasePos);
    

    
};

NS_CC_EXT_END

#endif
