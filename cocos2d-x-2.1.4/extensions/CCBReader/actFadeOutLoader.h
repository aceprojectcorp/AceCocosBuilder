//
//  actFadeOutLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actFadeOutLoader_h
#define ScrollViewTest_actFadeOutLoader_h

#include "actFadeOut.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class actFadeOutLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(actFadeOutLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(actFadeOut);
    
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    
};

NS_CC_EXT_END

#endif
