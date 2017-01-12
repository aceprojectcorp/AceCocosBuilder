//
//  AceClippingNodeLoader.h
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#ifndef AceBarGraphLoader_h
#define AceBarGraphLoader_h

#include "AceBarGraph.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceBarGraphLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceBarGraphLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceBarGraph);
    
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
    virtual void onHandlePropTypeInteger(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pInteger, CCBReader* pCCBReader);
    virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
