#ifndef _INPUT_WIDGET_H_
#define _INPUT_WIDGET_H_
#include "cocos2d.h"

USING_NS_CC;

class InputWidget : public cocos2d::Layer
{
private:
	  cocos2d::Size mSize;
	  cocos2d::Sprite* mBg;
      EventDispatcher* m_dispatcher ;
      EventListenerTouchOneByOne* m_listener;
public:
	  CREATE_FUNC(InputWidget);
	  bool init();
	  void SetShowType(int nFlag);
	  void onOK(Ref* pSender);
	  void onExit(Ref* pSender);

	  // default implements are used to call script callback if exist
	  virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
	  virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
	  virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
	  virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;
	  void step(float dt);
	  void close();

};			 

#endif