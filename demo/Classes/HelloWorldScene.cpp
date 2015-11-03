#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "CCDeviceLocale.h"
#include "CCURLOpener.h"

USING_NS_CC;
USING_NS_CC_EXT;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // add a facebook button
    CCMenuItemFont *fbItem = CCMenuItemFont::create("Facebook", this, menu_selector(HelloWorld::openFacebookURL));
    fbItem->setPosition(ccp(origin.x + visibleSize.width/1.5 - fbItem->getContentSize().width/2,
                            origin.y + visibleSize.height/2 - fbItem->getContentSize().height/2));
    
    // add a twitter button
    CCMenuItemFont *twitterItem = CCMenuItemFont::create("Twitter", this, menu_selector(HelloWorld::openTwitterURL));
    twitterItem->setPosition(ccp(origin.x + visibleSize.width/2.5 - twitterItem->getContentSize().width/2,
                            origin.y + visibleSize.height/2 - twitterItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, fbItem, twitterItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    // test device's locale
    CCLOG("Device language (raw): %s", ccdeviceLocale_getLanguage());
    CCLOG("Device language (code): %d", ccdeviceLocale_getLanguageK());
    
    return true;
}

void HelloWorld::openFacebookURL(cocos2d::CCObject *pSender)
{
    CCURLOpener *urlOpener = CCURLOpener::create();
    
    // try to open app-link of facebook
    if(!urlOpener->openURL("fb://profile/374701732647919"))
    {
        // open it with browser
        urlOpener->openURL("https://www.facebook.com/secretcharsg");
    }
}

void HelloWorld::openTwitterURL(cocos2d::CCObject *pSender)
{
    CCURLOpener *urlOpener = CCURLOpener::create();
    
    // try to open app-link of facebook
    if(!urlOpener->openURL("twitter://user?screen_name=secretcharsg"))
    {
        // open it with browser
        urlOpener->openURL("https://twitter.com/secretcharsg");
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
