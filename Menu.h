#ifndef GAMEBOX_MENU_H
#define GAMEBOX_MENU_H
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace::std;
using namespace::sf;
class Menu {
public:
    Text MainMenu[3];
    Menu(float width , float height);
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
#endif