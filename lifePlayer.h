#include <string>

#ifndef LIFEPLAYER_H
#define LIFEPLAYER_H

string lifeUpdate(string s, int &x){
    string str;
    x-=1;
    str = s+to_string(x);
    return str;
};

string lifeUpdate2(string s, int &x){
    string str;
    x+=1;
    str = s+to_string(x);
    return str;
};

#endif
