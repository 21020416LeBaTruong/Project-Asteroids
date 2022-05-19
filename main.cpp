#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <list>
#include <cmath>
#include <string>
#include <fstream>
#include "Menu.h"
#include "Animation.h"
#include "Entity.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include "isCollide.h"
#include "score.h"
#include "lifePlayer.h"
#include "enemy.h"
#include "heart.h"
#include "bombIcon.h"
#include "bomb.h"
#include "bombPlayer.h"
#include "highScore.h"
#include "boardHighScore.h"
#include "powerIcon.h"

using namespace sf;

const int W = 1200;
const int H = 800;
const float DEGTORAD = 0.017453f;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Asteroids!"); //Render window
    Menu menu(app.getSize().x, app.getSize().y); //Menu

    //Audio
    Music music;
    music.openFromFile("sounds/music.wav");
    music.setVolume(30);
    music.setLoop(true);
    SoundBuffer buffer1, buffer2, buffer3, buffer4, buffer5, buffer6, buffer7;
    buffer1.loadFromFile("sounds/test.wav");
    buffer2.loadFromFile("sounds/explosion.ogg");
    buffer3.loadFromFile("sounds/item.wav");
    buffer4.loadFromFile("sounds/menuOption.wav");
    buffer5.loadFromFile("sounds/menuSelect.wav");
    buffer6.loadFromFile("sounds/startGame.wav");
    buffer7.loadFromFile("sounds/endGame.wav");
    Sound sound1, sound2, sound3, sound4, sound5, sound6, sound7;

    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound3.setBuffer(buffer3);
    sound4.setBuffer(buffer4);
    sound5.setBuffer(buffer5);
    sound6.setBuffer(buffer6);
    sound7.setBuffer(buffer7);
    sound2.setVolume(5);
    sound3.setVolume(25);
    sound6.play();

    //Texture
    Texture t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_D.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    t8.loadFromFile("images/5c7ad84b2ad1eb07c808a411bcc0afc0.jpg");
    t9.loadFromFile("images/HOWTOPLAY.png");
    t10.loadFromFile("images/enemy.png");
    t11.loadFromFile("images/heart.png");
    t12.loadFromFile("images/bomb.png");
    t13.loadFromFile("images/rocket.png");
    t14.loadFromFile("images/fire_blue.png");
    t15.loadFromFile("images/power.png");
    t16.loadFromFile("images/gameOver.jpg");



    t1.setSmooth(0);
    t2.setSmooth(0);

    Sprite background(t2);
    Sprite backMenu(t8);
    Sprite backHow(t9);
    Sprite gameOver(t16);

    RectangleShape rectangle(Vector2f(1200, 800));
    rectangle.setFillColor(Color(255,255,255,50));

    //Font
    Font font;
    font.loadFromFile("fonts/arial.ttf");

    Text textTry;
    textTry.setFont(font);
    textTry.setColor(Color::Blue);

    //Animation
    Animation sExplosion(t3, 0,0,120,89, 20, 0.5);
    Animation sRock(t4, 0,0,64,64, 16, 0.2);
    Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animation sBullet1(t5, 0,0,32,64, 16, 0.8);
    Animation sBullet2(t14, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sPlayer_turnLeft(t1, 0, 0, 39, 40, 1, 0);
    Animation sPlayer_turnRight(t1, 80, 0, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);
    Animation sEnemy(t10, 0,0,64,47,1,0.2);
    Animation sHeart(t11, 0, 0, 84.73, 84, 34, 0.5);
    Animation sBomb(t12, 0, 0, 130, 133, 14, 0.3);
    Animation sBombIcon(t13, 0, 0, 30, 30, 1, 0);
    Animation sPower(t15, 0, 0, 30, 30, 1, 0);


    /////main loop/////
    while (app.isOpen()){
        //Score
        unsigned int score=0;
        string strScore="Score: ";
        Text textScore;
        textScore.setFont(font);
        textScore.setColor(Color::White);
        textScore.setString(strScore+to_string(score));

        //bomb
        int bombCount=1, bombCount2=1;
        string strBomb="Bomb: ";
        Text textBomb, textBomb2;
        textBomb.setFont(font);
        textBomb2.setFont(font);
        textBomb.setColor(Color::White);
        textBomb2.setColor(Color::White);
        textBomb.setString(strBomb+to_string(bombCount));
        textBomb2.setString(strBomb+to_string(bombCount2));
        textBomb.setPosition(0, 56);
        textBomb2.setPosition(900, 56);

        //Life
        int life=5, life2=5;
        string strLife="Life: ";
        Text textLife, textLife2;
        textLife.setFont(font);
        textLife2.setFont(font);
        textLife.setColor(Color::White);
        textLife2.setColor(Color::White);
        textLife.setString(strLife+to_string(life));
        textLife2.setString(strLife+to_string(life2));
        textLife.setPosition(0, 28);
        textLife2.setPosition(900, 28);
        Event event;

        int power=1, power2=1;
        while (app.pollEvent(event)){
            if (event.type == Event::Closed)
                app.close();
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Up){
                    menu.MoveUp();
                    sound4.play();
                }
                if (event.key.code == Keyboard::Down){
                    menu.MoveDown();
                    sound4.play();
                }
                if (event.key.code == Keyboard::Escape)
                    app.close();
                /*if (event.key.code == Keyboard::M){
                    if(music.play()==1)
                        music.pause();
                    else    music.play();*/
                if (event.key.code == Keyboard::Return){
                    sound5.play();
                    int x = menu.GetPressedItem();
                    if (x == 0){
                        RenderWindow Play(VideoMode(W, H), "Game!!!");
                        Play.setFramerateLimit(60);
                        music.play();
                        //Khoi tao nguoi choi va vat the
                        std::list<Entity*> entities;

                        for(int i=0;i<2;i++){
                          asteroid *a = new asteroid();
                          a->settings(sRock, rand()%W, rand()%H, rand()%360, 25);
                          entities.push_back(a);
                        }

                        player *p = new player();
                        p->settings(sPlayer,600,400,0,20);
                        p->life=5;
                        entities.push_back(p);

                        while (Play.isOpen()){
                            Event aevent;
                            while (Play.pollEvent(aevent)){
                                if (aevent.type == Event::Closed){
                                    Play.close();
                                    music.stop();
                                }
                                if (aevent.type == Event::KeyReleased){
                                    if (aevent.key.code == Keyboard::Escape){
                                        Play.close();
                                        music.stop();
                                    }
                                    if (aevent.key.code == Keyboard::Space){
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
                                        sound1.play();
                                    }
                                    if (aevent.key.code == Keyboard::B){
                                        if(bombCount>0){
                                            Entity *b = new bomb();
                                            b->settings(sBomb, p->x, p->y, p->angle-90, 0);
                                            entities.push_back(b);
                                            textBomb.setString(bombUpdate(strBomb, bombCount));
                                        }
                                    }
                                }
                            }
                            if (Keyboard::isKeyPressed(Keyboard::W)){
                                p->thrust=true;
                                p->anim = sPlayer_go;
                            }
                            else{
                                p->thrust=false;
                                p->anim = sPlayer;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::D)){
                                p->angle+=3;
                                p->anim = sPlayer_turnRight;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::A)){
                                p->angle-=3;
                                p->anim = sPlayer_turnLeft;
                            }

                            for(auto a:entities)
                                for(auto b:entities){
                                    if (a->name=="asteroid" && b->name=="bullet")
                                        if ( isCollide(a,b) ){
                                            a->life=0;
                                            b->life=0;
                                            sound2.play();
                                            textScore.setString(scoreUpdate(strScore, score));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                            if(rand()%30==0){
                                                Entity *h = new heart();
                                                h->settings(sHeart,b->x,b->y, -90, 15);
                                                entities.push_back(h);
                                            }
                                            if(rand()%30==1){
                                                Entity *p = new powerIcon();
                                                p->settings(sPower,b->x,b->y, -90, 15);
                                                entities.push_back(p);
                                            }

                                            for(int i=0;i<2;i++){
                                                if (a->R==15) continue;
                                                Entity *e = new asteroid();
                                                e->settings(sRock_small,a->x,a->y,rand()%360,15);
                                                entities.push_back(e);
                                            }
                                        }
                                    if (a->name=="enemy" && b->name=="bullet")
                                        if ( isCollide(a,b) ){
                                            a->life=0;
                                            b->life=0;
                                            sound2.play();
                                            textScore.setString(scoreUpdate(strScore, score));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                            if(rand()%15==0){
                                                Entity *b = new bombIcon();
                                                b->settings(sBombIcon,a->x, a->y, -90, 15);
                                                entities.push_back(b);
                                            }
                                        }
                                    if (a->name=="player" && b->name=="heart")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(p->life<5){
                                                p->life++;
                                                textLife.setString(lifeUpdate2(strLife, life));
                                            }
                                        }
                                    if (a->name=="player" && b->name=="powerIcon")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(power<3) power++;
                                        }
                                    if (a->name=="player" && b->name=="bombIcon")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(bombCount<3){
                                                textBomb.setString(bombUpdate2(strBomb, bombCount));
                                            }
                                        }
                                    if (a->name=="player" && b->name=="enemy")
                                        if ( isCollide(a,b) ){
                                            a->life-=1;
                                            b->life=0;
                                            if(power>1) --power;
                                            sound2.play();
                                            textLife.setString(lifeUpdate(strLife, life));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion_ship,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);

                                            //p->settings(sPlayer,W/2,H/2,0,20);
                                            //p->dx=0; p->dy=0;
                                        }
                                    if (a->name=="player" && b->name=="asteroid")
                                        if ( isCollide(a,b) ){
                                            a->life-=1;
                                            b->life=0;
                                            if(power>1) --power;
                                            sound2.play();
                                            textLife.setString(lifeUpdate(strLife, life));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion_ship,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                        }
                                }
                            for(auto e:entities)
                                if (e->name=="bomb")
                                    if (e->anim.isEnd()){
                                        e->life=0;
                                        for(auto a:entities)
                                            if(a->name == "asteroid" || a->name == "enemy"){
                                                textScore.setString(scoreUpdate(strScore, score));
                                                a->life=false;
                                                sound2.play();
                                                Entity *e = new Entity();
                                                e->settings(sExplosion,a->x,a->y);
                                                e->name="explosion";
                                                entities.push_back(e);
                                            }
                                    }
                            for(auto e:entities)
                                if (e->name=="explosion" || e->name=="bomb"){
                                    if (e->anim.isEnd())
                                        e->life=0;
                                }
                            if (rand()%200==0){
                                asteroid *a = new asteroid();
                                a->settings(sRock, 0,rand()%H, rand()%360, 25);
                                entities.push_back(a);
                            }
                            if (rand()%300==0){
                                enemy *e = new enemy();
                                e->settings(sEnemy, 0,rand()%H, rand()%360, 25);
                                entities.push_back(e);
                            }

                            for(auto i=entities.begin();i!=entities.end();){
                                Entity *e = *i;
                                //if(e->name=="bullet" || e->name=="player" || e->name=="explosion"){
                                e->update();
                                e->anim.update();
                                //}
                                if (e->life==0) {i=entities.erase(i); delete e;}
                                else i++;
                            }

                            if (p->life == 0){
                                RenderWindow tryAgain(VideoMode(W, H), "Try again?");
                                sound7.play();
                                music.stop();
                                while(tryAgain.isOpen()){
                                    Event bevent;
                                    while (tryAgain.pollEvent(bevent)){
                                        if (bevent.type == Event::Closed)
                                            tryAgain.close();

                                        if (bevent.type == Event::KeyPressed)
                                            if (bevent.key.code == Keyboard::Escape)
                                                tryAgain.close();
                                    }
                                    Play.close();
                                    tryAgain.draw(gameOver);
                                    textTry.setCharacterSize(40);
                                    textTry.setString("Your score: "+ to_string(score));
                                    textTry.setPosition(600, 450);
                                    textTry.setFillColor(Color::White);
                                    tryAgain.draw(textTry);
                                    tryAgain.display();
                                }
                                getHighScore(score);
                            }
                            //////draw//////
                            Play.draw(background);
                            Play.draw(textScore);
                            Play.draw(textLife);
                            Play.draw(textBomb);
                            for(auto i:entities) i->draw(Play);
                            Play.display();
                        }
                    }
                    if (x == 1){
                        RenderWindow Play(VideoMode(W, H), "Game!!!");
                        Play.setFramerateLimit(60);
                        music.play();
                        //Khoi tao nguoi choi va vat the
                        std::list<Entity*> entities;

                        for(int i=0;i<2;i++){
                          asteroid *a = new asteroid();
                          a->settings(sRock, rand()%W, rand()%H, rand()%360, 25);
                          entities.push_back(a);
                        }

                        player *p = new player();
                        p->settings(sPlayer,300,400,0,20);
                        p->life=5;
                        entities.push_back(p);
                        player *p2 = new player();
                        p2->settings(sPlayer,900,400,0,20);
                        p2->life=5;
                        p2->name="player2";
                        entities.push_back(p2);

                        while (Play.isOpen()){
                            Event aevent;
                            while (Play.pollEvent(aevent)){
                                if (aevent.type == Event::Closed){
                                    Play.close();
                                    music.stop();
                                }
                                if (aevent.type == Event::KeyReleased){
                                    if (aevent.key.code == Keyboard::Escape){
                                        Play.close();
                                        music.stop();
                                    }
                                    if (aevent.key.code == Keyboard::Space && p->life>0){
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
                                        sound1.play();
                                    }
                                    if (aevent.key.code == Keyboard::Numpad1 && p2->life>0){
                                        if(power2==1){
                                            bullet *b = new bullet();
                                            b->settings(sBullet2,p2->x,p2->y,p2->angle+3, 10);
                                            entities.push_back(b);
                                        }
                                        if(power2==2){
                                            bullet *b = new bullet();
                                            bullet *b2 = new bullet();
                                            b->settings(sBullet2,p2->x,p2->y,p2->angle+3, 10);
                                            b2->settings(sBullet2,p2->x,p2->y,p2->angle-3, 10);
                                            entities.push_back(b);
                                            entities.push_back(b2);
                                        }
                                        if(power2==3){
                                            bullet *b = new bullet();
                                            bullet *b2 = new bullet();
                                            bullet *b3 = new bullet();
                                            b->settings(sBullet2,p2->x,p2->y,p2->angle+3, 10);
                                            b2->settings(sBullet2,p2->x,p2->y,p2->angle-3, 10);
                                            b3->settings(sBullet2,p2->x,p2->y,p2->angle, 10);
                                            entities.push_back(b);
                                            entities.push_back(b2);
                                            entities.push_back(b3);
                                        }
                                        sound1.play();
                                    }
                                    if (aevent.key.code == Keyboard::B && p->life>0){
                                        if(bombCount>0){
                                            Entity *b = new bomb();
                                            b->settings(sBomb, p->x, p->y, p->angle-90, 0);
                                            entities.push_back(b);
                                            textBomb.setString(bombUpdate(strBomb, bombCount));
                                        }
                                    }
                                    if (aevent.key.code == Keyboard::Numpad2 && p2->life>0){
                                        if(bombCount2>0){
                                            Entity *b = new bomb();
                                            b->settings(sBomb, p2->x, p2->y, p2->angle-90, 0);
                                            entities.push_back(b);
                                            textBomb2.setString(bombUpdate(strBomb, bombCount2));
                                        }
                                    }
                                }
                            }
                            if(p->life>0){
                                if (Keyboard::isKeyPressed(Keyboard::W)){
                                    p->thrust=true;
                                    p->anim = sPlayer_go;
                                }
                                else{
                                    p->thrust=false;
                                    p->anim = sPlayer;
                                }
                            }
                            if(p2->life>0){
                                if (Keyboard::isKeyPressed(Keyboard::Up) && p2->life>0){
                                    p2->thrust=true;
                                    p2->anim = sPlayer_go;
                                }
                                else{
                                    p2->thrust=false;
                                    p2->anim = sPlayer;
                                }
                            }
                            if (Keyboard::isKeyPressed(Keyboard::D) && p->life>0){
                                p->angle+=3;
                                p->anim = sPlayer_turnRight;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::Right) && p2->life>0){
                                p2->angle+=3;
                                p2->anim = sPlayer_turnRight;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::A) && p->life>0){
                                p->angle-=3;
                                p->anim = sPlayer_turnLeft;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::Left) && p2->life>0){
                                p2->angle-=3;
                                p2->anim = sPlayer_turnLeft;
                            }


                            for(auto a:entities)
                                for(auto b:entities){
                                    if (a->name=="asteroid" && b->name=="bullet")
                                        if ( isCollide(a,b) ){
                                            a->life=0;
                                            b->life=0;
                                            sound2.play();
                                            textScore.setString(scoreUpdate(strScore, score));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                            if(rand()%40==0){
                                                Entity *h = new heart();
                                                h->settings(sHeart,b->x,b->y, -90, 15);
                                                entities.push_back(h);
                                            }
                                            if(rand()%40==1){
                                                Entity *p = new powerIcon();
                                                p->settings(sPower,b->x,b->y, -90, 15);
                                                entities.push_back(p);
                                            }
                                            for(int i=0;i<2;i++){
                                                if (a->R==15) continue;
                                                Entity *e = new asteroid();
                                                e->settings(sRock_small,a->x,a->y,rand()%360,15);
                                                entities.push_back(e);
                                            }
                                        }
                                    if (a->name=="enemy" && b->name=="bullet")
                                        if ( isCollide(a,b) ){
                                            a->life=0;
                                            b->life=0;
                                            sound2.play();
                                            textScore.setString(scoreUpdate(strScore, score));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                            if(rand()%30==0){
                                                Entity *b = new bombIcon();
                                                b->settings(sBombIcon,a->x, a->y, -90, 15);
                                                entities.push_back(b);
                                            }
                                        }
                                    if (a->name=="player" && b->name=="powerIcon")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(power<3) power++;
                                        }
                                    if (a->name=="player2" && b->name=="powerIcon")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(power2<3) power2++;
                                        }
                                    if (a->name=="player" && b->name=="heart")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(p->life<5){
                                                p->life++;
                                                textLife.setString(lifeUpdate2(strLife, life));
                                            }
                                        }
                                    if (a->name=="player2" && b->name=="heart")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(p2->life<5){
                                                p2->life++;
                                                textLife2.setString(lifeUpdate2(strLife, life2));
                                            }
                                        }
                                    if (a->name=="player" && b->name=="bombIcon")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(bombCount<3){
                                                textBomb.setString(bombUpdate2(strBomb, bombCount));
                                            }
                                        }
                                    if (a->name=="player2" && b->name=="bombIcon")
                                        if ( isCollide(a,b) ){
                                            b->life=0;
                                            sound3.play();
                                            if(bombCount2<3){
                                                textBomb2.setString(bombUpdate2(strBomb, bombCount2));
                                            }
                                        }
                                    if (a->name=="player" && b->name=="enemy")
                                        if ( isCollide(a,b) ){
                                            a->life-=1;
                                            b->life=0;
                                            if(power>1) --power;
                                            sound2.play();
                                            textLife.setString(lifeUpdate(strLife, life));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion_ship,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);

                                            //p->settings(sPlayer,W/2,H/2,0,20);
                                            //p->dx=0; p->dy=0;
                                        }
                                    if (a->name=="player2" && b->name=="enemy")
                                        if ( isCollide(a,b) ){
                                            a->life-=1;
                                            b->life=0;
                                            if(power2>1) --power2;
                                            sound2.play();
                                            textLife2.setString(lifeUpdate(strLife, life2));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion_ship,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);

                                            //p->settings(sPlayer,W/2,H/2,0,20);
                                            //p->dx=0; p->dy=0;
                                        }
                                    if (a->name=="player" && b->name=="asteroid")
                                        if ( isCollide(a,b) ){
                                            a->life-=1;
                                            b->life=0;
                                            if(power>1) --power;
                                            sound2.play();
                                            textLife.setString(lifeUpdate(strLife, life));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion_ship,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                        }
                                    if (a->name=="player2" && b->name=="asteroid")
                                        if ( isCollide(a,b) ){
                                            a->life-=1;
                                            b->life=0;
                                            if(power2>1) --power2;
                                            sound2.play();
                                            textLife2.setString(lifeUpdate(strLife, life2));

                                            Entity *e = new Entity();
                                            e->settings(sExplosion_ship,a->x,a->y);
                                            e->name="explosion";
                                            entities.push_back(e);
                                        }
                                }
                            for(auto e:entities)
                                if (e->name=="bomb")
                                    if (e->anim.isEnd()){
                                        e->life=0;
                                        for(auto a:entities)
                                            if(a->name == "asteroid" || a->name == "enemy"){
                                                textScore.setString(scoreUpdate(strScore, score));
                                                a->life=false;
                                                sound2.play();
                                                Entity *e = new Entity();
                                                e->settings(sExplosion,a->x,a->y);
                                                e->name="explosion";
                                                entities.push_back(e);
                                            }
                                    }

                            for(auto e:entities)
                                if (e->name=="explosion" || e->name=="bomb"){
                                    if (e->anim.isEnd())
                                        e->life=0;
                                }


                            if (rand()%200==0){
                                asteroid *a = new asteroid();
                                a->settings(sRock, 0,rand()%H, rand()%360, 25);
                                entities.push_back(a);
                            }
                            if (rand()%300==0){
                                enemy *e = new enemy();
                                e->settings(sEnemy, 0,rand()%H, rand()%360, 25);
                                entities.push_back(e);
                            }

                            for(auto i=entities.begin();i!=entities.end();){
                                Entity *e = *i;

                                e->update();
                                e->anim.update();

                                if (e->life==0) {i=entities.erase(i); delete e;}
                                else i++;
                            }
                            if (p->life == 0 && p2->life==0){
                                RenderWindow tryAgain(VideoMode(W, H), "End game");
                                sound7.play();
                                music.stop();
                                while(tryAgain.isOpen()){
                                    Event bevent;
                                    while (tryAgain.pollEvent(bevent)){
                                        if (bevent.type == Event::Closed)
                                            tryAgain.close();

                                        if (bevent.type == Event::KeyPressed)
                                            if (bevent.key.code == Keyboard::Escape)
                                                tryAgain.close();
                                    }
                                    Play.close();
                                    tryAgain.draw(gameOver);
                                    textTry.setCharacterSize(40);
                                    textTry.setString("Your score: "+ to_string(score));
                                    textTry.setPosition(600, 450);
                                    textTry.setFillColor(Color::White);
                                    tryAgain.draw(textTry);
                                    tryAgain.display();
                                }
                                getHighScore(score);
                            }
                            //////draw//////
                            Play.draw(background);
                            Play.draw(textScore);
                            Play.draw(textLife);
                            Play.draw(textBomb);
                            Play.draw(textLife2);
                            Play.draw(textBomb2);
                            for(auto i:entities) i->draw(Play);
                            Play.display();
                        }
                    }
                    if (x == 2){
                        RenderWindow howToPlay(VideoMode(W, H), "How to play");
                        while (howToPlay.isOpen()){
                            Event aevent;
                            while (howToPlay.pollEvent(aevent)){
                                if (aevent.type == Event::Closed)
                                    howToPlay.close();

                                if (aevent.type == Event::KeyPressed)
                                    if (aevent.key.code == Keyboard::Escape)
                                        howToPlay.close();
                            }
                            howToPlay.draw(backHow);
                            howToPlay.display();
                        }
                    }
                    if (x == 3){
                        RenderWindow highScore(VideoMode(W, H), "High score");
                        while (highScore.isOpen()){
                            boardScore board(app.getSize().x, app.getSize().y);
                            //getHighScore(score);
                            Event aevent;
                            while (highScore.pollEvent(aevent)){
                                if (aevent.type == Event::Closed)
                                    highScore.close();

                                if (aevent.type == Event::KeyPressed)
                                    if (aevent.key.code == Keyboard::Escape)
                                        highScore.close();
                            }
                            highScore.draw(background);
                            board.draw(highScore);
                            highScore.display();
                        }
                    }
                    if (x == 4) {
                        app.close();
                    }
                }
            }
        }
        app.draw(backMenu);
        menu.draw(app);
        app.display();
    }
    return 0;
}
