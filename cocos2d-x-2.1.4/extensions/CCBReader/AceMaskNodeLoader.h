//
//  AceMaskNodeLoader.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#ifndef ScrollViewTest_AceMaskNodeLoader_h
#define ScrollViewTest_AceMaskNodeLoader_h

#include "AceMaskNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceMaskNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceMaskNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceMaskNode);
    
    
    
};

NS_CC_EXT_END

#endif
