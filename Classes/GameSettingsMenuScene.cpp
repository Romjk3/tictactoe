#include "GameSettingsMenuScene.h"
#include "SimpleAudioEngine.h"
#include "StartMenuScene.h"

USING_NS_CC;

Scene* GameSettingsMenu::createScene()
{
    return GameSettingsMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameSettingsMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto sideLabel = Label::createWithTTF("Camp", "fonts/Marker Felt.ttf", 24);
    if (sideLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        sideLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                    origin.y + visibleSize.height - sideLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(sideLabel, 1);
    }

    auto difficultyLabel = Label::createWithTTF("Difficulty", "fonts/Marker Felt.ttf", 24);
    if (difficultyLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        difficultyLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                          origin.y + visibleSize.height/2 - difficultyLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(difficultyLabel, 1);
    }

    Vector<MenuItem*> sideMenuItems;
    
    auto *xLabel = Label::createWithTTF("X", "fonts/Marker Felt.ttf", 48);
    auto xItem = MenuItemLabel::create(xLabel,
    CC_CALLBACK_1(GameSettingsMenu::menuCloseCallback, this));

    sideMenuItems.pushBack(xItem);

    auto *oLabel = Label::createWithTTF("O", "fonts/Marker Felt.ttf", 48);
    auto oItem = MenuItemLabel::create(oLabel,
    CC_CALLBACK_1(GameSettingsMenu::menuCloseCallback, this));

    sideMenuItems.pushBack(oItem);
    
    auto sideMenu = Menu::createWithArray(sideMenuItems);
    sideMenu->alignItemsHorizontallyWithPadding(sideLabel->getContentSize().width);
    if (sideMenu == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else 
    {   
        sideMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   origin.y + visibleSize.height/2 + xLabel->getContentSize().height));
        this->addChild(sideMenu, 1);
    }


    Vector<MenuItem*> difficultyMenuItems;
    
    auto *easyLabel = Label::createWithTTF("Easy", "fonts/Marker Felt.ttf", 12);
    auto easyItem = MenuItemLabel::create(easyLabel,
    CC_CALLBACK_1(GameSettingsMenu::menuCloseCallback, this));

    difficultyMenuItems.pushBack(easyItem);

    auto *averageLabel = Label::createWithTTF("Average", "fonts/Marker Felt.ttf", 12);
    auto averageItem = MenuItemLabel::create(averageLabel,
    CC_CALLBACK_1(GameSettingsMenu::menuCloseCallback, this));

    difficultyMenuItems.pushBack(averageItem);
    
    auto *hardLabel = Label::createWithTTF("Hard", "fonts/Marker Felt.ttf", 12);
    auto hardItem = MenuItemLabel::create(hardLabel,
    CC_CALLBACK_1(GameSettingsMenu::menuCloseCallback, this));

    difficultyMenuItems.pushBack(hardItem);

    auto difficultyMenu = Menu::createWithArray(difficultyMenuItems);
    difficultyMenu->alignItemsVerticallyWithPadding(easyLabel->getContentSize().height);
    if (difficultyMenu == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else 
    {   
        difficultyMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                         origin.y + visibleSize.height/2
                                         - difficultyMenu->getContentSize().height/4));
        this->addChild(difficultyMenu, 1);
    }


    Vector<MenuItem*> backMenuItems;
    
    auto *backLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 12);
    auto backItem = MenuItemLabel::create(backLabel,
    CC_CALLBACK_1(GameSettingsMenu::goToStartMenu, this));

    backMenuItems.pushBack(backItem);

    auto backMenu = Menu::createWithArray(backMenuItems);
    if (difficultyMenu == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else 
    {   
        backMenu->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + backLabel->getContentSize().height));
        this->addChild(backMenu, 1);
    }

    return true;
}


void GameSettingsMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


void GameSettingsMenu::goToStartMenu(Ref* pSender)
{
    auto scene = StartMenu::createScene();
  
    Director::getInstance()->replaceScene(scene);
}
