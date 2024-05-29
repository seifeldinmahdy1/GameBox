//
// Created by Seif Mahdy on 24/05/2023.
//

#ifndef GAMEBOX_BRICK_H
#define GAMEBOX_BRICK_H
#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
public:
    bool enable = true;
    bool moveLeft = true;

    int health = 1;
    float speed = 0;
    sf::RectangleShape brikk;
    void initiate();
    void setSize(float width, float height);
    void setPosition(float x, float y);
    virtual bool hit();
};



#endif //GAMEBOX_BRICK_H
