//
//  cs_if_falseLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 16..
//
//

#ifndef ScrollViewTest_cs_if_falseLoader_h
#define ScrollViewTest_cs_if_falseLoader_h

#include "cs_if_false.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class cs_if_falseLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(cs_if_falseLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cs_if_false);
    
    
};

NS_CC_EXT_END

#endif
