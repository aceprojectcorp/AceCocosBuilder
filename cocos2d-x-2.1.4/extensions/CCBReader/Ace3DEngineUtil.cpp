//
//  Ace3DEngineUtil.cpp
//  MLB
//
//  Created by 허정목 on 2014. 4. 3..
//
//

#include "Ace3DEngineUtil.h"

static Ace3DEngineUtil* s_SharedAce3DEngineUtil;

Ace3DEngineUtil* Ace3DEngineUtil::sharedAce3DEngineUtil()
{
    if(!s_SharedAce3DEngineUtil)
    {
        s_SharedAce3DEngineUtil = new Ace3DEngineUtil();
    }
    
    return s_SharedAce3DEngineUtil;
}

Ace3DEngineUtil::Ace3DEngineUtil()
{
    
}

Ace3DEngineUtil::~Ace3DEngineUtil()
{
    
}