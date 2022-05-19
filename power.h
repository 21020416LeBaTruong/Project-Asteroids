#ifndef POWER_H
#define POWER_H
#include "bullet.h"
#include "Animation.h"

void power(int &power, Entity entities, player p, Animation sBullet1){
    if(power==1){
        bullet *b = new bullet();
        b->settings(sBullet1,p->x,p->y,p->angle+3, 10);
        entities.push_back(b);
    }
    if(power==2){
        bullet *b = new bullet();
        bullet *b2 = new bullet();
        b->settings(sBullet1,p->x,p->y,p->angle+3, 10);
        b2->settings(sBullet1,p->x,p->y,p->angle-3, 10);
        entities.push_back(b);
        entities.push_back(b2);
    }
    if(power==3){
        bullet *b = new bullet();
        bullet *b2 = new bullet();
        bullet *b3 = new bullet();
        b->settings(sBullet1,p->x,p->y,p->angle+3, 10);
        b2->settings(sBullet1,p->x,p->y,p->angle-3, 10);
        b3->settings(sBullet1,p->x,p->y,p->angle, 10);
        entities.push_back(b);
        entities.push_back(b2);
        entities.push_back(b3);
    }
}
#endif // POWER_H
