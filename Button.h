//
// Created by rakra on 11/24/2024.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <functional>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick() { func();} //calls private func on initialization, func in parameter
    ~Button();
private:
    sf::Vector2f position;
    sf::Sprite *sprite;
    std::function<void(void)> func; //private function wrapper
};


#endif //BUTTON_H
