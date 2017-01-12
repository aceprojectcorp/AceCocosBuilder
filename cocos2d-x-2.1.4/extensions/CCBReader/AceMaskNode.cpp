//
//  AceMaskNode.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 12. 30..
//
//

#include "AceMaskNode.h"

USING_NS_CC_EXT;

void AceMaskNode::onEnter()
{
    CCNode::onEnter();
    
    CCArray* children = this->getChildren();
    
    /*
    if(children == NULL)
    {
        CCLog("AceMaskNode.onEnter() children is NULL");
    }
    else
    {
        CCLog("AceMaskNode.onEnter() children is Success");
    }
    */
    
    int size = children->count();
    m_rt = NULL;
    if(size >= 2)
    {
        m_pMaskSprite = dynamic_cast<CCSprite*>(children->objectAtIndex(0));
        m_pTextureSprite = dynamic_cast<CCSprite*>(children->objectAtIndex(1));
        
        maskedSpriteWithSprite(m_pTextureSprite, m_pMaskSprite);
        addChild(m_rt);
        
        
    }
    
    this->schedule(schedule_selector(AceMaskNode::run));
}


void AceMaskNode::run(float dt)
{
    /*
    rt->clear(0, 0, 0, 0);
    
    rt->begin();
    pMaskSprite->visit();
    
    glColorMask(0, 0, 0, 1);
    
    pOriginSprite->visit();
    
    glColorMask(1, 1, 1, 1);
    
    rt->end();
     */
    
    
    maskedSpriteWithSprite(m_pTextureSprite, m_pMaskSprite);
    
    /*
    m_rt->begin();
    m_pMaskSprite->setVisible(true);
    m_pTextureSprite->setVisible(true);
    m_pMaskSprite->visit();
    m_pTextureSprite->visit();
    m_pMaskSprite->setVisible(false);
    m_pTextureSprite->setVisible(false);
    m_rt->end();
    */
}




void AceMaskNode::maskedSpriteWithSprite(CCSprite* pTextureSprite, CCSprite* pMaskSprite)
{
    pTextureSprite->setVisible(true);
    pMaskSprite->setVisible(true);
    
    CCPoint textureSpriteOrigPosition(pTextureSprite->getPosition().x, pTextureSprite->getPosition().y);
    CCPoint maskSpriteOrigPosition(pMaskSprite->getPosition().x, pMaskSprite->getPosition().y);
    
    //pTextureSprite->setPosition(ccp(pTextureSprite->getContentSize().width/2 + pTextureSprite->getPosition().x, pTextureSprite->getContentSize().height/2 + pTextureSprite->getPosition().y));
    //pMaskSprite->setPosition(ccp(pMaskSprite->getContentSize().width/2, pMaskSprite->getContentSize().height/2));
    
    pTextureSprite->setPosition(ccp(pMaskSprite->getContentSize().width/2 + pTextureSprite->getPosition().x, pMaskSprite->getContentSize().height/2 + pTextureSprite->getPosition().y));
    pMaskSprite->setPosition(ccp(pMaskSprite->getContentSize().width/2, pMaskSprite->getContentSize().height/2));
    
    if(m_rt == NULL)
    {
        m_rt = CCRenderTexture::create((int)pMaskSprite->getContentSize().width,
                                 (int)pMaskSprite->getContentSize().height);
        
        //m_rt->setAnchorPoint(pMaskSprite->getAnchorPoint());
        //m_rt->setPosition(pMaskSprite->getPosition());
        
        
        

        
    }
    
    ccBlendFunc bfMask = ccBlendFunc();
    bfMask.src = GL_ONE;
    bfMask.dst = GL_ZERO;
    pMaskSprite->setBlendFunc(bfMask);
    
    // turn off anti-aliasing around the mask sprite
    pMaskSprite->getTexture()->setAliasTexParameters();
    
    ccBlendFunc bfTexture = ccBlendFunc();
    bfTexture.src = GL_DST_ALPHA;
    bfTexture.dst = GL_ZERO;
    pTextureSprite->setBlendFunc(bfTexture);
    
    m_rt->begin();
    pMaskSprite->visit();
    pTextureSprite->visit();
    m_rt->end();
    
    
    
    
    pTextureSprite->setPosition(textureSpriteOrigPosition);
    pMaskSprite->setPosition(maskSpriteOrigPosition);
    
    pTextureSprite->setVisible(false);
    pMaskSprite->setVisible(false);
}

/* //원본
void AceMaskNode::maskedSpriteWithSprite(CCSprite* pTextureSprite, CCSprite* pMaskSprite)
{
    // store the original positions of both sprites
    CCPoint textureSpriteOrigPosition(pTextureSprite->getPosition().x, pTextureSprite->getPosition().y);
    
    CCLog("pTextureSprite.x = %f", pTextureSprite->getPosition().x);
    
    CCPoint maskSpriteOrigPosition(pMaskSprite->getPosition().x, pMaskSprite->getPosition().y);
    
    // convert the texture sprite position into mask sprite coordinate system
    //pTextureSprite->setPosition(ccp(pTextureSprite->getContentSize().width/2 - pMaskSprite->getPosition().x + pMaskSprite->getContentSize().width/2, pTextureSprite->getContentSize().height/2 - pMaskSprite->getPosition().y + pMaskSprite->getContentSize().height/2));
    
    //pTextureSprite->setPosition(ccp(pTextureSprite->getContentSize().width/2 + pTextureSprite->getPosition().x, pTextureSprite->getContentSize().height/2));
    
    // position the mask sprite so that the bottom left corner lies on the (o,o) coordinates
    //pMaskSprite->setPosition(ccp(pMaskSprite->getContentSize().width/2, pMaskSprite->getContentSize().height/2));
    
    rt = CCRenderTexture::create((int)pMaskSprite->getContentSize().width,
                                                  (int)pMaskSprite->getContentSize().height);
    
    ccBlendFunc bfMask = ccBlendFunc();
    bfMask.src = GL_ONE;
    bfMask.dst = GL_ZERO;
    pMaskSprite->setBlendFunc(bfMask);
    
    // turn off anti-aliasing around the mask sprite
    pMaskSprite->getTexture()->setAliasTexParameters();
    
    ccBlendFunc bfTexture = ccBlendFunc();
    bfTexture.src = GL_DST_ALPHA;
    bfTexture.dst = GL_ZERO;
    pTextureSprite->setBlendFunc(bfTexture);
    
    
    
    rt->begin();
    pMaskSprite->visit();
    pTextureSprite->visit();
    rt->end();
    
    
    
    
    // generate the resulting sprite
    //if(newSprite == NULL)
    //{
    //   newSprite = CCSprite::createWithTexture(rt->getSprite()->getTexture());
    //}
    //newSprite->setFlipY(true);
    
    
    // restore the original sprite positions
    //pTextureSprite->setPosition(textureSpriteOrigPosition);
    //pMaskSprite->setPosition(maskSpriteOrigPosition);
    //newSprite->setPosition(maskSpriteOrigPosition);
    
    
    this->addChild(rt);
}
*/
