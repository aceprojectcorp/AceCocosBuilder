//
//  AcePageScrollLayerLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 27..
//
//

#ifndef ScrollViewTest_AcePageScrollLayerLoader_h
#define ScrollViewTest_AcePageScrollLayerLoader_h

#include "AcePageScrollLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AcePageScrollLayerLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AcePageScrollLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AcePageScrollLayer);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
};

NS_CC_EXT_END

#endif
