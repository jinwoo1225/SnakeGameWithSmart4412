//
//  TactSW.cpp
//  Snake
//
//  Created by Jinwoo on 2020/11/25.
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
#include <sys/signal.h>
#include <sys/types.h>
#include <asm/ioctls.h>
#include "TactSW.hpp"

static char tactswDev[] = "/dev/tactsw";

class TactSW
{
private:
    // int btn;
    // static int tactswFd;

public:
    int get()
    {
        unsigned char b;
        int tactswFd = -1;
        if ((tactswFd = open(tactswDev, O_RDONLY)) < 0)
        {
            printf("Cannot open tactSW\n");
        }
        read(tactswFd, &b, sizeof(b));
        close(tactswFd);
        // printf("Tact : %d",b);
        switch (b)
        {
        case 2:
            return 0;
        case 4:
            return 2;
        case 5:
            return 4;
        case 6:
            return 3;
        case 8:
            return 1;

        default:
            return -1;
        }
        // return b;
    }
};
