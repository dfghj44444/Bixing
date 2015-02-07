#include "HelloWorldScene.h"
#include "CursorTextField.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"	

USING_NS_CC;
using namespace cocos2d::extension;  
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
//艗楼鈭偮�溍傗�撯�撆掆劉拢篓艗鈩⑩垜驴梅蟺艗鈩⒚糕�?
void HelloWorld::menuCallback(Ref* pSender)
{
	 MessageBox("thi btn hadnt bind to any callback","Alert");
}
//show events
void HelloWorld::onMenuEvent(Ref* pSender)
{

   //make "add new event" shows
	//簡單的建立和顯示
	CCTextFieldTTF*  tf1 = CCTextFieldTTF::textFieldWithPlaceHolder("InputHere","Thonburi",50);
	//設定顏色
	tf1->setColor(ccc3(255,0,0));
	//設定位置
	tf1->setPosition(ccp(100,100));
	//開啟文字輸入框
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
	{
		std::vector<std::string>  _array;
		for (int i = 0; i < 20; i++) {

			_array.push_back( StringUtils::format("listView_item_%d",i));
		}

		ui::ListView* listView = ui::ListView::create();
		//SCROLLVIEW_DIR_VERTICAL  SCROLLVIEW_DIR_HORIZONTAL   
		listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		listView->setTouchEnabled(true);
		listView->setBounceEnabled(true);
		listView->setBackGroundImage("green.png");
		listView->setBackGroundImageScale9Enabled(true);
		listView->setSize(Size(480, 260));
		listView->setPosition(Point(200.f , 200.f));
		listView->addEventListener( CC_CALLBACK_2(HelloWorld::selectedItemEvent,this));

		this->addChild(listView);

		//create model
		ui::Button* default_button = ui::Button::create("backtotoppressed.png","backtotopnormal.png");
		default_button->setName("Title Button");

		ui::Layout* default_item = ui::Layout::create();
		default_item->setTouchEnabled(true);
		default_item->setSize(default_button->getSize());
		default_button->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
		default_item->addChild(default_button);

		//set model
		listView->setItemModel(default_item);

		//add default item
		ssize_t count = _array.size();
		for (int i = 0; i < count / 4; ++i) {
			listView->pushBackDefaultItem();
		}

		//insert default item
		for (int i = 0; i < count / 4; ++i) {
			listView->insertDefaultItem(0);
		}

		//add custom item

		for (int i = 0; i < count / 4; ++i) {
			ui::Button* custom_button = ui::Button::create("button.png","buttonHighlighted.png");
			custom_button->setName("Title Button");
			custom_button->setScale9Enabled(true);
			custom_button->setSize(default_button->getSize());

			ui::Layout* custom_item = ui::Layout::create();
			custom_item->setSize(custom_button->getSize());
			custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
			custom_item->addChild(custom_button);
			listView->pushBackCustomItem(custom_item);
		}

		//insert custom item
		Vector<ui::Widget*>& items = listView->getItems();
		ssize_t items_count = items.size();
		for (int i = 0; i < count  / 4; ++i) {
			ui::Button* custom_button = ui::Button::create("button.png","buttonHighlighted.png");
			custom_button->setName("Title Button");
			custom_button->setScale9Enabled(true);
			custom_button->setSize(default_button->getSize());

			ui::Layout* custom_item = ui::Layout::create();
			custom_item->setSize(custom_button->getSize());
			custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
			custom_item->addChild(custom_button);
			listView->insertCustomItem(custom_item, items_count);
		}

		//set item data
		items_count = items.size();
		for (int i = 0; i < items_count; ++i) {
			ui::Widget* item = listView->getItem(i);
			ui::Button* button = static_cast<ui::Button*>(item->getChildByName("Title Button"));
			size_t index = listView->getIndex(item);
			button->setTitleText(static_cast<std::string>(_array.at(index)).c_str());
		}

		listView->removeLastItem();
		//  listView->removeAllItems();
		listView->setGravity( ui::ListView::Gravity::CENTER_VERTICAL);
		listView->setItemsMargin(15.0f);

	}

}
//show money
void HelloWorld::onMenuMoney(Ref* pSender)
{

}
//show member
void HelloWorld::onMenuMember(Ref* pSender)
{

}

void HelloWorld::selectedItemEvent(cocos2d::Ref *pSender, ui::ListView::EventType type)
{

	switch (type) {
	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
		{
			auto* listView = static_cast<ui::ListView*>(pSender);

			log("%ld",listView->getCurSelectedIndex());
		}
		break;


	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
		{
			auto* listView = static_cast<ui::ListView*>(pSender);

			log("%ld",listView->getCurSelectedIndex());
		}
		break;
	default:
		break;
	}
}