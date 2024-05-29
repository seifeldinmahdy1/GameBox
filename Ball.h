//
// Created by Seif Mahdy on 24/05/2023.
//

#ifndef GAMEBOX_BALL_H
#define GAMEBOX_BALL_H
#include "SFML/Graphics.hpp"
class Ball
{
public:
    float speed = 500.f;
    float angle;
    sf::CircleShape ball;
    void initiate();
    void setSize(float radius);
    void setPosition(float x, float y);
};

#endif //GAMEBOX_BALL_H
