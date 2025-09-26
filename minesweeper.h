//
// Created by rakra on 11/24/2024.
//

#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include "Toolbox.h"
int launch();
void restart();
void render();
inline void toggleDebugMode() {Toolbox::getInstance().debugMode = !Toolbox::getInstance().debugMode;}
inline bool getDebugMode() {return Toolbox::getInstance().debugMode;}

#endif //MINESWEEPER_H
