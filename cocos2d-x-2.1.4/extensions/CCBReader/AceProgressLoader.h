//
//  AceProgressLoader.h
//  MLB
//
//  Created by 승재 한 on 2014. 7. 21..
//
//

#ifndef __MLB__AceProgressLoader__
#define __MLB__AceProgressLoader__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "AceProgress.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN

class CCBReader;
class AceProgressLoader
: public CCNodeLoader
{
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceProgress);
    
    virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
    virtual void onHandlePropTypeIntegerLabeled(CCNode* pNode, CCNode* pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader* pCCBReader);
    virtual void onHandlePropTypeString(CCNode* pNode, CCNode* pParent, const char* pPropertyName, const char* pString, CCBReader* pCCBReader);
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceProgressLoader, loader);
};

NS_CC_EXT_END

#endif /* defined(__MLB__AceProgressLoader__) */
