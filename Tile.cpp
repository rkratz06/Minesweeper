//
// Created by rakra on 11/24/2024.
//

#include "Tile.h"
#include "Toolbox.h"

Tile::Tile(sf::Vector2f _position) {
    position = _position;
    state = HIDDEN;
    revealedTexture.loadFromFile("images/tile_revealed.png");
    revealedSprite.setTexture(revealedTexture);
    revealedSprite.setPosition(position.x, position.y);
    hiddenTexture.loadFromFile("images/tile_hidden.png");
    hiddenSprite.setTexture(hiddenTexture);
    hiddenSprite.setPosition(position.x, position.y);
    flagTexture.loadFromFile("images/flag.png");
    flagSprite.setTexture(flagTexture);
    flagSprite.setPosition(position.x, position.y);
    mineTexture.loadFromFile("images/mine.png");
    mineSprite.setTexture(mineTexture);
    mineSprite.setPosition(position.x, position.y);
    num1Texture.loadFromFile("images/number_1.png");
    numberSprites[0].setTexture(num1Texture);
    numberSprites[0].setPosition(position.x, position.y);
    num2Texture.loadFromFile("images/number_2.png");
    numberSprites[1].setTexture(num2Texture);
    numberSprites[1].setPosition(position.x, position.y);
    num3Texture.loadFromFile("images/number_3.png");
    numberSprites[2].setTexture(num3Texture);
    numberSprites[2].setPosition(position.x, position.y);
    num4Texture.loadFromFile("images/number_4.png");
    numberSprites[3].setTexture(num4Texture);
    numberSprites[3].setPosition(position.x, position.y);
    num5Texture.loadFromFile("images/number_5.png");
    numberSprites[4].setTexture(num5Texture);
    numberSprites[4].setPosition(position.x, position.y);
    num6Texture.loadFromFile("images/number_6.png");
    numberSprites[5].setTexture(num6Texture);
    numberSprites[5].setPosition(position.x, position.y);
    num7Texture.loadFromFile("images/number_7.png");
    numberSprites[6].setTexture(num7Texture);
    numberSprites[6].setPosition(position.x, position.y);
    num8Texture.loadFromFile("images/number_8.png");
    numberSprites[7].setTexture(num8Texture);
    numberSprites[7].setPosition(position.x, position.y);
    surroundingMines = 0;
}

sf::Vector2f Tile::getLocation() {return position;}
Tile::State Tile::getState() {return state;}
std::array<Tile*, 8>& Tile::getNeighbors() {
    int tempX = static_cast<int>(position.x/32);
    int tempY = static_cast<int>(position.y/32);
    neighbors = {Toolbox::getInstance().gameState->getTile(tempX - 1,tempY - 1), Toolbox::getInstance().gameState->getTile(tempX,tempY - 1), Toolbox::getInstance().gameState->getTile(tempX + 1,tempY - 1), Toolbox::getInstance().gameState->getTile(tempX - 1,tempY),
    Toolbox::getInstance().gameState->getTile(tempX + 1,tempY), Toolbox::getInstance().gameState->getTile(tempX - 1,tempY + 1), Toolbox::getInstance().gameState->getTile(tempX,tempY + 1), Toolbox::getInstance().gameState->getTile(tempX + 1,tempY + 1)};
    surroundingMines = 0;
    for (auto neighbor : neighbors) {
        if (neighbor != nullptr && neighbor->isMine) {
            surroundingMines++;
        }
    }
    return neighbors;
}
void Tile::setState(State _state) {
    state = _state;
}
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    neighbors = _neighbors;
}
void Tile::onClickLeft() {
    if (state == FLAGGED) {
        return;
    }
    if (state == HIDDEN) {
        if (isMine) {
            state = EXPLODED;
            Toolbox::getInstance().gameState->setPlayStatus(GameState::PlayStatus::LOSS);
        }
        //else set state to revealed, cascade surrounding tiles or place number on top
        else {
            if (surroundingMines == 0) {
                revealNeighbors();
            }
            else {
                state = REVEALED;
                Toolbox::getInstance().gameState->tilesLeft--;
            }
            if (Toolbox::getInstance().gameState->tilesLeft == Toolbox::getInstance().gameState->getMineCount()) {
                Toolbox::getInstance().gameState->setPlayStatus(GameState::PlayStatus::WIN);
            }
        }
    }
}
void Tile::onClickRight() {
    if (state == FLAGGED) {
        state = HIDDEN;
    }
    else if (state == HIDDEN) {
        state = FLAGGED;
    }
}
void Tile::draw() {
    if (Toolbox::getInstance().debugMode && isMine == true) {
        Toolbox::getInstance().window.draw(hiddenSprite);
        Toolbox::getInstance().window.draw(mineSprite);
    }
    else if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::PlayStatus::LOSS && isMine == true) {
        Toolbox::getInstance().window.draw(hiddenSprite);
        Toolbox::getInstance().window.draw(mineSprite);
    }
    else if (state == HIDDEN) {
        Toolbox::getInstance().window.draw(hiddenSprite);
    }
    else if (state == REVEALED) {
        Toolbox::getInstance().window.draw(revealedSprite);
        if (surroundingMines > 0) {
            Toolbox::getInstance().window.draw(numberSprites[surroundingMines - 1]);
        }
    }
    else if (state == FLAGGED) {
        Toolbox::getInstance().window.draw(hiddenSprite);
        Toolbox::getInstance().window.draw(flagSprite);
    }
    else if (state == EXPLODED) {
        Toolbox::getInstance().window.draw(revealedSprite);
        Toolbox::getInstance().window.draw(mineSprite);
    }
}
void Tile::revealNeighbors() {
    getNeighbors();
    if (state == REVEALED || state == FLAGGED) {
        return;
    }
    if (surroundingMines > 0 && !isMine) {
        state = REVEALED;
        Toolbox::getInstance().gameState->tilesLeft--;
        return;
    }
    state = REVEALED;
    Toolbox::getInstance().gameState->tilesLeft--;
    for (auto neighbor : neighbors) {
        if (neighbor != nullptr && neighbor->state == HIDDEN) {
            neighbor->revealNeighbors();
        }
    }
}
Tile::~Tile() {}