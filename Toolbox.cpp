//
// Created by rakra on 11/24/2024.
//

#include "Toolbox.h"
#include "minesweeper.h"
#include <iostream>

Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}
Toolbox::Toolbox() {
    //constructor, creates 800x600 window, gameState object, creates buttons
    gameState = new GameState();
    window.create(sf::VideoMode(800, 600), "Minesweeper");
    debugButton = new Button(sf::Vector2f(496, 512), []{ toggleDebugMode(); } );
    newGameButton = new Button(sf::Vector2f(368, 512), []{ restart(); });
    testButton1 = new Button(sf::Vector2f(560, 512), [this] {
        if (gameState != nullptr) {
            delete gameState;
        }
        gameState = new GameState("boards/testboard1.brd");
    });
    testButton2 =  new Button(sf::Vector2f(624, 512), [this] {
        if (gameState != nullptr) {
            delete gameState;
        }
        gameState = new GameState("boards/testboard2.brd");
    });
    debugTexture.loadFromFile("images/debug.png");
    debugSprite = sf::Sprite(debugTexture);
    debugButton->setSprite(&debugSprite);
    newGameTexture.loadFromFile("images/face_happy.png");
    newGameSprite = sf::Sprite(newGameTexture);
    newGameButton->setSprite(&newGameSprite);
    test1Texture.loadFromFile("images/test_1.png");
    test1Sprite = sf::Sprite(test1Texture);
    testButton1->setSprite(&test1Sprite);
    test2Texture.loadFromFile("images/test_2.png");
    test2Sprite = sf::Sprite(test2Texture);
    testButton2->setSprite(&test2Sprite);
    debugMode = false;
}