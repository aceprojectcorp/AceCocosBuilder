//
//  cs_if_trueLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_if_trueLoader_h
#define ScrollViewTest_cs_if_trueLoader_h

#include "cs_if_true.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class cs_if_trueLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(cs_if_trueLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cs_if_true);
    
    
};

NS_CC_EXT_END

#endif
