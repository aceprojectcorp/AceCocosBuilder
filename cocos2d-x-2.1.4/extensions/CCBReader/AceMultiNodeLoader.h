//
//  AceMultiNodeLoader.h
//  MLB
//
//  Created by 허정목 on 2014. 8. 11..
//
//

#ifndef MLB_AceMultiNodeLoader_h
#define MLB_AceMultiNodeLoader_h

#include "AceMultiNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceMultiNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceMultiNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceMultiNode);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
    

};

NS_CC_EXT_END

#endif
