#include <string>

#ifndef SCORE_H
#define SCORE_H

string scoreUpdate(string s, unsigned int &x){
    string str;
    x+=10;
    str = s+to_string(x);
    return str;
};

#endif // SCORE_H
