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

typedef enum : int {
    UP,
    DOWN,
    LEFT,
    RIGHT
} UDLR;

int getRandomNum(int max){
    return rand() % max;
}

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
    
    ~DotMatrix(){
//        실제 장비에서 사용하는 코드
//        close(dot_fd);
    }
    
    
    // Matrix에 원하는 점을 출력
    void set(coord C){
        matrix[C.y][C.x] = true;
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
                rows[i] |= matrix[i][j] << j;
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
    Snake(){
        coord C = {getRandomNum(8), getRandomNum(8)};
        //생성자 추가할때
        //사이즈 1로 설정
        this->size=1;
        //현재 위치를 C로 설정
        currentYX = C;
        //Trail에도 추가
        pushTrail(C);
    }
    
    coord get(){
        //현재 위치 출력
        return currentYX;
    }
    
    coord go(int heading){
        coord ret = currentYX;
        switch (heading) {
            case UP:
                ret.y -= 1;
                break;
                
            case DOWN:
                ret.y += 1;
                break;
                
            case LEFT:
                ret.x -= 1;
                break;
                
            case RIGHT:
                ret.x += 1;
                break;
                
            default:
                break;
        }
        if(isOnSpace(ret)){
            currentYX = ret;
            pushTrail(ret);
        }
        return currentYX;
    }
    
    void pushTrail(coord C){
//        trail의 앞부분에 C추가
        trail.insert(trail.begin(), C);
    }
    
    vector<coord> getTrail(int size){
//        trail의 앞부분 부터 size크기 만큼 반환
        vector<coord> ret;
        ret.assign(trail.begin(), trail.begin() + size);
        return ret;
    }
    
    static bool isOnSpace(coord C){
        bool ret = true;
        if (C.y > 8 || C.y < 0 || C.x > 8 || C.x <0) {
            ret = false;
        }
        return ret;
    }
    

};

class Game {
private:
    int timer;
    coord snakeCoord;
    Snake s;
    DotMatrix dM;
    
    void vector2Matrix(vector<coord> V){
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
