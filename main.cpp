#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <chrono>
#include "helpers.cpp"
#include "vectors.cpp"

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

void print_field(char *field, int width, int heigth)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < heigth; j++)
        {
            print_to_coordinates(j, i, field[i + j * width]);
        }
    }
}

int main()
{
    winsize w = get_resolution();
    int width = w.ws_col;
    int height = w.ws_row;;
    char *field = new char[width * height];
    float relation = (float)width / height;
    float pixel_relation = 11.0f / 23.0f;
    //char gradient[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    char gradient[] = " .:-=+*#%@";
    int gradient_size = std::size(gradient) - 2;


    for (int t = 0; t < 10000; t++)
    {
        vec3 light = vec3(sin(t*0.01), cos(t*0.01), sin(t*0.01)).norm();
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                vec2 point = vec2(i, j) / vec2(width, height) * 2.0f - 1.0f;
                point.x *= relation * pixel_relation;
                vec3 ro = vec3(sin(t*0.001)-2.3, 0, 0);
                vec3 rd = vec3(1, point).norm();
                char pixel = ' ';
                int color = 0;
                vec3 ce(0, 0, 0);
                vec2 intersection = sphIntersect(ro, rd, ce, 1.0f);
                if (intersection.x > 0)
                {
                    vec3 itPoint = ro + rd * intersection.x;
                    vec3 n = itPoint.norm();
                    float diff = n.dot(light);
                    color = (int)(diff *20);
                }

                color = clamp(color, 0, gradient_size);
                pixel = gradient[color];
                field[i + j * width] = pixel;
            }
        }
        print_field(field, width, height);
    }

    delete[] field;
    return 0;
}
