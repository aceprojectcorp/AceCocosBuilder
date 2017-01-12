//
//  Ace3DBallLoader.h
//  MLB
//
//  Created by 허정목 on 2014. 3. 3..
//
//

#ifndef MLB_Ace3DBallLoader_h
#define MLB_Ace3DBallLoader_h

#include "Ace3DBall.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class Ace3DBallLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Ace3DBallLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Ace3DBall);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
