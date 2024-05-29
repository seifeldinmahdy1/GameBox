//
// Created by Seif Mahdy on 24/05/2023.
//

#ifndef GAMEBOX_PADDLE_H
#define GAMEBOX_PADDLE_H
#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:
	float speed = 1000.f;
	sf::RectangleShape paddl;
	void initiate();
	void setSize(float width, float height);
	void setPosition(float x, float y);
};


#endif //GAMEBOX_PADDLE_H
