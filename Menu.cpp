#include "Menu.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
Menu::Menu(float width, float height) {
    font.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/PixeloidMono-d94EV.ttf" );
    MainMenu[0].setFont(font);
    MainMenu[0].setFillColor(Color{100,50,160});
    MainMenu[0].setString("Play");
    MainMenu[0].setCharacterSize(90);
    MainMenu[0].setPosition(width/2.3 , height/4+100);

    MainMenu[1].setFont(font);
    MainMenu[1].setFillColor(Color::White);
    MainMenu[1].setString("Credits");
    MainMenu[1].setCharacterSize(90);
    MainMenu[1].setPosition(width/2.55 , height/(4)+300);

    MainMenu[2].setFont(font);
    MainMenu[2].setFillColor(Color::White);
    MainMenu[2].setString("Exit");
    MainMenu[2].setCharacterSize(90);
    MainMenu[2].setPosition(width/2.3 , height/(4)+500);

    selected = 0;
}
void Menu::setSelected(int n) {
    selected = n;
}
void Menu::draw(RenderWindow& Window){
    for (int i = 0 ; i<3 ; i++){
        Window.draw(MainMenu[i]);
    }
}
void Menu::moveDown() {
    if (selected+1 <=3){ //exit is not selected.
        MainMenu[selected].setFillColor(Color::White);
        selected++;
    }
    if (selected==3){ //exit is selected.
        selected=0; // if moved down the play button gets selected
    }
    MainMenu[selected].setFillColor(Color{100,50,160});
}
void Menu::moveUp() {
    if (selected-1 >=-1){ //play not selected.
        MainMenu[selected].setFillColor(Color::White);
        selected--;

        if (selected==-1){ // if there is no selection select the last one or the exit button
            selected = 2;
        }
        MainMenu[selected].setFillColor(Color{100,50,160});
    }
}