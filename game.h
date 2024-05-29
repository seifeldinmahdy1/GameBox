#ifndef GAMEBOX_GAME_H
#define GAMEBOX_GAME_H
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

using namespace std;
class ScoreSnake {
    int score = -10;
public:
    void addScore() {
        score += 10;
    }
    int getScore() {
        return score;
    }
};

class snakePart {
public:
    int posX;
    int posY;
    int direction;
    sf::Sprite* s; //this is how the snake looks
    class snakePart* leftLink; //this is implementation of the linked list data structure
    class snakePart* rightLink;
};
typedef class snakePart* SNAKEPART;
enum direction {
    north, south, west, east
};
//this is to set each of the directions with a number so we can then put it in the class snakePart in the part called direction
// where north=0, south =1, west =2, east =3
class Game {
private:

    int speed = 400; //to call the updateGame function after 400 while loop iterations so the animation isnt very fast
    int count = 0; //count is used to check if we reached the speed
    ScoreSnake gameScore;
    SNAKEPART head, tail, current;
    sf::RenderWindow gameWindow;
    sf::Sprite snakeSprite; //snake sprite
    sf::Texture spriteSheet; //sprite sheet
    sf::Vector2f foodPos;
    sf::Sprite food;
    sf::Event event;
    sf::Text Score;
    sf::Font scoreFont;
    sf::Texture gameBackGround;
    sf::Sprite BackGround;
    sf::Vector2f getFoodCoords();
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
    void updateGame();
    void renderGame();
    void startGame();
    void loadSprite();
    void loadSound();
    SNAKEPART insertHead(SNAKEPART head, sf::Sprite* sprite); //function to insert the head to make it as if the snake is moving
    SNAKEPART deleteTail(SNAKEPART tail); //function to delete the tail after inserting the new tail to make the snake "move"
    void processEvents(); //function to process any event such as input
    void setTailSprite(SNAKEPART head, sf::Sprite* sp);
    void setHeadSprite(SNAKEPART node, sf::Sprite* sp);
    void headTouchedFood();
    bool foodIsTouched(SNAKEPART head, sf:: Sprite* food);
    void checkCollision(SNAKEPART head, sf::RenderWindow* gameWindow);
public:
    void runGame();//the function that runs the game
};
#endif //GAMEBOX_GAME_H
