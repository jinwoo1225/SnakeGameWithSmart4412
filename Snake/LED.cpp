#define LED_DEV "/dev/led"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

const unsigned char ledArray[9] = {
    0xFE,
    0xFD,
    0xFB,
    0xF7,
    0xEF,
    0xDF,
    0xBF,
    0x7F,
    0x00};
class LED
{
private:
    /* data */
    int offset;
    int led_fd;

    void openLED() { led_fd = open(LED_DEV, O_WRONLY); }
    void closeLED() { close(led_fd); }

public:
    LED()
    {
        offset = 0;
        led_fd = -1;
    }

    //다음 LED로 이동
    void next()
    {
        if (offset > 6)
            offset = 0;
        offset++;
    }
    //모든 LED점등
    void full() { offset = 8; }

    void draw(int microSec)
    {
        openLED();
        write(led_fd, &ledArray[offset], sizeof(unsigned char));
        usleep(microSec);
        closeLED();
    }
};
