//
// Created by Seif Mahdy on 24/05/2023.
//

#include "Brick.h"


void Brick::initiate()
{
    brikk.setFillColor(sf::Color::White);
}
void Brick::setSize(float width, float height)
{
    brikk.setSize(sf::Vector2f(width, height));
    brikk.setOrigin(brikk.getSize() / 2.f);
}
void Brick::setPosition(float x, float y)
{
    brikk.setPosition(sf::Vector2f(x, y));
}
bool Brick::hit()
{
    health--;
    if (health == 0)
    {
        enable = false;
        return true;
    }
    else
    {
        return false;
    }

}
