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
//#include <sys/signal.h>
//#include <sys/types.h>
//#include <asm/ioctls.h>

#include "DotMatrix.cpp"
#include "Snake.cpp"
#include "TactSW.cpp"

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
    RIGHT
} UDLR;
#endif

class Game
{
private:
    int timer;
    coord snakeCoord;
    Snake s;
    DotMatrix dM;
    TactSW TSW;

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
        snakeCoord = s.get();
        printf("snake constructed : %d,%d\n", snakeCoord.y, snakeCoord.x);
    }

    void start(int heading)
    {
        while (true)
        {
            // printf("%d\n",timer);
            if (!(timer % 10))
            {
                print();
            }
            if (!(timer % int(600 / s.getSpeed())))
            {
                move(heading); 
            }
            heading = TSW.get();
            usleep(TIME_QUANTUM);
            timer++;
            if (timer >= 600)
            {
                timer = 0;
            }
        }
    }

    //heading이 향하는 방향으로 움직임
    void move(int heading)
    {
        //snake의 go메소드를 통해서 heading으로 한칸 움직임
        s.go(heading);

        snakeCoord = s.get();
        printf("moving %d: %d, %d\n", heading, snakeCoord.y, snakeCoord.x);
    }

    //장비에 출력
    void print()
    {
        vector2Matrix(s.getTrail(1));
        dM.printToSerial();
    }
};

int main(int argc, const char *argv[])
{
    Game g;
    TactSW TSW;
    int keyStroke = 255;
    while (keyStroke < 4)
    {
        keyStroke = TSW.get();
    }
    printf("starting game...\n");
    g.start(keyStroke);
    
    //    usleep(16666);

    return 0;
}
