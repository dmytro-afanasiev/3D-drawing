#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <chrono>
#include <thread>


winsize get_resolution()
{
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}
void print_to_coordinates(int x, int y, char c)
{
    printf("\033[%d;%dH%c", x, y, c);
}

int main()
{
    winsize w = get_resolution();
    int height = w.ws_row;
    int width = w.ws_col;
    float relation = (float)width / height;
    float pixel_relation = 11.0f / 23.0f;

    float t = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float y = (float)i / height * 2.0f - 1.0f;
            float x = (float)j / width * 2.0f - 1.0f;

            x *= relation * pixel_relation;
            char pixel = ' ';
            if (x*x + y*y < 0.5)
            {
                pixel = '@';
            }
            print_to_coordinates(i, j, pixel);
        }
    }

    return 0;
}
