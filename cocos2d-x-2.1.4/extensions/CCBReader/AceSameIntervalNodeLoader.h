//
//  AceSameIntervalNodeLoader.h
//  MLB
//
//  Created by 허정목 on 2014. 7. 31..
//
//

#ifndef MLB_AceSameIntervalNodeLoader_h
#define MLB_AceSameIntervalNodeLoader_h

#include "AceSameIntervalNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceSameIntervalNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceSameIntervalNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceSameIntervalNode);
};

NS_CC_EXT_END

#endif