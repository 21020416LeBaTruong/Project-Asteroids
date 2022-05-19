#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

class boardScore{
public:
    boardScore(float w, float h);
    ~boardScore();
    void draw(RenderWindow& window);
private:
    Font font, font2;
    Text board[6];
};


