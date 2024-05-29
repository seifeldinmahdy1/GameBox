#include "pongmain.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <math.h>

#include "ScorePong.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

using namespace sf;
using namespace std;

const float pi = 3.14159f;

RenderWindow window;

Font font;
Text lifeText;
Text scoreText;

Clock gameClock;
float deltaTime;

float grid_sizeX = 800;
float grid_sizeY = 800;

bool isPlaying = false;
bool gameover = false;
bool win = false;

int life = 3;
int level = 0;
ScorePong SCORE;
int combo = 0;

const float startPosX = 55;
const float startPosY = 70;

Paddle paddle;
Ball ball;

Texture textureBall;
RectangleShape background;
Texture textureBackGround;
Texture texturePaddle;
Texture textureBrick;

SoundBuffer hitPaddleBuf;
SoundBuffer destroyBrickBuf;
SoundBuffer damageBrickBuf;
SoundBuffer bounceWallBuf;
SoundBuffer winBuf;


Sound hitPaddleSound;
Sound destroyBrickSound;
Sound damageBrickSound;
Sound bounceWallSound;
Sound winSound;


vector<Brick*> bricks;

void Start();
void Reset();
void Update();
void Render();
void HandleInput();
void loadLevel(int level);

bool BallLeft(RectangleShape rect);
bool BallRight(RectangleShape rect);
bool BallUp(RectangleShape rect);
bool BallBottom(RectangleShape rect);

void startPong()
{
    window.create(VideoMode(grid_sizeX, grid_sizeY), "Breakout pong");
    Start();
    loadLevel(0);
    while (window.isOpen())
    {
        deltaTime = gameClock.restart().asSeconds();
        HandleInput();

        if (isPlaying && ! gameover && ! win)
        {
            Update();
        }



        Render();
    }

}

void Start()
{
    font.loadFromFile("16020_FUTURAM.ttf");
    textureBall.loadFromFile("ball.png");
    textureBackGround.loadFromFile("background.png");
    texturePaddle.loadFromFile("paddle.png");
    textureBrick.loadFromFile("09-Breakout-Tiles.png");


    hitPaddleBuf.loadFromFile("jump_05.wav");
    destroyBrickBuf.loadFromFile("qubodup-crash.wav");
    damageBrickBuf.loadFromFile("hit17.flac");
    bounceWallBuf.loadFromFile("jump.flac");
    winBuf.loadFromFile("winfretless.ogg");


    hitPaddleSound.setBuffer(hitPaddleBuf);
    destroyBrickSound.setBuffer(destroyBrickBuf);
    damageBrickSound.setBuffer(damageBrickBuf);
    bounceWallSound.setBuffer(bounceWallBuf);
    winSound.setBuffer(winBuf);



    background.setSize(Vector2f(grid_sizeX, grid_sizeY));
    background.setPosition(0, 0);
    background.setTexture(&textureBackGround);


    lifeText.setFont(font);
    lifeText.setCharacterSize(20);
    lifeText.setPosition(620, grid_sizeY - 30);
    lifeText.setString("lives:" +to_string(life));



    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(80, grid_sizeY - 30);
    scoreText.setString("score:" + to_string(SCORE.getScore()));

}

void Reset()
{
    ball.setPosition(paddle.paddl.getPosition().x, paddle.paddl.getPosition().y - paddle.paddl.getSize().y / 2 - ball.ball.getRadius());
    ball.angle = (270 + rand() % 60 - 30) * 2 * pi / 360;

}

void Update()
{
    if (ball.angle < 0)
    {
        ball.angle += 2 * pi;
    }
    ball.angle = fmod(ball.angle, 2 * pi);

    float factor = ball.speed * deltaTime;
    ball.ball.move(cos(ball.angle) * factor, sin(ball.angle) * factor);
    //physics
    //edge
    if (ball.ball.getPosition().y + ball.ball.getRadius() > grid_sizeY)
    {
        isPlaying = false;
        life--;
        Reset();
    }
    else if (ball.ball.getPosition().x - ball.ball.getRadius() < 50.f)
    {
        ball.angle = pi - ball.angle;
        ball.ball.setPosition(ball.ball.getRadius() + 50.1f, ball.ball.getPosition().y);
        bounceWallSound.play();
    }
    else if (ball.ball.getPosition().x + ball.ball.getRadius() > grid_sizeX - 50)
    {
        ball.angle = pi - ball.angle;
        ball.setPosition(grid_sizeX - ball.ball.getRadius() - 50.1f, ball.ball.getPosition().y);
        bounceWallSound.play();
    }
    else if (ball.ball.getPosition().y - ball.ball.getRadius() < 50.f)
    {
        ball.angle = -ball.angle;
        ball.setPosition(ball.ball.getPosition().x, ball.ball.getRadius() + 50.1f);
        bounceWallSound.play();
    }

    //paddle
    if (BallBottom(paddle.paddl))
    {
        int dis = ball.ball.getPosition().x - paddle.paddl.getPosition().x;
        if (dis > 30 && ball.angle > 1.f / 2.f * pi)
        {
            ball.angle = ball.angle - pi;
        }
        else if (dis < -30 && ball.angle < 1.f / 2.f * pi)
        {
            ball.angle = ball.angle - pi;
        }
        else
        {
            ball.angle = -ball.angle;
            if (ball.angle > 1.f / 2.f * pi && ball.angle < 7.f / 8.f * pi)
            {
                ball.angle += (std::rand() % 15) * pi / 180;
            }
            else if (ball.angle < 1.f / 2.f * pi && ball.angle > 1.f / 8.f * pi)
            {
                ball.angle -= (std::rand() % 15) * pi / 180;
            }
            else if (ball.angle <= 1.f / 8.f * pi)
            {
                ball.angle += (std::rand() % 15) * pi / 180;
            }
            else if (ball.angle >= 7.f / 8.f * pi)
            {
                ball.angle -= (std::rand() % 15) * pi / 180;
            }
        }

        combo = 0;
        ball.setPosition(ball.ball.getPosition().x, paddle.paddl.getPosition().y - paddle.paddl.getSize().y / 2 - ball.ball.getRadius() - 0.1f);
        hitPaddleSound.play();
    }
    //bricks
    for (int i = 0; i < bricks.size(); ++i)
    {
        if (bricks[i]->enable)
        {
            if (bricks[i]->speed != 0.f)
            {
                if (bricks[i]->brikk.getPosition().x - bricks[i]->brikk.getSize().x / 2 < 50.f)
                    bricks[i]->moveLeft = false;
                else if (bricks[i]->brikk.getPosition().x + bricks[i]->brikk.getSize().x / 2 > grid_sizeX - 50.f)
                    bricks[i]->moveLeft = true;

                if (bricks[i]->moveLeft)
                    bricks[i]->brikk.move(-bricks[i]->speed * deltaTime, 0.0f);
                else
                    bricks[i]->brikk.move(bricks[i]->speed * deltaTime, 0.0f);


            }


            if (BallUp(bricks[i]->brikk))
            {
                ball.angle = -ball.angle;
                ball.setPosition(ball.ball.getPosition().x, bricks[i]->brikk.getPosition().y + bricks[i]->brikk.getSize().y / 2 + ball.ball.getRadius() + 0.1f);
                if (bricks[i]->hit())
                {
                    destroyBrickSound.play();
                }
                else
                {
                    damageBrickSound.play();
                }
                SCORE.addScore();
            }
            else if (BallBottom(bricks[i]->brikk))
            {
                ball.angle = -ball.angle;
                ball.setPosition(ball.ball.getPosition().x, bricks[i]->brikk.getPosition().y - bricks[i]->brikk.getSize().y / 2 - ball.ball.getRadius() - 0.1f);
                if (bricks[i]->hit())
                {
                    destroyBrickSound.play();
                }
                else
                {
                    damageBrickSound.play();
                }
                SCORE.addScore();
            }
            else if (BallLeft(bricks[i]->brikk))
            {
                ball.angle = pi - ball.angle;
                ball.setPosition(bricks[i]->brikk.getPosition().x + ball.ball.getRadius() + bricks[i]->brikk.getSize().x / 2 + 0.1f, ball.ball.getPosition().y);
                if (bricks[i]->hit())
                {
                    destroyBrickSound.play();
                }
                else
                {
                    damageBrickSound.play();
                }
                SCORE.addScore();
            }
            else if (BallRight(bricks[i]->brikk))
            {
                ball.angle = pi - ball.angle;
                ball.setPosition(bricks[i]->brikk.getPosition().x - ball.ball.getRadius() - bricks[i]->brikk.getSize().x / 2 - 0.1f, ball.ball.getPosition().y);
                if (bricks[i]->hit())
                {
                    destroyBrickSound.play();
                }
                else
                {
                    damageBrickSound.play();
                }
                SCORE.addScore();
            }
        }
    }
    if (life <= 0)
    {
        window.close();
    }

    int count = 0;
    for (int i = 0; i < bricks.size(); ++i)
    {
        if (bricks[i]->enable && bricks[i]->health < 3)
            count++;
    }

    if (count <= 0)
    {
        win = true;
        ball.speed += 100.f;
        winSound.play();

    }
    lifeText.setString("life:" + std::to_string(life));
    scoreText.setString("score:" + std::to_string(SCORE.getScore()));
}

void Render()
{
    window.clear(sf::Color::Black);
    window.draw(background);
    window.draw(paddle.paddl);
    window.draw(ball.ball);

    for (int i = 0; i < bricks.size(); ++i)
    {
        if (bricks[i]->enable)
        {
            if (bricks[i]->health == 1)
            {
                bricks[i]->brikk.setTexture(&textureBrick);
                bricks[i]->brikk.setFillColor(Color(0, 255, 255, 255));
            }
            else if (bricks[i]->health == 2)
            {
                bricks[i]->brikk.setTexture(&textureBrick);
                bricks[i]->brikk.setFillColor(Color(255, 0, 0, 255));
            }
            else
            {
                bricks[i]->brikk.setTexture(&textureBrick);
                bricks[i]->brikk.setFillColor(Color(255, 255, 255, 255));
            }
            window.draw(bricks[i]->brikk);
        }

    }
    window.draw(lifeText);
    window.draw(scoreText);
    window.display();
}

void HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            for (int i = 0; i < bricks.size(); ++i)
            {
                delete bricks[i];
                bricks[i] = nullptr;
            }
            bricks.clear();
        }

    }



    if (!gameover)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
            (paddle.paddl.getPosition().x - paddle.paddl.getSize().x / 2.f > 50.f))
        {
            isPlaying = true;
            paddle.paddl.move(-paddle.speed * deltaTime, 0.f);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
            (paddle.paddl.getPosition().x + paddle.paddl.getSize().x / 2.f < grid_sizeX - 50.f))
        {
            paddle.paddl.move(paddle.speed * deltaTime, 0.f);
        }

        if (!isPlaying)
        {
            ball.ball.setPosition(paddle.paddl.getPosition().x, paddle.paddl.getPosition().y - paddle.paddl.getSize().y / 2 - ball.ball.getRadius());
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if (gameover)
        {
            life = 3;
            gameover = false;
            SCORE.makeScoreZero();
            loadLevel(level);
        }


        else if (win)
        {
            win = false;
            level = (level + 1) % 3;
            loadLevel(level);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        level = 0;
        loadLevel(level);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        level = 1;
        loadLevel(level);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        level = 2;
        loadLevel(level);
    }

}


void loadLevel(int level)
{
    isPlaying = false;
    gameover = false;




    paddle.initiate();
    paddle.setSize(150, 35);
    paddle.setPosition(grid_sizeX / 2, grid_sizeY - paddle.paddl.getSize().y);
    paddle.paddl.setTexture(&texturePaddle);

    ball.initiate();
    ball.setSize(10);
    ball.setPosition(paddle.paddl.getPosition().x, paddle.paddl.getPosition().y - paddle.paddl.getSize().y / 2 - ball.ball.getRadius());
    ball.angle = (270 + std::rand() % 60 - 30) * 2 * pi / 360;
    ball.ball.setTexture(&textureBall);


    for (int i = 0; i < bricks.size(); ++i)
    {
        delete bricks[i];
        bricks[i] = nullptr;
    }
    bricks.clear();

    if (level == 0)
    {

        for (int i = 0; i < 10; i++)
        {
            Brick* bptr = new Brick; //brick dynamic array
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2);
            bptr->health = 1;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 10; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x, startPosY + 3 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2);
            bptr->health = 1;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                Brick* bptr = new Brick;
                bptr->initiate();
                bptr->setSize(70, 30);
                bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x, startPosY + 6 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y);
                bptr->health = 2;
                bricks.push_back(bptr);

            }
        }

        for (int i = 0; i < 10; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x, startPosY + 9 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2);
            bptr->health = 1;
            bptr->speed = 400;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 4; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x, startPosY + 11 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2);
            bptr->health= 99999;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 4; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x + 6 * bptr->brikk.getSize().x, startPosY + 11 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2);
            bptr->health = 99999;
            bricks.push_back(bptr);

        }
    }
    else if (level == 1)
    {

        for (int i = 0; i < 5; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x, startPosY + 10 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2 - i * bptr->brikk.getSize().y);
            bptr->health = 1;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 5; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x + 5 * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y + 6 * bptr->brikk.getSize().y);
            bptr->health = 1;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                Brick* bptr = new Brick;
                bptr->initiate();
                bptr->setSize(70, 30);
                bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x + 4 * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y);
                bptr->health = 2;
                bricks.push_back(bptr);

            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                Brick* bptr = new Brick;
                bptr->initiate();
                bptr->setSize(70, 30);
                bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x + 4 * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y + 4 * bptr->brikk.getSize().y);
                bptr->health = 2;
                bricks.push_back(bptr);

            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                Brick* bptr = new Brick;
                bptr->initiate();
                bptr->setSize(70, 30);
                bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y + 2 * bptr->brikk.getSize().y);
                bptr->health = 1;
                bptr->speed = 300;
                bricks.push_back(bptr);

            }
        }

        for (int i = 0; i < 4; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x, startPosY + 11 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2);
            bptr->health = 99999;
            bricks.push_back(bptr);

        }

        for (int i = 0; i < 4; i++)
        {
            Brick* bptr = new Brick;
            bptr->initiate();
            bptr->setSize(70, 30);
            bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + i * bptr->brikk.getSize().x + 6 * bptr->brikk.getSize().x, startPosY + 11 * bptr->brikk.getSize().y + bptr->brikk.getSize().y / 2);
            bptr->health = 99999;
            bricks.push_back(bptr);

        }

    }
    else if (level == 2)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                int temp = rand() % 5;
                if (temp == 0)
                {
                    Brick* bptr = new Brick;
                    bptr->initiate();
                    bptr->setSize(70, 30);
                    bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y);
                    bptr->health = 1;
                    bricks.push_back(bptr);
                }
                else if (temp == 1)
                {
                    Brick* bptr = new Brick;
                    bptr->initiate();
                    bptr->setSize(70, 30);
                    bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y);
                    bptr->health = 2;
                    bricks.push_back(bptr);
                }
                else if (temp == 2)
                {
                    Brick* bptr = new Brick;
                    bptr->initiate();
                    bptr->setSize(70, 30);
                    bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y);
                    bptr->health = 99999;
                    bricks.push_back(bptr);
                }
                else if (temp == 3)
                {
                    Brick* bptr = new Brick;
                    bptr->initiate();
                    bptr->setSize(70, 30);
                    bptr->setPosition(startPosX + bptr->brikk.getSize().x / 2 + j * bptr->brikk.getSize().x, startPosY + bptr->brikk.getSize().y / 2 + i * bptr->brikk.getSize().y);
                    bptr->health = 1;
                    bptr->speed = 300;
                    bricks.push_back(bptr);
                }

            }
        }

    }
}

//checks if ball hits border
bool BallLeft(RectangleShape rect)
{
    if (ball.ball.getPosition().x + ball.ball.getRadius() > rect.getPosition().x - rect.getSize().x / 2 &&
        ball.ball.getPosition().x + ball.ball.getRadius() < rect.getPosition().x + rect.getSize().x / 2 &&
        ball.ball.getPosition().y + ball.ball.getRadius() >= rect.getPosition().y - rect.getSize().y / 2 &&
        ball.ball.getPosition().y - ball.ball.getRadius() <= rect.getPosition().y + rect.getSize().y / 2)
        return true;
    else
        return false;
}
bool BallRight(RectangleShape rect)
{
    if (ball.ball.getPosition().x - ball.ball.getRadius() > rect.getPosition().x - rect.getSize().x / 2 &&
        ball.ball.getPosition().x - ball.ball.getRadius() < rect.getPosition().x + rect.getSize().x / 2 &&
        ball.ball.getPosition().y + ball.ball.getRadius() >= rect.getPosition().y - rect.getSize().y / 2 &&
        ball.ball.getPosition().y - ball.ball.getRadius() <= rect.getPosition().y + rect.getSize().y / 2)
        return true;
    else
        return false;
}
bool BallUp(RectangleShape rect)
{
    if (ball.ball.getPosition().x + ball.ball.getRadius() >= rect.getPosition().x - rect.getSize().x / 2 &&
        ball.ball.getPosition().x - ball.ball.getRadius() <= rect.getPosition().x + rect.getSize().x / 2 &&
        ball.ball.getPosition().y - ball.ball.getRadius() < rect.getPosition().y + rect.getSize().y / 2 &&
        ball.ball.getPosition().y - ball.ball.getRadius() > rect.getPosition().y - rect.getSize().y / 2)
        return true;
    else
        return false;
}
bool BallBottom(RectangleShape rect)
{
    if (ball.ball.getPosition().x + ball.ball.getRadius() >= rect.getPosition().x - rect.getSize().x / 2 &&
        ball.ball.getPosition().x - ball.ball.getRadius() <= rect.getPosition().x + rect.getSize().x / 2 &&
        ball.ball.getPosition().y + ball.ball.getRadius() < rect.getPosition().y + rect.getSize().y / 2 &&
        ball.ball.getPosition().y + ball.ball.getRadius() > rect.getPosition().y - rect.getSize().y / 2)
        return true;
    else
        return false;
}