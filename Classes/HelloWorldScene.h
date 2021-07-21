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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;



class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    cocos2d::EventListenerTouchOneByOne* listenerForGravityLine = EventListenerTouchOneByOne::create();
    cocos2d::EventListenerTouchOneByOne* listenerForPosVarLine = EventListenerTouchOneByOne::create();
    cocos2d::EventListenerTouchOneByOne* listenerForSpeedAngleLine = EventListenerTouchOneByOne::create();
    cocos2d::EventListenerTouchOneByOne* listenerForStartRadiusLine = EventListenerTouchOneByOne::create();
    cocos2d::EventListenerTouchOneByOne* listenerForEndRadiusLine = EventListenerTouchOneByOne::create();

    cocos2d::EventListenerTouchOneByOne* moveParticleListener = EventListenerTouchOneByOne::create();

    cocos2d::ClippingRectangleNode* clipper = ClippingRectangleNode::create();


    cocos2d::Sprite* blackBackgroundHelpPopup = Sprite::create("U5ntitled.png");
    cocos2d::Sprite* blackBackgroundInfoCheckboxesPopup = Sprite::create("U5ntitled.png");



    cocos2d::Label* infoCheckboxesTitle = Label::createWithBMFont("goldFont-uhd.fnt", "Info"); // info string
    cocos2d::Label* infoCheckBoxesString = Label::createWithBMFont("chatFont-uhd.fnt", "Thats an easter egg that you will never find.", TextHAlignment::CENTER); // "text de el helpe de checke boxe de info" String

    cocos2d::ParticleSystemQuad* particleSystem = ParticleSystemQuad::create("particle_texture.plist");
    cocos2d::ParticleSystemQuad* particleSystem2 = ParticleSystemQuad::create("particle_texture.plist");
    cocos2d::Sprite* selectTextureBox = Sprite::create("GJ_select_001.png");
    cocos2d::Sprite* particle_popup_texture = Sprite::create("particle_popup_texture.png"); // Brown popup

    cocos2d::Node* tabOneGravity = Node::create();
    cocos2d::Node* tabOneRadius = Node::create();
    cocos2d::Node* tabOne = Node::create();
    std::vector<Node*> tabTextures;
    cocos2d::Node* tabTwo = Node::create();

    cocos2d::Node* tabThree = Node::create();
    cocos2d::Node* infoPopupNode = Node::create();
    cocos2d::Node* infoCheckboxesPopupNode = Node::create();

    cocos2d::Node* popUpNode = Node::create();


    cocos2d::Node* test = Node::create();


    cocos2d::DrawNode* drawLineGravity;
    cocos2d::DrawNode* drawLinePosVar;
    cocos2d::DrawNode* drawLineSpeed;
    cocos2d::DrawNode* drawCircleStartRadius;
    cocos2d::DrawNode* drawCircleAngleReal;
    cocos2d::DrawNode* drawCircleEndRadius;


    ui::Button* infoCheckboxesOkButton = ui::Button::create("ok.png"); //ok button infoCheckbox

    std::vector<Button*> particleSprite;


    std::vector<Sprite*> testingAlign;

    std::vector<ui::Button*> restOfButtons;

    std::vector<ui::Button*> easyModifier;
    std::vector<Label*> easyModifierLabels;

    std::vector<Label*> labelArray;
    std::vector<ui::Slider*> sliderArray;
    std::vector<Sprite*> backgroundLabel;


    std::vector<Label*> labelArrayVisual;
    std::vector<ui::Slider*> sliderArrayVisual;
    std::vector<Sprite*> backgroundALabel;


    std::vector<ui::Button*> checkBoxes;
    std::vector<ui::Button*> checkBoxesInfo;
    std::vector<cocos2d::Label*> checkBoxesLabels;


    std::vector<Sprite*> upperButtons;


    std::vector<ui::Button*> upperButtonsArray;
    std::vector<Label*> buttonLabelArray;

    virtual bool init();
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void easyModify(Ref* sender, ui::Widget::TouchEventType type);
    void sliderEvent(Ref* sender, ui::Slider::EventType type);
    void calcButtonFunc(Ref* sender, ui::Widget::TouchEventType type);
    void reverseColorsButtonFunc(Ref* sender, ui::Widget::TouchEventType type);
    void switchToGravity(Ref* sender, ui::Widget::TouchEventType type);

    void switchParticleType(Ref* sender, ui::Widget::TouchEventType type);

    void checkBox(Ref* sender, ui::Widget::TouchEventType type);

    void upperButtonsFunction(Ref* sender, ui::Widget::TouchEventType type);


    void drawLines(int buttonNumber);

    void closeHelpPopup(Ref* sender, ui::Widget::TouchEventType type);
    void openHelpPopup(Ref* sender, ui::Widget::TouchEventType type);

    void closeInfoCheckboxesPopup(Ref* sender, ui::Widget::TouchEventType type);

    void textures(Ref* sender, ui::Widget::TouchEventType type);

    bool onTouchBeganGravity(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMovedGravity(cocos2d::Touch* touch, cocos2d::Event* event);

    bool onTouchBeganStartRadius(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMovedStartRadius(cocos2d::Touch* touch, cocos2d::Event* event);

    bool onTouchBeganEndRadius(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMovedEndRadius(cocos2d::Touch* touch, cocos2d::Event* event);

    void moveParticle(cocos2d::Touch* touch, cocos2d::Event* event);
    bool beganParticle(cocos2d::Touch* touch, cocos2d::Event* event);


    bool onTouchBeganPosVar(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMovedPosVar(cocos2d::Touch* touch, cocos2d::Event* event);

    void unckeckAll(bool changeButtonColor);
    void popUp(Ref* sender, ui::Widget::TouchEventType type);
    void popDown(Ref* sender, ui::Widget::TouchEventType type);
    void popTense(Ref* sender, ui::Widget::TouchEventType type);


    bool quitFunction(Ref* sender, ui::Widget::TouchEventType type);


    void onTouchMovedSpeedAngle(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onTouchBeganSpeedAngle(cocos2d::Touch* touch, cocos2d::Event* event);


    void createAlignedObject(int howMany, Vec2 scale, float spacing, int layer, bool horizontal,
        Vec2 point, cocos2d::Node* mainNode, std::vector<ui::Button*> button, std::vector<Sprite*> sprite = { Sprite::create("U5ntitled.png") }, std::string spriteName,
        bool differentSprite, Vec2 textureSize);

};

#endif // __HELLOWORLD_SCENE_H__
