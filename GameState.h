//
// Created by rakra on 11/24/2024.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class Tile;

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    ~GameState();
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
private:
    sf::Vector2i dimensions;
    int numberOfMines;
    int tilesLeft;
    PlayStatus status;
    std::vector<std::vector<Tile*>> tiles;
    std::vector<std::vector<bool>> mines;
    friend class Tile;
};



#endif //GAMESTATE_H
