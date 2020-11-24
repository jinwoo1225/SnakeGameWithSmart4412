//
//  Snake.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/25.
//

#include "Snake.hpp"
#include <iostream>
#include <vector>
#include <string.h>

#define ENUM_SET

using namespace std;

#ifndef COORD_SET
typedef struct coord
{
    int y;
    int x;
} coord;
#endif

typedef enum : int
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} UDLR;

class Snake
{
private:
    coord currentYX;
    vector<coord> trail;
    int size;
    int heading;
    int speed;

    int getRandomNum(int max)
    {
        return rand() % max;
    }

public:
    Snake()
    {
        coord C = {getRandomNum(8), getRandomNum(8)};
        //생성자 추가할때
        //사이즈 1로 설정
        this->size = 1;
        this->speed = 1;
        //현재 위치를 C로 설정
        currentYX = C;
        //Trail에도 추가
        pushTrail(C);
    }

    coord get()
    {
        //현재 위치 출력
        return currentYX;
    }

    //향하는 방향으로 움직임.
    coord go(int heading)
    {
        coord ret = currentYX;
        switch (heading)
        {
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
        if (isOnSpace(ret))
        {
            //규정된 space내에 위치한다면, 좌표로이동
            //그렇지 않다면, 제자리 걸음.
            currentYX = ret;
            pushTrail(ret);
        }
        return currentYX;
    }

    void pushTrail(coord C)
    {
        //        trail의 앞부분에 C추가
        trail.insert(trail.begin(), C);
    }

    vector<coord> getTrail(int size)
    {
        //        trail의 앞부분 부터 size크기 만큼 반환
        vector<coord> ret;
        ret.assign(trail.begin(), trail.begin() + size);
        return ret;
    }

    int getSpeed()
    {
        return this->speed;
    }

    // 8*8의 판 위에 존재하는 지 확인하는 코드
    static bool isOnSpace(coord C)
    {
        bool ret = true;
        if (C.y > 7 || C.y < 0 || C.x > 7 || C.x < 0)
        {
            ret = false;
        }
        return ret;
    }
};
