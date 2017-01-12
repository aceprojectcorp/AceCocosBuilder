//
//  AceExtMenu.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#ifndef ScrollViewTest_AceExtMenu_h
#define ScrollViewTest_AceExtMenu_h

#include "cocos2d.h"
#include "cocos-ext.h"


NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;




class AceExtMenu
: public cocos2d::CCMenu
{
public:
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceExtMenu, create);
    

private:
    //NODE_FACTORY_DEC(ExtMenu);
    
public:
    bool init();
    static AceExtMenu* menu();
    
    // itemForTouch 메소드가 CCMenu에서 virtual로 선언되지 않았기 때문에 라이브러리 코드를 수정하지 않고
    // 해당 메소드를 사용하는 메소드를 다시 override함. 그렇지 않으면 CCMenu의 itemForTouch가 실행됨
    bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    void ccTouchMoved(CCTouch* touch, CCEvent* event);
protected:
    CCMenuItem* itemForTouch(CCTouch * touch);
    
    
};

NS_CC_EXT_END

#endif
