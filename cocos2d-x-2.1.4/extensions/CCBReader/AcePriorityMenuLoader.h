//
//  AcePriorityMenuLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#ifndef ScrollViewTest_AcePriorityMenuLoader_h
#define ScrollViewTest_AcePriorityMenuLoader_h

#include "AcePriorityMenu.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AcePriorityMenuLoader : public CCMenuLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AcePriorityMenuLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AcePriorityMenu);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
