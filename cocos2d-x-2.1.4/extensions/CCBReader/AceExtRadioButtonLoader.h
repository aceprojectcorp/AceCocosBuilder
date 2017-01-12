//
//  AceExtRadioButtonLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 5..
//
//

#ifndef ScrollViewTest_AceExtRadioButtonLoader_h
#define ScrollViewTest_AceExtRadioButtonLoader_h

#include "AceExtRadioButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceExtRadioButtonLoader : public CCMenuItemLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceExtRadioButtonLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceExtRadioButton);
    
    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
