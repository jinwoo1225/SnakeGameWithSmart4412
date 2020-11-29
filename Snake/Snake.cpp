//
//  Snake.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/25.
//  스네이크가 어떻게 동작하고, 먹이를 어떻게 출력할지 정하는 파일

#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <ctime>

#define ENUM_SET

using namespace std;

// coord구조체 사용
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
    //뱀의 머리 좌표
    coord currentYX;
    // 뱀의 먹이 좌표
    coord prey;
    // 뱀의 머리부터 꼬리까지 담고있는 벡터
    vector<coord> trail;
    // trail와 prey를 제외한 나머지 벡터
    vector<coord> remaining;
    int size;
    int speed;

    // [0, max) 값을 반환
    int getRandomNum(int max) { return rand() % max; }

    // TrailVector에 C좌표 추가
    void pushTrail(coord C)
    {
        // trail의 앞부분에 C추가
        trail.insert(trail.begin(), C);
        // C를 remaining에서 제외
        removeFromRemaining(C);
        // remaining에 뱀의 길이에 맞지 않는 나머지 벡터 흡수
        remaining.insert(remaining.begin(), trail.begin() + size, trail.end());
        //trail에 뱀의 길이에 맞는 값만 재지정
        trail.assign(trail.begin(), trail.begin() + size);
    }

    // C를 remaining에서 제외
    void removeFromRemaining(coord C)
    {
        for (int i = 0; i < remaining.size(); i++)
        {
            if (C.x == remaining[i].x && C.y == remaining[i].y)
            {
                // coord C와 동일한 요소를 삭제
                remaining.erase(remaining.begin() + i);
                return;
            }
        }
    }

    // 먹이를 설정
    coord setPrey()
    {
        // 나머지 벡터에서 무작위로 하나를 뽑음
        prey = remaining[getRandomNum(remaining.size())];
        // 나머지 벡터에서 뽑은 요소를 제거
        removeFromRemaining(prey);
        printf("snake : prey setted at %d, %d\n", prey.y, prey.x);
        // 디버깅용
        // printVector(remaining);
        // printVector(trail);
        return prey;
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

    static bool isOnSpace(coord C)
    {
        if (C.y > 7 || C.y < 0 || C.x > 7 || C.x < 0)
        {
            return false;
        }
        return true;
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
        // trail, remaining을 빈깡통으로 재설정
        trail.clear();
        remaining.clear();
        // 새로운 뱀의 위치 지정
        coord C = {getRandomNum(8), getRandomNum(8)};
        printf("snake : constructed at %d, %d\n", C.y, C.x);
        // 나머지 벡터 재설정
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
        // 먹이 추가
        setPrey();
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

    // 8*8의 판 위에 존재하는 지 확인하는 코드

    int getScore() { return size; }
    int getSpeed() { return this->speed; }

    coord get() { return currentYX; }
    coord getPrey() { return prey; }

    vector<coord> getTrail() { return trail; }
};
