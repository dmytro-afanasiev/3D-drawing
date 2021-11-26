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

float cut(float value, float min, float max){
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else return value;
}

float distance_from_centre(float x, float y){
    return sqrt(x*x + y*y);
}

int main()
{
    winsize w = get_resolution();
    int height = w.ws_row;
    int width = w.ws_col;
    float relation = (float)width / height;
    float pixel_relation = 11.0f / 23.0f;
    char gradient[] = " .:!/r(l1Z4H9W8$@";
    int gradient_size = std::size(gradient) - 2;

    float t = 0;
    //while (true){
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float y = (float)i / height * 2.0f - 1.0f;
            float x = (float)j / width * 2.0f - 1.0f;
            x *= relation * pixel_relation;
            //x += sin(t*0.005);
            char pixel = ' ';
            float distance_to_point = distance_from_centre(x, y);
        
            int color = (int)(0.5f/ distance_to_point);
            color = cut(color, 0, gradient_size);
            pixel = gradient[color];
            print_to_coordinates(i, j, pixel);
        }
    //}
    t++;
    }

    return 0;
}
