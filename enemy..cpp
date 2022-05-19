#include "enemy.h"

const float DEGTORAD = 0.017453f;

const int W = 1200;
const int H = 800;
    enemy::enemy(){
        name="enemy";
    }
    void enemy::update(){
        dx=cos(angle*DEGTORAD)*6;
        dy=sin(angle*DEGTORAD)*6;
        angle+=rand()%10-5;
        x+=dx;
        y+=dy;

        if (x>W) x=0;  if (x<0) x=W;
        if (y>H) y=0;  if (y<0) y=H;
    }
