//
//  AceClippingScrollNodeLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 2..
//
//

#ifndef ScrollViewTest_AceClippingScrollNodeLoader_h
#define ScrollViewTest_AceClippingScrollNodeLoader_h

#include "AceClippingScrollNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceClippingScrollNodeLoader : public CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceClippingScrollNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceClippingScrollNode);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
    
};

NS_CC_EXT_END


#endif
