//
//  AceScale9SpriteNodeLoader.h
//  MLB
//
//  Created by 허정목 on 2014. 5. 23..
//
//

#ifndef MLB_AceScale9SpriteNodeLoader_h
#define MLB_AceScale9SpriteNodeLoader_h

#include "AceScale9SpriteNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceScale9SpriteNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceScale9SpriteNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceScale9SpriteNode);
};

NS_CC_EXT_END

#endif
