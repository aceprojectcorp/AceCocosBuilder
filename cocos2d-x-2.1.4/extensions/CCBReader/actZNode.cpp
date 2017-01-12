//
//  actZNode.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2014. 1. 13..
//
//

#include "actZNode.h"

#import "actMoveTo.h"
#import "actDelayTime.h"
#import "actPlace.h"
#import "actJumpTo.h"
#import "actBezierTo.h"
#import "actCardinalSplineTo.h"
#import "actCatmullRomTo.h"
#import "actScaleTo.h"
#import "actSkewTo.h"
#import "actRotationTo.h"
#import "actBlink.h"
#import "actShow.h"
#import "actHide.h"
#import "actToggleVisibility.h"
#import "actFadeIn.h"
#import "actFadeOut.h"
#import "actFadeTo.h"
#import "actTintTo.h"
#import "actOrbitCamera.h"

USING_NS_CC_EXT;

void actZNode::onEnter()
{
    CCNode::onEnter();
    
    actionStart();
    
    schedule(schedule_selector(actZNode::update));
}

void actZNode::update(float dt)
{
    
}

void actZNode::actionStart()
{
    this->getParent()->stopAllActions();
    
    CCArray* children = this->getChildren();
    int size = (int)children->count();
    CCNode* child = NULL;
    //std::list<CCFiniteTimeAction*> actions;
    //NSMutableArray* actions = [[NSMutableArray alloc] init];
    //cocos2d::CCMutableArray
    
    CCArray* actions = CCArray::createWithCapacity(size);
    
    for(int i=0; i<size; i++)
    {
        child = (CCNode*)children->objectAtIndex(i);
        
        if(isKindOfClass(child, E_actMoveTo))
        {
            actMoveTo* pNode = dynamic_cast<actMoveTo*>(child);
            float m_time = pNode->m_time;
            float m_x = pNode->m_x;
            float m_y = pNode->m_y;
            
            CCFiniteTimeAction* pAction = CCMoveTo::create(m_time, CCPointMake(m_x, m_y));
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actDelayTime))
        {
            actDelayTime* pNode = dynamic_cast<actDelayTime*>(child);
            float m_time = pNode->m_time;
            
            CCFiniteTimeAction* pAction = CCDelayTime::create(m_time);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actJumpTo))
        {
            actJumpTo* pNode = dynamic_cast<actJumpTo*>(child);
            float m_time = pNode->m_time;
            float m_x = pNode->m_x;
            float m_y = pNode->m_y;
            float m_height = pNode->m_height;
            float m_jumps = pNode->m_jumps;
            
            CCFiniteTimeAction* pAction = CCJumpTo::create(m_time, CCPointMake(m_x, m_y), m_height, m_jumps);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actBezierTo))
        {
            actBezierTo* pNode = dynamic_cast<actBezierTo*>(child);
            float m_time = pNode->m_time;
            float m_point1_x = pNode->m_point1_x;
            float m_point1_y = pNode->m_point1_y;
            float m_point2_x = pNode->m_point2_x;
            float m_point2_y = pNode->m_point2_y;
            float m_endPoint_x = pNode->m_endPoint_x;
            float m_endPoint_y = pNode->m_endPoint_y;
            
            ccBezierConfig bezier;
            bezier.controlPoint_1 = CCPointMake(m_point1_x, m_point1_y);
            bezier.controlPoint_2 = CCPointMake(m_point2_x, m_point2_y);
            bezier.endPosition = CCPointMake(m_endPoint_x, m_endPoint_y);
            CCFiniteTimeAction* pAction = CCBezierTo::create(m_time, bezier);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actCardinalSplineTo))
        {
            actCardinalSplineTo* pNode = dynamic_cast<actCardinalSplineTo*>(child);
            float m_time = pNode->m_time;
            float m_tension = pNode->m_tension;
            CCString* m_points = pNode->m_points;
            
            CCPointArray* array = parsePoints(m_points);
            CCFiniteTimeAction* pAction = CCCardinalSplineTo::create(m_time, array, m_tension);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actCatmullRomTo))
        {
            actCatmullRomTo* pNode = dynamic_cast<actCatmullRomTo*>(child);
            float m_time = pNode->m_time;
//            float m_tension = pNode->m_tension;
            CCString* m_points = pNode->m_points;
            
            CCPointArray* array = parsePoints(m_points);
            CCFiniteTimeAction* pAction = CCCatmullRomTo::create(m_time, array);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actScaleTo))
        {
            actScaleTo* pNode = dynamic_cast<actScaleTo*>(child);
            float m_time = pNode->m_time;
            float m_scale_x = pNode->m_scale_x;
            float m_scale_y = pNode->m_scale_y;
            
            CCFiniteTimeAction* pAction = CCScaleTo::create(m_time, m_scale_x, m_scale_y);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actPlace))
        {
            actPlace* pNode = dynamic_cast<actPlace*>(child);
            float m_x = pNode->m_x;
            float m_y = pNode->m_y;
            
            CCFiniteTimeAction* pAction = CCPlace::create(CCPointMake(m_x, m_y));
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actSkewTo))
        {
            actSkewTo* pNode = dynamic_cast<actSkewTo*>(child);
            float m_time = pNode->m_time;
            float m_skew_x = pNode->m_skew_x;
            float m_skew_y = pNode->m_skew_y;
            
            CCFiniteTimeAction* pAction = CCSkewTo::create(m_time, m_skew_x, m_skew_y);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actRotationTo))
        {
            actRotationTo* pNode = dynamic_cast<actRotationTo*>(child);
            float m_time = pNode->m_time;
            float m_angle_x = pNode->m_angle_x;
            float m_angle_y = pNode->m_angle_y;
            
            CCFiniteTimeAction* pAction = CCRotateTo::create(m_time, m_angle_x, m_angle_y);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actBlink))
        {
            actBlink* pNode = dynamic_cast<actBlink*>(child);
            float m_time = pNode->m_time;
            float m_blinkCount = pNode->m_blinkCount;
            
            CCFiniteTimeAction* pAction = CCBlink::create(m_time, m_blinkCount);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actShow))
        {
            CCFiniteTimeAction* pAction = CCShow::create();
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actHide))
        {
            CCFiniteTimeAction* pAction = CCHide::create();
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actToggleVisibility))
        {
            CCFiniteTimeAction* pAction = CCToggleVisibility::create();
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actFadeIn))
        {
            actFadeIn* pNode = dynamic_cast<actFadeIn*>(child);
            float m_time = pNode->m_time;
            
            CCFiniteTimeAction* pAction = CCFadeIn::create(m_time);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actFadeOut))
        {
            actFadeOut* pNode = dynamic_cast<actFadeOut*>(child);
            float m_time = pNode->m_time;
            
            CCFiniteTimeAction* pAction = CCFadeOut::create(m_time);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actFadeTo))
        {
            actFadeTo* pNode = dynamic_cast<actFadeTo*>(child);
            float m_time = pNode->m_time;
            GLubyte m_opacity = pNode->m_opacity;
            
            CCFiniteTimeAction* pAction = CCFadeTo::create(m_time, m_opacity);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actTintTo))
        {
            actTintTo* pNode = dynamic_cast<actTintTo*>(child);
            float m_time = pNode->m_time;
            GLubyte m_r = pNode->m_r;
            GLubyte m_g = pNode->m_g;
            GLubyte m_b = pNode->m_b;
            
            CCFiniteTimeAction* pAction = CCTintTo::create(m_time, m_r, m_g, m_b);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        else if(isKindOfClass(child, E_actOrbitCamera))
        {
            actOrbitCamera* pNode = dynamic_cast<actOrbitCamera*>(child);
            float m_time = pNode->m_time;
            float m_radius = pNode->m_radius;
            float m_deltaRadius = pNode->m_deltaRadius;
            float m_angleZ = pNode->m_angleZ;
            float m_deltaAngleZ = pNode->m_deltaAngleZ;
            float m_angleX = pNode->m_angleX;
            float m_deltaAngleX = pNode->m_deltaAngleX;
            
            CCFiniteTimeAction* pAction = CCOrbitCamera::create(m_time, m_radius, m_deltaRadius, m_angleZ, m_deltaAngleZ, m_angleX, m_deltaAngleX);
            
            //actions.push_back(pAction);
            actions->addObject(pAction);
        }
        
    }
    
    if(actions->count() > 0)
    {
        this->getParent()->runAction(CCSequence::create(actions));
    }
}

bool actZNode::isKindOfClass(CCNode* child, int classNameIdx)
{
    bool result = false;
    
    switch(classNameIdx)
    {
        case E_actMoveTo :{
            actMoveTo* pNode = dynamic_cast<actMoveTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actDelayTime :{
            actDelayTime* pNode = dynamic_cast<actDelayTime*>(child);
            if(pNode) result = true;
            break;}
        case E_actJumpTo :{
            actJumpTo* pNode = dynamic_cast<actJumpTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actBezierTo :{
            actBezierTo* pNode = dynamic_cast<actBezierTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actCardinalSplineTo :{
            actCardinalSplineTo* pNode = dynamic_cast<actCardinalSplineTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actCatmullRomTo :{
            actCatmullRomTo* pNode = dynamic_cast<actCatmullRomTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actScaleTo :{
            actScaleTo* pNode = dynamic_cast<actScaleTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actPlace :{
            actPlace* pNode = dynamic_cast<actPlace*>(child);
            if(pNode) result = true;
            break;}
        case E_actSkewTo :{
            actSkewTo* pNode = dynamic_cast<actSkewTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actRotationTo :{
            actRotationTo* pNode = dynamic_cast<actRotationTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actBlink :{
            actBlink* pNode = dynamic_cast<actBlink*>(child);
            if(pNode) result = true;
            break;}
        case E_actShow :{
            actShow* pNode = dynamic_cast<actShow*>(child);
            if(pNode) result = true;
            break;}
        case E_actHide :{
            actHide* pNode = dynamic_cast<actHide*>(child);
            if(pNode) result = true;
            break;}
        case E_actToggleVisibility :{
            actToggleVisibility* pNode = dynamic_cast<actToggleVisibility*>(child);
            if(pNode) result = true;
            break;}
        case E_actFadeIn :{
            actFadeIn* pNode = dynamic_cast<actFadeIn*>(child);
            if(pNode) result = true;
            break;}
        case E_actFadeOut :{
            actFadeOut* pNode = dynamic_cast<actFadeOut*>(child);
            if(pNode) result = true;
            break;}
        case E_actFadeTo :{
            actFadeTo* pNode = dynamic_cast<actFadeTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actTintTo :{
            actTintTo* pNode = dynamic_cast<actTintTo*>(child);
            if(pNode) result = true;
            break;}
        case E_actOrbitCamera :{
            actOrbitCamera* pNode = dynamic_cast<actOrbitCamera*>(child);
            if(pNode) result = true;
            break;}
    }
    
    return result;
}

CCPointArray* actZNode::parsePoints(CCString* m_points)
{
    //point가 몇개 셋팅되어있는지 검색한다.
    int size = 0;
    const char* strArr = m_points->getCString();
    for(int i=0; i<strlen(strArr); i++)
    {
        if(strArr[i] == '(')
        {
            size++;
        }
    }
    
    CCPointArray* array = CCPointArray::create(size);
    
    int x_pos = 0;
    int x_length = 0;
    int y_pos = 0;
    int y_length = 0;
    bool bXLengthCheck = false;
    bool bYLengthCheck = false;
    for(int i=0; i<strlen(strArr); i++)
    {
        if(strArr[i] == '(')
        {
            x_pos = i + 1;
            bXLengthCheck = true;
        }
        else if(strArr[i] == ',')
        {
            bXLengthCheck = false;
            
            y_pos = i + 1;
            bYLengthCheck = true;
        }
        else if(strArr[i] == ')')
        {
            bYLengthCheck = false;
            
            //????
        }
        else if(strArr[i] == ' ')
        {
            if(bYLengthCheck)
            {
                y_pos++;
            }
        }
        else
        {
            if(bXLengthCheck)
            {
                x_length++;
            }
            
            if(bYLengthCheck)
            {
                y_length++;
            }
        }
    }
    
    return array;
}