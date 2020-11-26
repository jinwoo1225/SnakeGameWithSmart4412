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


#define CLCD "/dev/clcd"

class CharacterLCD
{
private:
    int clcd_fd;
    void print(char text[]){
        clcd_fd = open(CLCD, O_WRONLY);
        write(clcd_fd, text, 32);
        close(clcd_fd);
    }
public:
    void beforeGame(){
        print("   Snake Game     Press Start   ");
    }

    void gaming(){
        print()
    }
    
};

