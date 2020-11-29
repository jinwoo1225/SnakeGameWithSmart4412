#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define FND_DEV "/dev/fnd"
#define FND_MAX 8

class FND
{
private:
    int fnd_fd;
    int timer;

    // n이 0부터 9까지의 값이라면 해당하는 FND비트를 해당하지 않으면 아무것도 표시하지않는 비트를 반환
    unsigned char asc_to_fnd(int n)
    {
        unsigned char FND_BITS[11] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98, 0xFF};
        return n >= 0 && n < 10 ? FND_BITS[n] : FND_BITS[10];
    }

    void openFND() { fnd_fd = open(FND_DEV, O_WRONLY); }
    void closeFND() { close(fnd_fd); }

public:
    FND()
    {
        fnd_fd = -1;
        timer = 0;
    }
    void reset() { timer = 0; }
    void next() { timer++; }

    // 지정된 시간동안 FND에 출력
    void draw(int microSec)
    {
        // shout out to 변우섭
        openFND();
        unsigned char Hex_Code[4];
        memset(Hex_Code, 0x00, sizeof(Hex_Code));

        int TargetNum = timer;
        int i;
        for (i = 1; i < 4 + 1; i++)
        {
            int Num = TargetNum / pow(10, 4 - i);
            TargetNum -= Num * pow(10, 4 - i);
            Hex_Code[i - 1] = asc_to_fnd(Num);
        }
        write(fnd_fd, Hex_Code, 4);
        usleep(microSec);
        closeFND();
    }
};
