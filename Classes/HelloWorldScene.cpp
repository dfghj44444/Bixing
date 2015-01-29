#include "HelloWorldScene.h"
#include "CursorTextField.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	//can be here, add 
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
															
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
	auto sizeScreen = Director::getInstance()->getVisibleSize();
	//add menu start
	const int MENU_COUNT = 4;
	MenuItemImage* theMenuItems[MENU_COUNT];
	//the blow buttons
	for (int i = 0 ;i < MENU_COUNT;i++)
	{
		auto* btnEvents = MenuItemImage::create( "btn.png" , "btn_.png" );
        auto tmpScale = sizeScreen.width/MENU_COUNT/btnEvents->getContentSize().width;
	    btnEvents->setPosition(Vec2(origin.x  + btnEvents->getContentSize().width/2*tmpScale + i *sizeScreen.width/4,
			origin.y + btnEvents->getContentSize().height/2));
		btnEvents->setScaleX(tmpScale);
	    theMenuItems[i]=btnEvents;
	}
	theMenuItems[0]->setCallback(CC_CALLBACK_1(HelloWorld::onMenuEvent ,this));
	theMenuItems[1]->setCallback(CC_CALLBACK_1(HelloWorld::onMenuMoney ,this));
	theMenuItems[2]->setCallback(CC_CALLBACK_1(HelloWorld::onMenuMember,this));
	auto menu_ = Menu::create(theMenuItems[0], theMenuItems[1],theMenuItems[2],theMenuItems[3],nullptr);

	menu_->setPosition(0,0);
	this->addChild(menu_, 0);
	//add menu ended
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//Œ¥∂®“Â––Œ™£¨Œ™∑¿÷πŒ™ø�?
void HelloWorld::menuCallback(Ref* pSender)
{
	 MessageBox("thi btn hadnt bind to any callback","Alert");
}
//show events
void HelloWorld::onMenuEvent(Ref* pSender)
{

   //make "add new event" shows
	//���εĽ������@ʾ
	CCTextFieldTTF*  tf1 = CCTextFieldTTF::textFieldWithPlaceHolder("InputHere","Thonburi",50);
	//�O���ɫ
	tf1->setColor(ccc3(255,0,0));
	//�O��λ��
	tf1->setPosition(ccp(100,100));
	//�_������ݔ���
	tf1->attachWithIME();
	this->addChild(tf1);
   //make list of event shows
//----------------------------------------------------------------	
    //make "add new event" shows
 //   auto* theInput = CursorTextField::textFieldWithPlaceHolder("InputHere","Thonburi",50);
	//tf1->setColor(ccc3(255,255,0));
 //   theInput->setPosition(200,200);
 //   this->addChild(theInput);
    //make list of event shows
//-----------------------------------------------------------------------------------

}
//show money
void HelloWorld::onMenuMoney(Ref* pSender)
{

}
//show member
void HelloWorld::onMenuMember(Ref* pSender)
{

}