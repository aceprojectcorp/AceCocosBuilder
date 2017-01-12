//
//  AceFlowLayerLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 26..
//
//

#ifndef ScrollViewTest_AceFlowLayerLoader_h
#define ScrollViewTest_AceFlowLayerLoader_h

#include "AceFlowLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceFlowLayerLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceFlowLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceFlowLayer);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
