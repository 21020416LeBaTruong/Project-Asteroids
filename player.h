#include "Entity.h"

#ifndef PLAYER_H
#define PLAYER_H

class player: public Entity{
    public:
    bool thrust=0;

    player();
    void update();
};
#endif // PLAYER_H
