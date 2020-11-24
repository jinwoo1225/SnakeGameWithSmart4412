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

using namespace std;

typedef struct coord{
    int y;
    int x;
} coord;

class DotMatrix {
private:
    int dot_fd;
    bool matrix[8][8];
    
public:
    DotMatrix(){
//        실제 장비에서 사용하는 코드
//        dot_fd = open(DOT_DEV, O_RDWR);
//        if (dot_fd < 0)
//        {
//            printf("Can't Open Device\n");
//        }
        memset(matrix, 0, sizeof(bool) * 8 * 8);
    }
    
    
    // Matrix에 원하는 점을 출력
    void set(int y, int x){
        matrix[y][x] = true;
    }
    // 시리얼로 출력
    void printToSerial(){
        for (int i =0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (matrix[i][j]) {
                    printf("* ");
                }else {
                    printf("o ");
                }
            }
            printf("\n");
        }
    }
    
    // 매트릭스로 출력
    void drawToMatrix(){
        unsigned char rows[8];
        for (int i = 0; i < 8; i++)
        {
            rows[i] = 0;
            for (int j = 0; j < 8; j++)
            {
                rows[i] += matrix[i][j] << j;
            }
        }
//        실제 장비에서의 출력
//        write(dot_fd, &rows, sizeof(rows));
    }
    
};

class Snake {
private:
    coord currentYX;
    int size;
    vector<coord> trail;
    int heading;
    
    
public:
    Snake(coord C){
        this->size=1;
        currentYX = C;
        pushTrail(C);
    }
    
    coord get(){
        return currentYX;
    }
    
    void pushTrail(coord C){
        trail.insert(trail.begin(), C);
    }
    
    vector<coord> getTrail(int size){
        vector<coord> ret;
        ret.assign(trail.begin(), trail.begin() + size);
        return ret;
    }
    

};

class Game {
private:
    int timer;
    coord snakeCoord;
    
public:
    Game(){
        
        Snake s({getRandomNum(8), getRandomNum(8)});
        DotMatrix dM;
        snakeCoord = s.get();
        printf("snake constructed : %d,%d\n",snakeCoord.y, snakeCoord.x);
    }
    
    void start(){
        
    }
    
    void move(){
        
    }
    
    
    
    static int getRandomNum(int max){
        return rand() % max;
    }
};

int main(int argc, const char * argv[]) {
    Game g;
    return 0;
}
