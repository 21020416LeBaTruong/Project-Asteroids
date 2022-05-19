#include "Menu.h"

Menu::Menu(float w, float h){
    if (!font.loadFromFile("fonts/Robus-BWqOd.otf")){
        std::cout << "Error";
    }
    if (!font2.loadFromFile("fonts/SpaceMission-rgyw9.otf")){
        std::cout << "Error";
    }
    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::Red);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(120);
    mainMenu[0].setPosition(505, 200);

    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::Blue);
    mainMenu[1].setString("Multiplayer");
    mainMenu[1].setCharacterSize(100);
    mainMenu[1].setPosition(390, 300);

    //How to play
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::Blue);
    mainMenu[2].setString("How to play");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(460, 410);

    //High score
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::Blue);
    mainMenu[3].setString("High score");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(480, 490);

    //Exit
    mainMenu[4].setFont(font);
    mainMenu[4].setFillColor(Color::Blue);
    mainMenu[4].setString("Exit");
    mainMenu[4].setCharacterSize(70);
    mainMenu[4].setPosition(550, 570);

    //Version
    mainMenu[5].setFont(font);
    mainMenu[5].setFillColor(Color::Red);
    mainMenu[5].setString("LBT");
    mainMenu[5].setCharacterSize(30);
    mainMenu[5].setPosition(10, 0);

    mainMenu[6].setFont(font2);
    mainMenu[6].setFillColor(Color::White);
    mainMenu[6].setString("ASTEROIDS");
    mainMenu[6].setCharacterSize(175);
    mainMenu[6].setPosition(200, 50);
    MainMenuSelected = 0;


}
Menu::~Menu(){
}
//Draw MainMenu
void Menu::draw(RenderWindow &window){
    for(int i=0; i<7; i++){
        window.draw(mainMenu[i]);
    }
}

void Menu::MoveUp(){
    if (MainMenuSelected -1 >= 0){
        mainMenu[MainMenuSelected].setColor(sf::Color::Blue);
        MainMenuSelected--;
        if (MainMenuSelected == -1) MainMenuSelected = 0;
        mainMenu[MainMenuSelected].setColor(sf::Color::Red);
    }
}

void Menu::MoveDown(){
    if (MainMenuSelected + 1 <= 5){
        mainMenu[MainMenuSelected].setColor(sf::Color::Blue);
        MainMenuSelected++;
        if (MainMenuSelected == 5) MainMenuSelected = 4;
        mainMenu[MainMenuSelected].setColor(sf::Color::Red);
    }
}
