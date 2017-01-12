//
//  AceExtMenuLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 3..
//
//

#ifndef ScrollViewTest_AceExtMenuLoader_h
#define ScrollViewTest_AceExtMenuLoader_h

#include "AceExtMenu.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceExtMenuLoader : public CCMenuLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceExtMenuLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceExtMenu);
    
    
};

NS_CC_EXT_END

#endif
