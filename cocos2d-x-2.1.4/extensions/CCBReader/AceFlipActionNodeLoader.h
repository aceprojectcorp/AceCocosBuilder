//
//  AceFlipActionNodeLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 31..
//
//

#ifndef ScrollViewTest_AceFlipActionNodeLoader_h
#define ScrollViewTest_AceFlipActionNodeLoader_h

#include "AceFlipActionNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceFlipActionNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceFlipActionNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceFlipActionNode);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
    virtual void onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader);
};

NS_CC_EXT_END

#endif
