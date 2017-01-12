//
//  AceTextFieldLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 29..
//
//

#ifndef ScrollViewTest_AceTextFieldLoader_h
#define ScrollViewTest_AceTextFieldLoader_h

#include "AceTextField.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceTextFieldLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceTextFieldLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceTextField);
    
    virtual void onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader);    
    
};

NS_CC_EXT_END

#endif
