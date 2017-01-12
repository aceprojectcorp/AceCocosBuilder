//
//  AceCompositeLabelLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#ifndef ScrollViewTest_AceCompositeLabelLoader_h
#define ScrollViewTest_AceCompositeLabelLoader_h

#include "AceCompositeLabel.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceCompositeLabelLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceCompositeLabelLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceCompositeLabel);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
