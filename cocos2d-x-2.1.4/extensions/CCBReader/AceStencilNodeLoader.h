//
//  AceClippingNodeLoader.h
//  ScrollViewTest
//
//  Created by 안현석 on 2015. 2. 25..
//
//

#ifndef AceStencilNodeLoader_h
#define AceStencilNodeLoader_h

#include "AceStencilNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceStencilNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceStencilNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceStencilNode);
    
};

NS_CC_EXT_END

#endif
