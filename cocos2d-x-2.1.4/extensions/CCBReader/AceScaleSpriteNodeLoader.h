//
//  AceScaleSpriteNodeLoader.h
//  MLB
//
//  Created by 허정목 on 2014. 7. 30..
//
//

#ifndef MLB_AceScaleSpriteNodeLoader_h
#define MLB_AceScaleSpriteNodeLoader_h

#include "AceScaleSpriteNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_CC_EXT_BEGIN



/* Forward declaration. */
class CCBReader;


class AceScaleSpriteNodeLoader : public CCNodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AceScaleSpriteNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AceScaleSpriteNode);
};

NS_CC_EXT_END

#endif
