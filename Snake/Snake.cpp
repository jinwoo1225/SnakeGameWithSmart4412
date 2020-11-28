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
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

#define ENUM_SET

using namespace std;

#ifndef COORD_SET
typedef struct coord
{
    int y;
    int x;
} coord;
#endif

//ENUM을 활용해서 0,1,2,3,4를 설정
typedef enum : int
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OK
} UDLR;

class Snake
{
private:
    coord currentYX;
    coord prey;
    vector<coord> trail;
    vector<coord> remaining;
    int size;
    int speed;

    int getRandomNum(int max)
    {
        return rand() % max;
    }

    void removeFromRemaining(coord C)
    {
        for (int i = 0; i < remaining.size(); i++)
        {
            if (C.x == remaining[i].x && C.y == remaining[i].y)
            {
                printf("snake: removed from v remainingector %d, %d\n", remaining[i].y, remaining[i].x);
                remaining.erase(remaining.begin() + i);
            }
        }
    }

    //디버깅용함수
    void printVector(vector<coord> V)
    {
        bool M[8][8];
        memset(&M, false, sizeof(bool) * 8 * 8);
        for (coord C : V)
        {
            M[C.y][C.x] = true;
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%d", M[i][7 - j]);
            }
            printf("\n");
        }
    }

public:
    Snake()
    {
        srand((unsigned int)time(NULL));
        reset();
    }

    void reset()
    {
        printf("snake : resetting snake game\n");
        trail.clear();
        remaining.clear();
        coord C = {getRandomNum(8), getRandomNum(8)};
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                remaining.push_back({i, j});
            }
        }

        //생성자 추가할때
        //사이즈 1로 설정
        this->size = 1;
        this->speed = 1;
        //현재 위치를 C로 설정
        currentYX = C;
        //Trail에도 추가
        pushTrail(C);
        setPrey();
    }

    coord get()
    {
        //현재 위치 출력
        return currentYX;
    }

    //향하는 방향으로 움직임.
    bool go(int heading)
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
            ret.x += 1;
            break;

        case RIGHT:
            ret.x -= 1;
            break;

        default:
            break;
        }
        if (isOnSpace(ret))
        {
            //규정된 space내에 위치한다면, 좌표로이동
            //그렇지 않다면 게임오버.
            currentYX = ret;

            //먹이를 먹으면 스코어==size++ 새로운 먹이 생성
            if (currentYX.y == prey.y && currentYX.x == prey.x)
            {
                printf("snake : prey eaten\n");
                size++;
                pushTrail(ret);
                setPrey();
                if ((size % 10) == 0)
                {
                    speed++;
                }
            }
            else
            {
                pushTrail(ret);
            }
            //자신의 꼬리와 만난다면 게임오버
            for (int i = 1; i < trail.size(); i++)
            {
                if ((ret.x == trail[i].x) && (ret.y == trail[i].y))
                {
                    return false;
                }
            }

            return true;
        }
        return false;
    }

    void pushTrail(coord C)
    {
        //        trail의 앞부분에 C추가
        trail.insert(trail.begin(), C);
        removeFromRemaining(C);
        remaining.insert(remaining.begin(), trail.begin() + size, trail.end());
        trail.assign(trail.begin(), trail.begin() + size);
    }

    vector<coord> getTrail()
    {
        return trail;
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

    coord setPrey()
    {
        prey = remaining[getRandomNum(remaining.size())];
        removeFromRemaining(prey);
        printf("snake : prey setted at %d, %d\n", prey.y, prey.x);
        // 디버깅용
        // printVector(remaining);
        // printVector(trail);
        return prey;
    }

    coord getPrey()
    {
        return prey;
    }
    int getScore()
    {
        return size;
    }
};
