#include "snakemain.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameWindows.h"
using namespace sf;
using namespace std;
#define side 15
#define size 250.6
const int grid_sizeX = 800;
const int grid_sizeY = 600;

SNAKEPART Game::insertHead(SNAKEPART head, sf::Sprite* sprite) {
    SNAKEPART temp;
    temp = new snakePart; //allocate memory for new node before inserting it in tail
    switch (head->direction) { //cases to insert the snake tail part based on the direction and position of the head
        case direction(north):
            temp->posY = head->posY - side * 2;
            temp->posX = head->posX;
            break;
        case direction(south):
            temp->posY = head->posY + side * 2;
            temp->posX = head->posX;
            break;
        case direction(west):
            temp->posX = head->posX - side * 2;
            temp->posY = head->posY;
            break;
        case direction(east):
            temp->posX = head->posX + side * 2;
            temp->posY = head->posY;
            break;
    }
    temp->direction = head->direction;
    temp->s = sprite;
    temp->rightLink = head;
    head->leftLink = temp;
    return temp;
}

SNAKEPART Game::deleteTail(SNAKEPART tail) { // updates the value of previous tail part and deletes the old node to make snake look like its moving, but its actually not hehehe :))
    SNAKEPART temp;
    temp = tail->leftLink;
    temp->rightLink = 0;
    delete tail;
    tail = 0;
    return temp; //temp is the new tail node in question :>
}
void Game::updateGame() {
    if (head->posX > grid_sizeX) {
        head->posX = 0;
    }
    if (head->posX < 0) {
        head->posX = grid_sizeX;
    }
    if (head->posY > grid_sizeY) {
        head->posY = 0;
    }
    if (head->posY < 0) {
        head->posY = grid_sizeY;
    }
    headTouchedFood();
    head = insertHead(head, &snakeSprite);
    tail = deleteTail(tail);
    checkCollision(head, &gameWindow);
    count = 0;
}
void Game::startGame() {
    loadSprite();
    loadSound();
    head = new snakePart;
    head->posX = 0;
    head->posY = 0;
    head->direction = east;
    head->s = &snakeSprite;
    head->leftLink = head->rightLink = 0;
    tail = head;
    food.setPosition(head->posX, head->posY);
    Score.setPosition(720, 20);
    Score.setString(String(to_string(gameScore.getScore())));
    gameWindow.create((sf::VideoMode(grid_sizeX, grid_sizeY)), "Snake", sf::Style::Titlebar | sf::Style::Close);
}
void Game::runGame() {
    startGame();
    while (gameWindow.isOpen()) {
        renderGame();
        processEvents();

        if (count == speed) {
            updateGame();

        }
        count++;
    }
}
void Game::renderGame() {
    gameWindow.clear();
    gameWindow.draw(BackGround);
    gameWindow.draw(Score);
    setHeadSprite(head, &snakeSprite);
    current = head;
    while (current != 0) {
        if (current != head) {
            setTailSprite(current, &snakeSprite);
        }
        (*current->s).setPosition(current->posX, current->posY);
        gameWindow.draw(*current->s);
        current = current->rightLink;
    }
    gameWindow.draw(food);
    gameWindow.display();
}
void Game::loadSprite() {
    this->spriteSheet.loadFromFile("/Users/seifmahdy/CLionProjects/untitled8/snakeSprite.png");
    snakeSprite.setTexture(spriteSheet);
    snakeSprite.setScale(sf::Vector2f(0.25, 0.25));
    snakeSprite.setOrigin(104.5, 104.5);
    food.setTexture(spriteSheet);
    food.setTextureRect(IntRect(size *4.2, size * 1.3, size*1.4, size));
    food.setScale(0.25, 0.25);
    food.setOrigin(104.5, 104.5);
    scoreFont.loadFromFile("/Users/seifmahdy/CLionProjects/untitled8/16020_FUTURAM.ttf");
    Score.setFont(scoreFont);
    Score.setFillColor(Color::White);
    this->gameBackGround.loadFromFile("/Users/seifmahdy/CLionProjects/untitled8/grass.jpg");
    BackGround.setTexture(gameBackGround);
    BackGround.setScale(1.2, 1.2);
}
void Game::loadSound() {
    this->soundBuffer.loadFromFile("/Users/seifmahdy/CLionProjects/untitled8/food_G1U6tlb.wav");
    sound.setBuffer(soundBuffer);
}
void Game::setHeadSprite(SNAKEPART head, sf::Sprite* sp) {
    switch (head->direction) {
        case north:sp->setTextureRect(IntRect(size * 1.6, size * 0.25, size, size));
            head->s = sp; break;
        case south: sp->setTextureRect(IntRect(size * 0, size * 0, size, size));
            head->s = sp; break;
        case west: sp->setTextureRect(IntRect(size * 4.2, size * 0, size*1.4, size));
            head->s = sp; break;
        case east: sp->setTextureRect(IntRect(size * 2.25, size * 0, size*1.45, size));
            head->s = sp; break;
    }
}
void Game::setTailSprite(SNAKEPART node, sf::Sprite* sp) {
    switch (node->direction) {
        case north:sp->setTextureRect(IntRect(size * 2.767, size * 1.35, size , size));
            node->s = sp; break;
        case south: sp->setTextureRect(IntRect(size * 1.465, size * 1.4, size*0.73, size*0.96));
            node->s = sp; break;
        case west: sp->setTextureRect(IntRect(size * 0, size * 1.43, size, size));
            node->s = sp; break;
        case east: sp->setTextureRect(IntRect(size * 0, size * 1.43, size, size));
            node->s = sp; break;
    }
}
void Game::processEvents() {
    if (gameWindow.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:gameWindow.close();
            break;
            case Event::KeyPressed: {
                if (event.key.code == Keyboard::W && head->direction != south) {
                    head->direction = north; //These if conditions are basically to see if input is in reverse to the head's direction of movement it will not change the direction of the head then because it will then collide with the tail behind it
                }
                else if (event.key.code == Keyboard::S && head->direction != north) {
                    head->direction = south;
                }
                else if (event.key.code == Keyboard::A && head->direction != east) {
                    head->direction = west;
                }
                else if (event.key.code == Keyboard::D && head->direction != west) {
                    head->direction = east;
                }
                else if (event.key.code == Keyboard::Up && head->direction != south) {
                    head->direction = north;
                }
                else if (event.key.code == Keyboard::Down && head->direction != north) {
                    head->direction = south;
                }
                else if (event.key.code == Keyboard::Left && head->direction != east) {
                    head->direction = west;
                }
                else if (event.key.code == Keyboard::Right && head->direction != west) {
                    head->direction = east;
                }
                break;
            }
        }
    }
}

Vector2f Game::getFoodCoords() {
    return Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}
bool Game::foodIsTouched(SNAKEPART head, sf::Sprite* food) {
    return Vector2f(head->posX, head->posY) == food->getPosition();
}
void Game::headTouchedFood() {
    if (foodIsTouched(head, &food)) {
        head = insertHead(head, &snakeSprite);
        speed-=10;
        gameScore.addScore();
        sound.play();
        Score.setString(String(to_string(gameScore.getScore())));
        while (1) {
            foodPos = getFoodCoords();
            current = head;
            while (current != 0) {
                if (current->posX == foodPos.x && current->posY == foodPos.y) {
                    break;
                }
                current = current->rightLink;
            }
            if (current == 0)
                break;
        }
        food.setPosition(getFoodCoords());
    }
}
void Game::checkCollision(SNAKEPART head, RenderWindow* gameWindow) {
    SNAKEPART current = head->rightLink;
    while (current != 0) {
        if (head->posX == current->posX && head->posY == current->posY) {
            gameWindow->close();
        }
        current = current->rightLink;
    }
}