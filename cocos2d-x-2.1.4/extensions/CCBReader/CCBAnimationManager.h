#ifndef __CCB_CCBANIMATION_MANAGER_H__
#define __CCB_CCBANIMATION_MANAGER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBSequence.h"
#include "CCBValue.h"
#include "CCBSequenceProperty.h"

NS_CC_EXT_BEGIN

class CCBAnimationManagerDelegate
{
public:
    virtual void completedAnimationSequenceNamed(const char *name) = 0;
};

class CCBAnimationManager : public CCObject
{
private:
    CCArray *mSequences;
    CCDictionary *mNodeSequences;
    CCDictionary *mBaseValues;
    int mAutoPlaySequenceId;
    
    CCNode *mRootNode;
    
    CCSize mRootContainerSize;
    
    CCBAnimationManagerDelegate *mDelegate;
    CCBSequence *mRunningSequence;
    
    CCArray *mDocumentOutletNames;
    CCArray *mDocumentOutletNodes;
    CCArray *mDocumentCallbackNames;
    CCArray *mDocumentCallbackNodes;
    CCArray *mKeyframeCallbacks;
    CCDictionary *mKeyframeCallFuncs;

    std::string mDocumentControllerName;
    std::string lastCompletedSequenceName;

    SEL_CallFunc mAnimationCompleteCallbackFunc;
    CCObject *mTarget;
    
    //---jambam 추가 : 1 = 원래 속도 2 = 두배 속도
    float mActionSpeed;
    //---
    
    float m_fDelay;
    bool m_bDelayAction;
    
public:
    bool jsControlled;
    CCBAnimationManager();
    ~CCBAnimationManager();


    CCObject *mOwner;
    
    virtual bool init();
    
    CCArray* getSequences();
    void setSequences(CCArray* seq);

    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    CCNode* getRootNode();
    void setRootNode(CCNode* pRootNode); // weak reference
    
    //---jambam 추가
    float getActionSpeed();
    void setActionSpeed(float nSpeed);
    //---
    
    void setDelayAction(float fDelay);
    float getDelayAction();
    

    void addDocumentCallbackNode(CCNode *node);
    void addDocumentCallbackName(std::string name);
    void addDocumentOutletNode(CCNode *node);
    void addDocumentOutletName(std::string name);

    void setDocumentControllerName(const std::string &name);
    
    std::string getDocumentControllerName();
    CCArray* getDocumentCallbackNames();
    CCArray* getDocumentCallbackNodes();
    CCArray* getDocumentOutletNames();
    CCArray* getDocumentOutletNodes();
    std::string getLastCompletedSequenceName();
    
    CCArray* getKeyframeCallbacks();
    
    const CCSize& getRootContainerSize();
    void setRootContainerSize(const CCSize &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const CCSize& getContainerSize(CCNode* pNode);
    
    void addNode(CCNode *pNode, CCDictionary *pSeq);
    void setBaseValue(CCObject *pValue, CCNode *pNode, const char *pPropName);
    void moveAnimationsFromNode(CCNode* fromNode, CCNode* toNode);

    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName, float fTweenDuration);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(int nSeqId, float fTweenDuraiton);

    void runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration, bool ignoreBaseValue = false);
    void runAnimationsForSequenceNamed(const char *pName, bool ignoreBaseValue = false);
    void runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuraiton, bool ignoreBaseValue = false);

    void setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc);

    void debug();
    
    void setCallFunc(CCCallFunc *callFunc, const std::string &callbackNamed);

    CCObject* actionForCallbackChannel(CCBSequenceProperty* channel);
    CCObject* actionForSoundChannel(CCBSequenceProperty* channel);
    
private:
    CCObject* getBaseValue(CCNode *pNode, const char* pPropName);
    //int getSequenceId(const char* pSequenceName); //jambam 원본 주석(public 으로 수정한다.)
    CCBSequence* getSequence(int nSequenceId);
    CCActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, CCNode *pNode);
    void setAnimatedProperty(const char *pPropName, CCNode *pNode, CCObject *pValue, float fTweenDuraion);
    void setFirstFrame(CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    CCActionInterval* getEaseAction(CCActionInterval *pAction, int nEasingType, float fEasingOpt);
    void runAction(CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
    
public:
    int getSequenceId(const char* pSequenceName); //jambam 수정(위의 private함수를 public 으로 수정한다.)
};

class CCBSetSpriteFrame : public CCActionInstant
{
private:
    CCSpriteFrame *mSpriteFrame;
    
public:
    ~CCBSetSpriteFrame();
    
    /** creates a Place action with a position */
    static CCBSetSpriteFrame* create(CCSpriteFrame *pSpriteFrame);
    bool initWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
};



class CCBSoundEffect : public CCActionInstant
{
private:
  std::string mSoundFile;
  float mPitch, mPan, mGain;
    
public:
    ~CCBSoundEffect();
    
    static CCBSoundEffect* actionWithSoundFile(const std::string &file, float pitch, float pan, float gain);
    bool initWithSoundFile(const std::string &file, float pitch, float pan, float gain);
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
};


class CCBRotateTo : public CCActionInterval
{
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
    
public:
    static CCBRotateTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void startWithTarget(CCNode *pNode);
};


class CCBRotateXTo: public CCActionInterval {
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
public:
    static CCBRotateXTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void startWithTarget(CCNode *pNode);
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void update(float time);
};


class CCBRotateYTo: public CCActionInterval {
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
    
public:
    static CCBRotateYTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void startWithTarget(CCNode *pNode);
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void update(float time);
};


class CCBEaseInstant : public CCActionEase
{
public:
    static CCBEaseInstant* create(CCActionInterval *pAction);
    
    virtual void update(float dt);
};


NS_CC_EXT_END

#endif // __CCB_CCBANIMATION_MANAGER_H__
