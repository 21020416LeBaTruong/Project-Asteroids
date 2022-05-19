#ifndef ISCOLLIDE_H
#define ISCOLLIDE_H

bool isCollide(Entity *a,Entity *b){
    return  (b->x - a->x)*(b->x - a->x)+
            (b->y - a->y)*(b->y - a->y)<
            (a->R + b->R)*(a->R + b->R);
}

#endif // ISCOLLIDE_H
