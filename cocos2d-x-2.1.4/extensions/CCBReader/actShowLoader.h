//
//  actShowLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actShowLoader_h
#define ScrollViewTest_actShowLoader_h

#include "actShow.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class actShowLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(actShowLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(actShow);
    
    
    
    
    
};

NS_CC_EXT_END

#endif
