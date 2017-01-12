//
//  AceTextField.cpp
//  ScrollViewTest
//
//  Created by 허정목 on 2013. 11. 29..
//
//

#include "AceTextField.h"

using namespace std;
USING_NS_CC_EXT;


string AceTextField::substr(const string& str, int pos, int len)
{
    int index = 0;
    int count = 0;
    int n = 0;
    string::const_iterator start = str.end();
    string::const_iterator it = str.begin(), end = str.end();
    while(it != end) {
        const char c = *it;
        if((c & 0x80) == 0) n = 1;
        else if((c & 0xE0) == 0xC0) n = 2;
        else if((c & 0xF0) == 0xE0) n = 3;
        else n = 4;
        
        if(index == pos) start = it;
        
        index++;
        
        if(start != end) {
            count++;
            if(count >= len) return string(start, it + n);
        }
        
        it += n;
    }
    
    return start == end ? "" : string(start, end);
}

int AceTextField::strlen(const string &str)
{
    int count = 0;
    int n = 0;
    string::const_iterator it = str.begin(), end = str.end();
    while(it != end) {
        const char c = *it;
        if((c & 0x80) == 0) n = 1;
        else if((c & 0xE0) == 0xC0) n = 2;
        else if((c & 0xF0) == 0xE0) n = 3;
        else n = 4;
        
        count++;
        it += n;
    }
    
    return count;
}

size_t AceTextField::UnicodeToUTF8(wchar_t uc, char* UTF8)
{
    size_t tRequiredSize = 0;
    
    if (uc <= 0x7f)
    {
        if( NULL != UTF8 )
        {
            UTF8[0] = (char) uc;
            UTF8[1] = (char) '\0';
        }
        tRequiredSize = 1;
    }
    else if (uc <= 0x7ff)
    {
        if( NULL != UTF8 )
        {
            UTF8[0] = (char)(0xc0 + uc / (0x01 << 6));
            UTF8[1] = (char)(0x80 + uc % (0x01 << 6));
            UTF8[2] = (char) '\0';
        }
        tRequiredSize = 2;
    }
    else if (uc <= 0xffff)
    {
        if( NULL != UTF8 )
        {
            UTF8[0] = (char)(0xe0 + uc / (0x01 <<12));
            UTF8[1] = (char)(0x80 + uc / (0x01 << 6) % (0x01 << 6));
            UTF8[2] = (char)(0x80 + uc % (0x01 << 6));
            UTF8[3] = (char) '\0';
        }
        tRequiredSize = 3;
    }
    
    return tRequiredSize;
}

//size_t UTF8ToUnicode(const char* UTF8, wchar_t& uc)
//{
//    size_t tRequiredSize = 0;
//    
//    uc = 0x0000;
//    
//    // ASCII byte
//    if( 0 == (UTF8[0] & 0x80) )
//    {
//        uc = UTF8[0];
//        tRequiredSize = 1;
//    }
//    // Start byte for 2byte
//    else if( 0xC0 == (UTF8[0] & 0xE0) &&
//            0x80 == (UTF8[1] & 0xC0) )
//    {
//        uc += (UTF8[0] & 0x1F) << 6;
//        uc += (UTF8[1] & 0x3F) << 0;
//        tRequiredSize = 2;
//    }
//    // Start byte for 3byte
//    else if( 0xE0 == (UTF8[0] & 0xE0) &&
//            0x80 == (UTF8[1] & 0xC0) &&
//            0x80 == (UTF8[2] & 0xC0) )
//    {
//        uc += (UTF8[0] & 0x1F) << 12;
//        uc += (UTF8[1] & 0x3F) << 6;
//        uc += (UTF8[2] & 0x3F) << 0;
//        tRequiredSize = 3;
//    }
//    else
//    {
//        // Invalid case
//        assert(false);
//    }
//    
//    return tRequiredSize;
//}

size_t AceTextField::UTF8ToUnicode(const char* UTF8, wchar_t& uc)
{
    size_t tRequiredSize = 0;
    
    uc = 0x0000;
    
    // ASCII byte
    if( 0 == (UTF8[0] & 0x80) )
    {
        uc = UTF8[0];
        tRequiredSize = 1;
    }
    // Start byte for 2byte
    else if( 0xC0 == (UTF8[0] & 0xE0) &&
            0x80 == (UTF8[1] & 0xC0) )
    {
        uc += (UTF8[0] & 0x1F) << 6;
        uc += (UTF8[1] & 0x3F) << 0;
        tRequiredSize = 2;
    }
    // Start byte for 3byte
    else if( 0xE0 == (UTF8[0] & 0xF0) &&
            0x80 == (UTF8[1] & 0xC0) &&
            0x80 == (UTF8[2] & 0xC0) )
    {
        uc += (UTF8[0] & 0x1F) << 12;
        uc += (UTF8[1] & 0x3F) << 6;
        uc += (UTF8[2] & 0x3F) << 0;
        tRequiredSize = 3;
    }
    else
    {
        uc += (UTF8[0] & 0x07) << 18;
        uc += (UTF8[1] & 0x3F) << 12;
        uc += (UTF8[2] & 0x3F) << 6;
        uc += (UTF8[3] & 0x3F) << 0;
        tRequiredSize = 4;
    }
    
    return tRequiredSize;
}

bool AceTextField::init()
{
    CCLayer::init();
    
    //haru - 초기 최대글자제한은 8자
    setMaxLength(8);
    
    return true;
}

void AceTextField::onEnter()
{
    CCLayer::onEnter();
    setEditBox();
}

void AceTextField::setEditBox()
{
    if (m_pEditBox)
    {
        m_pEditBox->removeFromParent();
        m_pEditBox = NULL;
    }
    m_pEditBox = CCEditBox::create(this->getContentSize(), CCScale9Sprite::create("packaging/common/image/image.png"));
    m_pEditBox->setPosition(this->getContentSize()*0.5f);
    m_pEditBox->setReturnType(kKeyboardReturnTypeDone);
    m_pEditBox->setDelegate(this);
    this->addChild(m_pEditBox);
    
    setMaxLength(m_nMaxLength);
    setPriority(m_nPriority);
}

void AceTextField::closeKeyboard()
{
    m_pEditBox->closeKeyboard();
}

void AceTextField::editBoxEditingDidBegin(CCEditBox* editBox)
{
    CCLog("ediBox %p DidBdgin !", editBox);
}

void AceTextField::editBoxEditingDidEnd(CCEditBox* editBox)
{
    CCLog("ediBox %p DidEnd !", editBox);
}

void AceTextField::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
    CCLog("ediBox %p TextChanged, text: %s", editBox, text.c_str());
}

void AceTextField::editBoxReturn(CCEditBox* editBox)
{
    CCLog("ediBox %p was returned !", editBox);
    
    std::string str(m_pEditBox->getText());
    CCLog("입력된 문자 : %s", str.c_str());
    
    string newStr = "";
    
    for (int i = 0; i < strlen(str); i++)
    {
        string ch = substr(str.c_str(), i, 1);
        wchar_t uniCh = 0;
        UTF8ToUnicode(ch.c_str(), uniCh);
        
        for (int j = 0; j < strlen(ch.c_str()); j++)
        {
             CCLog("ch: %x", (int) ch.c_str()[j]);
        }
        
        CCLog("char: %c", uniCh);
        CCLog("hex: %x", (int) uniCh);
        
//   이모티콘 유니코드  https://en.wikipedia.org/wiki/Emoji 참고
        if ((uniCh >= 0x1f300 && uniCh <= 0x1f5ff) ||
            (uniCh >= 0x1f900 && uniCh <= 0x1f9ff) ||
            (uniCh >= 0x1f600 && uniCh <= 0x1f64f) ||
            (uniCh >= 0x1f680 && uniCh <= 0x1f6ff) ||
            (uniCh >= 0x2600 && uniCh <= 0x26ff) ||
            (uniCh >= 0x2700 && uniCh <= 0x27bf))
        {
            // 이모티콘이 나올 조건
            CCLog("이모티콘이 나올 조건");
        }
        else
        {
            newStr += ch;
            CCLog("newStr : %s", newStr.c_str());
        }
    }
    
    m_pEditBox->setText(newStr.c_str());
}

void AceTextField::setText(const char* pText)
{
    if (m_pEditBox)
    {
        m_pEditBox->setText(pText);
        m_pEditBox->setPlaceHolder(pText);
    }
}

//haru - Max length 설정
void AceTextField::setMaxLength(int lenght)
{
    m_nMaxLength = lenght;
    
    if (m_pEditBox && m_nMaxLength != -1)
    {
        m_pEditBox->setMaxLength(m_nMaxLength);
    }
}

void AceTextField::setPriority(int priority)
{
    m_nPriority = priority;
    
    if (m_pEditBox && m_nPriority != -1)
    {
        m_pEditBox->setTouchPriority(m_nPriority);
    }
}