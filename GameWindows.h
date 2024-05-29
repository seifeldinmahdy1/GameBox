#ifndef GAMEBOX_GAMEWINDOWS_H
#define GAMEBOX_GAMEWINDOWS_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include <fstream>
using namespace sf;
using namespace std;

class GameWindows {
public:
    Text Games[3];
    int pagenumber;
    string name;
    string n;
    void playerName(RenderWindow& window);
    void creditsName(RenderWindow& window);
    void gamesWindow(RenderWindow&window);
public:
    void draw(RenderWindow& Window);
    void moveUp();
    void moveDown();
    void setSelected(int n);
    int pressed(){
        return selected;
    }
private:
    int selected;
    Font font;
};
#endif //GAMEBOX_GAMEWINDOWS_H
