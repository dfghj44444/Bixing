#include "CursorTextField.h"  
//bug ：内容超上限崩溃，solution：记录长度 
//仍需添加背景
const static float DELTA = 0.5f;  
  
using namespace cocos2d;  
using namespace std;  
  
CursorTextField::CursorTextField()  
{  
    CCTextFieldTTF();  
  
    m_pCursorSprite = NULL;  
    m_pCursorAction = NULL;  
  
    m_pInputText = NULL;  
    codeNumType = NULL;  
}  
  
CursorTextField::~CursorTextField()  
{  
    CC_SAFE_DELETE(m_pInputText);  
    CC_SAFE_DELETE_ARRAY(codeNumType);  
}  
  
void CursorTextField::onEnter()  
{  
    CCTextFieldTTF::onEnter();  
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);  
    auto m_dispatcher = Director::getInstance()->getEventDispatcher();
	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(CursorTextField::onTouchBegan, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(CursorTextField::onTouchEnded, this);
	m_dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    this->setDelegate(this);  
}  
  
CursorTextField * CursorTextField::textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)  
{  
    CursorTextField *pRet = new CursorTextField();  
    if(pRet && pRet->initWithPlaceHolder("", fontName, fontSize))  
    {  
        pRet->autorelease();  
        if (placeholder)  
        {  
            pRet->setPlaceHolder(placeholder);  
        }  
        pRet->init();  
        pRet->initCursorSprite(fontSize);  
        pRet->setHorizontalAlignment(kCCTextAlignmentLeft);  
        return pRet;  
    }  
    CC_SAFE_DELETE(pRet);  
    return NULL;  
}  
  
bool CursorTextField::init(){  
    this->inputFrameWidth = 400;  
    this->inputMaxLength = 38;  
    this->nLenCount = 0;  
    this->codeNumType = new int[50];  
    this->codeCur = 0;  
    this->startCur = 0;  
    this->endCur = 0;  
    inpuText = "";  
    return true;  
}  
void CursorTextField::initCursorSprite(const int mHeight)  
{  
    // 初始化光标  
    const int column = 4;  
    const int nHeight = (const int)mHeight;  
    int pixels[25][column];  
    for (int i=0; i<nHeight; ++i) {  
        for (int j=0; j<column; ++j) {  
            pixels[i][j] = 0xffffffff;  
        }  
    }  
    CCTexture2D *texture = new CCTexture2D();  
    texture->initWithData(pixels,25*column, Texture2D::PixelFormat::RGB888, 1, 1, CCSizeMake(column, nHeight));  
    m_pCursorSprite = CCSprite::createWithTexture(texture);  
    CCSize winSize = getContentSize();  
    m_cursorPos = ccp(0, winSize.height / 2);  
    m_pCursorSprite->setPosition(m_cursorPos);  
    this->addChild(m_pCursorSprite);  
    m_pCursorSprite->setVisible(false);  
    m_pCursorAction = CCRepeatForever::create((CCActionInterval *) CCSequence::create(CCFadeOut::create(0.25f), CCFadeIn::create(0.25f), NULL));  
    m_pCursorSprite->runAction(m_pCursorAction);  
    m_pInputText = new std::string();  
}  
  
bool CursorTextField::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{      
    m_beginPos = pTouch->getLocation();  
    return true;  
}  

void CursorTextField::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)  
{  
	CCPoint endPos = pTouch->getLocation();  
	// 判断是否为点击事件  
	if (::abs(endPos.x - m_beginPos.x) > DELTA ||   
		::abs(endPos.y - m_beginPos.y))   
	{  
		// 不是点击事件  
		m_beginPos.x = m_beginPos.y = -1;  
		return;  
	}  

	// 判断是打开输入法还是关闭输入法  
	isInTextField(pTouch) ? openIME() : closeIME();  
}  
  
CCRect CursorTextField::getRect()  
{  
    CCSize size = getContentSize();  
    return  CCRectMake(0, -size.height / 2, inputFrameWidth, size.height);  
}  
  
//获取输入框内容  
const char* CursorTextField::getInputText(){  
    const char* text = m_pInputText->c_str();  
    return text;  
}  
  
//设置输入框内容  
void CursorTextField::setInpuntText(char* text){  
    *m_pInputText = "";  
    setString(text);  
    m_pCursorSprite->setPositionX(0);  
    CC_SAFE_DELETE_ARRAY(codeNumType);  
    codeNumType = new int[50];  
    codeCur = 0;  
    startCur = 0;  
    endCur = 0;  
    inpuText = "";  
}  
  
//设置输入框宽度 一旦字符串宽度超度这个长度 字符串会自动向左缩进  
void CursorTextField::setInputWidth(float width){  
    this->inputFrameWidth = width;  
}  
  
//设置输入宽显示的最大字符数量Unicode  
void CursorTextField::setInputMaxLength(float length){  
    this->inputMaxLength = length;  
}  
  
//判断点击事件，是否响应在输入框范围内  
bool CursorTextField::isInTextField(cocos2d::CCTouch *pTouch)  
{  
    return getRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));  
}  

  
//弹出手机键盘时响应事件  
bool CursorTextField::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *pSender)  
{  
    if (m_pInputText->empty()) {  
        return false;  
    }  
    m_pCursorSprite->setPositionX(getContentSize().width);  
    return false;  
}  
  
//当有输入进来时响应  
//@param pSender 发送事件对象  
//@param text 输入内容  
//@param  内容字节长度  
bool CursorTextField::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)  
{  
    std::string sText = m_pInputText->c_str();  
    wchar_t* wText = new wchar_t[200];  
    char t[200];  
    memset(t,0,200);  
    strcpy(t,sText.c_str());  
    //将字符串转换为Unicode，并返回Unicode字符数量  
    int cou = Utf82Unicode(wText,200,t,sText.length());  
    //当字符数量超过规定值 不做处理  
    if(cou >= inputMaxLength) return true;  
    //屏蔽回车输入  
    if(text[0] == '\n')  
        return true;  
    //输入框总内容添加  
    m_pInputText->append(text);  
  
    //测试  
    CCLabelTTF* ttf = CCLabelTTF::create(text,"Verdana-Bold",26);  
    float teWidth = ttf->getContentSize().width;  
    CCLOG("any code length---%f",teWidth);  
  
    //输入框当前字符串添加  
    inpuText.append(text);  
    //当前字符的长度  
    codeNumType[codeCur++] = nLen;  
    std::string* localText = m_pInputText;  
    setString(m_pInputText->c_str());  
    //如果总字符串的长度大于指定宽度  
    if(getContentSize().width > inputFrameWidth){  
        //大于，截取字符串，直到字符串的长度小于指定宽度为止  
        setString(inpuText.c_str());  
        while(getContentSize().width > inputFrameWidth){  
            int nnLen = nLen;  
            if(codeNumType[startCur] == 1){  
                nnLen = 1;  
            }  
            if(codeNumType[startCur] == 3){  
                nnLen = 3;  
            }  
            startCur++;  
            nLenCount += nnLen;  
            float gap = localText->size() - nLenCount;  
            inpuText = localText->substr(nLenCount,gap);  
            setString(inpuText.c_str());  
            float coWidth = getContentSize().width;  
        }  
    }  
    else{  
        //小于，直接设置显示总字符串  
        nLenCount = 0;  
        startCur = 0;  
        setString(m_pInputText->c_str());  
    }  
    //设置光标位置  
    m_pCursorSprite->setPositionX(getContentSize().width);  
    CC_SAFE_DELETE_ARRAY(wText);  
    return true;  
}  
  
  
//当有输入进来时响应  
//@param pSender 发送事件对象  
//@param text 删除内容  
//@param  内容字节长度  
bool CursorTextField::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen)  
{  
    //将总字符串长度减去nLen字节长  
    m_pInputText->resize(m_pInputText->size() - nLen);  
    //当前字符数减一  
    codeNumType[codeCur--] = 0;  
    std::string* localText = m_pInputText;  
    setString(m_pInputText->c_str());  
    if(getContentSize().width > inputFrameWidth){  
        //大于指定宽度，截取字符串，直到字符串长度小于指定宽度  
        while(getContentSize().width > inputFrameWidth){  
            int nnLen = nLen;  
            if(codeNumType[startCur - 1] == 1){  
                nnLen = 1;  
            }  
            if(codeNumType[startCur - 1] == 3){  
                nnLen = 3;  
            }  
            nLenCount -= nnLen;  
            startCur--;  
            if(startCur <=0)  
                startCur = 0;  
            if(nLenCount <=0 )  
                nLenCount = 0;  
            float gap = localText->size() - nLenCount;  
            const std::string text = localText->substr(nLenCount,gap);  
            setString(text.c_str());  
            inpuText = text;  
        }  
    }  
    else{  
        nLenCount = 0;  
        startCur = 0;  
        setString(m_pInputText->c_str());  
    }  
    //设置光标位置  
    m_pCursorSprite->setPositionX(getContentSize().width);  
    if (m_pInputText->empty()) {  
        m_pCursorSprite->setPositionX(0);  
    }  
  
    return true;  
}  
  
bool CursorTextField::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *pSender)  
{  
    return false;  
}  
  
void CursorTextField::openIME()  
{  
    m_pCursorSprite->setVisible(true);  
    this->attachWithIME();  
}  
  
void CursorTextField::closeIME()  
{  
    m_pCursorSprite->setVisible(false);  
    this->detachWithIME();  
}  
  
void CursorTextField::onExit()  
{  
    CCTextFieldTTF::onExit();  
    //CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
}  
int  CursorTextField::Utf82Unicode(LPWSTR out,  int outsize , LPSTR in,int insize)    
{    
    //-------------------------------------------------------------------------------------------    
    //参数有效性判断    
    if(out == NULL || in == NULL || insize<0)    
    {    
        return -1;    
    }    
    int typeCount = 0;  
    int totalNum = 0;    
    char *p = in;    
    for(int i=0;i<insize;i++)    
    {    
        if (*p >= 0x00 && *p <= 0x7f)//说明最高位为'0'，这意味着utf8编码只有1个字节！    
        {    
            p++;    
            totalNum += 1;    
        }    
        else if ((*p & (0xe0))== 0xc0)//只保留最高三位，看最高三位是不是110，如果是则意味着utf8编码有2个字节！    
        {    
            p++;    
            p++;    
            totalNum += 1;    
        }    
        else if ((*p & (0xf0))== 0xe0)//只保留最高四位，看最高三位是不是1110，如果是则意味着utf8编码有3个字节！    
        {    
            p++;    
            p++;    
            p++;    
            totalNum += 1;    
        }    
    }    
    if( outsize < totalNum )//参数有效性判断！    
    {    
        return -1;    
    }    
    //------------------------------------------------    
        int resultsize = 0;    
    
        p = in;    
        char* tmp = (char *)out;    
        while(*p)    
        {    
            if (*p >= 0x00 && *p <= 0x7f)//说明最高位为'0'，这意味着utf8编码只有1个字节！    
            {    
                *tmp = *p;    
                tmp++;    
                //*tmp = '/0';    
                tmp++;    
                resultsize += 1;    
            }    
            else if ((*p & 0xe0)== 0xc0)//只保留最高三位，看最高三位是不是110，如果是则意味着utf8编码有2个字节！    
            {    
                wchar_t t = 0;    
                char t1 = 0;    
                char t2 = 0;    
    
                t1 = *p & (0x1f);//高位的后5位！（去除了头部的110这个标志位）    
                p++;    
                t2 = *p & (0x3f);//低位的后6位！（去除了头部的10这个标志位）    
    
                *tmp = t2 | ((t1 & (0x03)) << 6);    
                tmp++;    
                *tmp = t1 >> 2;//留下其保留的三位    
                tmp++;    
                resultsize += 1;    
            }    
            else if ((*p & (0xf0))== 0xe0)//只保留最高四位，看最高三位是不是1110，如果是则意味着utf8编码有3个字节！    
            {    
                wchar_t t = 0;    
                wchar_t t1 = 0;    
                wchar_t t2 = 0;    
                wchar_t t3 = 0;    
                t1 = *p & (0x1f);    
                p++;    
                t2 = *p & (0x3f);    
                p++;    
                t3 = *p & (0x3f);    
    
                *tmp = ((t2 & (0x03)) << 6) | t3;    
                tmp++;    
                *tmp = (t1 << 4) | (t2 >> 2);    
                tmp++;    
                resultsize += 1;    
            }    
            p++;    
        }    
        /*不考虑结束符，如果考虑则打开此段！    
        *tmp = '/0';    
        tmp++;    
        *tmp = '/0';    
        resultsize += 2;    
        */    
        return resultsize;    
}    