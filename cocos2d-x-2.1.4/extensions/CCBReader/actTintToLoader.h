//
//  actTintToLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actTintToLoader_h
#define ScrollViewTest_actTintToLoader_h

#include "actTintTo.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class actTintToLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(actTintToLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(actTintTo);
    
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
    
};

NS_CC_EXT_END

#endif
