
#include "Paddle.h"

void Paddle::initiate()
{
    paddl .setFillColor(sf::Color::White);
}
void Paddle::setSize(float width, float height)
{
    paddl.setSize(sf::Vector2f(width, height));
    paddl.setOrigin(paddl.getSize() / 2.f);
}
void Paddle::setPosition(float x, float y)
{
    paddl.setPosition(sf::Vector2f(x, y));
}
