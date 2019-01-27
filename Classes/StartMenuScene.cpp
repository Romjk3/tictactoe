#include "StartMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameSettingsMenuScene.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
    return StartMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem*> MenuItems;
    
    auto *PvsAIMenuLabel = Label::createWithTTF("P vs AI", "fonts/Marker Felt.ttf", 24);
   
    auto PvsAIItem = MenuItemLabel::create(PvsAIMenuLabel,
    CC_CALLBACK_1(StartMenu::goToGameMenuScene, this));

    MenuItems.pushBack(PvsAIItem);

    auto *PvsPMenuLabel = Label::createWithTTF("P vs P", "fonts/Marker Felt.ttf", 24);
    auto PvsPItem = MenuItemLabel::create(PvsPMenuLabel,
    CC_CALLBACK_1(StartMenu::menuCloseCallback, this));

    MenuItems.pushBack(PvsPItem);
    
    auto *exitMenuLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
    auto exitItem = MenuItemLabel::create(exitMenuLabel,
    CC_CALLBACK_1(StartMenu::menuCloseCallback, this));

    MenuItems.pushBack(exitItem);
    
    auto menu = Menu::createWithArray(MenuItems);
    menu->alignItemsVerticallyWithPadding(PvsAIMenuLabel->getContentSize().height);
    if (menu == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else 
    {   
        menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                               origin.y + visibleSize.height/2));
        this->addChild(menu, 1);
    }
    
    auto label = Label::createWithTTF("X vs 0", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    return true;
}


void StartMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void StartMenu::goToGameMenuScene(Ref* pSender)
{
    auto scene = GameSettingsMenu::createScene();
  
    Director::getInstance()->replaceScene(scene);
}