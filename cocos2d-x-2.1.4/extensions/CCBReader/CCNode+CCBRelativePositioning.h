#ifndef __CCB_CCNODE_RELATIVEPOSITIONING_H__
#define __CCB_CCNODE_RELATIVEPOSITIONING_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

extern CCPoint getAbsolutePosition(const CCPoint &pt, int nType, const CCSize &containerSize, const char *pPropName);

extern void setRelativeScale(CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName);

extern void setRelativeScale(CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName, CCNode* pParent); //jambam 추가

NS_CC_EXT_END

#endif // __CCB_CCNODE_RELATIVEPOSITIONING_H__
