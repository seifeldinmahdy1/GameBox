#include "GameWindows.h"
#include <iostream>
#include <fstream>
#include<SFML/Graphics.hpp>
#include "game.h"
#include "source.h"
#include "pongmain.h"
#include "Brick.h"
#include "Block.h"
#include "Ball.h"
#include "paddle.h"
#include "Hangman.h"
using namespace std;
using namespace sf;
void GameWindows::playerName(RenderWindow &window) {
    if (!name.empty()){
        name.clear();
    }
    Texture background;
    background.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/coma_star_cluster_coma_berenices_constellation_891324_1920x1080.jpg");
    Sprite bg;
    bg.setTexture(background);
    Font font;
    font.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/PixeloidMono-d94EV.ttf" );
    Text t1;
    Text t2;
    t1.setFont(font);
    t2.setFont(font);
    t1.setString("Enter your name: ");
    t1.setCharacterSize(100);
    t2.setCharacterSize(100);
    t1.setPosition(460,190);
    t2.setPosition(600,330);
    t1.setFillColor(Color::White);
    t2.setFillColor(Color{100,50,160});
    while(window.isOpen()){
        Event evnt;
        while(window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {
                window.close();
            }
            if (evnt.type==Event::TextEntered){
                name+=static_cast<char>(evnt.text.unicode);
                // adds the characters of the name character by character to the empty string.
            }
            if (Keyboard::isKeyPressed(Keyboard::Backspace) && name.size()>0 ){ //erases characters if backspace is pressed
                // and if the size of the name is more than 0.
                name.resize(name.size()-1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && name.size() >= 1){
                pagenumber = 2;
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenumber = 10;
                return;
            }
        }
        t2.setString(name);
        t2.getString();
        window.clear();
        window.draw(bg);
        window.draw(t1);
        window.draw(t2);
        window.display();
    }
}
void GameWindows::creditsName(RenderWindow &window) {
    Texture background;
    background.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/coma_star_cluster_coma_berenices_constellation_891324_1920x1080.jpg");
    Sprite bg;
    bg.setTexture(background);
    Font font;
    font.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/PixeloidMono-d94EV.ttf");
    Text t1;
    Text t2;
    Text t3;
    Text t4;
    t1.setFont(font);
    t2.setFont(font);
    t3.setFont(font);
    t4.setFont(font);
    t1.setString("Created By");
    t2.setString("Seif El Din Mahdy");
    t3.setString("Youssef El Bashaar");
    t4.setString("Seif Mohamed");
    t1.setCharacterSize(60);
    t2.setCharacterSize(75);
    t3.setCharacterSize(75);
    t4.setCharacterSize(75);
    t1.setPosition(750, 190);
    t2.setPosition(520, 380);
    t3.setPosition(520, 540);
    t4.setPosition(520, 700);
    t1.setFillColor({Color{19, 168, 163}});
    t2.setFillColor(Color::White);
    t3.setFillColor(Color::White);
    t4.setFillColor(Color::White);
    while (window.isOpen()) {
        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenumber = 10;
                return;
            }
            window.clear();
            window.draw(bg);
            window.draw(t1);
            window.draw(t2);
            window.draw(t3);
            window.draw(t4);
            window.display();
        }
    }
}
void GameWindows::setSelected(int n) {
    selected = n;
}
void GameWindows::draw(RenderWindow& Window){
    for (int i = 0 ; i<3 ; i++){
        Window.draw(Games[i]);
    }
}
void GameWindows::moveDown() {
    if (selected+1 <=3){ //hangman is not selected.
        Games[selected].setFillColor(Color::White);
        selected++;
    }
    if (selected==3){ //hangman is selected.
        selected=0; // if moved down the snake button gets selected
    }
    Games[selected].setFillColor(Color{100,50,160});
}
void GameWindows::moveUp() {
    if (selected-1 >=-1){ //snake not selected.
        Games[selected].setFillColor(Color::White);
        selected--;
        if (selected==-1){ // if there is no selection select the last one or the hangman button
            selected = 2;
        }
        Games[selected].setFillColor(Color{100,50,160});
    }
}
void GameWindows::gamesWindow(RenderWindow &window) {
    Texture background;
    background.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/coma_star_cluster_coma_berenices_constellation_891324_1920x1080.jpg");
    Sprite bg;
    bg.setTexture(background);
    Font font;
    font.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/PixeloidMono-d94EV.ttf" );
    Text t1;
    t1.setFont(font);
    t1.setString("Choose a Game you want to Play");
    t1.setCharacterSize(73);
    t1.setPosition(45,55);
    t1.setFillColor(Color::White);

    Games[0].setFont(font);
    Games[0].setFillColor(Color{100,50,160});
    Games[0].setString("Snake");
    Games[0].setCharacterSize(90);
    Games[0].setPosition(1920 /2.4 , 1080 / (4)+25);

    Games[1].setFont(font);
    Games[1].setFillColor(Color::White);
    Games[1].setString("Breakout Pong");
    Games[1].setCharacterSize(90);
    Games[1].setPosition(1920/3.28 , 1080/(4)+255);

    Games[2].setFont(font);
    Games[2].setFillColor(Color::White);
    Games[2].setString("Hangman");
    Games[2].setCharacterSize(90);
    Games[2].setPosition(1920 / 2.6, 1080/(4)+500);

    selected = 0;

    while (window.isOpen()) {
        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {
                window.close();
            }
            if (evnt.type == Event::KeyPressed) {
                if (evnt.key.code == Keyboard::Up) {
                    moveUp();
                }
                if (evnt.key.code == Keyboard::Down) {
                    moveDown();
                }
                if (evnt.key.code == Keyboard::Enter) {
                    if (pressed() == 0) {
                        StartSnakeGame();
                    }
                    if (pressed() == 1) {
                        pagenumber = 4;
                        startPong();
                    }
                    if (pressed() == 2) {
                        window.close();
                        pagenumber = -1;
                        StartHangman();
                        break;
                    }
                }
            }
        }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenumber = 10;
                return;
            }
            window.clear();
            window.draw(bg);
            window.draw(t1);
            draw(window);
            window.display();
        }
    }