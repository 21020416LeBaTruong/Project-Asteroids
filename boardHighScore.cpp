#include "boardHighScore.h"
#include "SFML/Graphics.hpp"

#include <string>
#include <fstream>

boardScore::boardScore(float w, float h){
    if (!font.loadFromFile("fonts/arial.ttf")){
        cout << "Error";
    }
    if (!font2.loadFromFile("fonts/Elecstrom Font - Free Trial-c0a4.woff")){
        cout << "Error";
    }
    fstream input("highScore.txt");
    unsigned int topScore[5];
    for(int i=0; i<5; i++){
        input >> topScore[i];
    }
    //Play
    board[0].setFont(font);
    board[0].setFillColor(Color::White);
    board[0].setString("1. " + to_string(topScore[0]));
    board[0].setCharacterSize(50);
    board[0].setPosition(520, 250);

    board[1].setFont(font);
    board[1].setFillColor(Color::White);
    board[1].setString("2. " + to_string(topScore[1]));
    board[1].setCharacterSize(50);
    board[1].setPosition(520, 350);

    board[2].setFont(font);
    board[2].setFillColor(Color::White);
    board[2].setString("3. " + to_string(topScore[2]));
    board[2].setCharacterSize(50);
    board[2].setPosition(520, 450);

    board[3].setFont(font);
    board[3].setFillColor(Color::White);
    board[3].setString("4. " + to_string(topScore[3]));
    board[3].setCharacterSize(50);
    board[3].setPosition(520, 550);

    board[4].setFont(font);
    board[4].setFillColor(Color::White);
    board[4].setString("5. " + to_string(topScore[4]));
    board[4].setCharacterSize(50);
    board[4].setPosition(520, 650);

    board[5].setFont(font2);
    board[5].setFillColor(Color::Red);
    board[5].setString("HIGHSCORE");
    board[5].setCharacterSize(160);
    board[5].setPosition(300, 20);
}
boardScore::~boardScore(){
}
//Draw MainMenu
void boardScore::draw(RenderWindow &window){
    for(int i=0; i<6; i++){
        window.draw(board[i]);
    }
}

