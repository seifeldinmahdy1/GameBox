//
// Created by Seif Mahdy on 24/05/2023.
//

#include "Ball.h"
#pragma once
#include <SFML/Graphics.hpp>

void Ball::initiate()
{
    ball.setFillColor(sf::Color::Green);
}
void Ball::setSize(float radius)
{
    ball.setRadius(radius);
    ball.setOrigin(radius / 2.f, radius / 2.f);
}
void Ball::setPosition(float x, float y)
{
    ball.setPosition(sf::Vector2f(x, y));
}
