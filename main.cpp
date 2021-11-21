#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>

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
    int width = w.ws_col;
    int height = w.ws_row;
    float relation = (float)width / height;
    float pixel_relation = 11.0f / 23.0f;


    float t = 0;
    while (true)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                float x = (float)i / width * 2.0f - 1.0f;
                float y = (float)j / height * 2.0f - 1.0f;
                x *= relation * pixel_relation;
                char pixel = ' ';
                if (0.7f * cos(x + t * M_PI) < y)
                {
                    pixel = '@';
                }
                print_to_coordinates(j, i, pixel);
            }
        }
        if (t <= 2 * M_PI)
            t += 0.01;
        else
            t = t- 2*M_PI;
    }

    return 0;
}
