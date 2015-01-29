#ifndef CursorInputDemo_CursorTextField_h  
#define CursorInputDemo_CursorTextField_h  

#include "cocos2d.h"  

USING_NS_CC;  

class CursorTextField: public CCTextFieldTTF, public CCTextFieldDelegate
{  
private:  
	// �����ʼλ��  
	CCPoint m_beginPos;  
	// ��꾫��  
	CCSprite *m_pCursorSprite;  
	// ��궯��  
	CCAction *m_pCursorAction;  
	// �������  
	CCPoint m_cursorPos;  
	//����򳤶�  
	float inputFrameWidth;  
	//�������������ַ���Unicode  
	float inputMaxLength;  
	int nLenCount;  
	int* codeNumType;    //ÿ���ַ���Ӧ���ֽ�����  
	int codeCur;         //��ǰ�ڼ����ַ�  
	int startCur;        //�п�ͷ�ַ��±�  
	int endCur;          //��ĩβ�±�  
	// �����������  
	std::string *m_pInputText;  
	std::string inpuText; //��ǰ���������  
public:  
	CursorTextField();  
	~CursorTextField();  
	// static  
	static CursorTextField* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);  
	// CCLayer  
	void onEnter();  
	void onExit();  
	bool init();  
	// ��ʼ����꾫��  
	void initCursorSprite(int nHeight);  

	// CCTextFieldDelegate  
	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);  
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);  
	virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);  
	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);  

	// �ж��Ƿ�����TextField��  
	bool isInTextField(CCTouch *pTouch);  
	// �õ�TextField����  
	CCRect getRect();  

	// �����뷨  
	void openIME();  
	// �ر����뷨  
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