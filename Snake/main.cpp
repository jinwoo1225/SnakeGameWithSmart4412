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

using namespace std;

#ifndef COORD_SET
typedef struct coord{
    int y;
    int x;
} coord;
#endif

#ifndef ENUM_SET
typedef enum : int {
    UP,
    DOWN,
    LEFT,
    RIGHT
} UDLR;
#endif

class Game {
private:
    int timer;
    coord snakeCoord;
    Snake s;
    DotMatrix dM;
    
    void vector2Matrix(vector<coord> V){
        dM.clear();
        for (coord trail : V) {
            dM.set(trail);
        }
    }
    
public:
    Game(){
        snakeCoord = s.get();
        printf("snake constructed : %d,%d\n",snakeCoord.y, snakeCoord.x);
    }
    
    void start(int heading){
        move(heading);
    }
    
    void move(int heading){
        s.go(heading);
        snakeCoord = s.get();
        printf("moving %d: %d, %d\n",heading,snakeCoord.y, snakeCoord.x);
    }
    
    void print(){
        vector2Matrix(s.getTrail(1));
        dM.printToSerial();
    }
};

int main(int argc, const char * argv[]) {
    Game g;
    
//    usleep(16666);
    
    g.start(UP);
    g.print();
    g.move(RIGHT);
    g.print();
    g.move(DOWN);
    g.print();
    g.move(DOWN);
    g.print();
    g.move(DOWN);
    g.print();
    
    return 0;
}
