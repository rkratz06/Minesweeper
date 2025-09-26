//
// Created by rakra on 11/24/2024.
//

#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "Toolbox.h"

class Tile {
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f _position);
    ~Tile();
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
protected:
    void revealNeighbors();
private:
    std::array<Tile*, 8> neighbors;
    sf::Vector2f position;
    State state;
    sf::Texture revealedTexture, hiddenTexture, flagTexture, mineTexture, num1Texture, num2Texture, num3Texture, num4Texture, num5Texture, num6Texture, num7Texture, num8Texture;
    sf::Sprite revealedSprite, hiddenSprite, flagSprite, mineSprite;
    sf::Sprite numberSprites[8];
    bool isMine;
    int surroundingMines;
    friend class GameState;
};



#endif //TILE_H
