//
//  actToggleVisibilityLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actToggleVisibilityLoader_h
#define ScrollViewTest_actToggleVisibilityLoader_h

#include "actToggleVisibility.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class actToggleVisibilityLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(actToggleVisibilityLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(actToggleVisibility);
    
    
    
    
    
};

NS_CC_EXT_END

#endif
