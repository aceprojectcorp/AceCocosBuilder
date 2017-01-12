//
//  AceExtMenuItemLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#ifndef ScrollViewTest_AceExtMenuItemLoader_h
#define ScrollViewTest_AceExtMenuItemLoader_h

#include "AceExtMenuItem.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceExtMenuItemLoader : public CCMenuItemLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceExtMenuItemLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceExtMenuItem);
    
    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
