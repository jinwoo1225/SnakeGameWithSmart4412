#define LED_DEV "/dev/led"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

const unsigned char ledArray[8] = {
    0xFE,
    0xFD,
    0xFB,
    0xF7,
    0xEF,
    0xDF,
    0xBF,
    0x7F};
class LED
{
private:
    /* data */
    int offset;
    int led_fd;

public:
    LED()
    {
        offset = 0;
        led_fd = -1;
    }

    void openLED()
    {
        led_fd = open(LED_DEV, O_RDWR);
    }

    void closeLED()
    {
        close(led_fd);
    }

    void next()
    {
        int led = 0;
        if (offset > 7)
        {
            offset = 0;
        }

        write(led_fd, &ledArray[offset++], sizeof(unsigned char));
    }

    void full()
    {
        unsigned char a = 0x00;
        write(led_fd, &a, sizeof(unsigned char));
    }
};
