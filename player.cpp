#include "player.h"

const int W = 1200;
const int H = 800;
const float DEGTORAD = 0.017453f;

    player::player(){
        name="player";
    }

    void player::update(){
        if (thrust){
            dx+=cos(angle*DEGTORAD)*0.1;
            dy+=sin(angle*DEGTORAD)*0.1;
        }
        else{
            dx*=0.99;
            dy*=0.99;
        }

    int maxSpeed=15;
    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>W) x=0; if (x<0) x=W;
    if (y>H) y=0; if (y<0) y=H;
    }


