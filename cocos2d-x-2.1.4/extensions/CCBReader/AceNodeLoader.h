//
//  AceNodeLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 19..
//
//

#ifndef ScrollViewTest_AceNodeLoader_h
#define ScrollViewTest_AceNodeLoader_h

#include "AceNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceNode);
};

NS_CC_EXT_END

#endif
