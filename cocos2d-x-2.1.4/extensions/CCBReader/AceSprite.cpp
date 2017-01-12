//
//  AceSprite.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#include "AceSprite.h"

USING_NS_CC_EXT;

void AceSprite::onEnter()
{
    CCNode::onEnter();
    
    setBlendType(blendType);
}

void AceSprite::setBlendType(int type)
{
    ccBlendFunc _blendFunc;
    switch(type)
    {
        case BLEND_TYPE_NORMAL :
            _blendFunc.src = GL_ONE;
            _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
            break;
        case BLEND_TYPE_LINEAR_DODGE :
            _blendFunc.src = GL_ONE;
            _blendFunc.dst = GL_ONE;
            break;
        case BLEND_TYPE_SCREEN :
            _blendFunc.src = GL_ONE;
            _blendFunc.dst = GL_ONE_MINUS_SRC_COLOR;
            break;
        case BLEND_TYPE_MULTIPLY :
            _blendFunc.src = GL_DST_COLOR;
            _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
            break;
    }
    setBlendFunc(_blendFunc);
}