/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ClippingNodeTest.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "AudioEngine.h"
#include<sstream>
#include<cmath>
#include <cocos\editor-support\cocostudio\SimpleAudioEngine.h>
#include <iomanip>
#include<iostream>
#include<fstream>
#include "external\tinyxml2\tinyxml2.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace tinyxml2;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
unsigned short int onTabNum = 0;
unsigned short int usedSprite;
unsigned short int modifyer = 0;
unsigned short int modifyerNumber = 8;
bool startRadIsActive = false;
bool startRadIsActive2 = false;

bool endRadIsActive = false;
bool endRadIsActive2 = false;

bool posVarIsActive = false;
bool posVarIsActive2 = false;

bool speedAngleIsActive = false;
bool speedIsActive = false;

bool angleIsActive = false;

bool gravityIsActive = false;
bool gravityIsActive2 = false;

int changeWhenDone = 97;
bool moveParticleIsActive = true;
# define M_PI           3.14159265358979323846
int randNum(int min, int max)
{
    return rand() % max + min;
}
bool particleEditio = false;
unsigned short int valueXGlobal = 338;
unsigned short int valueYGlobal = 320;
unsigned short int valueXGlobalGravity;
unsigned short int valueYGlobalGravity;
unsigned short int highlightedInfoMessageCheckbox = 0;
// on "init" you need to initialize your instance
class particleProperties {
public:
};
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
    auto winSize = Director::getInstance()->getWinSize();

    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    auto screenSize = glView->getFrameSize();
    int xPosFixed = screenSize.width / 2 + origin.x;
    int yPosFixed = screenSize.height / 2 + origin.y;

    clipper->setClippingRegion(Rect(xPosFixed - 594, yPosFixed - 378, 324, 487));
    particleSystem->setAngleVar(90);
    particleSystem->setAngle(90);
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    //view->setFullscreen();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("533164_-Sunken-field-.mp3", true);
    //Nodes:
    particle_popup_texture->setPosition(Vec2(xPosFixed, yPosFixed));
    particle_popup_texture->setScaleX(0.25);
    particle_popup_texture->setScaleY(0.25);
    this->addChild(particle_popup_texture, -1);

    auto sprite = Sprite::create("U5ntitled.png");
    sprite->setPosition(Vec2(xPosFixed, yPosFixed)); //Background!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    sprite->setScaleX(0.25);
    sprite->setScaleY(0.25);
    sprite->setOpacity(255);
    this->addChild(sprite, -7);

    selectTextureBox->setTag(0);
    auto visualFakeText = Sprite::create("titles2.png"); // Particle properties (Colors etc...)
    visualFakeText->setPosition(Vec2(xPosFixed, yPosFixed));
    visualFakeText->setScaleX(0.25);
    visualFakeText->setScaleY(0.25);
    visualFakeText->setOpacity(255);
    visualFakeText->setLocalZOrder(5);

    auto motionFakeText = Sprite::create("titles.png"); // Particle properties (Max Particles, Duration, etc...)
    motionFakeText->setPosition(Vec2(xPosFixed, yPosFixed));
    motionFakeText->setScaleX(0.25);
    motionFakeText->setScaleY(0.25);
    motionFakeText->setOpacity(255);
    motionFakeText->setLocalZOrder(5);

    auto gravityFakeText = Sprite::create("titles5.png"); // Particle properties (Speed, PosVar, etc...)
    gravityFakeText->setPosition(Vec2(xPosFixed, yPosFixed));
    gravityFakeText->setScaleX(0.25);
    gravityFakeText->setScaleY(0.25);
    gravityFakeText->setOpacity(255);
    gravityFakeText->setLocalZOrder(5);


    auto radiusFakeText = Sprite::create("titles6.png"); // Particle properties (StartRad, EndRad, etc...)
    radiusFakeText->setPosition(Vec2(xPosFixed, yPosFixed));
    radiusFakeText->setScaleX(0.25);
    radiusFakeText->setScaleY(0.25);
    radiusFakeText->setOpacity(255);
    radiusFakeText->setLocalZOrder(5);


    particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED); // The particle
    particleSystem->setPosition(Vec2((xPosFixed)-430, (yPosFixed)-125));
    particleSystem->setScaleX(2);
    particleSystem->setScaleY(2);
    particleSystem->setLocalZOrder(2);



    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("arrows.plist");

    //__String* filename = __String::create("Particle_p.plist");
    clipper->addChild(particleSystem, 7);
    this->addChild(clipper, 4);
    restOfButtons.push_back(ui::Button::create("calcButton.png")); // Calc button
    restOfButtons[0]->setPosition(Vec2(xPosFixed + 393, yPosFixed + 38));
    restOfButtons[0]->setScaleX(0.25);
    restOfButtons[0]->setScaleY(0.25);
    restOfButtons[0]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::calcButtonFunc, this));
    this->addChild(restOfButtons[0]);
    short int i_Ydifference = 350; // The Y difference between each slider
    /*01*/restOfButtons.push_back(ui::Button::create("GJ_checkOn_001.png")); // Gravity checkbox
    /*02*/restOfButtons.push_back(ui::Button::create("GJ_checkOff_001.png")); // Radius checkbox
    /*03*/restOfButtons.push_back(ui::Button::create("GJ_checkOn_001.png")); // Grouped checkbox
    /*04*/restOfButtons.push_back(ui::Button::create("GJ_checkOff_001.png")); // Free checkbox
    /*05*/restOfButtons.push_back(ui::Button::create("GJ_checkOff_001.png")); // Relative checkbox
    /*06*/restOfButtons.push_back(ui::Button::create("ok.png")); // ok button
    /*07*/restOfButtons.push_back(ui::Button::create("quit.png")); // quit button
    /*08*/restOfButtons.push_back(ui::Button::create("GJ_colorBtn_001.png")); // color1 button
    /*09*/restOfButtons.push_back(ui::Button::create("GJ_colorBtn_001.png")); // color2 button
    /*10*/restOfButtons.push_back(ui::Button::create("GJ_colorBtn_001.png")); // color1Var button
    /*11*/restOfButtons.push_back(ui::Button::create("GJ_colorBtn_001.png")); // color2Var button
    /*12*/restOfButtons.push_back(ui::Button::create("reversecolor.png")); // reverse colors button
    /*13*/restOfButtons.push_back(ui::Button::create("reversecolor.png")); // reverse colorsVar button
    /*14*/restOfButtons.push_back(ui::Button::create("GJ_editObjBtn4_001.png")); // edit special button
    /*15*/restOfButtons.push_back(ui::Button::create("gj_ytIcon_001.png")); // YT button
    /*16*/restOfButtons.push_back(ui::Button::create("GJ_infoIcon_001.png")); // info button
    /*17*/restOfButtons.push_back(ui::Button::create("ok.png")); // ok button for help popup
    /*18*/restOfButtons.push_back(ui::Button::create("colorWood.png")); // 2.2's color thing
    /*19*/restOfButtons.push_back(ui::Button::create("full.png")); // fullscreen button
    /*20*/restOfButtons.push_back(ui::Button::create("window.png")); // windowed button
    /*21*/restOfButtons.push_back(ui::Button::create("maxButton.png")); // max button
    /*22*/restOfButtons.push_back(ui::Button::create("stop.png")); // stop button
    /*23, arrows*/
    srand(time(0));
    
    int randomArrow = randNum(0, 3);
    restOfButtons.push_back(ui::Button::create(
        "arrow_" + std::to_string(randomArrow) + ".png",
        "arrow_" + std::to_string(randomArrow) + ".png",
        "arrow_" + std::to_string(randomArrow) + ".png",
        ui::Widget::TextureResType::PLIST));
    /*24*/restOfButtons.push_back(ui::Button::create("lock.png")); // sub Lock button
    /*25*/restOfButtons.push_back(ui::Button::create("sub.png")); // [sub]  button
    /*26*/restOfButtons.push_back(ui::Button::create("infButton.png")); // INF. button
    /*...*/
    for (unsigned short int i = 1; i < 6; i++) {
        if (i == 4) {
            i_Ydifference = 350;

        }
        if (i < 3) {
            restOfButtons[i]->setPosition(Vec2(xPosFixed - 568, yPosFixed + i_Ydifference));
            restOfButtons[i]->setScaleX(0.135);
            restOfButtons[i]->setScaleY(0.135);
            restOfButtons[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::switchToGravity, this));
            this->addChild(restOfButtons[i]);
            i_Ydifference -= 64;
        }
        else {
            restOfButtons[i]->setPosition(Vec2(xPosFixed - 568, yPosFixed + i_Ydifference));
            restOfButtons[i]->setScaleX(0.135);
            restOfButtons[i]->setScaleY(0.135);
            restOfButtons[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::switchParticleType, this));
            this->addChild(restOfButtons[i]);
            i_Ydifference -= 64;
        }
    }

    restOfButtons[21]->setPosition(Vec2(xPosFixed + 299, yPosFixed + 38));
    restOfButtons[21]->setScaleX(0.25);
    restOfButtons[21]->setScaleY(0.25);
    restOfButtons[21]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[21]->stopAllActions();
            restOfButtons[21]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[21]->stopAllActions();
            restOfButtons[21]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));

            //particleSystem->setEmissionRate(-1);
            //labelArray[3]->setString(std::to_string((int)particleSystem->getEmissionRate()));

            particleSystem->fixTimings();
            //particleSystem->setFadeIn(0.5);
            labelArray[3]->setString(std::to_string((int)(particleSystem->getTotalParticles() / particleSystem->getLife())));
            //sliderArray[3]->setPercent(sliderArray[3]->getMaxPercent()/2);
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[21]->stopAllActions();
            restOfButtons[21]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
            break;
        default:
            break;
        }
        });

    //INF. button
    restOfButtons[26]->setPosition(Vec2(xPosFixed + 299, yPosFixed + 168));
    restOfButtons[26]->setScaleX(0.25);
    restOfButtons[26]->setScaleY(0.25);
    restOfButtons[26]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[26]->stopAllActions();
            restOfButtons[26]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[26]->stopAllActions();
            restOfButtons[26]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));
            particleSystem->setDuration(ParticleSystem::DURATION_INFINITY);
            particleSystem->resetSystem();
            labelArray[1]->setString("-1.00");
            sliderArray[1]->setPercent(0);
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[26]->stopAllActions();
            restOfButtons[26]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
            break;
        default:
            break;
        }
        });

    restOfButtons[22]->setPosition(Vec2(xPosFixed + 299+(93*2), yPosFixed + 38));
    restOfButtons[22]->setScaleX(0.25);
    restOfButtons[22]->setScaleY(0.25);
    restOfButtons[22]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[22]->stopAllActions();
            restOfButtons[22]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[22]->stopAllActions();
            restOfButtons[22]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));
            particleSystem->stopSystem();
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[22]->stopAllActions();
            restOfButtons[22]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
            break;
        default:
            break;
        }
        });
    this->addChild(restOfButtons[22]);

    restOfButtons[20]->setPosition(Vec2(xPosFixed + 540, yPosFixed - 338));
    restOfButtons[20]->setScaleX(0.175);
    restOfButtons[20]->setScaleY(0.175);
    restOfButtons[20]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (!infoPopupNode->getParent()) {
            GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
            switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                restOfButtons[20]->stopAllActions();
                restOfButtons[20]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.175 * 1.25)));
                break;
            case ui::Widget::TouchEventType::ENDED:
                restOfButtons[20]->stopAllActions();
                restOfButtons[20]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.175)));

                view->setWindowed(1920 * 0.8, 1080 * 0.8);
                break;
            case ui::Widget::TouchEventType::CANCELED:
                restOfButtons[20]->stopAllActions();
                restOfButtons[20]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.175)));
                break;
            default:
                break;
            }
        }
        });
    tabThree->addChild(restOfButtons[20], 16);

    restOfButtons[19]->setPosition(Vec2(xPosFixed + 425, yPosFixed - 338));
    restOfButtons[19]->setScaleX(0.175);
    restOfButtons[19]->setScaleY(0.175);
    restOfButtons[19]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (!infoPopupNode->getParent()) {
            GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
            switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                restOfButtons[19]->stopAllActions();
                restOfButtons[19]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.175 * 1.25)));
                break;
            case ui::Widget::TouchEventType::ENDED:
                restOfButtons[19]->stopAllActions();
                restOfButtons[19]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.175)));

                view->setFullscreen();
                break;
            case ui::Widget::TouchEventType::CANCELED:
                restOfButtons[19]->stopAllActions();
                restOfButtons[19]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.175)));
                break;
            default:
                break;
            }
        }
        });
    tabThree->addChild(restOfButtons[19], 16);



    restOfButtons[6]->setPosition(Vec2(xPosFixed + 513, yPosFixed + 340));
    restOfButtons[6]->setScaleX(0.25);
    restOfButtons[6]->setScaleY(0.25);
    restOfButtons[6]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::popUp, this));
    this->addChild(restOfButtons[6], 16);

    restOfButtons[7]->setPosition(Vec2(xPosFixed + 715, yPosFixed + 377));
    restOfButtons[7]->setScaleX(0.21);
    restOfButtons[7]->setScaleY(0.21);
    restOfButtons[7]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::quitFunction, this));
    this->addChild(restOfButtons[7], -3);

    restOfButtons[8]->setPosition(Vec2(xPosFixed - 565, yPosFixed + 350));
    restOfButtons[8]->setScaleX(0.15);
    restOfButtons[8]->setScaleY(0.15);
    //restOfButtons[8]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::quitFunction, this));
    this->addChild(restOfButtons[8], 16);

    restOfButtons[9]->setPosition(Vec2(xPosFixed - 480, yPosFixed + 350));
    restOfButtons[9]->setScaleX(0.15);
    restOfButtons[9]->setScaleY(0.15);
    //restOfButtons[8]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::quitFunction, this));
    this->addChild(restOfButtons[9], 16);

    restOfButtons[10]->setPosition(Vec2(xPosFixed - 565, yPosFixed + (350 - 85)));
    restOfButtons[10]->setScaleX(0.15);
    restOfButtons[10]->setScaleY(0.15);
    //restOfButtons[8]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::quitFunction, this));
    this->addChild(restOfButtons[10], 16);

    restOfButtons[11]->setPosition(Vec2(xPosFixed - 480, yPosFixed + (350 - 85)));
    restOfButtons[11]->setScaleX(0.15);
    restOfButtons[11]->setScaleY(0.15);
    //restOfButtons[8]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::quitFunction, this));
    this->addChild(restOfButtons[11], 16);

    restOfButtons[12]->setPosition(Vec2(xPosFixed - (480 - 85), yPosFixed + 350));
    restOfButtons[12]->setScaleX(0.25);
    restOfButtons[12]->setScaleY(0.25);
    restOfButtons[12]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::reverseColorsButtonFunc, this));
    this->addChild(restOfButtons[12], 16);

    restOfButtons[13]->setPosition(Vec2(xPosFixed - (480 - 85), yPosFixed + (350 - 85)));
    restOfButtons[13]->setScaleX(0.25);
    restOfButtons[13]->setScaleY(0.25);
    restOfButtons[13]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::reverseColorsButtonFunc, this));
    this->addChild(restOfButtons[13], 16);

    restOfButtons[14]->setPosition(Vec2(xPosFixed + 498, yPosFixed + +173));
    restOfButtons[14]->setScaleX(0.215);
    restOfButtons[14]->setScaleY(0.215);
    restOfButtons[14]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::popDown, this));
    this->addChild(restOfButtons[14], -1);

    restOfButtons[15]->setPosition(Vec2(xPosFixed - 665, yPosFixed - 370));
    restOfButtons[15]->setScaleX(0.18);
    restOfButtons[15]->setScaleY(0.18);
    restOfButtons[15]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::popTense, this));
    this->addChild(restOfButtons[15], 7);

    restOfButtons[18]->setPosition(Vec2(xPosFixed + 675, yPosFixed - 370));
    restOfButtons[18]->setScaleX(0.28 * 1.25 / 2);
    restOfButtons[18]->setScaleY(0.28*1.25/2);
    restOfButtons[18]->setTag(0);
    restOfButtons[18]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[18]->stopAllActions();
            restOfButtons[18]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.28 * 1.25 / 2 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[18]->stopAllActions();
            restOfButtons[18]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.28 * 1.25 / 2)));
            if (restOfButtons[18]->getTag() == 0) {
                restOfButtons[18]->setTag(1);
                particle_popup_texture->runAction(Repeat::create(Sequence::create(
                    TintTo::create(0.50, Color3B(255, 0, 0)),
                    TintTo::create(0.50, Color3B(255, 255, 0)),
                    TintTo::create(0.50, Color3B(0, 255, 0)),
                    TintTo::create(0.50, Color3B(0, 255, 255)),
                    TintTo::create(0.50, Color3B(0, 0, 255)),
                    TintTo::create(0.50, Color3B(255, 0, 255)), NULL), 623));

            }
            else if (restOfButtons[18]->getTag() == 1) {
                restOfButtons[18]->setTag(0);
                particle_popup_texture->stopAllActions();
                particle_popup_texture->setColor(Color3B::WHITE);
            }

            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[18]->stopAllActions();
            restOfButtons[18]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.28 * 1.25 / 2)));
            break;
        default:
            restOfButtons[18]->stopAllActions();
            restOfButtons[18]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.28 * 1.25 / 2)));
            break;
        
        }
        });
    popUpNode->addChild(restOfButtons[18], 7);

    //restOfButtons[16]->setPosition(Vec2(xPosFixed + 365, yPosFixed + 340));
    restOfButtons[16]->setPosition(Vec2(xPosFixed - 660, yPosFixed + 370));
    restOfButtons[16]->setScaleX(0.20);
    restOfButtons[16]->setScaleY(0.20);
    restOfButtons[16]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::openHelpPopup, this));
    this->addChild(restOfButtons[16], 10);

    auto infoPopup = Sprite::create("infoPopup.png");
    infoPopup->setPosition(0, 0);
    infoPopup->setScaleX(0.25);
    infoPopup->setScaleY(0.25);
    infoPopupNode->addChild(infoPopup, 30);

    auto infoPopupCheckboxes = Sprite::create("infoCheckBoxPopup.png");
    infoPopupCheckboxes->setPosition(0, 0);
    infoPopupCheckboxes->setScaleX(0.36);
    infoPopupCheckboxes->setScaleY(0.36);
    infoCheckboxesPopupNode->addChild(infoPopupCheckboxes, 30);
    infoCheckboxesPopupNode->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    infoCheckboxesTitle->setPosition(Vec2(0, 0 + 130));
    infoCheckboxesTitle->setScaleX(0.185);
    infoCheckboxesTitle->setScaleY(0.185);
    infoCheckboxesPopupNode->addChild(infoCheckboxesTitle, 31);
    this->addChild(infoCheckboxesPopupNode, 31);

    infoCheckboxesOkButton->setPosition(Vec2(0, -115));
    infoCheckboxesOkButton->setScaleX(0.23);
    infoCheckboxesOkButton->setScaleY(0.23);
    infoCheckboxesOkButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::closeInfoCheckboxesPopup, this));
    infoCheckboxesPopupNode->addChild(infoCheckboxesOkButton, 31);
    this->removeChild(infoCheckboxesPopupNode);

    cocos2d::Label* infoTitleLabel = Label::createWithBMFont("goldFont-uhd.fnt", "Particle Editor Help"); // "Particle Editor Help" String
    infoTitleLabel->setPosition(Vec2(0, 0 + 180));
    infoTitleLabel->setScaleX(0.175);
    infoTitleLabel->setScaleY(0.175);
    infoPopupNode->addChild(infoTitleLabel, 31);

    cocos2d::Label* infoLabel = Label::createWithBMFont("chatFont-uhd.fnt", "This is the info message... Recreated by XcreatorGoal.\nI hope you enjoy it, done in around 31 days.\n Credits: RobTopGames (used many of his textures)\n\n Thanks to sleicreider, jasmine, NachoBIT and xdpuppet\n for helping me get started :)", TextHAlignment::CENTER); // "text de el helpe" String

    std::string infoLabelColored = infoLabel->getString();
    for (unsigned short int i = 41; i < 53; i++) {
        if (infoLabel->getLetter(i) != nullptr)
    {infoLabel->getLetter(i)->setColor(Color3B(255, 0, 0));} }

    
    for (unsigned short int i = 100; i < 108; i++) {
        if (infoLabel->getLetter(i) != nullptr)
        {
            infoLabel->getLetter(i)->setColor(Color3B(250, 167, 255));
        }
    }
    
    for (unsigned short int i = 109; i < 121; i++) {
        if (infoLabel->getLetter(i) != nullptr)
        {
            infoLabel->getLetter(i)->setColor(Color3B(0, 255, 255));
        }
    }


    infoLabel->setPosition(Vec2(0, 0 + 13));
    infoLabel->setScaleX(0.18);
    infoLabel->setScaleY(0.18);
    infoPopupNode->addChild(infoLabel, 31);

    restOfButtons[17]->setPosition(Vec2(0, 0 - 165));
    restOfButtons[17]->setScaleX(0.230);
    restOfButtons[17]->setScaleY(0.230);
    restOfButtons[17]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::closeHelpPopup, this));
    infoPopupNode->addChild(restOfButtons[17], 31);


    blackBackgroundInfoCheckboxesPopup->setPosition(Vec2(xPosFixed, yPosFixed));
    blackBackgroundInfoCheckboxesPopup->setScaleX(0.25);
    blackBackgroundInfoCheckboxesPopup->setScaleY(0.25);
    blackBackgroundInfoCheckboxesPopup->setColor(Color3B::BLACK);
    blackBackgroundInfoCheckboxesPopup->setOpacity(120);
    blackBackgroundInfoCheckboxesPopup->setLocalZOrder(10);
    blackBackgroundInfoCheckboxesPopup->retain();


    blackBackgroundHelpPopup->setPosition(Vec2(xPosFixed, yPosFixed));
    blackBackgroundHelpPopup->setScaleX(0.25);
    blackBackgroundHelpPopup->setScaleY(0.25);
    blackBackgroundHelpPopup->setColor(Color3B::BLACK);
    blackBackgroundHelpPopup->setOpacity(155);
    blackBackgroundHelpPopup->setLocalZOrder(10);

    blackBackgroundHelpPopup->retain();
    infoPopupNode->retain();
    infoCheckboxesPopupNode->retain();
    infoPopupNode->setPosition(Vec2(xPosFixed, yPosFixed));
    infoPopupNode->setLocalZOrder(31);

    i_Ydifference -= 64;
    cocos2d::Label* gravityLabel = Label::createWithBMFont("bigFont-uhd.fnt", "Gr"); // "Gravity" String (1)
    gravityLabel->setPosition(Vec2(xPosFixed - 497, yPosFixed + 352));
    gravityLabel->setScaleX(0.08);
    gravityLabel->setScaleY(0.08);
    gravityLabel->setLocalZOrder(3);
    this->addChild(gravityLabel, 1);

    cocos2d::Label* gravityLabel2 = Label::createWithBMFont("bigFont-uhd.fnt", "avity"); // "Gravity" String (2)
    gravityLabel2->setPosition(Vec2(xPosFixed - 430, yPosFixed + 352));
    gravityLabel2->setScaleX(0.08);
    gravityLabel2->setScaleY(0.08);
    gravityLabel2->setLocalZOrder(3);
    this->addChild(gravityLabel2, 1);

    cocos2d::Label* radiusLabel = Label::createWithBMFont("bigFont-uhd.fnt", "Radius"); // "Radius" String
    radiusLabel->setPosition(Vec2(xPosFixed - 460, yPosFixed + 287));
    radiusLabel->setScaleX(0.08);
    radiusLabel->setScaleY(0.08);
    radiusLabel->setLocalZOrder(3);
    this->addChild(radiusLabel, 1);

    cocos2d::Label* freeLabel = Label::createWithBMFont("bigFont-uhd.fnt", "Free"); // "Free" String
    freeLabel->setPosition(Vec2(xPosFixed - 477, yPosFixed + 352));
    freeLabel->setScaleX(0.08);
    freeLabel->setScaleY(0.08);
    freeLabel->setLocalZOrder(3);
    this->addChild(freeLabel, 1);

    cocos2d::Label* relativeLabel = Label::createWithBMFont("bigFont-uhd.fnt", "Relative"); // "Relative" String
    relativeLabel->setPosition(Vec2(xPosFixed - 442, yPosFixed + 287));
    relativeLabel->setScaleX(0.08);
    relativeLabel->setScaleY(0.08);
    relativeLabel->setLocalZOrder(3);
    this->addChild(relativeLabel, 1);

    cocos2d::Label* groupedLabel = Label::createWithBMFont("bigFont-uhd.fnt", "Grouped"); // "Grouped" String
    groupedLabel->setPosition(Vec2(xPosFixed - 445, yPosFixed + 222));
    groupedLabel->setScaleX(0.08);
    groupedLabel->setScaleY(0.08);
    groupedLabel->setLocalZOrder(3);
    this->addChild(groupedLabel, 1);

    cocos2d::Label* titleLabel = Label::createWithBMFont("goldFont-uhd.fnt", "30"); // "Cre" Popup Title (1)
    titleLabel->setPosition(Vec2(xPosFixed - 209.6, yPosFixed + 370));
    titleLabel->setScaleX(0.125);
    titleLabel->setScaleY(0.125);
    titleLabel->setLocalZOrder(3);
    titleLabel->setString("Cre");
    this->addChild(titleLabel, 1);

    cocos2d::Label* titleLabel1 = Label::createWithBMFont("goldFont-uhd.fnt", "30"); // "ate Particle Effect" Popup Title (2)
    titleLabel1->setPosition(Vec2(xPosFixed + 34, yPosFixed + 370));
    titleLabel1->setScaleX(0.125);
    titleLabel1->setScaleY(0.125);
    titleLabel1->setLocalZOrder(3);
    titleLabel1->setString("ate Particle Effect");
    this->addChild(titleLabel1, 1);


    tabTextures.push_back(Node::create());
    tabTextures.push_back(Node::create());
    selectTextureBox->setPosition(Vec2(xPosFixed + (-134) + 1, yPosFixed + (217) - 1)); // Select Box for "Textures".
    selectTextureBox->setScaleX(0.15);
    selectTextureBox->setScaleY(0.15);
    tabTextures[0]->addChild(selectTextureBox, 25); //Adding the select box to tabTextures[0] node.


    //Upper buttons, "Motion", "Visual", "Extra", "Texture".
    short int xDifferenceUpperButtons = -204;
    for (unsigned short int i = 0; i < 4; i++) {

        // "Motion" Text
        buttonLabelArray.push_back(Label::createWithBMFont("goldFont-uhd.fnt", "0.5"));

        // Buttons
        upperButtonsArray.push_back(ui::Button::create("greyButton.png", "greyButton.png"));

        // Node that contains text and the button
        upperButtons.push_back(Sprite::create());

        //Position
        upperButtons[i]->setPosition(Vec2(xPosFixed + (xDifferenceUpperButtons), yPosFixed + 310));

        // Add all stuff to uperButtons Node
        upperButtons[i]->addChild(buttonLabelArray[i], 35);
        upperButtons[i]->addChild(upperButtonsArray[i], 25);


        // Rest of the stuff
        upperButtonsArray[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upperButtonsFunction, this));
        buttonLabelArray[i]->setPosition(Vec2(-2, 4.5));
        buttonLabelArray[i]->setScaleX(0.07);
        buttonLabelArray[i]->setScaleY(0.07);
        upperButtonsArray[i]->setScaleX(0.25);
        upperButtonsArray[i]->setScaleY(0.25);
        this->addChild(upperButtons[i]);
        xDifferenceUpperButtons += 136;

    }

    buttonLabelArray[2]->setScaleX(0.075);
    buttonLabelArray[2]->setScaleY(0.075);
    buttonLabelArray[3]->setScaleX(0.060);
    buttonLabelArray[3]->setScaleY(0.060);
    upperButtonsArray[0]->loadTextures("greenButton.png", "greenButton.png");
    buttonLabelArray[0]->setString("Motion");
    buttonLabelArray[1]->setString("Visual");
    buttonLabelArray[2]->setString("Extra");
    buttonLabelArray[3]->setString("Texture");



    //Particle properties arrays "Motion/Gravity".
    for (unsigned short int i = 0; i < 17; i++) {

        // Sliders array (First tab *GRAVITY*)
        sliderArray.push_back(ui::Slider::create());


        // Labels for first tab "Motion"
        labelArray.push_back(Label::createWithBMFont("bigFont-uhd.fnt", "0"));


        // Background for labels in first tab "Motion"
        backgroundLabel.push_back(Sprite::create("square02_small-uhd.png"));
    }
    labelArray[3]->setString("30");
    labelArray[4]->setString("-90");
    labelArray[5]->setString("29");
    labelArray[6]->setString("11");
    labelArray[11]->setString("90");
    sliderArray[4]->setMaxPercent(360);
    sliderArray[5]->setMaxPercent(400);
    sliderArray[7]->setMaxPercent(1200);
    sliderArray[8]->setMaxPercent(2000);
    sliderArray[9]->setMaxPercent(2000);
    sliderArray[10]->setMaxPercent(200);
    sliderArray[11]->setMaxPercent(180);
    sliderArray[12]->setMaxPercent(1000);
    sliderArray[14]->setMaxPercent(1200);
    sliderArray[15]->setMaxPercent(1000);
    sliderArray[16]->setMaxPercent(1000);


    for (unsigned short int i = 0; i < 6; i++) {

        // Sliders array (Second tab *RADIUS*)
        sliderArray.push_back(ui::Slider::create());

        // Labels for second tab "Motion"
        labelArray.push_back(Label::createWithBMFont("bigFont-uhd.fnt", "0"));


        // Background for labels in first tab "Motion"
        backgroundLabel.push_back(Sprite::create("square02_small-uhd.png"));
    }

    //Particle properties arrays "Visual".
    for (unsigned short int i = 0; i < 24; i++) {

        // Sliders for second tab "Visual"
        sliderArrayVisual.push_back(ui::Slider::create());


        // Labels for second tab "Visual"
        labelArrayVisual.push_back(Label::createWithBMFont("bigFont-uhd.fnt", "0"));

        // Background for labels in second tab "Visual"
        backgroundALabel.push_back(Sprite::create("square02_small-uhd.png"));
    }
    sliderArrayVisual[0]->setMaxPercent(50);
    sliderArrayVisual[1]->setMaxPercent(50);
    sliderArrayVisual[2]->setMaxPercent(360);
    sliderArrayVisual[3]->setMaxPercent(360);
    sliderArrayVisual[14]->setMaxPercent(360);
    sliderArrayVisual[15]->setMaxPercent(360);
    labelArrayVisual[0]->setString("2");
    labelArrayVisual[1]->setString("1");
    for (int i = 0; i < 8; i++) {
        labelArrayVisual[i + 4]->setString("1.00");
        labelArrayVisual[i + 16]->setString("0.00");
    }
    labelArrayVisual[12]->setString("1");
    labelArrayVisual[13]->setString("1");
    short int i_Ydifference2 = 243; // The Y difference between each slider *second tab*
    short int i_YdifferenceText2 = 12;  // The Y difference between each label/bg box *second tab*

    i_Ydifference = 232; // The Y difference between each slider
    short int i_YdifferenceText = 3;  // The Y difference between each label/bg box

    //Adds 17 Sliders, 17 Labels, 17 Boxes form arrays. Each has different x and y pos.
    for (unsigned short int i = 0; i < 17; i++) {


        sliderArray[i]->loadBarTexture("slidergroove-uhd.png");
        sliderArray[i]->loadSlidBallTextureNormal("sliderthumb-uhd.png");
        sliderArray[i]->loadSlidBallTexturePressed("sliderthumbsel-uhd.png");
        sliderArray[i]->setScaleX(0.1225);
        sliderArray[i]->setScaleY(0.1225);
        sliderArray[i]->setLocalZOrder(24);
        labelArray[i]->setScaleX(0.0889);
        labelArray[i]->setScaleY(0.0889);
        labelArray[i]->setLocalZOrder(+99);
        backgroundLabel[i]->setScaleX(0.12);
        backgroundLabel[i]->setScaleY(0.09);
        backgroundLabel[i]->setOpacity(100);
        backgroundLabel[i]->setLocalZOrder(1);
        if (i < 10) {// left Sliders/Labels/BackroundBoxes
            labelArray[i]->setPosition(Vec2((xPosFixed - 83), (yPosFixed + 232.6) + i_YdifferenceText));
            sliderArray[i]->setPosition(Vec2(xPosFixed + 110, yPosFixed + i_Ydifference));
            backgroundLabel[i]->setPosition(Vec2((xPosFixed - 83) + 1, (yPosFixed + 232.6) + i_YdifferenceText - 1));
        }
        else if (i == 10) {// "LifeVar" Sliders/Labels/BackroundBoxes
            i_Ydifference = 102;
            i_YdifferenceText = -130;
            labelArray[i]->setPosition(Vec2((xPosFixed + 307), (yPosFixed + 232.6) + i_YdifferenceText));
            sliderArray[i]->setPosition(Vec2(xPosFixed + 500, yPosFixed + i_Ydifference));
            backgroundLabel[i]->setPosition(Vec2((xPosFixed + 307) + 2, (yPosFixed + 232.6) + i_YdifferenceText));
        }
        else {// Bottom right Sliders/Labels/BackroundBoxes
            if (i == 11) {// do only once
                i_Ydifference = -28;
                i_YdifferenceText = -260;
            }
            labelArray[i]->setPosition(Vec2((xPosFixed + 307), (yPosFixed + 232.6) + i_YdifferenceText));
            sliderArray[i]->setPosition(Vec2(xPosFixed + 500, yPosFixed + i_Ydifference));
            backgroundLabel[i]->setPosition(Vec2((xPosFixed + 307) + 2, (yPosFixed + 232.6) + i_YdifferenceText));
        }
        sliderArray[i]->addEventListener(CC_CALLBACK_2(HelloWorld::sliderEvent, this));
        this->addChild(backgroundLabel[i], 1);
        this->addChild(sliderArray[i]);
        this->addChild(labelArray[i], 1);
        backgroundLabel[i]->retain();
        sliderArray[i]->retain();
        labelArray[i]->retain();

        i_Ydifference -= 65; // Y Difference between each slider
        i_YdifferenceText -= 65; // Y Difference between each Label
    }

    i_Ydifference = -93;
    i_YdifferenceText = -322;
    //Adds 6 Sliders, 6 Labels, 6 Boxes form arrays. Each has different x and y pos.
    for (unsigned short int i = 17; i < 23; i++) {


        sliderArray[i]->loadBarTexture("slidergroove-uhd.png");
        sliderArray[i]->loadSlidBallTextureNormal("sliderthumb-uhd.png");
        sliderArray[i]->loadSlidBallTexturePressed("sliderthumbsel-uhd.png");
        sliderArray[i]->setScaleX(0.1225);
        sliderArray[i]->setScaleY(0.1225);
        sliderArray[i]->setLocalZOrder(24);
        labelArray[i]->setScaleX(0.0889);
        labelArray[i]->setScaleY(0.0889);
        labelArray[i]->setLocalZOrder(+99);
        backgroundLabel[i]->setScaleX(0.12);
        backgroundLabel[i]->setScaleY(0.09);
        backgroundLabel[i]->setOpacity(100);
        backgroundLabel[i]->setLocalZOrder(1);
        if (i < 20) {// left Sliders/Labels/BackroundBoxes
            labelArray[i]->setPosition(Vec2((xPosFixed - 83), (yPosFixed + 232.6) + i_YdifferenceText));
            sliderArray[i]->setPosition(Vec2(xPosFixed + 110, yPosFixed + i_Ydifference));
            backgroundLabel[i]->setPosition(Vec2((xPosFixed - 83) + 1, (yPosFixed + 232.6) + i_YdifferenceText - 1));
        }
        else {
            if (i == 20) { // Do only once
                i_Ydifference = (-93);
                i_YdifferenceText = (-322);
            }
            // right Sliders/Labels/BackroundBoxes
            labelArray[i]->setPosition(Vec2((xPosFixed + 307), (yPosFixed + 232.6) + i_YdifferenceText));
            sliderArray[i]->setPosition(Vec2(xPosFixed + 500, yPosFixed + i_Ydifference));
            backgroundLabel[i]->setPosition(Vec2((xPosFixed + 307) + 2, (yPosFixed + 232.6) + i_YdifferenceText));
        }
        sliderArray[i]->addEventListener(CC_CALLBACK_2(HelloWorld::sliderEvent, this));
        this->addChild(backgroundLabel[i], 1);
        this->addChild(sliderArray[i]);
        this->addChild(labelArray[i], 1);
        backgroundLabel[i]->retain();
        sliderArray[i]->retain();
        labelArray[i]->retain();

        i_Ydifference -= 65; // Y Difference between each slider
        i_YdifferenceText -= 65; // Y Difference between each Label
    }



    //Adding Sliders/Backgrounds/Labels for the second tab "Visual".
    for (unsigned short int i = 0; i < 24; i++) {

        sliderArrayVisual[i]->loadBarTexture("slidergroove-uhd.png");
        sliderArrayVisual[i]->loadSlidBallTextureNormal("sliderthumb-uhd.png");
        sliderArrayVisual[i]->loadSlidBallTexturePressed("sliderthumbsel-uhd.png");
        sliderArrayVisual[i]->setScaleX(0.1225);
        sliderArrayVisual[i]->setScaleY(0.1225);
        sliderArrayVisual[i]->setLocalZOrder(12);
        labelArrayVisual[i]->setScaleX(0.0889);
        labelArrayVisual[i]->setScaleY(0.0889);
        labelArrayVisual[i]->setLocalZOrder(14);
        backgroundALabel[i]->setScaleX(0.12);
        backgroundALabel[i]->setScaleY(0.09);
        backgroundALabel[i]->setOpacity(100);
        backgroundALabel[i]->setLocalZOrder(1);
        if (i < 12) {// Left Sliders/Labels/BackroundBoxes
            labelArrayVisual[i]->setPosition(Vec2((xPosFixed - 83), (yPosFixed + 232.6) + i_YdifferenceText2));
            sliderArrayVisual[i]->setPosition(Vec2(xPosFixed + 110, yPosFixed + i_Ydifference2));
            backgroundALabel[i]->setPosition(Vec2((xPosFixed - 83) + 1, (yPosFixed + 232.6) + i_YdifferenceText2 - 1));
        }
        else {// Right Sliders/Labels/BackroundBoxes
            if (i == 12) {// do only once
                i_Ydifference2 = 243;
                i_YdifferenceText2 = 12;
            }
            labelArrayVisual[i]->setPosition(Vec2((xPosFixed + 307), (yPosFixed + 232.6) + i_YdifferenceText2));
            sliderArrayVisual[i]->setPosition(Vec2(xPosFixed + 500, yPosFixed + i_Ydifference2));
            backgroundALabel[i]->setPosition(Vec2((xPosFixed + 307) + 2, (yPosFixed + 232.6) + i_YdifferenceText2));
        }
        sliderArrayVisual[i]->addEventListener(CC_CALLBACK_2(HelloWorld::sliderEvent, this));
        sliderArrayVisual[i]->retain();
        labelArrayVisual[i]->retain();
        i_Ydifference2 -= 54; // Y Difference between each slider
        i_YdifferenceText2 -= 54; // Y Difference between each Label
    }
    infoCheckBoxesString->setPosition(Vec2(0, 0 + 15));
    infoCheckboxesPopupNode->addChild(infoCheckBoxesString, 31);

    short int yDifferenceTextures = 55;
    //Adding 5 Checkboxes in "Extra".
    for (unsigned short int i = 0; i < 5; i++)
    {
        checkBoxesLabels.push_back(Label::createWithBMFont("bigFont-uhd.fnt", "30"));
        checkBoxesLabels[i]->setScaleX(0.065);
        checkBoxesLabels[i]->setScaleY(0.065);

        checkBoxes.push_back(ui::Button::create("GJ_checkOff_001.png"));
        checkBoxesInfo.push_back(ui::Button::create("GJ_infoIcon_001.png", "GJ_infoIcon_001.png"));
        checkBoxes[i]->setPosition(Vec2(xPosFixed - 162.5, yPosFixed + yDifferenceTextures)); //CheckBoxes
        checkBoxesInfo[i]->setPosition(Vec2((xPosFixed - 162.5) - 40, (yPosFixed + yDifferenceTextures) + 40)); //CheckBoxes info
        checkBoxes[i]->setScaleX(0.135);
        checkBoxes[i]->setScaleY(0.135);
        checkBoxesInfo[i]->setScaleX(0.1);
        checkBoxesInfo[i]->setScaleY(0.1);
        checkBoxes[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::checkBox, this));
        checkBoxesInfo[i]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
            if (!infoCheckboxesPopupNode->getParent() && !infoPopupNode->getParent()) {
                infoCheckBoxesString->setScaleX(0.185);
                infoCheckBoxesString->setScaleY(0.185);
                for (unsigned short int i = 0; i < 106; i++) {
                    if (infoCheckBoxesString->getLetter(i) != nullptr)
                    {
                        infoCheckBoxesString->getLetter(i)->setColor(Color3B(255, 255, 255));
                    }
                }

                if (restOfButtons[25]->getParent()) {
                    infoCheckboxesPopupNode->removeChild(restOfButtons[25], 55);
                }
                infoCheckboxesTitle->setString("Info");
                infoCheckboxesOkButton->setPosition(Vec2(0, -115));
                for (unsigned short int l = 0; l < 5; l++) {
                    if (checkBoxesInfo[l]->isHighlighted()) {
                        highlightedInfoMessageCheckbox = l;
                    }
                }
                switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->stopAllActions();
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.1 * 1.25)));
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->stopAllActions();
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.1)));
                    infoCheckboxesPopupNode->setScale(0.0);
                    blackBackgroundInfoCheckboxesPopup->setOpacity(0.0);
                    switch (highlightedInfoMessageCheckbox)
                    {
                    case 0:
                        infoCheckBoxesString->setString("Makes the particle blending."); break;
                    case 1:
                        infoCheckBoxesString->setString("Changes the Start Size of the particle to be similar to\nthe End Size."); break;
                    case 2:
                        infoCheckBoxesString->setString("Changes the Start Spin of the particle to be similar to\nthe the End Spin."); break;
                    case 3:
                        infoCheckBoxesString->setString("Changes the Start Radius of the particle to be similar to \nthe End Radius.\nNote: Only works in Radius mode!"); break;
                    case 4:
                        infoCheckBoxesString->setString("Rotates every particle to the angle of where it's going.\nNote: Only works in Gravity mode!"); break;

                    default:
                        break;
                    }
                    if (!infoCheckboxesPopupNode->getParent()) {
                        this->addChild(blackBackgroundInfoCheckboxesPopup);
                        this->addChild(infoCheckboxesPopupNode);
                        infoCheckboxesPopupNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.6f));
                        blackBackgroundInfoCheckboxesPopup->runAction(EaseInOut::create(FadeTo::create(0.10, 125), 2));
                    }
                    break;
                case ui::Widget::TouchEventType::CANCELED:
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->stopAllActions();
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.1)));
                    break;
                default:
                    break;
                }
            }
            });
        yDifferenceTextures -= 92;

        tabThree->addChild(checkBoxes[i], 5);
        tabThree->addChild(checkBoxesLabels[i], 5);
        tabThree->addChild(checkBoxesInfo[i], 5);

    }
    
        
    checkBoxes[0]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
    tabThree->retain();

    //Checkboxes in Extra, properties:
    checkBoxesLabels[0]->setPosition(Vec2(xPosFixed - 53, yPosFixed + 55)); // Additive CheckBox Label
    checkBoxesLabels[1]->setPosition(Vec2(xPosFixed, yPosFixed + 55 - (92))); // Start Size = End CheckBox Label
    checkBoxesLabels[2]->setPosition(Vec2(xPosFixed, yPosFixed + 55 - (92 * 2))); // Start Spin = End CheckBox Label
    checkBoxesLabels[3]->setPosition(Vec2(xPosFixed + 21, yPosFixed + 55 - (92 * 3))); // Start Radius = End CheckBox Label
    checkBoxesLabels[4]->setPosition(Vec2(xPosFixed + 34, yPosFixed + 55 - (92 * 4))); // Start rotation is Dir CheckBox Label

    checkBoxesLabels[0]->setString("Additive");
    checkBoxesLabels[1]->setString("Start Size = End");
    checkBoxesLabels[2]->setString("Start Spin = End");
    checkBoxesLabels[3]->setString("Start Radius = End");
    checkBoxesLabels[4]->setString("Start rotation is Dir");


    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particlesSpriteSheet.plist");
    yDifferenceTextures = 217;
    short int xDifferenceTextures = -134;
    //Adding all useable textures for the particle.
    for (unsigned short int i = 0; i < 64; i++)
    {

        if (i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || i == 48 || i == 56) {
            yDifferenceTextures -= 79;
            xDifferenceTextures = -134;
        }

        particleSprite.push_back(ui::Button::create(
            "particle_" + std::to_string(i) + ".png",
            "particle_" + std::to_string(i) + ".png",
            "particle_" + std::to_string(i) + ".png"/*,
            ui::Widget::TextureResType::PLIST*/));

        particleSprite[i]->setPosition(Vec2(xPosFixed + (xDifferenceTextures), yPosFixed + (yDifferenceTextures)));
        particleSprite[i]->setColor(Color3B(155, 155, 155));

        if (i < 52) {
            particleSprite[i]->setScaleX(0.095);
            particleSprite[i]->setScaleY(0.095);
        }
        else {
            particleSprite[i]->setScaleX(0.14);
            particleSprite[i]->setScaleY(0.14);
        }
        particleSprite[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::textures, this));
        particleSprite[i]->retain();
        tabTextures[0]->addChild(particleSprite[i], 24);
        xDifferenceTextures += 78;
    }
    // [Sub] Button to unlock textures
    restOfButtons[25]->retain();
    restOfButtons[25]->setPosition(Vec2(105,-115));
    restOfButtons[25]->setScaleX(0.234);
    restOfButtons[25]->setScaleY(0.234);
    restOfButtons[25]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[25]->stopAllActions();
            restOfButtons[25]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.234 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[25]->stopAllActions();
            restOfButtons[25]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.234)));
            Application::getInstance()->openURL("https://www.youtube.com/channel/UC33L-Y8asG7gju6f-4-Cl2g?sub_confirmation=1");
            
            tabTextures[0]->removeChild(restOfButtons[24]);

            if (infoCheckboxesPopupNode->getParent()) {
                this->removeChild(blackBackgroundInfoCheckboxesPopup);
                this->removeChild(infoCheckboxesPopupNode);
            }

            for (unsigned short int i = 0; i < 64; i++) particleSprite[i]->setColor(Color3B(255, 255, 255)); 

            restOfButtons[23]->setColor(Color3B(255, 255, 255));
            particleEditio = true;
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[25]->stopAllActions();
            restOfButtons[25]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.234)));
            break;
        }
        });

    //Lock
    restOfButtons[24]->setPosition(Vec2(xPosFixed +175, yPosFixed -65));
    restOfButtons[24]->setScaleX(0.345);
    restOfButtons[24]->setScaleY(0.345);
    restOfButtons[24]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[24]->stopAllActions();
            restOfButtons[24]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.345 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[24]->stopAllActions();
            restOfButtons[24]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.345)));
            if (!restOfButtons[25]->getParent()) {
                infoCheckboxesPopupNode->addChild(restOfButtons[25], 55);
            }
            infoCheckboxesTitle->setString("YouTube");
            infoCheckboxesOkButton->setPosition(Vec2(-95, -115));
            infoCheckBoxesString->setScaleX(0.2);
            infoCheckBoxesString->setScaleY(0.2);
            if (!infoCheckboxesPopupNode->getParent() && !infoPopupNode->getParent()) {
                std::string infoSubColored = infoCheckBoxesString->getString();
                switch (type) {
                case ui::Widget::TouchEventType::BEGAN:
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->stopAllActions();
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.1 * 1.25)));
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->stopAllActions();
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.1)));
                    infoCheckboxesPopupNode->setScale(0.0);
                    blackBackgroundInfoCheckboxesPopup->setOpacity(0.0);
                    infoCheckBoxesString->setString("Subscribe to XcreatorGoal on YouTube\nto unlock Textures!");
                    
                    if (!infoCheckboxesPopupNode->getParent()) {
                        this->addChild(blackBackgroundInfoCheckboxesPopup);
                        this->addChild(infoCheckboxesPopupNode);
                        infoCheckboxesPopupNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.6f));
                        blackBackgroundInfoCheckboxesPopup->runAction(EaseInOut::create(FadeTo::create(0.10, 125), 2));
                    }

                    for (unsigned short int i = 12; i < 25; i++) {
                        if (infoCheckBoxesString->getLetter(i) != nullptr)
                        {
                            infoCheckBoxesString->getLetter(i)->setColor(Color3B(0, 255, 0));
                        }
                    }

                    for (unsigned short int i = 28; i < 36; i++) {
                        if (infoCheckBoxesString->getLetter(i) != nullptr)
                        {
                            infoCheckBoxesString->getLetter(i)->setColor(Color3B(250, 2, 2));
                        }
                    }

                    for (unsigned short int i = 47; i < 57; i++) {
                        if (infoCheckBoxesString->getLetter(i) != nullptr)
                        {
                            infoCheckBoxesString->getLetter(i)->setColor(Color3B(250, 255, 2));
                        }
                    }

                    break;
                case ui::Widget::TouchEventType::CANCELED:
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->stopAllActions();
                    checkBoxesInfo[highlightedInfoMessageCheckbox]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.1)));
                    break;
                default:
                    break;
                }
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[24]->stopAllActions();
            restOfButtons[24]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.345)));
            break;
        default:
            break;
        }
        });
    if (!particleEditio) {
        tabTextures[0]->addChild(restOfButtons[24], 116);

    }
    tabTextures[0]->retain();

    yDifferenceTextures = 217;
    xDifferenceTextures = -134;
    for (unsigned short int i = 64; i < changeWhenDone; i++)
    {
    
        if (i == (8 + 64) || i == (16 + 64) || i == (24 + 64) || i == (32 + 64) || i == (40 + 64) || i == (48 + 64) || i == (56 + 64)) {
            yDifferenceTextures -= 79;
            xDifferenceTextures = -134;
        }
        particleSprite.push_back(ui::Button::create(
            "particle_" + std::to_string(i) + ".png",
            "particle_" + std::to_string(i) + ".png",
            "particle_" + std::to_string(i) + ".png"/*,
            ui::Widget::TextureResType::PLIST*/));
    
    
        particleSprite[i]->setPosition(Vec2(xPosFixed + (xDifferenceTextures), yPosFixed + (yDifferenceTextures)));

        particleSprite[i]->setScaleX(0.095);
        particleSprite[i]->setScaleY(0.095);
        particleSprite[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::textures, this));
        particleSprite[i]->retain();
        
        xDifferenceTextures += 78;
    }
    tabTextures[1]->retain();
    selectTextureBox->retain();
    this->addChild(tabTextures[1]);
    
    //Textures Arrow
    restOfButtons[23]->setPosition(Vec2(xPosFixed + 500, yPosFixed - 40));
    restOfButtons[23]->setFlippedX(true);
    restOfButtons[23]->setScaleY(0.165);
    restOfButtons[23]->setScaleX(0.165);
    restOfButtons[23]->setColor(Color3B(155, 155, 155));
    restOfButtons[23]->setTag(0);
    restOfButtons[23]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (!infoPopupNode->getParent()) {
            switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                restOfButtons[23]->stopAllActions();
                restOfButtons[23]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.165 * 1.25)));
                break;
            case ui::Widget::TouchEventType::ENDED:
                restOfButtons[23]->stopAllActions();
                restOfButtons[23]->runAction(EaseBounceOut::create(ScaleTo::create(0, 0.165)));
                if (restOfButtons[23]->getTag() == 0) {

                    restOfButtons[23]->setTag(1);
                    for (unsigned short int i = 0; i < 64; i++) { tabTextures[0]->removeChild(particleSprite[i]); }
                    for (unsigned short int i = 64; i < changeWhenDone; i++) { tabTextures[1]->addChild(particleSprite[i]); }
                    restOfButtons[23]->setFlippedX(false);
                    restOfButtons[23]->runAction(MoveBy::create(0, Vec2(-725, 0)));


                    if (selectTextureBox->getTag() < 64) {
                        tabTextures[0]->removeChild(selectTextureBox);
                    }
                    else {
                        tabTextures[0]->addChild(selectTextureBox);
                    }

                }
                else if (restOfButtons[23]->getTag() == 1) {

                    restOfButtons[23]->setTag(0);
                    for (unsigned short int i = 0; i < 64; i++) { tabTextures[0]->addChild(particleSprite[i], 35); }
                    for (unsigned short int i = 64; i < changeWhenDone; i++) { tabTextures[1]->removeChild(particleSprite[i]); }
                    restOfButtons[23]->setFlippedX(true);
                    restOfButtons[23]->runAction(MoveBy::create(0, Vec2(+725, 0)));

                    if (selectTextureBox->getTag() < 64) {
                        tabTextures[0]->addChild(selectTextureBox);
                    }
                    else {
                        tabTextures[0]->removeChild(selectTextureBox);
                    }
                }
                break;
            case ui::Widget::TouchEventType::CANCELED:
                restOfButtons[23]->stopAllActions();
                restOfButtons[23]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.165)));
                break;
            default:
                break;
            }
        }
        });



    // Percentage of each slider in array second tab 
    float percent[17] = { 15, 0, 50, 15, (360 / 4), 29 , 11, 600, 1000, 1000 ,30, 90, 0, 0, 600, 0, 0 };
    for (unsigned short int i = 0; i < 17; i++) {
        sliderArray[i]->setPercent(percent[i]);
    }


    //Array for the second tab ("Visual") sliders.
    float percent2[24] = { 2,1,0,0,100,100,100,100,100,100,100,100,1,1,0,0,0,0,0,0,0,0,0,0 };
    for (unsigned short int i = 0; i < 24; i++) {
        sliderArrayVisual[i]->setPercent(percent2[i]);
        //Add all second tabs nodes to "tabTwo".
        this->removeChild(backgroundALabel[i], 1);
        this->removeChild(sliderArrayVisual[i]);
        this->removeChild(labelArrayVisual[i], 1);
        tabTwo->addChild(backgroundALabel[i]);
        tabTwo->addChild(sliderArrayVisual[i]);
        tabTwo->addChild(labelArrayVisual[i]);
    }


    //Array for the Radius tab ("Motion") sliders.
    float percentRadius[6] = { 0, 0, 360, 0, 0, 0 };
    for (unsigned short int i = 17; i < 23; i++) {
        percentRadius[i] = sliderArray[i]->getPercent();
        //Add sliders that are available for Radius only 
        this->removeChild(backgroundLabel[i], 1);
        this->removeChild(sliderArray[i]);
        this->removeChild(labelArray[i], 1);
        tabOneRadius->addChild(backgroundLabel[i], 1);
        tabOneRadius->addChild(sliderArray[i]);
        tabOneRadius->addChild(labelArray[i], 1);
    }
    sliderArray[19]->setMaxPercent(720);

    sliderArray[19]->setPercent(360);

    //std::string path = FileUtils::getInstance()->fullPathForFilename("Particle_p.plist");
    //
    //ValueMap data;
    //data = FileUtils::getInstance()->getValueMapFromFile(path);
    //auto arrLevels = data.at("activate").asValueVector();
    //
    //ValueMap sData = (arrLevels[0]).asValueMap();
    //
    //bool x = sData["activated"].asBool();
    //particleEditio = x;

    //Add sliders that are available for Gravity only 
    for (unsigned short int i = 5; i < 10; i++) {
        this->removeChild(backgroundLabel[i], 1);
        this->removeChild(sliderArray[i]);
        this->removeChild(labelArray[i], 1);
        tabOneGravity->addChild(backgroundLabel[i], 1);
        tabOneGravity->addChild(sliderArray[i]);
        tabOneGravity->addChild(labelArray[i], 1);
    }
    for (unsigned short int i = 12; i < 17; i++) {
        this->removeChild(backgroundLabel[i], 1);
        this->removeChild(sliderArray[i]);
        this->removeChild(labelArray[i], 1);
        tabOneGravity->addChild(backgroundLabel[i], 1);
        tabOneGravity->addChild(sliderArray[i]);
        tabOneGravity->addChild(labelArray[i], 1);
    }


    //Add all things that are available for gravity and radius to tabOne
    for (unsigned short int i = 0; i < 5; i++) {
        this->removeChild(backgroundLabel[i], 1);
        this->removeChild(sliderArray[i]);
        this->removeChild(labelArray[i], 1);
        tabOne->addChild(backgroundLabel[i], 1);
        tabOne->addChild(sliderArray[i]);
        tabOne->addChild(labelArray[i], 1);
    }
    for (unsigned short int i = 10; i < 12; i++) {
        this->removeChild(backgroundLabel[i], 1);
        this->removeChild(sliderArray[i]);
        this->removeChild(labelArray[i], 1);
        tabOne->addChild(backgroundLabel[i], 1);
        tabOne->addChild(sliderArray[i]);
        tabOne->addChild(labelArray[i], 1);
    }

    this->removeChild(restOfButtons[8]);
    tabTwo->addChild(restOfButtons[8]);
    this->removeChild(restOfButtons[9]);
    tabTwo->addChild(restOfButtons[9]);
    this->removeChild(restOfButtons[10]);
    tabTwo->addChild(restOfButtons[10]);
    this->removeChild(restOfButtons[11]);
    tabTwo->addChild(restOfButtons[11]);
    this->removeChild(restOfButtons[12]);
    tabTwo->addChild(restOfButtons[12]);
    this->removeChild(restOfButtons[13]);
    tabTwo->addChild(restOfButtons[13]);



    this->removeChild(restOfButtons[0]);
    this->removeChild(restOfButtons[21]);
    this->removeChild(restOfButtons[22]);
    this->removeChild(restOfButtons[23]);
    this->removeChild(restOfButtons[3]);
    this->removeChild(restOfButtons[4]);
    this->removeChild(restOfButtons[5]);
    this->removeChild(motionFakeText, 1);
    this->removeChild(radiusFakeText, 1);
    this->removeChild(gravityFakeText, 1);
    this->removeChild(restOfButtons[1]);
    this->removeChild(restOfButtons[2]);
    this->removeChild(gravityLabel);
    this->removeChild(gravityLabel2);
    this->removeChild(radiusLabel);
    this->removeChild(restOfButtons[16]);
    this->removeChild(freeLabel);
    this->removeChild(relativeLabel);
    this->removeChild(groupedLabel);

    tabThree->addChild(freeLabel, 5);
    tabThree->addChild(relativeLabel, 5);
    tabThree->addChild(groupedLabel, 5);
    tabThree->addChild(restOfButtons[3], 5);
    tabThree->addChild(restOfButtons[4], 5);
    tabThree->addChild(restOfButtons[5], 5);
    tabOne->addChild(restOfButtons[0]);
    tabOne->addChild(restOfButtons[21]);
    tabOne->addChild(restOfButtons[22]);
    tabOne->addChild(restOfButtons[26]);
    tabOne->addChild(restOfButtons[1]);
    tabOne->addChild(restOfButtons[2]);
    tabOne->addChild(gravityLabel);
    tabOne->addChild(gravityLabel2);
    tabOne->addChild(radiusLabel);
    tabOne->addChild(motionFakeText);
    tabOneRadius->addChild(radiusFakeText);
    tabOneGravity->addChild(gravityFakeText);

    popUpNode->removeChild(tabOneRadius);
    popUpNode->removeChild(tabOneGravity);
    popUpNode->addChild(restOfButtons[16]);

    popUpNode->addChild(tabOneGravity);
    popUpNode->addChild(tabOne);

    tabOneRadius->retain();
    tabOneGravity->retain();
    tabOne->retain();


    tabTwo->addChild(visualFakeText, 25);
    popUpNode->removeChild(tabTwo);
    tabTwo->retain();

    tabTextures[0]->removeChild(restOfButtons[23]);
    tabTextures[0]->addChild(restOfButtons[23]);

    particleSystem->setStartSize(3);
    //Adding the listener for Gravity modifier line.
    listenerForGravityLine->setSwallowTouches(false);
    listenerForGravityLine->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMovedGravity, this);
    listenerForGravityLine->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBeganGravity, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerForGravityLine, this);

    //Adding the listener for Speed Angle modifier line.
    listenerForSpeedAngleLine->setSwallowTouches(false);
    listenerForSpeedAngleLine->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMovedSpeedAngle, this);
    listenerForSpeedAngleLine->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBeganSpeedAngle, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerForSpeedAngleLine, this);

    //Adding the listener for StartRadius modifier line.
    listenerForStartRadiusLine->setSwallowTouches(false);
    listenerForStartRadiusLine->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMovedStartRadius, this);
    listenerForStartRadiusLine->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBeganStartRadius, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerForStartRadiusLine, this);

    //Adding the listener for EndRadius modifier line.
    listenerForEndRadiusLine->setSwallowTouches(false);
    listenerForEndRadiusLine->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMovedEndRadius, this);
    listenerForEndRadiusLine->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBeganEndRadius, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerForEndRadiusLine, this);

    //Adding the listener for PosVar modifier line.
    listenerForPosVarLine->setSwallowTouches(false);
    listenerForPosVarLine->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMovedPosVar, this);
    listenerForPosVarLine->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBeganPosVar, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerForPosVarLine, this);


    //Adding the 3 buttons on top of the particle to easily modify particle properties.
    xDifferenceTextures = -427;
    for (unsigned short int i = 0; i < 3; i++) {

        easyModifier.push_back(ui::Button::create("easyModifierGrey.png"));
        easyModifier[i]->setPosition(Vec2(xPosFixed + xDifferenceTextures, yPosFixed + 150));
        easyModifier[i]->setScaleX(0.26);
        easyModifier[i]->setScaleY(0.26);
        easyModifier[i]->addTouchEventListener(CC_CALLBACK_2(HelloWorld::easyModify, this));
        easyModifierLabels.push_back(Label::createWithBMFont("goldFont-uhd.fnt", "0.5"));
        easyModifier[i]->addChild(easyModifierLabels[i], 7);
        easyModifierLabels[i]->setPosition(Vec2(110, 100));
        easyModifierLabels[i]->setScaleX(0.408);
        easyModifierLabels[i]->setScaleY(0.408);
        popUpNode->addChild(easyModifier[i]);
        xDifferenceTextures -= 66.8;
    }
    easyModifier.push_back(ui::Button::create("easyModifierBrightBlue.png"));
    easyModifier[3]->setPosition(Vec2(xPosFixed - 360.2, yPosFixed + 150));
    easyModifier[3]->setScaleX(0.26);
    easyModifier[3]->setScaleY(0.26);
    easyModifierLabels.push_back(Label::createWithBMFont("goldFont-uhd.fnt", "c"));
    easyModifier[3]->addChild(easyModifierLabels[3], 7);
    easyModifierLabels[3]->setPosition(Vec2(110, 100));
    easyModifierLabels[3]->setScaleX(0.43);
    easyModifierLabels[3]->setScaleY(0.43);
    popUpNode->addChild(easyModifier[3]);

    easyModifierLabels[0]->setString("3");
    easyModifierLabels[1]->setString("2");
    easyModifierLabels[2]->setString("1");


    this->removeChild(restOfButtons[15]);
    this->removeChild(particle_popup_texture);
    popUpNode->removeChild(tabTwo);
    popUpNode->removeChild(tabThree);
    popUpNode->removeChild(tabOne);
    popUpNode->removeChild(tabTextures[0]);
    popUpNode->removeChild(tabTextures[1]);
    this->removeChild(titleLabel);
    popUpNode->removeChild(tabOneRadius);
    popUpNode->removeChild(tabOneGravity);
    this->removeChild(upperButtons[0]);
    this->removeChild(upperButtons[1]);
    this->removeChild(upperButtons[2]);
    this->removeChild(upperButtons[3]);
    this->removeChild(restOfButtons[6], 16);
    this->removeChild(titleLabel1);


    popUpNode->addChild(particle_popup_texture);
    popUpNode->addChild(titleLabel);
    popUpNode->addChild(upperButtons[0]);
    popUpNode->addChild(upperButtons[1]);
    popUpNode->addChild(upperButtons[2]);
    popUpNode->addChild(upperButtons[3]);
    popUpNode->addChild(restOfButtons[6], 16);
    //popUpNode->addChild(restOfButtons[15]);
    popUpNode->addChild(titleLabel1);

    this->removeChild(tabTextures[1]);
    popUpNode->addChild(tabTwo);
    popUpNode->addChild(tabThree);
    popUpNode->addChild(tabOne);
    popUpNode->addChild(tabTextures[0]);
    popUpNode->removeChild(tabTextures[1]);
    popUpNode->addChild(tabTextures[1]);
    popUpNode->addChild(tabOneRadius);
    popUpNode->addChild(tabOneGravity);

    popUpNode->removeChild(tabTwo);
    popUpNode->removeChild(tabThree);
    popUpNode->removeChild(tabTextures[0]);
    popUpNode->removeChild(tabOneRadius);



    cocos2d::Label* hella = Label::createWithBMFont("bigFont-uhd.fnt", "Made By XcreatorGoal", TextHAlignment::CENTER); // text String
    hella->setPosition(Vec2(xPosFixed - 555, yPosFixed + 110));
    hella->setScaleX(0.05);
    hella->setScaleY(0.05);
    hella->setLocalZOrder(8);
    hella->setAnchorPoint(Vec2(0, 0));
    hella->setOpacity(100);

    //fun stuff
//   for (unsigned short int i = 0; i < 65; i++)
//   {
//                                                                                                                            particleSprite[i]->runAction(Repeat::create(Sequence::create(
//                                                                                                                                TintTo::create(0.50, Color3B(255, 0, 0)),
//                                                                                                                              RotateBy::create(0.250, 90),
//                                                                                                                                TintTo::create(0.50, Color3B(255, 255, 0)),
//                                                                                                                              RotateBy::create(0.250, 90),
//                                                                                                                                TintTo::create(0.50, Color3B(0, 255, 0)),
//                                                                                                                              RotateBy::create(0.250, 90),
//                                                                                                                                TintTo::create(0.50, Color3B(0, 255, 255)),
//                                                                                                                              RotateBy::create(0.250, 90),
//                                                                                                                                TintTo::create(0.50, Color3B(0, 0, 255)),
//                                                                                                                                TintTo::create(0.50, Color3B(255, 0, 255)), NULL), 623));
//   }
    //popUpNode->addChild(hella);

    this->removeChild(popUpNode);
    this->addChild(popUpNode);
    popUpNode->retain();


    particleSystem->retain();
    clipper->retain();

    //Adding the listener move particle
    moveParticleListener->setSwallowTouches(true);
    moveParticleListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::moveParticle, this);
    moveParticleListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::beganParticle, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(moveParticleListener, this);

    checkBoxes[0]->setTag(1);
    checkBoxes[1]->setTag(0);
    checkBoxes[2]->setTag(0);
    checkBoxes[3]->setTag(0);
    checkBoxes[4]->setTag(0);

    restOfButtons[10]->setColor(Color3B(0,0,0));
    restOfButtons[11]->setColor(Color3B(0, 0, 0));

    //Draw circle once
    if (!drawCircleAngleReal) {
        removeChild(drawCircleAngleReal);
        drawCircleAngleReal = DrawNode::create();
        drawCircleAngleReal->drawCircle(Vec2(0,0),
            55,
            0,
            30,
            false,
            Color4F(1, 1, 0.65, 1));
        this->addChild(drawCircleAngleReal, 29);
        drawCircleAngleReal->setLineWidth(1.0f);
    }
    //
    this->removeChild(drawCircleAngleReal);
    drawCircleAngleReal->retain();
    drawCircleAngleReal->setPosition(particleSystem->getPosition());

    createAlignedObject(7, Vec2(0.1, 0.1), 100, 500, false, Vec2(particleSystem->getPosition()), test, restOfButtons, std::vector<Sprite*>, "particle_", true, Vec2(178,178));
    
    this->removeChild(test);
    this->addChild(test, 500);
    return true;
}
void HelloWorld::createAlignedObject(int howMany, Vec2 scale, float spacing, int layer, bool horizontal,
    Vec2 point, cocos2d::Node* mainNode, std::vector<ui::Button*> button, std::vector<Sprite*> sprite = { Sprite::create("U5ntitled.png") }, std::string spriteName,
    bool differentSprite, Vec2 textureSize) {

    for (int i = 0; i < howMany; i++) {
        if (differentSprite) sprite.push_back(Sprite::create(spriteName + std::to_string(i) + ".png"));

        else sprite.push_back(Sprite::create(spriteName));

        if (horizontal) {
            float spriteWidth = textureSize.x * sprite[0]->getScaleX();
            if (i == 0) {
                sprite[i]->setPosition(Vec2(point.x + (i * (spriteWidth + spacing)), point.y));
            }
            else {
                sprite[i]->setPosition(Vec2(point.x + (i * (spriteWidth + spacing) - (((sprite.size() - 1) * (spriteWidth + spacing) + (spriteWidth / 2)) / 2)), point.y));
            }
        }
        else {
            float spriteWidth = textureSize.y * sprite[0]->getScaleX();
            if (i == 0) {
                sprite[i]->setPosition(Vec2(point.x, point.y + (i * (spriteWidth + spacing))));
            }
            else {
                sprite[i]->setPosition(Vec2(point.x , point.y + (i * (spriteWidth + spacing) - (((sprite.size() - 1) * (spriteWidth + spacing) + (spriteWidth / 2)) / 2))));
            }
        }

        sprite[i]->setScaleX(scale.x);
        sprite[i]->setScaleY(scale.y);
        mainNode->addChild(sprite[i], layer);
    }
    if (horizontal) {
        mainNode->setPosition(Vec2(-(((sprite.size() - 1) * (textureSize.x * sprite[0]->getScaleX() + spacing)
            + (textureSize.x * sprite[0]->getScaleX() / 2)) / 4), 0));

    }
    else {
        mainNode->setPosition(Vec2(0, -(((sprite.size() - 1) * (textureSize.y * sprite[0]->getScaleX() + spacing)
            + (textureSize.y * sprite[0]->getScaleX() / 2)) / 4)));

    }

    //labelArray[0]->setString(std::to_string(sprite[0]->getContentSize().width));
    //mainNode->setPosition(Vec2(-(((sprite.size() - 1) * ((sprite[0]->getContentSize().width * sprite[0]->getScaleX()) + spacing) + ((sprite[0]->getContentSize().width * sprite[0]->getScaleX()) / 2)) / 4), 0));
}


unsigned short int switchButtons;
unsigned short int switchTypeButtons;
void HelloWorld::moveParticle(cocos2d::Touch* touch, cocos2d::Event* event) {

    if (moveParticleIsActive && !infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        if (popUpNode->getParent()) {

            //If he is touching the black area
            if (touch->getLocation().x > 173 &&
                touch->getLocation().x < 497 &&
                touch->getLocation().y > 55 &&
                touch->getLocation().y < 541) {

                particleSystem->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
                drawCircleAngleReal->setPosition(particleSystem->getPosition());
            }
        }
        else { particleSystem->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
        drawCircleAngleReal->setPosition(particleSystem->getPosition());
        }
    }
}
bool HelloWorld::beganParticle(cocos2d::Touch* touch, cocos2d::Event* event) {
    moveParticle(touch, event);
    return true;
}
void HelloWorld::popDown(Ref* sender, ui::Widget::TouchEventType type) { //EDIT SPECIAL
    if (!popUpNode->getParent() && !infoCheckboxesPopupNode->getParent()) {

        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[14]->stopAllActions();
            restOfButtons[14]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.215 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[14]->stopAllActions();
            restOfButtons[14]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.215)));
            this->addChild(popUpNode);
            restOfButtons[14]->setGlobalZOrder(-1);
            restOfButtons[7]->setGlobalZOrder(-1);
            particleSystem->setPosition(Vec2(340, 305));
            unckeckAll(true);
            if (!clipper->getParent()) {
                this->addChild(clipper);
            }
            this->removeChild(particleSystem);
            clipper->addChild(particleSystem);
            modifyerNumber = 0;
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[14]->stopAllActions();
            restOfButtons[14]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.215)));
            break;
        default:
            break;
        }
    }
}

void HelloWorld::popUp(Ref* sender, ui::Widget::TouchEventType type) { // OK button
    if (!infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[6]->stopAllActions();
            restOfButtons[6]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[6]->stopAllActions();
            restOfButtons[6]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));
            if (popUpNode->getParent()) {
                this->removeChild(popUpNode);
                restOfButtons[14]->setGlobalZOrder(25);
                restOfButtons[7]->setGlobalZOrder(25);
                particleSystem->setPosition(Vec2(720, 510));
                clipper->removeChild(particleSystem);

                removeChild(drawLinePosVar);
                removeChild(drawLineGravity);
                removeChild(drawLineSpeed);
                removeChild(drawCircleStartRadius);
                removeChild(drawCircleEndRadius);
                unckeckAll(false);
                if (!particleSystem->getParent()) {
                    this->addChild(particleSystem);
                }
                moveParticleListener->setSwallowTouches(true);
                moveParticleIsActive = true;
            }
            restOfButtons[6]->setScaleX(0.25);
            restOfButtons[6]->setScaleY(0.25);
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[6]->stopAllActions();
            restOfButtons[6]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
            break;
        default:
            break;
        }
    }
}

void HelloWorld::popTense(Ref* sender, ui::Widget::TouchEventType type) {
    switch (type) {
    case ui::Widget::TouchEventType::BEGAN:
        restOfButtons[15]->stopAllActions();
        restOfButtons[15]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.18 * 1.25)));
        break;
    case ui::Widget::TouchEventType::ENDED:
        restOfButtons[15]->stopAllActions();
        restOfButtons[15]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.18)));
        Application::getInstance()->openURL("https://www.youtube.com/channel/UC33L-Y8asG7gju6f-4-Cl2g?sub_confirmation=1/");
        tabTextures[0]->removeChild(restOfButtons[24]);

        if (infoCheckboxesPopupNode->getParent()) {
            this->removeChild(blackBackgroundInfoCheckboxesPopup);
            this->removeChild(infoCheckboxesPopupNode);
        }

        for (unsigned short int i = 0; i < 64; i++) particleSprite[i]->setColor(Color3B(255, 255, 255));

        restOfButtons[23]->setColor(Color3B(255, 255, 255));
        particleEditio = true;
        break;
    case ui::Widget::TouchEventType::CANCELED:
        restOfButtons[15]->stopAllActions();
        restOfButtons[15]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.18)));
        break;
    default:
        break;
    }
}
void HelloWorld::openHelpPopup(Ref* sender, ui::Widget::TouchEventType type) {
    if (!infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[16]->stopAllActions();
            restOfButtons[16]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.2 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[16]->stopAllActions();
            restOfButtons[16]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.2)));
            infoPopupNode->setScale(0.0);
            blackBackgroundHelpPopup->setOpacity(0.0);

            if (!infoPopupNode->getParent()) {
                this->addChild(blackBackgroundHelpPopup);
                this->addChild(infoPopupNode);
                infoPopupNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.6f));
                blackBackgroundHelpPopup->runAction(EaseInOut::create(FadeTo::create(0.10, 125), 2));
            }

            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[16]->stopAllActions();
            restOfButtons[16]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.2)));
            break;
        default:
            break;
        }
    }

}
void HelloWorld::closeInfoCheckboxesPopup(Ref* sender, ui::Widget::TouchEventType type) {

    switch (type) {
    case ui::Widget::TouchEventType::BEGAN:
        infoCheckboxesOkButton->stopAllActions();
        infoCheckboxesOkButton->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
        break;
    case ui::Widget::TouchEventType::ENDED:
        infoCheckboxesOkButton->stopAllActions();
        infoCheckboxesOkButton->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));
        if (infoCheckboxesPopupNode->getParent()) {
            this->removeChild(blackBackgroundInfoCheckboxesPopup);
            this->removeChild(infoCheckboxesPopupNode);
        }
        infoCheckboxesOkButton->setScaleX(0.25);
        infoCheckboxesOkButton->setScaleY(0.25);

        break;
    case ui::Widget::TouchEventType::CANCELED:
        infoCheckboxesOkButton->stopAllActions();
        infoCheckboxesOkButton->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
        break;
    default:
        break;
    }

}
void HelloWorld::closeHelpPopup(Ref* sender, ui::Widget::TouchEventType type) {
    switch (type) {
    case ui::Widget::TouchEventType::BEGAN:
        restOfButtons[17]->stopAllActions();
        restOfButtons[17]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
        break;
    case ui::Widget::TouchEventType::ENDED:
        restOfButtons[17]->stopAllActions();
        restOfButtons[17]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));
        if (infoPopupNode->getParent()) {
            this->removeChild(blackBackgroundHelpPopup);
            this->removeChild(infoPopupNode);
        }
        restOfButtons[17]->setScaleX(0.25);
        restOfButtons[17]->setScaleY(0.25);

        break;
    case ui::Widget::TouchEventType::CANCELED:
        restOfButtons[17]->stopAllActions();
        restOfButtons[17]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
        break;
    default:
        break;
    }

}
void HelloWorld::switchParticleType(Ref* sender, ui::Widget::TouchEventType type) {

    if (!infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        //Check which button of the three (freee,relative,goruped) is being pressed.
        for (int i = 0; i < 6; i++) {
            if (restOfButtons[i]->isHighlighted()) {
                switchTypeButtons = i;
            }
        }
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[switchTypeButtons]->stopAllActions();
            restOfButtons[switchTypeButtons]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.135 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            switch (switchTypeButtons)
            {
            case 3:
                particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED);
                restOfButtons[3]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                restOfButtons[4]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                restOfButtons[5]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                break;
            case 4:
                particleSystem->setPositionType(ParticleSystem::PositionType::RELATIVE);
                restOfButtons[4]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                restOfButtons[3]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                restOfButtons[5]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                break;
            case 5:
                particleSystem->setPositionType(ParticleSystem::PositionType::FREE);
                restOfButtons[5]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                restOfButtons[3]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                restOfButtons[4]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                break;
            default:
                break;
            }
            restOfButtons[switchTypeButtons]->stopAllActions();
            restOfButtons[switchTypeButtons]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.135)));
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[switchTypeButtons]->stopAllActions();
            restOfButtons[switchTypeButtons]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.135)));
            break;
        default:
            break;
        }
    }
}
void HelloWorld::switchToGravity(Ref* sender, ui::Widget::TouchEventType type) {

    if (!infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        //Check which button is being pressed - (gravity checkbox | radius checkbox)
        for (int i = 1; i < 3; i++) {
            if (restOfButtons[i]->isHighlighted()) {
                switchButtons = i;
            }
        }
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[switchButtons]->stopAllActions();
            restOfButtons[switchButtons]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.135 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            unckeckAll(false);
            if (switchButtons == 1) {// Gravity checkbox is pressed
                particleSystem->setEmitterMode(ParticleSystem::Mode::GRAVITY);
                restOfButtons[1]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                restOfButtons[2]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                if (!tabOneGravity->getParent()) {
                    popUpNode->addChild(tabOneGravity);
                }
                switch (modifyerNumber)
                {
                    case 1:
                        posVarIsActive = true;
                        listenerForPosVarLine->setSwallowTouches(true);
                        drawLines(1); break;
                    case 2:
                        gravityIsActive = true;
                        listenerForGravityLine->setSwallowTouches(true);
                        drawLines(2); break;
                    default:
                        break;
                }
                popUpNode->removeChild(tabOneRadius);
            }
            else {// Radius checkbox is pressed
                particleSystem->setEmitterMode(ParticleSystem::Mode::RADIUS);
                restOfButtons[2]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                restOfButtons[1]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                if (!tabOneRadius->getParent()) {
                    popUpNode->addChild(tabOneRadius);
                }
                switch (modifyerNumber)
                {
                case 1:
                    startRadIsActive = true;
                    listenerForStartRadiusLine->setSwallowTouches(true);
                    drawLines(4); break;
                case 2:
                    endRadIsActive = true;
                    listenerForEndRadiusLine->setSwallowTouches(true);
                    drawLines(5); break;
                default:
                    break;
                }
                popUpNode->removeChild(tabOneGravity);
            }
            restOfButtons[switchButtons]->stopAllActions();
            restOfButtons[switchButtons]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.135)));
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[switchButtons]->stopAllActions();
            restOfButtons[switchButtons]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.135)));
            break;
        default:
            break;
        }
    }
}

void HelloWorld::onTouchMovedEndRadius(cocos2d::Touch* touch, cocos2d::Event* event) {

    if (173 < touch->getLocation().x < 497 && 55 < touch->getLocation().y < 541 && endRadIsActive) {

        endRadIsActive2 = true;

        int c = pow((particleSystem->getPosition().y / 2 - (touch->getLocation().y) / 2), 2) +
            pow(particleSystem->getPosition().x / 2 - ((touch->getLocation().x) / 2), 2);
        c = sqrt(c);


        drawLines(5);

        particleSystem->setEndRadius(c);


        //Change Angle Label, depending on where the touch position is
        std::stringstream ss6;
        ss6 << c;
        labelArray[18]->setString((ss6.str().c_str()));

        //If Angle is under 0, set the slider pecentage to 0, if higher than 100, set it to max

        sliderArray[18]->setPercent(c);

        //If Speed is under 0, set the slider pecentage to 0, if higher than 100, set it to max
        if (particleSystem->getEndRadius() > 100) {
            sliderArray[18]->setPercent(sliderArray[18]->getMaxPercent());
        }
        else { sliderArray[18]->setPercent(particleSystem->getEndRadius()); }

        endRadIsActive2 = false;
    }
}
bool HelloWorld::onTouchBeganEndRadius(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (popUpNode->getParent() && !infoCheckboxesPopupNode->getParent()) {


        //If he is touching the black area
        if (touch->getLocation().x > 173 &&
            touch->getLocation().x < 497 &&
            touch->getLocation().y > 55 &&
            touch->getLocation().y < 541) {

            onTouchMovedEndRadius(touch, event);
            onTouchMovedEndRadius(touch, event); //twice because someone is dumb but dont say loud who
        }
    }

    return true;
}

void HelloWorld::onTouchMovedStartRadius(cocos2d::Touch* touch, cocos2d::Event* event) {


    //Draw Rect
    if (startRadIsActive) {

        startRadIsActive2 = true;

        int c = pow((particleSystem->getPosition().y / 2 - (touch->getLocation().y) / 2), 2) +
            pow(particleSystem->getPosition().x / 2 - ((touch->getLocation().x) / 2), 2);
        c = sqrt(c);

        drawLines(4);

        particleSystem->setStartRadius(c);



        //Change Angle Label, depending on where the touch position is
        std::stringstream ss6;
        ss6 << c;
        labelArray[17]->setString((ss6.str().c_str()));

        //If Start Radius is under 0, set the slider pecentage to 0, if higher than 100, set it to max

        sliderArray[17]->setPercent(c);

        //If Start Radius is under 0, set the slider pecentage to 0, if higher than 100, set it to max
        if (particleSystem->getStartRadius() > 100) {
            sliderArray[17]->setPercent(sliderArray[17]->getMaxPercent());
        }
        else { sliderArray[17]->setPercent(particleSystem->getStartRadius()); }

        startRadIsActive2 = false;
    }
}
bool HelloWorld::onTouchBeganStartRadius(cocos2d::Touch* touch, cocos2d::Event* event) {

    if (popUpNode->getParent() && !infoCheckboxesPopupNode->getParent()) {


        //If he is touching the black area
        if (touch->getLocation().x > 173 &&
            touch->getLocation().x < 497 &&
            touch->getLocation().y > 55 &&
            touch->getLocation().y < 541) {

            onTouchMovedStartRadius(touch, event);
            onTouchMovedStartRadius(touch, event);
        }
    }
    return true;
}

short int angle = 0;
void HelloWorld::onTouchMovedSpeedAngle(cocos2d::Touch* touch, cocos2d::Event* event) {
    //If he clicked on the third button [3]
    if (speedAngleIsActive) {


        //Tell that speed is being changed using a line
        speedIsActive = true;
        angleIsActive = true;

        short int angleAmount;

        //Draw a line for speed and angle
        if (drawLineSpeed)
        {
            removeChild(drawLineSpeed);
            drawLineSpeed = DrawNode::create();
            drawLineSpeed->drawLine(Vec2(touch->getLocation().x, touch->getLocation().y), particleSystem->getPosition(), Color4F(1, 1, 0.65, 1));
            this->addChild(drawLineSpeed, 29);
            drawLineSpeed->setLineWidth(1.0f);
        }

        //
        //Store "touch Location" for later
        valueXGlobal = touch->getLocation().x;
        valueYGlobal = touch->getLocation().y;


        //Get Hypotenuse (Speed)
        int c = pow((valueYGlobal - particleSystem->getPosition().y), 2) +
            pow((valueXGlobal - particleSystem->getPosition().x), 2);
        c = sqrt(c);
        particleSystem->setSpeed(c);


        /*--=Define Angle depending on where the touch location is=--*/
        // TOP-LEFT
        if (valueXGlobal - particleSystem->getPosition().x > 0 && valueYGlobal - particleSystem->getPosition().y > 0) {
            angleAmount = (-(::atan(-(valueXGlobal - particleSystem->getPosition().x) /
                -(valueYGlobal - particleSystem->getPosition().y)) * (180 / M_PI))) + 90;
        }
        // BOTTOM-RIGHT
        else if (valueXGlobal - particleSystem->getPosition().x > 0 && valueYGlobal - particleSystem->getPosition().y < 0)
        {
            angleAmount = (((::atan(-(valueXGlobal - particleSystem->getPosition().x) /
                (valueYGlobal - particleSystem->getPosition().y)) * (-180 / M_PI))) + 90) * -1;
        }
        // BOTTOM-LEFT
        else if (valueXGlobal - particleSystem->getPosition().x < 0 && valueYGlobal - particleSystem->getPosition().y < 0)
        {
            angleAmount = (-(::atan((valueXGlobal - particleSystem->getPosition().x) /
                -(valueYGlobal - particleSystem->getPosition().y)) * (-180 / M_PI))) - 90;
        }
        // TOP-RIGHT
        else {
            angleAmount = (-((::atan((valueXGlobal - particleSystem->getPosition().x) /
                -(valueYGlobal - particleSystem->getPosition().y)) * (-180 / M_PI)))) + 90;
        }
        if (valueYGlobal - particleSystem->getPosition().y < 0) {
        }
        particleSystem->setAngle(angleAmount);


        //Change Angle Label, depending on where the touch position is
        std::stringstream ss6;
        ss6 << angleAmount * -1;
        labelArray[4]->setString((ss6.str().c_str()));


        //Set the angle slider pecentage
        sliderArray[4]->setPercent(-(angleAmount - 180));


        //Change Speed Label, depending on where the touch position is
        std::stringstream ss7;
        ss7 << c;
        labelArray[5]->setString((ss7.str().c_str()));


        //If Speed is under 0, set the slider pecentage to 0, if higher than 100, set it to max
        if (particleSystem->getSpeed() > 400) {
            sliderArray[5]->setPercent(sliderArray[5]->getMaxPercent());
        }
        else { sliderArray[5]->setPercent(particleSystem->getSpeed()); }


        //Stopped using lines
        speedIsActive = false;
        angleIsActive = false;
    }
}
bool HelloWorld::onTouchBeganSpeedAngle(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (popUpNode->getParent()) {


        //If he is touching the black area
        if (touch->getLocation().x > 173 &&
            touch->getLocation().x < 497 &&
            touch->getLocation().y > 55 &&
            touch->getLocation().y < 541) {

            onTouchMovedSpeedAngle(touch, event);
            onTouchMovedSpeedAngle(touch, event);
        }
    }
    return true;
}

void HelloWorld::onTouchMovedPosVar(cocos2d::Touch* touch, cocos2d::Event* event) {
    //If he clicked on first button [1]
    if (posVarIsActive) {


        //He is using lines 
        posVarIsActive2 = true;



        //Draw Rect
        if (drawLinePosVar)
        {
            removeChild(drawLinePosVar);
        }
        drawLinePosVar = DrawNode::create();
        drawLinePosVar->drawRect(Vec2((touch->getLocation().x), (touch->getLocation().y)), particleSystem->getPosition() * 2 - Vec2((touch->getLocation().x), (touch->getLocation().y)),
            Color4F(0, 1, 0, 1));
        this->addChild(drawLinePosVar, 29);
        drawLinePosVar->setLineWidth(1.0f);


        //Change Particle PosVar, depending on where the touch position is
        if (touch->getLocation().y < 0) {
            particleSystem->setPosVar(Vec2(((touch->getLocation().x - particleSystem->getPosition().x) / 2),
                ((touch->getLocation().y - particleSystem->getPosition().y) / -2)));
        }
        else {
            particleSystem->setPosVar(Vec2(((touch->getLocation().x - particleSystem->getPosition().x) / 2),
                ((touch->getLocation().y - particleSystem->getPosition().y) / 2)));
        }
        if (touch->getLocation().x < 0) {
            particleSystem->setPosVar(Vec2(((touch->getLocation().x - particleSystem->getPosition().x) / 2) * -1,
                ((touch->getLocation().y - particleSystem->getPosition().y) / 2)));
        }
        else {
            particleSystem->setPosVar(Vec2(((touch->getLocation().x - particleSystem->getPosition().x) / 2),
                ((touch->getLocation().y - particleSystem->getPosition().y) / 2)));
        }


        //If PosVar is negative, multiple it by -1 -> positive
        if (particleSystem->getPosVar().x < 0 && particleSystem->getPosVar().y > 0) {
            particleSystem->setPosVar(Vec2(particleSystem->getPosVar().x * -1, particleSystem->getPosVar().y));
        }
        else if (particleSystem->getPosVar().x > 0 && particleSystem->getPosVar().y > 0) {
            particleSystem->setPosVar(Vec2(particleSystem->getPosVar().x, particleSystem->getPosVar().y));
        }
        else if (particleSystem->getPosVar().x > 0 && particleSystem->getPosVar().y < 0) {
            particleSystem->setPosVar(Vec2(particleSystem->getPosVar().x, particleSystem->getPosVar().y * -1));
        }
        else if (particleSystem->getPosVar().x < 0 && particleSystem->getPosVar().y < 0) {
            particleSystem->setPosVar(Vec2(particleSystem->getPosVar().x * -1, particleSystem->getPosVar().y * -1));
        }


        //Change PosVar Label, depending on where the touch position is
        std::stringstream ss7;
        ss7 << std::floor(particleSystem->getPosVar().x * 1) / 1;
        labelArray[6]->setString((ss7.str().c_str()));
        std::stringstream ss14;
        ss14 << std::floor((particleSystem->getPosVar().y * 1) / 1) * 1;
        labelArray[13]->setString((ss14.str().c_str()));


        //If the PosVar is under 0, set the slider pecentage to 0, if higher than 100, set it to max
        if (particleSystem->getPosVar().x < 0) {
            sliderArray[6]->setPercent(0);
        }
        else if (particleSystem->getPosVar().x > 100) {
            sliderArray[6]->setPercent(sliderArray[6]->getMaxPercent());
        }
        else { sliderArray[6]->setPercent(particleSystem->getPosVar().x); }
        if (particleSystem->getPosVar().y < 0) {
            sliderArray[13]->setPercent(0);
        }
        else if (particleSystem->getPosVar().y > 100) {
            sliderArray[13]->setPercent(sliderArray[13]->getMaxPercent());
        }
        else { sliderArray[13]->setPercent(particleSystem->getPosVar().y); }


        //Stopped using lines
        posVarIsActive2 = false;
    }
}
bool HelloWorld::onTouchBeganPosVar(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (popUpNode->getParent()) {


        //If he is touching the black area
        if (touch->getLocation().x > 173 &&
            touch->getLocation().x < 497 &&
            touch->getLocation().y > 55 &&
            touch->getLocation().y < 541) {

            onTouchMovedPosVar(touch, event);
        }
    }
    return true;
}

void HelloWorld::easyModify(Ref* sender, ui::Widget::TouchEventType type) {

    if (!infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        //Check which button of the three ([1],[2],[3]) is being pressed.
        for (int i = 0; i < 3; i++) {
            if (easyModifier[i]->isHighlighted()) {
                modifyer = i;
            }
        }

        easyModifier[modifyer]->stopAllActions();

        //If button touch started, ended or canceled.
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            easyModifier[modifyer]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.26 * 1.4)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            unckeckAll(true); //every button is grey | cant draw | remove line
            switch (modifyer)
            {
            case 0:
                //If the third button [3] Button is Grey, make it Green. He is on tab 3
                if (modifyerNumber != 3) {
                    easyModifier[0]->loadTextures("easyModifierBlue.png", "easyModifierBlue.png");
                    modifyerNumber = 3; //on which tab is he?

                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                        listenerForSpeedAngleLine->setSwallowTouches(true);
                        speedAngleIsActive = true;
                        drawLines(3);
                    }
                }
                else { modifyerNumber = 0;
                }

                break;
            case 1:

                if (modifyerNumber != 2) {
                    easyModifier[1]->loadTextures("easyModifierBlue.png", "easyModifierBlue.png");
                    modifyerNumber = 2;
                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                        gravityIsActive = true;
                        listenerForGravityLine->setSwallowTouches(true);
                        drawLines(2);
                    }
                    else {
                        endRadIsActive = true;
                        listenerForEndRadiusLine->setSwallowTouches(true);
                        drawLines(5);
                    }
                }
                else { modifyerNumber = 0;
                }

                break;
            case 2:

                if (modifyerNumber != 1) {
                    easyModifier[2]->loadTextures("easyModifierBlue.png", "easyModifierBlue.png");
                    modifyerNumber = 1;
                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                        posVarIsActive = true;
                        listenerForPosVarLine->setSwallowTouches(true);
                        drawLines(1);
                    }
                    else {
                        startRadIsActive = true;
                        listenerForStartRadiusLine->setSwallowTouches(true);
                        drawLines(4);
                    }
                }
                else {
                    modifyerNumber = 0;
                }
                break;
            default:
                break;
            }
            easyModifier[modifyer]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.26)));

            break;
        case ui::Widget::TouchEventType::CANCELED:
            easyModifier[modifyer]->runAction(EaseBounceOut::create(ScaleTo::create(0.35, 0.26)));
            break;
        default:
            break;
        }
    }
}
void HelloWorld::onTouchMovedGravity(cocos2d::Touch* touch, cocos2d::Event* event) {

    if (gravityIsActive == 1) { //Check if he has clicked the Gravity button.

        //He is using lines!
        gravityIsActive2 = true;


        //Draw Line.
        drawLines(2);


        //Store final position of the line (incase he changed it using sliders)
        valueXGlobalGravity = touch->getLocation().x;
        valueYGlobalGravity = touch->getLocation().y;


        //Change Particle Gravity, depending on where the touches are located.
        particleSystem->setGravity(Vec2((touch->getLocation().x - particleSystem->getPosition().x) * 3,
            (touch->getLocation().y - particleSystem->getPosition().y) * 3));


        //Change Strings.
        std::stringstream ss7;
        ss7 << std::floor(particleSystem->getGravity().x * 1) / 1;
        labelArray[7]->setString((ss7.str().c_str()));
        std::stringstream ss14;
        ss14 << std::floor(particleSystem->getGravity().y * 1) / 1;
        labelArray[14]->setString((ss14.str().c_str()));


        //--X--
        //Change gravity sliders
        sliderArray[7]->setPercent((particleSystem->getGravity().x) + 600);

        //--Y--
        //Change gravity sliders
        sliderArray[14]->setPercent((particleSystem->getGravity().y) + 600);

        //He stopped using lines!
        gravityIsActive2 = false;
    }
}
bool HelloWorld::onTouchBeganGravity(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (popUpNode->getParent()) {

        //If he is touching the black area
        if (touch->getLocation().x > 173 &&
            touch->getLocation().x < 497 &&
            touch->getLocation().y > 55 &&
            touch->getLocation().y < 541) {

            onTouchMovedGravity(touch, event);
            onTouchMovedGravity(touch, event);
        }
    }
    return true;
}
int usedButtonArray = 1;
void HelloWorld::unckeckAll(bool changeButtonColor) {
    if (changeButtonColor) {
        easyModifier[0]->loadTextures("easyModifierGrey.png", "easyModifierGrey.png");
        easyModifier[1]->loadTextures("easyModifierGrey.png", "easyModifierGrey.png");
        easyModifier[2]->loadTextures("easyModifierGrey.png", "easyModifierGrey.png");
    }
    posVarIsActive = false;
    speedAngleIsActive = false;
    gravityIsActive = false;
    startRadIsActive = false;
    endRadIsActive = false;
    this->removeChild(drawCircleAngleReal);
    this->removeChild(drawLineGravity);
    this->removeChild(drawLinePosVar);
    this->removeChild(drawLineSpeed);
    this->removeChild(drawCircleStartRadius);
    this->removeChild(drawCircleEndRadius);
    listenerForSpeedAngleLine->setSwallowTouches(false);
    listenerForGravityLine->setSwallowTouches(false);
    listenerForPosVarLine->setSwallowTouches(false);
    listenerForStartRadiusLine->setSwallowTouches(false);
    listenerForEndRadiusLine->setSwallowTouches(false);
}
int usedCheckBox = 0;
void HelloWorld::checkBox(Ref* sender, ui::Widget::TouchEventType type) {
    if (!infoCheckboxesPopupNode->getParent() && !infoPopupNode->getParent()) {

        //Check which box is being touched.
        for (int i = 0; i < 5; i++) {
            if (checkBoxes[i]->isHighlighted()) {
                usedCheckBox = i;
            }
        }

        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            checkBoxes[usedCheckBox]->stopAllActions();
            checkBoxes[usedCheckBox]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.13 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            checkBoxes[usedCheckBox]->stopAllActions();
            checkBoxes[usedCheckBox]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.13)));

            switch (usedCheckBox)
            {
            case 0:
                if (checkBoxes[0]->getTag() == 0) {
                    particleSystem->setBlendAdditive(1);
                    checkBoxes[0]->setTag(1);
                    checkBoxes[0]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                }
                else {
                    checkBoxes[0]->setTag(0);
                    particleSystem->setBlendAdditive(0);
                    checkBoxes[0]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                }
                break;
            case 1:
                if (checkBoxes[1]->getTag() == 0) {
                    particleSystem->setEndSize(particleSystem->getStartSize());
                    labelArrayVisual[1]->setString(labelArrayVisual[0]->getString());
                    sliderArrayVisual[1]->setPercent(sliderArrayVisual[0]->getPercent());
                    checkBoxes[1]->setTag(1);
                    checkBoxes[1]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                }
                else {
                    checkBoxes[1]->setTag(0);
                    particleSystem->setEndSize(0);
                    labelArrayVisual[1]->setString("0");
                    sliderArrayVisual[1]->setPercent(0);
                    checkBoxes[1]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                }
                break;
            case 2:
                if (checkBoxes[2]->getTag() == 0) {
                    particleSystem->setEndSpin(particleSystem->getStartSpin());
                    labelArrayVisual[3]->setString(labelArrayVisual[2]->getString());
                    sliderArrayVisual[3]->setPercent(sliderArrayVisual[2]->getPercent());
                    checkBoxes[2]->setTag(1);
                    checkBoxes[2]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                }
                else {
                    checkBoxes[2]->setTag(0);
                    particleSystem->setStartSpin(0);
                    labelArrayVisual[3]->setString("0");
                    sliderArrayVisual[3]->setPercent(0);
                    checkBoxes[2]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                }
                break;
            case 3:
                if (checkBoxes[3]->getTag() == 0) {
                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::RADIUS) {
                        particleSystem->setEndRadius(particleSystem->getStartRadius());
                        labelArray[18]->setString(labelArray[17]->getString());
                        sliderArray[18]->setPercent(sliderArray[17]->getPercent());
                    }
                    checkBoxes[3]->setTag(1);
                    checkBoxes[3]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                }
                else {
                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::RADIUS) {
                        particleSystem->setEndRadius(0);
                        labelArray[18]->setString("0");
                        sliderArray[18]->setPercent(0);
                    }
                    checkBoxes[3]->setTag(0);
                    checkBoxes[3]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                }
                break;
            case 4:
                if (checkBoxes[4]->getTag() == 0) {
                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                        particleSystem->setRotationIsDir(true);
                    }
                    checkBoxes[4]->setTag(1);
                    checkBoxes[4]->loadTextures("GJ_checkOn_001.png", "GJ_checkOn_001.png");
                }
                else {
                    if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                        particleSystem->setRotationIsDir(false);
                    }
                    checkBoxes[4]->setTag(0);
                    checkBoxes[4]->loadTextures("GJ_checkOff_001.png", "GJ_checkOff_001.png");
                }
                break;
            default:
                break;
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            checkBoxes[usedCheckBox]->stopAllActions();
            checkBoxes[usedCheckBox]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.13)));
            break;
        default:
            break;
        }
    }
}
void HelloWorld::textures(Ref* sender, ui::Widget::TouchEventType type) {
    if (!infoPopupNode->getParent()) {


        //Check which button is being pressed from all textures buttons
        for (unsigned short int i = 0; i < changeWhenDone; i++) {
            if (particleSprite[i]->isHighlighted()) {
                usedSprite = i;
            }
        }

        //Define Animations.
        EaseBounceOut* scaleUpSlowEase = EaseBounceOut::create(ScaleTo::create(0.25, 0.095 * 1.25)); // Animation when TouchEventType::BEGAN
        EaseBounceOut* scaleDownFastEase = EaseBounceOut::create(ScaleTo::create(0.01, 0.095)); // Animation when TouchEventType::BEGAN
        EaseBounceOut* scaleDownSlowEase = EaseBounceOut::create(ScaleTo::create(0.34, 0.095)); // Animation when TouchEventType::CANCELED

        //Some of the particles have bigger texuture, so for them use a differnt animations (size).
        if (usedSprite < 52 || usedSprite > 63) {
            scaleUpSlowEase = EaseBounceOut::create(ScaleTo::create(0.25, 0.095 * 1.25)); // Animation when TouchEventType::
            scaleDownFastEase = EaseBounceOut::create(ScaleTo::create(0.01, 0.095)); // Animation when TouchEventType::
            scaleDownSlowEase = EaseBounceOut::create(ScaleTo::create(0.34, 0.095)); // Animation when TouchEventType::CANCELED
        }
        else {
            scaleUpSlowEase = EaseBounceOut::create(ScaleTo::create(0.25, 0.14 * 1.25)); // Animation when TouchEventType::BEGAN
            scaleDownFastEase = EaseBounceOut::create(ScaleTo::create(0.01, 0.14)); // Animation when TouchEventType::BEGAN
            scaleDownSlowEase = EaseBounceOut::create(ScaleTo::create(0.34, 0.14)); // Animation when TouchEventType::CANCELED
        }

        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            particleSprite[usedSprite]->stopAllActions();
            particleSprite[usedSprite]->runAction(scaleUpSlowEase);
            break;
        case ui::Widget::TouchEventType::ENDED:
            particleSprite[usedSprite]->stopAllActions();
            particleSprite[usedSprite]->runAction(scaleDownFastEase);

            if (particleEditio) {
                //Change the pos of the selection box
                if (!selectTextureBox->getParent()) {
                    tabTextures[0]->addChild(selectTextureBox);
                }
                selectTextureBox->setPosition(Vec2(particleSprite[usedSprite]->getPosition().x + 1, particleSprite[usedSprite]->getPosition().y - 1));

                selectTextureBox->setTag(usedSprite);

                //Change the particle texture to the texture he clicked on
                if (usedSprite < changeWhenDone) {
                    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("particle_" + std::to_string(usedSprite) +
                        ".png"));
                }
                else {
                    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("GJ_infoIcon_001.png"));

                }
            }

            //particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage(
            //   "particle_" + std::to_string(usedSprite) + ".png", ui::Widget::TextureResType::PLIST));
            break;
        case ui::Widget::TouchEventType::CANCELED:
            particleSprite[usedSprite]->stopAllActions();
            particleSprite[usedSprite]->runAction(scaleDownSlowEase);
            break;
        default:
            break;
        }
    }
}
void HelloWorld::upperButtonsFunction(Ref* sender, ui::Widget::TouchEventType type) {

    if (!infoPopupNode->getParent() && !infoCheckboxesPopupNode->getParent()) {
        for (int i = 0; i < 4; i++) {
            if (upperButtonsArray[i]->isHighlighted()) {
                usedButtonArray = i;
            }
        }

        std::stringstream ss0;
        ss0 << usedButtonArray;
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            upperButtons[usedButtonArray]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.34 / 0.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:

            upperButtonsArray[0]->loadTextures("greyButton.png", "greyButton.png");
            upperButtonsArray[1]->loadTextures("greyButton.png", "greyButton.png");
            upperButtonsArray[2]->loadTextures("greyButton.png", "greyButton.png");
            upperButtonsArray[3]->loadTextures("greyButton.png", "greyButton.png");
            upperButtonsArray[usedButtonArray]->loadTextures("greenButton.png", "greenButton.png");

            upperButtons[usedButtonArray]->stopAllActions();
            upperButtons[usedButtonArray]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25 / 0.25)));
            if (usedButtonArray == 0 && onTabNum != 0) {
                if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                    popUpNode->addChild(tabOneGravity);
                }
                else { popUpNode->addChild(tabOneRadius); }

                popUpNode->addChild(tabOne);
                onTabNum = 0;
                popUpNode->removeChild(tabTwo);
                popUpNode->removeChild(tabThree);
                popUpNode->removeChild(tabTextures[0]);
                popUpNode->removeChild(tabTextures[1]);
            }

            if (usedButtonArray == 1 && onTabNum != 1) {
                popUpNode->removeChild(tabOneGravity);
                popUpNode->removeChild(tabOneRadius);
                popUpNode->removeChild(tabOne);
                popUpNode->addChild(tabTwo);
                onTabNum = 1;
                popUpNode->removeChild(tabThree);
                popUpNode->removeChild(tabTextures[0]);
                popUpNode->removeChild(tabTextures[1]);
            }

            if (usedButtonArray == 2 && onTabNum != 2) {
                popUpNode->removeChild(tabOneGravity);
                popUpNode->removeChild(tabOneRadius);
                popUpNode->removeChild(tabOne);
                popUpNode->removeChild(tabTwo);
                popUpNode->addChild(tabThree);
                onTabNum = 2;
                popUpNode->removeChild(tabTextures[0]);
                popUpNode->removeChild(tabTextures[1]);
            }

            if (usedButtonArray == 3 && onTabNum != 3) {
                popUpNode->removeChild(tabOneGravity);
                popUpNode->removeChild(tabOneRadius);
                popUpNode->removeChild(tabOne);
                popUpNode->removeChild(tabTwo);
                popUpNode->removeChild(tabThree);
                popUpNode->removeChild(tabTextures[0]);
                popUpNode->removeChild(tabTextures[1]);
                popUpNode->addChild(tabTextures[0]);
                popUpNode->addChild(tabTextures[1]);
                if (restOfButtons[23]->getTag() == 0) {
                    for (unsigned short int i = 0; i < 64; i++) { 
                        if (!particleSprite[i]->getParent()) {
                            tabTextures[0]->addChild(particleSprite[i], 35);
                        }
                    }
                }
                else if(restOfButtons[23]->getTag() == 1) {
                    for (unsigned short int i = 64; i < changeWhenDone; i++) {
                        if (!particleSprite[i]->getParent()) {
                            tabTextures[1]->addChild(particleSprite[i]);
                        }
                    }
                }
                //for (unsigned short int i = 0; i < 64; i++) { tabTextures[0]->addChild(particleSprite[i], 35); }
                //for (unsigned short int i = 64; i < changeWhenDone; i++) { tabTextures[1]->addChild(particleSprite[i]); }
                onTabNum = 3;
            }

            break;
        case ui::Widget::TouchEventType::CANCELED:
            upperButtons[usedButtonArray]->runAction(EaseBounceOut::create(ScaleTo::create(0.35, 0.25 / 0.25)));
            break;
        default:
            break;
        }
    }
}
void HelloWorld::calcButtonFunc(Ref* sender, ui::Widget::TouchEventType type) {

    if (!infoPopupNode->getParent()) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[0]->stopAllActions();
            restOfButtons[0]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            particleSystem->resetSystem();
            restOfButtons[0]->stopAllActions();
            restOfButtons[0]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[0]->stopAllActions();
            restOfButtons[0]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
            break;
        default:
            break;
        }
    }
}
int reverseColors = 0;
void HelloWorld::reverseColorsButtonFunc(Ref* sender, ui::Widget::TouchEventType type) {
    //Check if switch color var or normal is being pressed

    if (!infoPopupNode->getParent()) {
        if (restOfButtons[12]->isHighlighted()) {
            reverseColors = 12;
        }
        else if (restOfButtons[13]->isHighlighted()) {
            reverseColors = 13;
        }

        //save old colors
        Color3B startColorSave = restOfButtons[8]->getColor();
        Color3B endColorSave = restOfButtons[9]->getColor();

        Color3B startColorSaveVar = restOfButtons[10]->getColor();
        Color3B endColorSaveVar = restOfButtons[11]->getColor();


        //save old color sliders percent
        int startColorPercentage[] = { sliderArrayVisual[4]->getPercent(),
        sliderArrayVisual[5]->getPercent(),
        sliderArrayVisual[6]->getPercent(),
        sliderArrayVisual[7]->getPercent(),
        sliderArrayVisual[8]->getPercent(),
        sliderArrayVisual[9]->getPercent(),
        sliderArrayVisual[10]->getPercent(),
        sliderArrayVisual[11]->getPercent(),
        sliderArrayVisual[16]->getPercent(),
        sliderArrayVisual[17]->getPercent(),
        sliderArrayVisual[18]->getPercent(),
        sliderArrayVisual[19]->getPercent(),
        sliderArrayVisual[20]->getPercent(),
        sliderArrayVisual[21]->getPercent(),
        sliderArrayVisual[22]->getPercent(),
        sliderArrayVisual[23]->getPercent() };

        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[reverseColors]->stopAllActions();
            restOfButtons[reverseColors]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.25 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[reverseColors]->stopAllActions();
            restOfButtons[reverseColors]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.25)));

            if (reverseColors == 13) { // color var

                //Apply percent
                sliderArrayVisual[16]->setPercent(startColorPercentage[12]);
                sliderArrayVisual[17]->setPercent(startColorPercentage[13]);
                sliderArrayVisual[18]->setPercent(startColorPercentage[14]);
                sliderArrayVisual[19]->setPercent(startColorPercentage[15]);

                sliderArrayVisual[20]->setPercent(startColorPercentage[8]);
                sliderArrayVisual[21]->setPercent(startColorPercentage[9]);
                sliderArrayVisual[22]->setPercent(startColorPercentage[10]);
                sliderArrayVisual[23]->setPercent(startColorPercentage[11]);


                //Apply color
                restOfButtons[10]->setColor(endColorSaveVar);
                restOfButtons[11]->setColor(startColorSaveVar);
                particleSystem->setStartColorVar(Color4F(endColorSaveVar));
                particleSystem->setEndColorVar(Color4F(startColorSaveVar));
            }
            else if (reverseColors == 12) { // color normal


               //Apply percent
                sliderArrayVisual[4]->setPercent(startColorPercentage[4]);
                sliderArrayVisual[5]->setPercent(startColorPercentage[5]);
                sliderArrayVisual[6]->setPercent(startColorPercentage[6]);
                sliderArrayVisual[7]->setPercent(startColorPercentage[7]);

                sliderArrayVisual[8]->setPercent(startColorPercentage[0]);
                sliderArrayVisual[9]->setPercent(startColorPercentage[1]);
                sliderArrayVisual[10]->setPercent(startColorPercentage[2]);
                sliderArrayVisual[11]->setPercent(startColorPercentage[3]);


                //Apply color
                restOfButtons[8]->setColor(endColorSave);
                restOfButtons[9]->setColor(startColorSave);
                particleSystem->setStartColor(Color4F(endColorSave));
                particleSystem->setEndColor(Color4F(startColorSave));
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[reverseColors]->stopAllActions();
            restOfButtons[reverseColors]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.25)));
            break;
        default:
            break;
        }
    }
}
void HelloWorld::sliderEvent(Ref* sender, ui::Slider::EventType type) {
    if (!startRadIsActive2 && !endRadIsActive2 && !posVarIsActive2 && !speedIsActive && !gravityIsActive2 && !angleIsActive && type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED && !infoPopupNode->getParent()) {
        
        std::stringstream ss1;
        std::stringstream ss2;
        std::stringstream ss10;
        std::stringstream ss18;
        std::stringstream ss14;
        std::stringstream ss5;
        std::stringstream ss6;
        std::stringstream ss7;
        std::stringstream ss8;
        std::stringstream ss9;
        std::stringstream ss104;
        std::stringstream ss11;
        std::stringstream ss12;
        std::stringstream ss13;
        std::stringstream ss15;
        std::stringstream ss16;
        std::stringstream ss17;
        std::stringstream ss19;
        if (onTabNum == 0) {

            float percentMotion[23] = { 15, 0, 50, 15, (360 / 4), 29 , 11, 600, 1000, 1000 ,30, 90, 0, 0, 600, 0, 0,0,0,0,0,0,0 };
            for (int i = 0; i < 23; i++) {
                percentMotion[i] = sliderArray[i]->getPercent();
            }
            int sliderMotionIsBeingTouched = 0;
            for (int i = 0; i < 23; i++) {
                if (sliderArray[i]->isHighlighted()) {
                    sliderMotionIsBeingTouched = i;
                }
            }
            switch (sliderMotionIsBeingTouched)
            {
            case 0:
                particleSystem->setTotalParticles(percentMotion[0] * 2);
                labelArray[0]->setString(std::to_string((int)particleSystem->getTotalParticles()));
                particleSystem->setEmissionRate(percentMotion[3] * 2);
                labelArray[3]->setString(std::to_string((int)particleSystem->getEmissionRate()));
                sliderArray[3]->setPercent(sliderArray[0]->getPercent()); break;
                //case 1:
                //    if (percentMotion[1] == 0) {   particleSystem->setDuration(-1);   }
                //    else {   particleSystem->setDuration(percentMotion[1] / 50);   }
                //    labelArray[0]->setString(std::to_string((int)particleSystem->getDuration())); break;
                //case 2:
                //    particleSystem->setLife((percentMotion[2]) / 50);
                //    labelArray[2]->setString(std::to_string((int)particleSystem->getLife())); break;
            case 3:
                particleSystem->setEmissionRate(percentMotion[3] * 2);
                labelArray[3]->setString(std::to_string((int)particleSystem->getEmissionRate())); break;
            case 4:
                particleSystem->setAngle(-(percentMotion[4]) + 180);
                labelArray[4]->setString(std::to_string((int)particleSystem->getAngle() * -1));
                drawLines(3);
                break;
                //case 10:
                //    particleSystem->setLifeVar((percentMotion[10]) / 100);
                //    labelArray[10]->setString(std::to_string((int)std::fixed << std::setprecision(2) << particleSystem->getLifeVar())); break;
            case 11:
                particleSystem->setAngleVar(percentMotion[11]);
                labelArray[11]->setString(std::to_string((int)particleSystem->getAngleVar()));
                drawLines(3);
                break;


            //Gravity
            case 5:
                particleSystem->setSpeed(percentMotion[5]);
                labelArray[5]->setString(std::to_string((int)particleSystem->getSpeed()));

                //If he is using sliders (Stopped using lines) SPEED
                drawLines(3);
                break;
            case 6:
                particleSystem->setPosVar(Vec2(percentMotion[6], particleSystem->getPosVar().y));
                labelArray[6]->setString(std::to_string((int)particleSystem->getPosVar().x));

                //If he is using sliders (Stopped using lines) POSVAR
                drawLines(1);
                break;
            case 13:
                particleSystem->setPosVar(Vec2(particleSystem->getPosVar().x, percentMotion[13]));
                labelArray[13]->setString(std::to_string((int)particleSystem->getPosVar().y));
                //If he is using sliders (Stopped using lines) POSVAR
                drawLines(1);
                break;
            case 7:
                particleSystem->setGravity(Vec2((percentMotion[7]) - 600, particleSystem->getGravity().y));
                labelArray[7]->setString(std::to_string((int)particleSystem->getGravity().x));

                //If he is using sliders (Stopped using lines) GRAVITY
                drawLines(2);
                break;
            case 14:
                particleSystem->setGravity(Vec2(particleSystem->getGravity().x, (percentMotion[14]) - 600));
                labelArray[14]->setString(std::to_string((int)particleSystem->getGravity().y));

                //If he is using sliders (Stopped using lines) GRAVITY
                drawLines(2);
                break;
            case 8:
                particleSystem->setRadialAccel((percentMotion[8]) - 1000);
                labelArray[8]->setString(std::to_string((int)particleSystem->getRadialAccel())); break;
            case 9:
                particleSystem->setTangentialAccel((percentMotion[9]) - 1000);
                labelArray[9]->setString(std::to_string((int)particleSystem->getTangentialAccel())); break;
            case 12:
                particleSystem->setSpeedVar(percentMotion[12]);
                labelArray[12]->setString(std::to_string((int)particleSystem->getSpeedVar()));

                //If he is using sliders (Stopped using lines) SPEED
                drawLines(3);
                break;
            case 15:
                particleSystem->setRadialAccelVar(percentMotion[15]);
                labelArray[15]->setString(std::to_string((int)particleSystem->getRadialAccelVar())); break;
            case 16:
                particleSystem->setTangentialAccelVar(percentMotion[16]);
                labelArray[16]->setString(std::to_string((int)particleSystem->getTangentialAccelVar())); break;

            //Radius
            case 17:
                particleSystem->setStartRadius(percentMotion[17]);
                labelArray[17]->setString(std::to_string((int)particleSystem->getStartRadius()));

                //If he is using sliders (Stopped using lines) START RADIUS
                drawLines(4);
                break;
            case 18:
                particleSystem->setEndRadius(percentMotion[18]);
                labelArray[18]->setString(std::to_string((int)particleSystem->getEndRadius()));

                //If he is using sliders (Stopped using lines) END RADIUS
                drawLines(5);
                break;
            case 19:
                particleSystem->setRotatePerSecond((percentMotion[19]) - 360);
                labelArray[19]->setString(std::to_string((int)particleSystem->getRotatePerSecond())); break;
            case 20:
                particleSystem->setStartRadiusVar(percentMotion[20]);
                labelArray[20]->setString(std::to_string((int)particleSystem->getStartRadiusVar()));

                //If he is using sliders (Stopped using lines) START RADIUS
                drawLines(4);
                break;
            case 21:
                particleSystem->setEndRadiusVar(percentMotion[21]);
                labelArray[21]->setString(std::to_string((int)particleSystem->getEndRadiusVar()));
                //If he is using sliders (Stopped using lines) END RADIUS
                drawLines(5);
                break;
            case 22:
                particleSystem->setRotatePerSecondVar(percentMotion[22] * 3.6);
                labelArray[22]->setString(std::to_string((int)particleSystem->getRotatePerSecondVar())); break;
            default:
                break;
            }


            if (percentMotion[1] == 0) { particleSystem->setDuration(-1); }
            else { particleSystem->setDuration(percentMotion[1] / 50); }

            particleSystem->setLife((percentMotion[2]) / 50);
            particleSystem->setLifeVar((percentMotion[10]) / 100);

            ss1 << std::fixed << std::setprecision(2) << particleSystem->getDuration();
            labelArray[1]->setString((ss1.str().c_str()));

            ss2 << std::fixed << std::setprecision(2) << particleSystem->getLife();
            labelArray[2]->setString((ss2.str().c_str()));

            ss10 << std::fixed << std::setprecision(2) << particleSystem->getLifeVar();
            labelArray[10]->setString((ss10.str().c_str()));
        }
        else if (onTabNum == 1){

            float percentVisual[24] = { 2,1,0,0,100,100,100,100,100,100,100,100,1,1,0,0,0,0,0,0,0,0,0,0 };
            int sliderVisualIsBeingTouched = 0;
            for (int i = 0; i < 24; i++) {
                percentVisual[i] = sliderArrayVisual[i]->getPercent();
                if (sliderArrayVisual[i]->isHighlighted()) { //check which slider is being touched
                    sliderVisualIsBeingTouched = i;
                }
            }

            //Change properties depending on which slider is being used.
            switch (sliderVisualIsBeingTouched)
            {
            case 0:
                particleSystem->setStartSize(percentVisual[0]);
                labelArrayVisual[0]->setString(std::to_string((int)std::floor(percentVisual[0] * 100) / 100)); break;
            case 1:
                particleSystem->setEndSize(percentVisual[1]);
                labelArrayVisual[1]->setString(std::to_string((int)std::floor(percentVisual[1] * 100) / 100)); break;
            case 2:
                particleSystem->setStartSpin(percentVisual[2]);
                labelArrayVisual[2]->setString(std::to_string((int)std::floor(percentVisual[2] * 100) / 100)); break;
            case 3:
                particleSystem->setEndSpin(percentVisual[3]);
                labelArrayVisual[3]->setString(std::to_string((int)std::floor(percentVisual[3] * 100) / 100)); break;
            case 4: case 5: case 6: case 7: //Start Color
                restOfButtons[8]->setColor(Color3B(percentVisual[4] * 2.55,
                    percentVisual[5] * 2.55,
                    percentVisual[6] * 2.55));
                particleSystem->setStartColor(Color4F(percentVisual[4] / 100,
                    percentVisual[5] / 100,
                    percentVisual[6] / 100,
                    percentVisual[7] / 100));
                break;
            case 8: case 9: case 10: case 11: //End Color
                restOfButtons[9]->setColor(Color3B(percentVisual[8] * 2.55,
                    percentVisual[9] * 2.55,
                    percentVisual[10] * 2.55));
                particleSystem->setEndColor(Color4F(percentVisual[8] / 100,
                    percentVisual[9] / 100,
                    percentVisual[10] / 100,
                    percentVisual[11] / 100));
                break;
            case 12:
                particleSystem->setStartSizeVar(percentVisual[12]);
                labelArrayVisual[12]->setString(std::to_string((int)std::floor(percentVisual[12] * 100) / 100)); break;
            case 13:
                particleSystem->setEndSizeVar(percentVisual[13]);
                labelArrayVisual[13]->setString(std::to_string((int)std::floor(percentVisual[13] * 100) / 100)); break;
            case 14:
                particleSystem->setStartSpinVar(percentVisual[14]);
                labelArrayVisual[14]->setString(std::to_string((int)std::floor(percentVisual[14] * 100) / 100)); break;
            case 15:
                particleSystem->setEndSpinVar(percentVisual[15]);
                labelArrayVisual[15]->setString(std::to_string((int)std::floor(percentVisual[15] * 100) / 100)); break;
            case 16: case 17: case 18: case 19: //Start Color Var

                restOfButtons[10]->setColor(Color3B(
                    restOfButtons[8]->getColor().r - percentVisual[16] * 2.55  ,
                    restOfButtons[8]->getColor().g - percentVisual[17] * 2.55  ,
                    restOfButtons[8]->getColor().b - percentVisual[18] * 2.55 
                ));


                particleSystem->setStartColorVar(Color4F(
                    percentVisual[16] / 100,
                    percentVisual[17] / 100,
                    percentVisual[18] / 100,
                    percentVisual[19] / 100));
                break;
            case 20: case 21: case 22: case 23: //End Color Var
                restOfButtons[11]->setColor(Color3B(percentVisual[20] * 2.55,
                    percentVisual[21] * 2.55,
                    percentVisual[22] * 2.55));
                particleSystem->setEndColorVar(Color4F(
                    percentVisual[20] / 100,
                    percentVisual[21] / 100,
                    percentVisual[22] / 100,
                    percentVisual[23] / 100));
                break;
            default:
                break;
            }

            //Start Color

            std::stringstream ss4;
            ss4 << std::fixed << std::setprecision(2) << particleSystem->getStartColor().r;
            labelArrayVisual[4]->setString((ss4.str().c_str()));
            

            ss5 << std::fixed << std::setprecision(2) << particleSystem->getStartColor().g;
            labelArrayVisual[5]->setString((ss5.str().c_str()));

            ss6 << std::fixed << std::setprecision(2) << particleSystem->getStartColor().b;
            labelArrayVisual[6]->setString((ss6.str().c_str()));

            ss7 << std::fixed << std::setprecision(2) << particleSystem->getStartColor().a;
            labelArrayVisual[7]->setString((ss7.str().c_str()));


            //End Color
            ss8 << std::fixed << std::setprecision(2) << particleSystem->getEndColor().r;
            labelArrayVisual[8]->setString((ss8.str().c_str()));

            ss9 << std::fixed << std::setprecision(2) << particleSystem->getEndColor().g;
            labelArrayVisual[9]->setString((ss9.str().c_str()));

            ss104 << std::fixed << std::setprecision(2) << particleSystem->getEndColor().b;
            labelArrayVisual[10]->setString((ss104.str().c_str()));

            ss11 << std::fixed << std::setprecision(2) << particleSystem->getEndColor().a;
            labelArrayVisual[11]->setString((ss11.str().c_str()));


            //Start Color Var
            ss12 << std::fixed << std::setprecision(2) << particleSystem->getStartColorVar().r;
            labelArrayVisual[16]->setString((ss12.str().c_str()));

            ss13 << std::fixed << std::setprecision(2) << particleSystem->getStartColorVar().g;
            labelArrayVisual[17]->setString((ss13.str().c_str()));

            ss14 << std::fixed << std::setprecision(2) << particleSystem->getStartColorVar().b;
            labelArrayVisual[18]->setString((ss14.str().c_str()));

            ss15 << std::fixed << std::setprecision(2) << particleSystem->getStartColorVar().a;
            labelArrayVisual[19]->setString((ss15.str().c_str()));

            //End Color Var
            ss16 << std::fixed << std::setprecision(2) << particleSystem->getEndColorVar().r;
            labelArrayVisual[20]->setString((ss16.str().c_str()));

            ss17 << std::fixed << std::setprecision(2) << particleSystem->getEndColorVar().g;
            labelArrayVisual[21]->setString((ss17.str().c_str()));

            ss18 << std::fixed << std::setprecision(2) << particleSystem->getEndColorVar().b;
            labelArrayVisual[22]->setString((ss18.str().c_str()));

            ss19 << std::fixed << std::setprecision(2) << particleSystem->getEndColorVar().a;
            labelArrayVisual[23]->setString((ss19.str().c_str()));
            
        }
    }
    else if (!startRadIsActive2 && !endRadIsActive2 && !posVarIsActive2 && !speedIsActive && !gravityIsActive2 && !angleIsActive && type == ui::Slider::EventType::ON_SLIDEBALL_UP && !infoPopupNode->getParent()&& onTabNum == 0) {
        switch (modifyerNumber)
        {
        case 1:
            if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                this->removeChild(drawLineGravity);
                this->removeChild(drawLineSpeed);
                this->removeChild(drawCircleStartRadius);
                this->removeChild(drawCircleEndRadius);
                this->removeChild(drawCircleAngleReal);
            }
            else {
                this->removeChild(drawLineGravity);
                this->removeChild(drawLinePosVar);
                this->removeChild(drawLineSpeed);
                this->removeChild(drawCircleEndRadius);
                this->removeChild(drawCircleAngleReal);
            }
            break;
        case 2:

            if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                this->removeChild(drawLinePosVar);
                this->removeChild(drawLineSpeed);
                this->removeChild(drawCircleStartRadius);
                this->removeChild(drawCircleEndRadius);
                this->removeChild(drawCircleAngleReal);
            }
            else {
                this->removeChild(drawLineGravity);
                this->removeChild(drawLinePosVar);
                this->removeChild(drawLineSpeed);
                this->removeChild(drawCircleStartRadius);
                this->removeChild(drawCircleAngleReal);
            }
            break;
        case 3:
            if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {
                this->removeChild(drawLineGravity);
                this->removeChild(drawLinePosVar);
                this->removeChild(drawCircleStartRadius);
                this->removeChild(drawCircleEndRadius);
            }
            break;
        default:
            this->removeChild(drawLineGravity);
            this->removeChild(drawLinePosVar);
            this->removeChild(drawLineSpeed);
            this->removeChild(drawCircleStartRadius);
            this->removeChild(drawCircleEndRadius);
            this->removeChild(drawCircleAngleReal);
            break;
        }
    }
}
bool HelloWorld::quitFunction(Ref* sender, ui::Widget::TouchEventType type)
{

    if (!infoPopupNode->getParent()) {

        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            restOfButtons[7]->stopAllActions();
            restOfButtons[7]->runAction(EaseBounceOut::create(ScaleTo::create(0.25, 0.21 * 1.25)));
            break;
        case ui::Widget::TouchEventType::ENDED:
            restOfButtons[7]->stopAllActions();
            restOfButtons[7]->runAction(EaseBounceOut::create(ScaleTo::create(0.01, 0.21)));

            //Close the cocos2d-x game scene and quit the application
            Director::getInstance()->end();
            break;
        case ui::Widget::TouchEventType::CANCELED:
            restOfButtons[7]->stopAllActions();
            restOfButtons[7]->runAction(EaseBounceOut::create(ScaleTo::create(0.34, 0.21)));
            break;
        default:
            break;
        }
        /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

        //EventCustom customEndEvent("game_scene_close_event");
        //_eventDispatcher->dispatchEvent(&customEndEvent);
    }
    return false;
}
void HelloWorld::drawLines(int buttonNumber) {
    
    switch (buttonNumber)
    {
    case 1: //PosVar

        if (drawLinePosVar) {
            removeChild(drawLinePosVar);
        }
        drawLinePosVar = DrawNode::create();
        drawLinePosVar->drawRect(Vec2(((particleSystem->getPosition().x - particleSystem->getPosVar().x * 2)),
            (particleSystem->getPosition().y - particleSystem->getPosVar().y * 2)),
            particleSystem->getPosition() * 2 - Vec2(((particleSystem->getPosition().x - particleSystem->getPosVar().x * 2)),
                ((particleSystem->getPosition().y - particleSystem->getPosVar().y * 2))),
            Color4F(0, 1, 0, 1));
        this->addChild(drawLinePosVar, 29);
        drawLinePosVar->setLineWidth(1.0f);
        break;
    case 2: //Gravity

        if (drawLineGravity)
        {
            //Change line end position
            removeChild(drawLineGravity);
        }
        drawLineGravity = DrawNode::create();
        drawLineGravity->drawLine(Vec2((particleSystem->getGravity().x / 3) + particleSystem->getPosition().x
            , (particleSystem->getGravity().y / 3) + particleSystem->getPosition().y),
            particleSystem->getPosition(),
            Color4F(0, 1, 1, 1));
        this->addChild(drawLineGravity,29);
        drawLineGravity->setLineWidth(1.0f);
        break;
    case 3: //Speed/Angle

        drawCircleAngleReal->setPosition(particleSystem->getPosition());
        if (particleSystem->getEmitterMode() == ParticleSystem::Mode::GRAVITY) {

            if (!drawCircleAngleReal->getParent()) {
                this->addChild(drawCircleAngleReal, 29);
            }

            //Make the line longer/shorter depending on moving the (Speed) slider to right/left
            if (drawLineSpeed)
            {
                removeChild(drawLineSpeed);
            }
            drawLineSpeed = DrawNode::create(); //xD
            drawLineSpeed->drawLine(Vec2(particleSystem->getPosition().x + ((::cos((particleSystem->getAngle()) * M_PI / 180)) * particleSystem->getSpeed()) /*x*/,
                particleSystem->getPosition().y + (::sin((particleSystem->getAngle()) * M_PI / 180)) * particleSystem->getSpeed()) /*y*/,
                particleSystem->getPosition(),
                Color4F(1, 1, 0.65, 1));
            this->addChild(drawLineSpeed, 29);
            drawLineSpeed->setLineWidth(1.0f);
        }
        break;
    case 4: //Start Radius

        if (drawCircleStartRadius)
        {
            removeChild(drawCircleStartRadius);
        }
        drawCircleStartRadius = DrawNode::create();

        //TODO = only segment
        drawCircleStartRadius->drawCircle(particleSystem->getPosition(),
            particleSystem->getStartRadius() * 2,
            particleSystem->getStartRadius(),
            130,
            false,
            Color4F(0, 1, 0, 1));

        this->addChild(drawCircleStartRadius, 29);
        drawCircleStartRadius->setLineWidth(0.60f);
        break;
    case 5: //End Radius

        if (drawCircleEndRadius)
        {
            removeChild(drawCircleEndRadius);
        }
        drawCircleEndRadius = DrawNode::create();

        //TODO = only segment
        drawCircleEndRadius->drawCircle(particleSystem->getPosition(),
            particleSystem->getEndRadius() * 2,
            0,
            130,
            false,
            Color4F(0, 1, 1, 1));

        this->addChild(drawCircleEndRadius, 29);
        drawCircleEndRadius->setLineWidth(1.0f);
        break;
    default:
        break;
    }
}
void update(float dt)
{
    //  CCLOG("this is being called every frame, no matter the replaced scene");
}
