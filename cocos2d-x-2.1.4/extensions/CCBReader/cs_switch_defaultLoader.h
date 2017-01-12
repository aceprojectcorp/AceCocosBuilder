//
//  cs_switch_defaultLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_switch_defaultLoader_h
#define ScrollViewTest_cs_switch_defaultLoader_h

#include "cs_switch_default.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class cs_switch_defaultLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(cs_switch_defaultLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cs_switch_default);
    
    
};

NS_CC_EXT_END

#endif
