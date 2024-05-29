#include <vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Menu.h"
#include "GameWindows.h"
#include "game.h"
using namespace std;
using namespace sf;

int main(void)
{
    GameWindows g;
    Game g1;
    RenderWindow window(VideoMode(1920, 1080), "GameBox",sf::Style::Close | sf::Style::Titlebar);
    Menu menu(1920, 1080);
    Texture mainmenubg;
    mainmenubg.loadFromFile("/Users/seifmahdy/CLionProjects/GameBox/fotor_2023-5-7_16_34_19.png");
    Sprite bg;
    g.pagenumber = 10;
    bg.setTexture(mainmenubg);
    // 10  main menu
    //-1 close
    //0 entername page
    // 1 credits
    // 20 scores
    // 2 choose game menu
    // 3 snake
    // 4 pong
    // 5 hangman
    // 6 gameover prompt and replay and return to game menu (2) button
    string name;
    while (true) {
        if (g.pagenumber == 10) {
            while (window.isOpen()) {
                Event evnt;
                while (window.pollEvent(evnt)) {
                    if (evnt.type == Event::Closed) {
                        window.close();
                        break;
                    }
                    if (evnt.type == Event::KeyPressed) {
                        if (evnt.key.code == Keyboard::Up) {
                            menu.moveUp();
                        }
                        if (evnt.key.code == Keyboard::Down) {
                            menu.moveDown();
                        }
                        if (evnt.key.code == Keyboard::Enter) {
                            if (menu.pressed() == 0) {
                                g.pagenumber = 0;
                            }
                            if (menu.pressed() == 1) {
                                g.pagenumber = 1;
                            }
                            if (menu.pressed() == 2) {
                                g.pagenumber = -1;
                            }
                        }
                    }
                }
                window.clear();
                if (g.pagenumber != 10) {
                    break;
                }
                window.draw(bg);
                menu.draw(window);
                window.display();
            }
            if (g.pagenumber == -1) {
                window.close();
                break;
            }
            if (g.pagenumber == 0) {
                g.playerName(window);
            }
            if (g.pagenumber == 1) {
                g.creditsName(window);
            }
            if (g.pagenumber == 2) {
                g.gamesWindow(window);
            }
        }
    }
}
