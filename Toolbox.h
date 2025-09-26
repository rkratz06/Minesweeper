//
// Created by rakra on 11/24/2024.
//

#ifndef TOOLBOX_H
#define TOOLBOX_H
#include "Button.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

class GameState;

class Toolbox {
public:
    sf::RenderWindow window; // SFML application window
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets / starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    static Toolbox& getInstance();
    GameState* gameState; // Primary game state representation
    bool debugMode; //public for now idk if i can keep public

private:
    Toolbox();
    sf::Texture debugTexture, newGameTexture, test1Texture, test2Texture;
    sf::Sprite debugSprite, newGameSprite, test1Sprite, test2Sprite;
    Toolbox(Toolbox const&) = delete;
    Toolbox& operator=(Toolbox const&) = delete;
};



#endif //TOOLBOX_H
