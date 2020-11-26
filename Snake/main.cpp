//
//  main.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/24.
//

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstdlib>
#include <sys/signal.h>
#include <sys/types.h>
#include <asm/ioctls.h>

#include "DotMatrix.cpp"
#include "Snake.cpp"
#include "TactSW.cpp"
#include "CharacterLCD.cpp"

#define TIME_QUANTUM 1667

using namespace std;

#ifndef COORD_SET
typedef struct coord
{
    int y;
    int x;
} coord;
#endif

#ifndef ENUM_SET
typedef enum : int
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OK
} UDLR;
#endif

class Game
{
private:
    int timer;
    int highScore;
    coord snakeCoord;
    Snake s;
    DotMatrix dM;
    TactSW TSW;
    CharacterLCD CL;

    //벡터를 매트릭스로 표현
    void vector2Matrix(vector<coord> V)
    {
        dM.clear();
        for (coord trail : V)
        {
            dM.set(trail);
        }
    }

public:
    Game()
    {
        highScore = 0;
    }

    void start()
    {
        int score;
        int head;
        int temp;
        printf("game : waiting for user to press OK\n");
        CL.beforeGame();
        while (true)
        {

            snakeCoord = s.get();
            printf("game : snake constructed @ y:%d x:%d\n", snakeCoord.y, snakeCoord.x);
            while (TSW.get() != 4)
                ;
            timer = score = 0;
            head = -1;
            printf("game : waiting for selecting head\n");
            CL.gaming(score, highScore);
            while ((head < 0) || (head > 3))
            {
                dM.openDot();
                print();
                usleep(TIME_QUANTUM * 20);
                head = TSW.get();
                dM.closeDot();
            }

            move(head);
            printf("game : user selected head and game just started\n");
            while (true)
            {

                dM.openDot();
                print();
                usleep(TIME_QUANTUM * 20);
                dM.closeDot();
                temp = TSW.get();

                if ((temp >= 0) && (temp < 4))
                {
                    head = temp;
                }
                if (!(timer % int(30 / s.getSpeed())))
                {
                    if (!move(head))
                    {
                        break;
                    }
                    if (score != s.getScore())
                    {
                        score = s.getScore();
                        // 먹이 하나먹을때마다 갱신
                        CL.gaming(score, highScore);
                    }
                }

                timer++;
                if (timer >= 30)
                {
                    timer = 0;
                }
            }
            printf("game : user just losted the game\nscore : %d", score);
            CL.gameOver(score);
            if (score > highScore)
            {
                highScore = score;
            }
            sleep(5);
            printf("game : waiting for user to press OK\n");
            CL.beforeGame();
            s.reset();
        }
    }

    //heading이 향하는 방향으로 움직임
    bool move(int heading)
    {

        //snake의 go메소드를 통해서 heading으로 한칸 움직임
        bool ret = s.go(heading);
        snakeCoord = s.get();
        printf("moving %d: %d, %d\n", heading, snakeCoord.y, snakeCoord.x);
        return ret;
    }

    //장비에 출력
    void print()
    {
        vector2Matrix(s.getTrail());
        dM.set(s.getPrey());
        // dM.printToSerial();
        dM.drawToMatrix();
    }

    bool isGameOver(coord C, vector<coord> T)
    {
        for (coord trail : T)
        {
            if ((C.x == trail.x) && (C.y == trail.y))
            {
                return true;
            }
        }

        if (!(s.isOnSpace(C)))
        {
            return false;
        }

        return true;
    }
};

int main(int argc, const char *argv[])
{
    Game g;

    printf("starting game...\n");
    g.start();
    printf("ending game...\n");

    return 0;
}
