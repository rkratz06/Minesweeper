//
// Created by rakra on 11/24/2024.
//

#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) : position(_position), func(_onClick), sprite(nullptr) {} //constructor
sf::Vector2f Button::getPosition(){ return position; }
sf::Sprite* Button::getSprite(){ return sprite;}
void Button::setSprite(sf::Sprite* _sprite) {
    sprite = _sprite;
    sprite->setPosition(position);
}
Button::~Button() {}