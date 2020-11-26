#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define CLCD "/dev/clcd"
using namespace std;

class CharacterLCD
{
private:
    int clcd_fd;
    void print(string S)
    {
        char *cstr = new char[S.length() + 1];
        strcpy(cstr, S.c_str());
        clcd_fd = open(CLCD, O_WRONLY);
        write(clcd_fd, cstr, 32);
        close(clcd_fd);
    }

public:
    void beforeGame()
    {
        string s1 = "   Snake Game   ";
        string s2 = "   Press Start  ";
        print(s1 + s2);
    }

    void gaming(int score, int highScore)
    {

        string s1 = "Score   : " + scoreSpacer(score, 4) + "  ";

        string s2 = "Hi Score: " + scoreSpacer(highScore, 4) + "  ";
        print(s1 + s2);
    }

    string scoreSpacer(int I, int space)
    {
        string STR = to_string(I);
        for (int i = STR.length(); i < space; i++)
        {
            STR = '0' + STR;
        }
        return STR;
    }
};
