//
//  actZNodeLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#ifndef ScrollViewTest_actZNodeLoader_h
#define ScrollViewTest_actZNodeLoader_h

#include "actZNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class actZNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(actZNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(actZNode);
    
    
    
};

NS_CC_EXT_END

#endif
