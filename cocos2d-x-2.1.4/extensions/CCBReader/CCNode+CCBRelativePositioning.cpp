#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

CCPoint getAbsolutePosition(const CCPoint &pt, int nType, const CCSize &containerSize, const char *pPropName)
{
    CCPoint absPt = CCPointZero;
    if (nType == kCCBPositionTypeRelativeBottomLeft)
    {
        absPt = pt;
    }
    else if (nType == kCCBPositionTypeRelativeTopLeft)
    {
        absPt.x = pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (nType == kCCBPositionTypeRelativeTopRight)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (nType == kCCBPositionTypeRelativeBottomRight)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = pt.y;
    }
    else if (nType == kCCBPositionTypePercent)
    {
//        absPt.x = (int)(containerSize.width * pt.x / 100.0f);
//        absPt.y = (int)(containerSize.height * pt.y / 100.0f);
        // [sj] 코코스 빌더와 위치가 일치하지 않아 int -> float 으로 변경
        absPt.x = roundf(containerSize.width * pt.x * 0.01f);
        absPt.y = roundf(containerSize.height * pt.y * 0.01f);
    }
    else if (nType == kCCBPositionTypeMultiplyResolution)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        absPt.x = pt.x * resolutionScale;
        absPt.y = pt.y * resolutionScale;
    }
    
    return absPt;
}

void setRelativeScale(CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName)
{
    CCAssert(pNode, "pNode should not be null");
    
    if (nType == kCCBScaleTypeMultiplyResolution)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        fScaleX *= resolutionScale;
        fScaleY *= resolutionScale;
    }
    
    pNode->setScaleX(fScaleX);
    pNode->setScaleY(fScaleY);
}

//--- jambam 추가
void setRelativeScale(CCNode *pNode, float fScaleX, float fScaleY, int nType, const char* pPropName, CCNode* pParent)
{
    CCAssert(pNode, "pNode should not be null");
    
//    CCLog("<--- pNode.size = (%f, %f)", pNode->getContentSize().width, pNode->getContentSize().height);
    
    if (nType == kCCBScaleTypeMultiplyResolution)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        fScaleX *= resolutionScale;
        fScaleY *= resolutionScale;
    }
    
    //---jambam 추가
    else if(nType == kCCBScaleTypePercent)
    {
        CCSize parentSize = pParent->getContentSize();
        CCSize pNodeSize = pNode->getContentSize();
        
        fScaleX = ((parentSize.width * fScaleX) / 100) / pNodeSize.width;
        fScaleY = ((parentSize.height * fScaleY) / 100) / pNodeSize.height;
        
//        CCLog("fScaleX = %f", fScaleX);
//        CCLog("fScaleY = %f", fScaleY);
    }
    //---
    
    pNode->setScaleX(fScaleX);
    pNode->setScaleY(fScaleY);
}
//---

NS_CC_EXT_END
