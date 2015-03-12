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

	m_QuestList=nullptr;
	m_MoneyRecord=nullptr;
	m_ListMember=nullptr;

	initPageQuest();
	initPageMoney();
	initPageMember();
	enablePage(2);//show page quest
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto label = LabelTTF::create("Hello World", "Arial", 24);
    //// position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(label, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
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
	tf1->setColor( ccc3( 255 , 0 , 0 ) );
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

}
//show money and hide others
void HelloWorld::onMenuMoney(Ref* pSender)
{

}
//show memberand hide others
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

void HelloWorld::editBoxEditingDidBegin( EditBox* editBox )
{

}

void HelloWorld::editBoxEditingDidEnd( EditBox* editBox )
{
	//如果有内容，则增加一条
    auto theContent = editBox->getText();

	////insert custom item
	m_QuestList->pushBackDefaultItem();		 
	Vector<ui::Widget*>& items = m_QuestList->getItems();
	int theLastIndex = items.size()-1;
	ui::Widget* item = m_QuestList->getItem(theLastIndex);
	ui::Button* button = static_cast<ui::Button*>(item->getChildByName("Title"));

	button->setTitleText(static_cast<std::string>(theContent));

	ui::Button* btnSign = static_cast<ui::Button*>(item->getChildByName("Sign"));

	btnSign->setTitleText("xingmin:2015/3/5-205/4/6");
	btnSign->setTitleColor(Color3B(0x00,0xff,0x80));
}

void HelloWorld::editBoxTextChanged( EditBox* editBox, const std::string& text )
{

}

void HelloWorld::editBoxReturn( EditBox* editBox )
{

}

	
void HelloWorld::initPageQuest()
{
	auto sizeScreen = Director::getInstance()->getVisibleSize();
	//add text input
	CCSize editBoxSize = CCSizeMake(sizeScreen.width - 50, 60);
	EditBox* editBoxName = EditBox::create(editBoxSize, Scale9Sprite::create("green_edit.png"));
	editBoxName->setPosition( ccp(sizeScreen.width/2 , sizeScreen.height-30 ) );	 //左下角定位
	this->addChild(editBoxName);
	editBoxName->setFontName("fonts/Paint Boy.ttf");
	editBoxName->setFontSize(20);
	editBoxName->setFontColor(ccRED);
	editBoxName->setPlaceHolder("输入新任务后回车:");
	editBoxName->setPlaceholderFontColor(ccWHITE);
	editBoxName->setMaxLength(8); //限制字符长度	

	//模式类型设置
	editBoxName->setInputMode(EditBox::InputMode::SINGLE_LINE);
	editBoxName->setInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS);
	editBoxName->setReturnType(EditBox::KeyboardReturnType::DEFAULT);
	//委托代理对象this
	editBoxName->setDelegate(this);	
	m_inputQuest = editBoxName;

	//初始化list
	std::vector<std::string>  _array;
	for (int i = 0; i < 20; i++)
		_array.push_back( StringUtils::format("listView_item_%d",i));

	ui::ListView* listView = ui::ListView::create();
	//SCROLLVIEW_DIR_VERTICAL  SCROLLVIEW_DIR_HORIZONTAL   
	listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);
	//listView->setBackGroundImage("green.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setSize(Size(sizeScreen.width, sizeScreen.height-200));
	listView->setPosition(Point(0 , (sizeScreen.height-200)/2-300));
	listView->addEventListener( CC_CALLBACK_2(HelloWorld::selectedItemEvent,this));
	this->addChild(listView);
	m_QuestList = listView;

	//create model	
	//标题
	const int HEIGHT_ITEM = 30;
	ui::Layout* default_item = ui::Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setBackGroundImageScale9Enabled(true);
	default_item->setBackGroundImage("ItemBg.png");
	default_item->setSize(Size(sizeScreen.width,HEIGHT_ITEM*2));

	ui::Button* default_button = ui::Button::create();
	default_button->setName("Title");
	default_button->setPosition(Point(default_item->getSize().width / 2.0f, HEIGHT_ITEM / 2.0f*3 ));

	//姓名和日期
	ui::Button* btnSign	= ui::Button::create();
	btnSign->setName("Sign");
	btnSign->setPosition(Point(default_item->getSize().width / 2.0f, HEIGHT_ITEM / 2.0f));

	default_item->addChild(default_button);
	default_item->addChild(btnSign);

	//set model ，模板
	listView->setItemModel(default_item);

	//add default item
	//ssize_t count = _array.size();
	//for ( int i = 0; i < count / 4; ++i ) 
	//	listView->pushBackDefaultItem();
	//insert default item
	//for ( int i = 0; i < count / 4; ++i )
	//	listView->insertDefaultItem(0);

	////add custom item	,这是和defaultitem长得不一样的
	//for ( int i = 0 ; i < count / 4 ; ++i ) {
	//	ui::Button* custom_button = ui::Button::create("button.png","buttonHighlighted.png");
	//	custom_button->setName("Title Button");
	//	custom_button->setScale9Enabled(true);
	//	custom_button->setSize(default_button->getSize());

	//	ui::Layout* custom_item = ui::Layout::create();
	//	custom_item->setSize(custom_button->getSize());
	//	custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
	//	custom_item->addChild(custom_button);
	//	listView->pushBackCustomItem(custom_item);
	//}

	////insert custom item
	//Vector<ui::Widget*>& items = listView->getItems();
	//for (int i = 0; i < items.size(); ++i) {
	//	ui::Widget* item = listView->getItem(i);
	//	ui::Button* button = static_cast<ui::Button*>(item->getChildByName("Title Button"));
	//	size_t index = listView->getIndex(item);
	//	button->setTitleText(static_cast<std::string>(_array.at(index)).c_str());
	//}

	//  listView->removeLastItem();
	//  listView->removeAllItems();
	listView->setGravity( ui::ListView::Gravity::TOP);
	listView->setItemsMargin(50.0f);
}

void HelloWorld::initPageMoney()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
		auto sizeScreen = Director::getInstance()->getVisibleSize();
	//初始化list
	std::vector<std::string>  _array;
	for (int i = 0; i < 20; i++)
		_array.push_back( StringUtils::format("listView_item_%d",i));

	ui::ListView* listView = ui::ListView::create();
	//SCROLLVIEW_DIR_VERTICAL  SCROLLVIEW_DIR_HORIZONTAL   
	listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);
	//listView->setBackGroundImage("green.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setSize(Size(sizeScreen.width, sizeScreen.height-60));
	listView->setPosition(Point(0 ,0));
	listView->addEventListener( CC_CALLBACK_2(HelloWorld::selectedItemEvent,this));
	this->addChild(listView);
	
	//create model	
	//数额
	const int HEIGHT_ITEM = 30;
	ui::Layout* default_item = ui::Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setBackGroundImageScale9Enabled(true);
	default_item->setBackGroundImage("ItemBg.png");
	default_item->setSize(Size(sizeScreen.width,HEIGHT_ITEM*2));

	ui::Button* default_button = ui::Button::create();
	default_button->setName("Title");
	default_button->setPosition(Point(default_item->getSize().width / 2.0f, HEIGHT_ITEM / 2.0f*3 ));
	default_button->setColor(ccc3(0x00,0x0f,0xf0));
	//姓名和日期
	ui::Button* btnSign	= ui::Button::create();
	btnSign->setName("Sign");
	btnSign->setPosition(Point(default_item->getSize().width / 2.0f, HEIGHT_ITEM / 2.0f));

	default_item->addChild(default_button);
	default_item->addChild(btnSign);

	//set model ，模板
	listView->setItemModel(default_item);

	listView->setGravity( ui::ListView::Gravity::TOP);
	listView->setItemsMargin(50.0f);

	m_MoneyRecord = listView;

	//造数据
	for (int i = 0 ; i < 2; i++)
	{
		listView->pushBackDefaultItem();
		Vector<ui::Widget*>& items = listView->getItems();
		int theLastIndex = items.size()-1;
		ui::Widget* item = listView->getItem(theLastIndex);
		ui::Button* button = static_cast<ui::Button*>(item->getChildByName("Title"));
		button->setTitleText(static_cast<std::string>("￥:100"));
		ui::Button* btnSign = static_cast<ui::Button*>(item->getChildByName("Sign"));
		btnSign->setTitleText("邢敏--写作<我与宗师二三事》:2015/3/5 ");
		btnSign->setTitleColor(Color3B(0x00,0xff,0x80));
	}
}
void HelloWorld::initPageMember()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
		auto sizeScreen = Director::getInstance()->getVisibleSize();
	//初始化list
	std::vector<std::string>  _array;
	for (int i = 0; i < 20; i++)
		_array.push_back( StringUtils::format("listView_item_%d",i));

	ui::ListView* listView = ui::ListView::create();
	//SCROLLVIEW_DIR_VERTICAL  SCROLLVIEW_DIR_HORIZONTAL   
	listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);
	//listView->setBackGroundImage("green.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setSize(Size(sizeScreen.width, sizeScreen.height-200));
	listView->setPosition(Point(0 , (sizeScreen.height-200)/2-300));
	listView->addEventListener( CC_CALLBACK_2(HelloWorld::selectedItemEvent,this));
	this->addChild(listView);

	//create model	
	//数额
	const int HEIGHT_ITEM = 30;
	ui::Layout* default_item = ui::Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setBackGroundImageScale9Enabled(true);
	default_item->setBackGroundImage("ItemBg.png");
	default_item->setSize(Size(sizeScreen.width,HEIGHT_ITEM*2));

	ui::Button* default_button = ui::Button::create();
	default_button->setName("Title");
	default_button->setPosition(Point(default_item->getSize().width / 2.0f, HEIGHT_ITEM / 2.0f*3 ));
	default_button->setColor(ccc3(0x00,0xff,0xf0));
	//姓名和日期
	ui::Button* btnSign	= ui::Button::create();
	btnSign->setName("Sign");
	btnSign->setPosition(Point(default_item->getSize().width / 2.0f, HEIGHT_ITEM / 2.0f));

	default_item->addChild(default_button);
	default_item->addChild(btnSign);

	//set model ，模板
	listView->setItemModel(default_item);

	listView->setGravity( ui::ListView::Gravity::TOP);
	listView->setItemsMargin(50.0f);

	m_ListMember = listView;

	//造数据
	std::string names[3] = {"panpan","xingmin","guoguo","+"};
	for (int i = 0 ; i < 3; i++)
	{
		listView->pushBackDefaultItem();
		Vector<ui::Widget*>& items = listView->getItems();
		int theLastIndex = items.size()-1;
		ui::Widget* item = listView->getItem(theLastIndex);
		ui::Button* button = static_cast<ui::Button*>(item->getChildByName("Title"));
		button->setTitleText(names[i]);
		ui::Button* btnSign = static_cast<ui::Button*>(item->getChildByName("Sign"));
		btnSign->setTitleText("加入日期:2015/3/5 ");
		btnSign->setTitleColor(Color3B(0x00,0xff,0x80));
	}

	//ui::Button* button = ui::Button::create("btn_create.png")  ;
	//button->setPosition(Point(button->getSize().wit , button->getSize().height));
	//this->addChild(button);
	//m_CreateGroup = button;
}

void HelloWorld::enablePage( int flgPage )
{
	m_inputQuest->setVisible(flgPage==0);
	m_QuestList->setVisible(flgPage==0);

	m_MoneyRecord->setVisible(flgPage == 1);

	m_ListMember->setVisible(flgPage == 2) ;
	m_CreateGroup->setVisible(flgPage == 2);
}
