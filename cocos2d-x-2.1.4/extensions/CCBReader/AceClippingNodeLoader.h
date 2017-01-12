//
//  AceClippingNodeLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 25..
//
//

#ifndef ScrollViewTest_AceClippingNodeLoader_h
#define ScrollViewTest_AceClippingNodeLoader_h

#include "AceClippingNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceClippingNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceClippingNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceClippingNode);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);

};

NS_CC_EXT_END

#endif
