#include "InputWidget.h"  
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


bool InputWidget::init()  
{  
	if (!CCLayer::init())    return false;  
	
	mSize=Director::getInstance()->getWinSize();
	mBg= CCSprite::create("msgbox.png");  
	mBg->setPosition(Vec2(mSize.width / 2, mSize.height / 2));
	this->addChild(mBg);
    
    m_dispatcher = Director::getInstance()->getEventDispatcher();
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(InputWidget::onTouchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(InputWidget::onTouchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(InputWidget::onTouchEnded, this);
    m_dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
    
	return true;  
}  

void InputWidget::onOK(Ref* pSender)
{
	this->removeFromParentAndCleanup(true);  
}  



bool InputWidget::onTouchBegan(Touch *pTouch, Event *pEvent)
{    
	//吞掉触摸事件  
	return true;    
}    

void InputWidget::onTouchMoved(Touch *pTouch, Event *pEvent)
{    

}    

void InputWidget::onTouchEnded(Touch *pTouch, Event *pEvent)
{    
	Menu* pMenu = (Menu*)this->getChildByTag(133);
	if ( pMenu && pMenu->ccTouchBegan(pTouch,pEvent))
		pMenu->ccTouchEnded(pTouch,pEvent);
}    

void InputWidget::onTouchCancelled(Touch *pTouch, Event *pEvent)
{    

}  

 //132 for text,133 for menu,134 for sprite
void InputWidget::SetShowType( int nFlag )
{
	using namespace CocosDenshion;
	if ( 0 == nFlag )//第一次提示你要打电话
	{
		LabelTTF* pLabel=LabelTTF::create("请找到电话并打给鑫林","Arial",40);
		pLabel->setColor(Color3B(0x80,0x4c,0x1b));
		pLabel->setPosition(Vec2(mSize.width / 2, mSize.height / 2+40));
		this->addChild(pLabel);  

		MenuItemImage *pMenuItem = MenuItemImage::create(
			"ok_01.png",  
			"ok_02.png",  
			CC_CALLBACK_1(InputWidget::onOK,this));
		pMenuItem->setPosition(Vec2(mSize.width / 2, mSize.height / 2-40));
		Menu* pMenu = Menu::create(pMenuItem,NULL);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu); 
		pMenu->setTag(133);
		SimpleAudioEngine::getInstance()->playEffect("alert.mp3");
	}
	else if ( 1 == nFlag )//显示正在拨通
	{
		Sprite *ItemBox = Sprite::create("phone.png");

		ItemBox->setPosition(Vec2(mSize.width / 2, mSize.height / 2));
		ItemBox->setTag(134);		
		this->addChild(ItemBox); 
		SimpleAudioEngine::getInstance()->playEffect("phone.mp3");

		this->schedule(schedule_selector(InputWidget::step), 5.0f);
	}
	else if ( 2 == nFlag )//显示捡到钥匙
	{
		LabelTTF* pLabel=LabelTTF::create("你发现了一枚闪闪发亮的钥匙！","Arial",35);
		pLabel->setColor(Color3B(0x80,0x4c,0x1b));
		pLabel->setPosition(Vec2(mSize.width / 2, mSize.height / 2+40));
		this->addChild(pLabel);  
		SimpleAudioEngine::getInstance()->playEffect("ring.mp3");

		MenuItemImage *pMenuItem = MenuItemImage::create(
			"ok_01.png",  
			"ok_02.png",  
			CC_CALLBACK_1(InputWidget::onOK,this));
		pMenuItem->setPosition(Vec2(mSize.width / 2, mSize.height / 2-40));
		Menu* pMenu = Menu::create(pMenuItem,NULL);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu); 
		pMenu->setTag(133);
	}
	else if ( 3 == nFlag )//显示胜利
	{
		LabelTTF* pLabel=LabelTTF::create("恭喜逃出，快回家烧饭吧^.^","Arial",35);
		pLabel->setColor(Color3B(0x80,0x4c,0x1b));
		pLabel->setPosition(Vec2(mSize.width / 2, mSize.height / 2+40));
		this->addChild(pLabel);
		SimpleAudioEngine::getInstance()->playEffect("dooropen.mp3");
		//退出按钮
		MenuItemImage *pMenuItem = MenuItemImage::create(
			"exit_.png",  
			"exit.png",  
			CC_CALLBACK_1(InputWidget::onOK,this));
		pMenuItem->setPosition(Vec2(mSize.width / 2, mSize.height / 2-40));
		Menu* pMenu = Menu::create(pMenuItem,NULL);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu); 
		pMenu->setTag(133);
	}
}

void InputWidget::close()
{

	this->removeFromParentAndCleanup(true); 
}
//拨号中的延时
void InputWidget::step(float dt)
{
	this->unschedule(schedule_selector( InputWidget::step ));
    m_dispatcher->removeEventListener(m_listener);
	auto* pSprite = this->getChildByTag(134);
	Texture2D * texture =CCTextureCache::getInstance()->addImage("phone.png");
	static_cast<Sprite*>(pSprite)->setTexture(texture);

	using namespace CocosDenshion;
	SimpleAudioEngine::getInstance()->playEffect("wei.mp3") ;
						
	auto player = this->getParent()->getChildByTag(248);
	auto* pLabel = player->getChildByTag(250);
	static_cast<LabelTTF*>(pLabel)->setString("喂喂！");
}

void InputWidget::onExit(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}