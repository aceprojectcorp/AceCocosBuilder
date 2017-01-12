//
//  AceTextField.h
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 29..
//
//

#ifndef ScrollViewTest_AceTextField_h
#define ScrollViewTest_AceTextField_h

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

USING_NS_CC;
USING_NS_CC_EXT;


class AceTextField
: public CCLayer
, public CCEditBoxDelegate
{
public:
    virtual bool init();
    virtual void onEnter();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AceTextField, create);
    
    AceTextField()
    : m_pEditBox(NULL)
    , m_nMaxLength(-1)
    , m_nPriority(-1)
    {
    }
    
public:
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    
    virtual void editBoxReturn(CCEditBox* editBox);
    
private:
    CCEditBox* m_pEditBox;
    
    int m_nMaxLength;
    int m_nPriority;
    
    
    std::string substr(const std::string& str, int pos, int len);
    int strlen(const std::string& str);
    
    size_t UnicodeToUTF8(wchar_t uc, char* UTF8);
    size_t UTF8ToUnicode(const char* UTF8, wchar_t& uc);
    
public:
    CCEditBox* getEditBox() {return m_pEditBox;}
    void setEditBox();
    void setText(const char* pText);
    void setMaxLength(int lenght);
    void setPriority(int priority);
    
    void closeKeyboard();
};

NS_CC_EXT_END

#endif
