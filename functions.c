#include <stdint.h>

uint8_t get_pixel(int width, int height, int x, int y, uint8_t* ptr, int8_t channel)
{
    if(x >= width) x = width - 1;
    if(y >= height) y = height - 1;
    return *(ptr + (y*width + x) * 3 + channel);
}


void set_pixel(int width, int height, int x, int y, uint8_t* ptr, int8_t channel, uint8_t value)
{
    if(x >= width) x = width - 1;
    if(y >= height) y = height - 1;
    *(ptr + (y*width + x) * 3 + channel) = value;
}