//
//  AceSpriteLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#ifndef ScrollViewTest_AceSpriteLoader_h
#define ScrollViewTest_AceSpriteLoader_h

#include "AceSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceSpriteLoader : public CCSpriteLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceSpriteLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceSprite);
    
    virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
    
};

NS_CC_EXT_END

#endif
