#include<fstream>
#include<iostream>
using namespace std;

#ifndef HIGHSCORE_H
#define HIGHSCORE_H


void getHighScore(unsigned int score){
    fstream input("highScore.txt");
    fstream output("highScore.txt");
    unsigned int topScore[5];
    for(int i=0; i<5; i++){
        input >> topScore[i];
    }
    for(int i=0; i<5; i++){
        if(score <= topScore[i])
            continue;
        else{
            for(int j=4; j>i; j--){
                topScore[j]=topScore[j-1];
            }
            topScore[i]=score;
            break;
        }
    }
    for(int i=0; i<5; i++){
        output << topScore[i] << endl;
    }
};

#endif
