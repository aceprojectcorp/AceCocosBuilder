//
//  AceExtToggleButtonLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#ifndef ScrollViewTest_AceExtToggleButtonLoader_h
#define ScrollViewTest_AceExtToggleButtonLoader_h

#include "AceExtToggleButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceExtToggleButtonLoader : public CCMenuItemLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceExtToggleButtonLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceExtToggleButton);
    
   
    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
