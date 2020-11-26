//
//  DotMatrix.cpp
//  Snake
//
//  Created by HongJinwoo on 2020/11/25.
//

#include "DotMatrix.hpp"
#define DOT_DEV "/dev/dot"
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

public:
    DotMatrix()
    {
        dot_fd = -1;
        //        실제 장비에서 사용하는 코드
        // dot_fd = open(DOT_DEV, O_RDWR);
        // if (dot_fd < 0)
        // {
        //     printf("Can't Open Device\n");
        // }
        memset(matrix, 0, sizeof(bool) * 8 * 8);
    }

    ~DotMatrix()
    {
        //        실제 장비에서 사용하는 코드
        close(dot_fd);
    }

    void clear()
    {
        memset(matrix, 0, sizeof(bool) * 8 * 8);
    }

    // Matrix에 원하는 점을 출력
    void set(coord C)
    {
        matrix[C.y][C.x] = true;
    }

    // 시리얼로 출력
    void printToSerial()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (matrix[i][j])
                {
                    printf("* ");
                }
                else
                {
                    printf("o ");
                }
            }
            printf("\n");
        }
    }

    // 매트릭스로 출력
    void drawToMatrix()
    {
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
            // printf("%x",rows[i]);
            // printf("\n");
        }
        //        실제 장비에서의 출력
        write(dot_fd, &rows, sizeof(rows));
    }

    void closeDot()
    {
        close(dot_fd);
    }

    void openDot()
    {
       dot_fd = open(DOT_DEV, O_WRONLY);
    }
};
