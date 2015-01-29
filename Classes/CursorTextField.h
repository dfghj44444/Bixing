#ifndef CursorInputDemo_CursorTextField_h  
#define CursorInputDemo_CursorTextField_h  

#include "cocos2d.h"  

USING_NS_CC;  

class CursorTextField: public CCTextFieldTTF, public CCTextFieldDelegate
{  
private:  
	// 点击开始位置  
	CCPoint m_beginPos;  
	// 光标精灵  
	CCSprite *m_pCursorSprite;  
	// 光标动画  
	CCAction *m_pCursorAction;  
	// 光标坐标  
	CCPoint m_cursorPos;  
	//输入框长度  
	float inputFrameWidth;  
	//允许输入的最大字符数Unicode  
	float inputMaxLength;  
	int nLenCount;  
	int* codeNumType;    //每个字符对应的字节数量  
	int codeCur;         //当前第几个字符  
	int startCur;        //行开头字符下标  
	int endCur;          //行末尾下标  
	// 输入框总内容  
	std::string *m_pInputText;  
	std::string inpuText; //当前输入框内容  
public:  
	CursorTextField();  
	~CursorTextField();  
	// static  
	static CursorTextField* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);  
	// CCLayer  
	void onEnter();  
	void onExit();  
	bool init();  
	// 初始化光标精灵  
	void initCursorSprite(int nHeight);  

	// CCTextFieldDelegate  
	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);  
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);  
	virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);  
	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);  

	// 判断是否点击在TextField处  
	bool isInTextField(CCTouch *pTouch);  
	// 得到TextField矩形  
	CCRect getRect();  

	// 打开输入法  
	void openIME();  
	// 关闭输入法  
	void closeIME();  

	const char* getInputText();  
	void setInpuntText(char* text);  
	void setInputWidth(float width);  
	void setInputMaxLength(float length);  

	int Utf82Unicode(LPWSTR out,  int outsize , LPSTR in,int insize);

	// CCLayer Touch  
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ; 
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;  
};  

#endif  