//
//  DotMatrix.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/25.
//

#define DOT_DEV "/dev/dot"
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

#define COORD_SET
typedef struct coord
{
    int y;
    int x;
} coord;

class DotMatrix
{
private:
    int dot_fd;
    bool matrix[8][8];

    void openDot() { dot_fd = open(DOT_DEV, O_WRONLY); }
    void closeDot() { close(dot_fd); }

public:
    DotMatrix()
    {
        dot_fd = -1;
        memset(matrix, 0, sizeof(bool) * 8 * 8);
    }
    ~DotMatrix() { close(dot_fd); }

    // 모든 매트릭스 초기화
    void clear() { memset(matrix, 0, sizeof(bool) * 8 * 8); }
    // Matrix에 원하는 점을 출력
    void set(coord C) { matrix[C.y][C.x] = true; }

    // 시리얼로 출력 -> 디버깅용
    void printToSerial()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf(matrix[i][j] ? "* " : "o ");
            }
            printf("\n");
        }
    }

    // 매트릭스로 출력
    void drawToMatrix(int microSec)
    {
        openDot();
        unsigned char rows[8];
        for (int i = 0; i < 8; i++)
        {
            rows[i] = 0;
            for (int j = 0; j < 8; j++)
            {
                if (matrix[i][j])
                {
                    rows[i] |= 1 << j;
                }
            }
        }
        write(dot_fd, &rows, sizeof(rows));
        usleep(microSec);
        closeDot();
    }
};
