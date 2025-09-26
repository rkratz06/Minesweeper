//
// Created by rakra on 11/24/2024.
//

#include "GameState.h"
#include <fstream>
#include <string>
#include <iostream>

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    numberOfMines = _numberOfMines;
    tilesLeft = _dimensions.x * _dimensions.y;
    int counter = 0;
    mines = std::vector<std::vector<bool>>(dimensions.x, std::vector<bool>(dimensions.y, false));
    srand(time(nullptr));
    while (counter < _numberOfMines) {
        int positionx = rand() % _dimensions.x;
        int positiony = rand() % _dimensions.y;
        if (mines[positionx][positiony] == false) {
            mines[positionx][positiony] = true;
            counter++;
        }
    }
    for (int i = 0; i < dimensions.x; i++) {
        std::vector<Tile*> tempTiles(dimensions.x);
        for (int j = 0; j < dimensions.y; j++) {
            sf::Vector2f pos = sf::Vector2f(i * 32, j * 32);
            tempTiles[j] = new Tile(pos);
            tempTiles[j]->isMine = mines[i][j];
        }
        tiles.push_back(tempTiles);
    }
    status = PLAYING;
}
GameState::GameState(const char* filepath) {
    numberOfMines = 0;
    std::ifstream file(filepath);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::vector<bool> temp(line.length());
            for (int i =0; i < line.size(); i++) {
                if (line[i] == '1') {
                    temp[i] = true;
                    numberOfMines++;
                }
                else {
                    temp[i] = false;
                }
            }
            mines.push_back(temp);
        }
    }
    file.close();
    dimensions = sf::Vector2i(mines[0].size(), mines.size());
    tilesLeft = dimensions.x * dimensions.y;
    for (int i = 0; i < dimensions.x; i++) {
        std::vector<Tile*> tempTiles(dimensions.x);
        for (int j = 0; j < dimensions.y; j++) {
            sf::Vector2f pos = sf::Vector2f(i * 32, j * 32);
            tempTiles[j] = new Tile(pos);
            tempTiles[j]->isMine = mines[j][i];
        }
        tiles.push_back(tempTiles);
    }
    status = PLAYING;
}

int GameState::getMineCount() {return numberOfMines;}
int GameState::getFlagCount() {
    int flagCount = 0;
    for (std::vector<Tile*> row : tiles) {
        for (Tile* tile : row) {
            if (tile != nullptr && tile->getState() == Tile::State::FLAGGED) {
                ++flagCount;
            }
        }
    }
    return flagCount;
}
Tile* GameState::getTile(int x, int y) {
    if (x >= dimensions.x || y >= dimensions.y || x < 0 || y < 0) {
        return nullptr;
    }
    return tiles.at(x).at(y);
}
GameState::PlayStatus GameState::getPlayStatus() {return status;}
void GameState::setPlayStatus(PlayStatus _status) {status = _status;}
GameState::~GameState() {
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            delete tiles[i][j];
        }
    }
    tiles.clear();
}