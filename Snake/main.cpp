//
//  main.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/24.
//  스네이크 게임에 필요한 장비들의 클래스 초기화 게임로직을 담고있는 파일

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "DotMatrix.cpp"
#include "Snake.cpp"
#include "TactSW.cpp"
#include "CharacterLCD.cpp"
#include "LED.cpp"
#include "FND.cpp"

// 1/600초를 정의
#define TIME_QUANTUM 1667

using namespace std;

// YX좌표를 표현하기 위한 구조체
#ifndef COORD_SET
typedef struct coord
{
    int y;
    int x;
} coord;
#endif

class Game
{
private:
    int timer;
    int highScore;
    coord snakeCoord;
    Snake s;
    DotMatrix DM;
    TactSW TSW;
    CharacterLCD CL;
    LED LE;
    FND FN;

    //주어진 벡터를 닷 매트릭스로 설정
    void vector2Matrix(vector<coord> V)
    {
        DM.clear();
        for (coord dot : V)
        {
            DM.set(dot);
        }
    }

public:
    Game()
    {
        highScore = 0;
    }

    // 게임 시작
    void start()
    {
        int score, head, temp, temp2;

        // CLCD에 게임시작방법 표시
        printf("game : waiting for user to press OK\n");
        CL.beforeGame();
        while (true)
        {
            // 현재 뱀의 위치 반환 후 시리얼에 표시
            snakeCoord = s.get();
            printf("game : snake constructed @ y:%d x:%d\n", snakeCoord.y, snakeCoord.x);

            //TactSW가 OK 버튼을 누를때까지 대기
            while (TSW.get() != 4)
                ;

            //타이머와 스코어 초기화
            timer = score = 1;

            // head를 -1로 초기화하여 사용자가 플레이어를 확인하고 시작하게 도움
            head = -1;

            // 게임이 시작되었으므로 CLCD 표시 내용 변경
            printf("game : waiting for selecting head\n");
            CL.gaming(score, highScore);

            // 사용자가 방향키를 입력할때까지 무한 대기 화면에 Snake만 출력
            while ((head < 0) || (head > 3))
            {
                printWoPrey(TIME_QUANTUM * 20);
                head = TSW.get();
            }

            // snake의 시작방향 정의
            // go메소드가 실패하면 게임 오버 다시 실행
            temp2 = s.go(head);
            printf("game : user selected head and game just started\n");

            while (temp2)
            {
                // 20/600초 동안 dotMatrix에 표시
                print(TIME_QUANTUM * 20);
                // 1/600초 동안 LED에 표시
                LE.draw(TIME_QUANTUM * 1);
                // 9/600초 동안 FND에 표시
                FN.draw(TIME_QUANTUM * 9);

                // 이 순간은 모든 장치가 Close되어있음
                // TactSW의 메소드 get은 장치를 빠른 속도로 열고
                // 장치의 값을 read함
                temp = TSW.get();

                // TactSW의 값이 내가 원하는 값인가?
                if ((temp >= 0) && (temp < 4))
                {
                    // 그렇다면 진행방향으로 이동
                    head = temp;
                }
                // Snake의 속도에 비례해서 이동속도 표현
                if (!(timer % int(20 / s.getSpeed())))
                {
                    LE.next();
                    // snake가 head방향으로 전진
                    if (!s.go(head))
                    {
                        // 이동에 문제가 발생하였다면 게임오버
                        break;
                    }

                    // 현재 스코어와 스네이크의 스코어가 다르다면?
                    if (score != s.getScore())
                    {
                        // 스코어를 저장
                        score = s.getScore();
                        // CLCD 갱신
                        CL.gaming(score, highScore);
                    }
                }

                //타이머 시간초 추가
                timer++;
                // 20번 수행할때마다 0으로 초기화
                // 20번 수행하면 1초가 지나감
                if (!(timer % 20))
                {
                    timer = 0;
                    FN.next();
                }
            }

            // While문을 탈출했다면 CLCD값 변경
            printf("game : user just losted the game\nscore : %d\n", score);
            CL.gameOver(score);

            // HighScore를 넘겼다면 값 변경
            if (score > highScore)
            {
                highScore = score;
            }

            // 모든 LED 점등
            LE.full();
            // 5초동안 그리기
            LE.draw(5 * 1000 * 1000);

            // 게임 리셋
            printf("game : waiting for user to press OK\n");
            CL.beforeGame();
            FN.reset();
            s.reset();
        }
    }

    //장비에 출력
    void print(int microSec)
    {
        vector2Matrix(s.getTrail());
        DM.set(s.getPrey());
        // DM.printToSerial();
        DM.drawToMatrix(microSec);
    }

    // 먹이를 띄우지 않고 출력
    void printWoPrey(int microSec)
    {
        vector2Matrix(s.getTrail());
        DM.drawToMatrix(microSec);
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
