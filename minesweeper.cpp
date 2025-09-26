#include "minesweeper.h"
#include <iostream>
#include "Toolbox.h"
#include "Tile.h"

void restart() {
    delete Toolbox::getInstance().gameState;
    Toolbox::getInstance().gameState = new GameState();
}

void render() {
    Toolbox::getInstance().window.clear(sf::Color::White);
    Toolbox::getInstance().window.draw(*Toolbox::getInstance().debugButton->getSprite());
    Toolbox::getInstance().window.draw(*Toolbox::getInstance().testButton1->getSprite());
    Toolbox::getInstance().window.draw(*Toolbox::getInstance().testButton2->getSprite());

    int row = 0;
    int col = 0;
    while (true) {
        Tile* tempTile = Toolbox::getInstance().gameState->getTile(col, row);
        if (tempTile == nullptr) {
            break;
        }
        tempTile->draw();
        row++;
        if (Toolbox::getInstance().gameState->getTile(col, row) == nullptr) {
            col++;
            row = 0;
        }
    }

    signed int counter = Toolbox::getInstance().gameState->getMineCount() - Toolbox::getInstance().gameState->getFlagCount();
    sf::Texture digits;
    digits.loadFromFile("images/digits.png");
    std::vector<sf::Sprite> digitSprites(11);
    for (int i = 0; i < 11; i++) {
        digitSprites[i].setTexture(digits);
        digitSprites[i].setTextureRect(sf::IntRect(i*21, 0, 21, 32));
    }
    sf::Sprite hundredsDigit, tensDigit, onesDigit;
    int hundreds;
    if (counter < 0) {
        hundreds = 10;
        counter *= -1;
    }
    else {
        hundreds = counter / 100;
    }
    int tens = (counter % 100) / 10;
    int ones = counter % 10;
    hundredsDigit = digitSprites[hundreds];
    tensDigit = digitSprites[tens];
    onesDigit = digitSprites[ones];
    hundredsDigit.setPosition(sf::Vector2f(0, 512));
    tensDigit.setPosition(sf::Vector2f(21, 512));
    onesDigit.setPosition(sf::Vector2f(42, 512));
    Toolbox::getInstance().window.draw(hundredsDigit);
    Toolbox::getInstance().window.draw(tensDigit);
    Toolbox::getInstance().window.draw(onesDigit);
    if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::PlayStatus::PLAYING) {
        Toolbox::getInstance().window.draw(*Toolbox::getInstance().newGameButton->getSprite());
    }
    else if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::PlayStatus::WIN) {
        sf::Sprite winSprite;
        sf::Texture winTexture;
        winTexture.loadFromFile("images/face_win.png");
        winSprite = sf::Sprite(winTexture);
        winSprite.setPosition(sf::Vector2f(368, 512));
        Toolbox::getInstance().window.draw(winSprite);
    }
    else if (Toolbox::getInstance().gameState->getPlayStatus() == GameState::PlayStatus::LOSS) {
        sf::Sprite lossSprite;
        sf::Texture lossTexture;
        lossTexture.loadFromFile("images/face_lose.png");
        lossSprite = sf::Sprite(lossTexture);
        lossSprite.setPosition(sf::Vector2f(368, 512));
        Toolbox::getInstance().window.draw(lossSprite);
    }
    Toolbox::getInstance().window.display();
}

int launch() {
    Toolbox::getInstance();
    while (Toolbox::getInstance().window.isOpen()) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(Toolbox::getInstance().window);
        sf::Event event;
        while (Toolbox::getInstance().window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    Toolbox::getInstance().window.close();
                    break;
                case sf::Event::MouseButtonPressed:{
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //left click
                        if (mousePosition.x/32 < 25 && mousePosition.y/32 < 16 && mousePosition.x/32 >= 0 && mousePosition.y/32 >= 0 && Toolbox::getInstance().gameState->getPlayStatus() == GameState::PlayStatus::PLAYING) {
                            Toolbox::getInstance().gameState->getTile(mousePosition.x/32, mousePosition.y/32)->onClickLeft();
                        }
                        if (mousePosition.x >= Toolbox::getInstance().newGameButton->getSprite()->getPosition().x && mousePosition.x <= Toolbox::getInstance().newGameButton->getSprite()->getPosition().x + 64
                            && mousePosition.y >= Toolbox::getInstance().newGameButton->getSprite()->getPosition().y && mousePosition.y <= Toolbox::getInstance().newGameButton->getSprite()->getPosition().y + 64) {
                            Toolbox::getInstance().newGameButton->onClick();
                        }
                        if (mousePosition.x >= Toolbox::getInstance().debugButton->getSprite()->getPosition().x && mousePosition.x <= Toolbox::getInstance().debugButton->getSprite()->getPosition().x + 64
                            && mousePosition.y >= Toolbox::getInstance().debugButton->getSprite()->getPosition().y && mousePosition.y <= Toolbox::getInstance().debugButton->getSprite()->getPosition().y + 64) {
                            Toolbox::getInstance().debugButton->onClick();
                        }
                        if (mousePosition.x >= Toolbox::getInstance().testButton1->getSprite()->getPosition().x && mousePosition.x <= Toolbox::getInstance().testButton1->getSprite()->getPosition().x + 64
                            && mousePosition.y >= Toolbox::getInstance().testButton1->getSprite()->getPosition().y && mousePosition.y <= Toolbox::getInstance().testButton1->getSprite()->getPosition().y + 64) {
                            Toolbox::getInstance().testButton1->onClick();
                        }
                        if (mousePosition.x >= Toolbox::getInstance().testButton2->getSprite()->getPosition().x && mousePosition.x <= Toolbox::getInstance().testButton2->getSprite()->getPosition().x + 64
                            && mousePosition.y >= Toolbox::getInstance().testButton2->getSprite()->getPosition().y && mousePosition.y <= Toolbox::getInstance().testButton2->getSprite()->getPosition().y + 64) {
                            Toolbox::getInstance().testButton2->onClick();
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        //right click
                        if (mousePosition.x/32 < 25 && mousePosition.y/32 < 16 && mousePosition.x/32 >= 0 && mousePosition.y/32 >= 0 && Toolbox::getInstance().gameState->getPlayStatus() == GameState::PlayStatus::PLAYING) {
                            Toolbox::getInstance().gameState->getTile(mousePosition.x/32, mousePosition.y/32)->onClickRight();
                        }
                    }
                }
                default:
                    break;
            }
            if (event.type == sf::Event::Closed) {
                Toolbox::getInstance().window.close();
            }
        }
        render();
    }
    return 0;
}

int main() { return launch(); }