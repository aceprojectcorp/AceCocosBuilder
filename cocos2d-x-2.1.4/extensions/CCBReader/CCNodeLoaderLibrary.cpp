#include "CCNodeLoaderLibrary.h"

#include "CCLayerLoader.h"
#include "CCLayerColorLoader.h"
#include "CCLayerGradientLoader.h"
#include "CCLabelBMFontLoader.h"
#include "CCLabelTTFLoader.h"
#include "CCSpriteLoader.h"
#include "CCScale9SpriteLoader.h"
#include "CCBFileLoader.h"
#include "CCMenuLoader.h"
#include "CCMenuItemLoader.h"
#include "CCMenuItemImageLoader.h"
#include "CCControlButtonLoader.h"
#include "CCParticleSystemQuadLoader.h"
#include "CCScrollViewLoader.h"

//---jambam
#include "AceClippingNodeLoader.h"
#include "AceGridLayerLoader.h"
#include "AceCompositeLabelLoader.h"
#include "AceFlowLayerLoader.h"
#include "AceTickerLoader.h"
#include "AcePageScrollLayerLoader.h"
#include "AceTextFieldLoader.h"
#include "AceClippingScrollNodeLoader.h"
#include "AceExtMenuLoader.h"
#include "AceExtMenuItemLoader.h"
#include "AcePriorityMenuLoader.h"
#include "AceExtToggleButtonLoader.h"
#include "AceExtRadioButtonLoader.h"
#include "cs_ifLoader.h"
#include "cs_if_trueLoader.h"
#include "cs_if_falseLoader.h"
#include "cs_switchLoader.h"
#include "cs_switch_caseLoader.h"
#include "cs_switch_defaultLoader.h"
#include "AceNodeLoader.h"
#include "AceFrameAnimationLoader.h"
#include "AceSpriteLoader.h"
#include "AceMaskNodeLoader.h"
#include "AceFlipActionNodeLoader.h"
#include "actMoveToLoader.h"
#include "actDelayTimeLoader.h"
#include "actPlaceLoader.h"
#include "actJumpToLoader.h"
#include "actBezierToLoader.h"
#include "actCardinalSplineToLoader.h"
#include "actCatmullRomToLoader.h"
#include "actScaleToLoader.h"
#include "actZNodeLoader.h"
#include "actSkewToLoader.h"
#include "actRotationToLoader.h"
#include "actBlinkLoader.h"
#include "actShowLoader.h"
#include "actHideLoader.h"
#include "actToggleVisibilityLoader.h"
#include "actFadeInLoader.h"
#include "actFadeOutLoader.h"
#include "actFadeToLoader.h"
#include "actTintToLoader.h"
#include "actOrbitCameraLoader.h"
#include "Ace3DNodeLoader.h"
#include "Ace3DWorldLoader.h"
#include "Ace3DBallLoader.h"
#include "Ace3DPlayerLoader.h"
#include "AceScale9SpriteNodeLoader.h"
#include "AceScaleSpriteNodeLoader.h"
#include "AceSameIntervalNodeLoader.h"
#include "AceMultiNodeLoader.h"

#include "AceProgressLoader.h"
#include "AceStencilNodeLoader.h"
#include "AceCoverPageScrollLoader.h"
#include "AceAreaGraphLoader.h"
#include "AceBarGraphLoader.h"
//---



NS_CC_EXT_BEGIN

CCNodeLoaderLibrary::CCNodeLoaderLibrary() {

}

CCNodeLoaderLibrary::~CCNodeLoaderLibrary() {
    this->purge(true);
}

void CCNodeLoaderLibrary::registerDefaultCCNodeLoaders() {
    this->registerCCNodeLoader("CCNode", CCNodeLoader::loader());
    this->registerCCNodeLoader("CCLayer", CCLayerLoader::loader());
    this->registerCCNodeLoader("CCLayerColor", CCLayerColorLoader::loader());
    this->registerCCNodeLoader("CCLayerGradient", CCLayerGradientLoader::loader());
    this->registerCCNodeLoader("CCSprite", CCSpriteLoader::loader());
    this->registerCCNodeLoader("CCLabelBMFont", CCLabelBMFontLoader::loader());
    this->registerCCNodeLoader("CCLabelTTF", CCLabelTTFLoader::loader());
    this->registerCCNodeLoader("CCScale9Sprite", CCScale9SpriteLoader::loader());
    this->registerCCNodeLoader("CCScrollView", CCScrollViewLoader::loader());
    this->registerCCNodeLoader("CCBFile", CCBFileLoader::loader());
    this->registerCCNodeLoader("CCMenu", CCMenuLoader::loader());
    this->registerCCNodeLoader("CCMenuItemImage", CCMenuItemImageLoader::loader());
    this->registerCCNodeLoader("CCControlButton", CCControlButtonLoader::loader());
    this->registerCCNodeLoader("CCParticleSystemQuad", CCParticleSystemQuadLoader::loader());
    
    //---jambam
    this->registerCCNodeLoader("AceClippingNode", AceClippingNodeLoader::loader());
    this->registerCCNodeLoader("AceGridLayer", AceGridLayerLoader::loader());
    this->registerCCNodeLoader("AceCompositeLabel", AceCompositeLabelLoader::loader());
    this->registerCCNodeLoader("AceFlowLayer", AceFlowLayerLoader::loader());
    this->registerCCNodeLoader("AceTicker", AceTickerLoader::loader());
    this->registerCCNodeLoader("AcePageScrollLayer", AcePageScrollLayerLoader::loader());
    this->registerCCNodeLoader("AceTextField", AceTextFieldLoader::loader());
    this->registerCCNodeLoader("AceClippingScrollNode", AceClippingScrollNodeLoader::loader());
    this->registerCCNodeLoader("AceExtMenu", AceExtMenuLoader::loader());
    this->registerCCNodeLoader("AceExtMenuItem", AceExtMenuItemLoader::loader());
    this->registerCCNodeLoader("AcePriorityMenu", AcePriorityMenuLoader::loader());
    this->registerCCNodeLoader("AceExtToggleButton", AceExtToggleButtonLoader::loader());
    this->registerCCNodeLoader("AceExtRadioButton", AceExtRadioButtonLoader::loader());    
    this->registerCCNodeLoader("cs_if", cs_ifLoader::loader());
    this->registerCCNodeLoader("cs_if_true", cs_if_trueLoader::loader());
    this->registerCCNodeLoader("cs_if_false", cs_if_falseLoader::loader());
    this->registerCCNodeLoader("cs_switch", cs_switchLoader::loader());
    this->registerCCNodeLoader("cs_switch_case", cs_switch_caseLoader::loader());
    this->registerCCNodeLoader("cs_switch_default", cs_switch_defaultLoader::loader());
    this->registerCCNodeLoader("AceNode", AceNodeLoader::loader());
    this->registerCCNodeLoader("AceFrameAnimation", AceFrameAnimationLoader::loader());
    this->registerCCNodeLoader("AceSprite", AceSpriteLoader::loader());
    this->registerCCNodeLoader("AceMaskNode", AceMaskNodeLoader::loader());
    this->registerCCNodeLoader("AceFlipActionNode", AceFlipActionNodeLoader::loader());
    this->registerCCNodeLoader("actMoveTo", actMoveToLoader::loader());
    this->registerCCNodeLoader("actDelayTime", actDelayTimeLoader::loader());
    this->registerCCNodeLoader("actPlace", actPlaceLoader::loader());
    this->registerCCNodeLoader("actJumpTo", actJumpToLoader::loader());
    this->registerCCNodeLoader("actBezierTo", actBezierToLoader::loader());
    this->registerCCNodeLoader("actCardinalSplineTo", actCardinalSplineToLoader::loader());
    this->registerCCNodeLoader("actCatmullRomTo", actCatmullRomToLoader::loader());
    this->registerCCNodeLoader("actScaleTo", actScaleToLoader::loader());
    this->registerCCNodeLoader("actZNode", actZNodeLoader::loader());
    this->registerCCNodeLoader("actSkewTo", actSkewToLoader::loader());
    this->registerCCNodeLoader("actRotationTo", actRotationToLoader::loader());
    this->registerCCNodeLoader("actBlink", actBlinkLoader::loader());
    this->registerCCNodeLoader("actShow", actShowLoader::loader());
    this->registerCCNodeLoader("actHide", actHideLoader::loader());
    this->registerCCNodeLoader("actToggleVisibility", actToggleVisibilityLoader::loader());
    this->registerCCNodeLoader("actFadeIn", actFadeInLoader::loader());
    this->registerCCNodeLoader("actFadeOut", actFadeOutLoader::loader());
    this->registerCCNodeLoader("actFadeTo", actFadeToLoader::loader());
    this->registerCCNodeLoader("actTintTo", actTintToLoader::loader());
    this->registerCCNodeLoader("actOrbitCamera", actOrbitCameraLoader::loader());
    this->registerCCNodeLoader("Ace3DNode", Ace3DNodeLoader::loader());
    this->registerCCNodeLoader("Ace3DWorld", Ace3DWorldLoader::loader());
    this->registerCCNodeLoader("Ace3DBall", Ace3DBallLoader::loader());
    this->registerCCNodeLoader("Ace3DPlayer", Ace3DPlayerLoader::loader());
    this->registerCCNodeLoader("AceScale9SpriteNode", AceScale9SpriteNodeLoader::loader());
    this->registerCCNodeLoader("AceScaleSpriteNode", AceScaleSpriteNodeLoader::loader());
    this->registerCCNodeLoader("AceSameIntervalNode", AceSameIntervalNodeLoader::loader());
    this->registerCCNodeLoader("AceMultiNode", AceMultiNodeLoader::loader());
    
    this->registerCCNodeLoader("AceProgress", AceProgressLoader::loader());
    this->registerCCNodeLoader("AceStencilNode", AceStencilNodeLoader::loader());
    
    this->registerCCNodeLoader("AceCoverPageScroll", AceCoverPageScrollLoader::loader());
    this->registerCCNodeLoader("AceAreaGraph", AceAreaGraphLoader::loader());
    this->registerCCNodeLoader("AceBarGraph", AceBarGraphLoader::loader());


    //---
}

void CCNodeLoaderLibrary::registerCCNodeLoader(const char * pClassName, CCNodeLoader * pCCNodeLoader) {
    //CCLog("CCNodeLoaderLibrary.registerCCNodeLoader().pClassName = %s", pClassName);
    pCCNodeLoader->retain();
    this->mCCNodeLoaders.insert(CCNodeLoaderMapEntry(pClassName, pCCNodeLoader));
}

void CCNodeLoaderLibrary::unregisterCCNodeLoader(const char * pClassName) {
    CCNodeLoaderMap::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
    if (ccNodeLoadersIterator != this->mCCNodeLoaders.end())
    {
        ccNodeLoadersIterator->second->release();
        mCCNodeLoaders.erase(ccNodeLoadersIterator);
    }
    else
    {
        CCLOG("The loader (%s) doesn't exist", pClassName);
    }
}

CCNodeLoader * CCNodeLoaderLibrary::getCCNodeLoader(const char* pClassName) {
    //CCLog("CCNodeLoaderLibrary.getCCNodeLoader().pClassName = %s", pClassName);
    CCNodeLoaderMap::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->mCCNodeLoaders.end());
    return ccNodeLoadersIterator->second;
}

void CCNodeLoaderLibrary::purge(bool pReleaseCCNodeLoaders) {
    if(pReleaseCCNodeLoaders) {
        for(CCNodeLoaderMap::iterator it = this->mCCNodeLoaders.begin(); it != this->mCCNodeLoaders.end(); it++) {
            it->second->release();
        }
    }
    this->mCCNodeLoaders.clear();
}



static CCNodeLoaderLibrary * sSharedCCNodeLoaderLibrary = NULL;

CCNodeLoaderLibrary * CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() {
    if(sSharedCCNodeLoaderLibrary == NULL) {
        sSharedCCNodeLoaderLibrary = new CCNodeLoaderLibrary();

        sSharedCCNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    }
    return sSharedCCNodeLoaderLibrary;
}

void CCNodeLoaderLibrary::purgeSharedCCNodeLoaderLibrary() {
    CC_SAFE_DELETE(sSharedCCNodeLoaderLibrary);
}

CCNodeLoaderLibrary * CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary() {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::library();
    
    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();

    return ccNodeLoaderLibrary;
}

NS_CC_EXT_END