#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
USING_NS_CC;
using namespace cocos2d::extension;
class HelloWorld : public cocos2d::Layer,cocos2d::extension::EditBoxDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//通用未定义回调，无实义
	void menuCallback(Ref* pSender);
	void onMenuEvent(Ref* pSender);
	void onMenuMoney(Ref* pSender);
	void onMenuMember(Ref* pSender);
	void selectedItemEvent(cocos2d::Ref *pSender, ui::ListView::EventType type);

	virtual void editBoxEditingDidBegin(EditBox* editBox);                      //开始编辑
	virtual void editBoxEditingDidEnd(EditBox* editBox);                        //结束编辑
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text); //编辑框文字改变
	virtual void editBoxReturn(EditBox* editBox);     

protected:
	ui::ListView* m_QuestList;
};

#endif // __HELLOWORLD_SCENE_H__
