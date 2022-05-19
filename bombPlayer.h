#include <string>

#ifndef BOMBPLAYER_H
#define BOMBPLAYER_H

string bombUpdate(string s, int &x){
    string str;
    x-=1;
    str = s+to_string(x);
    return str;
};

string bombUpdate2(string s, int &x){
    string str;
    x+=1;
    str = s+to_string(x);
    return str;
};

#endif

