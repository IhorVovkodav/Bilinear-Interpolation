#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "struct.h"

//channel: r = 0; g = 1; b = 2

void basic_scale(struct ppm_file file, int8_t scale, uint8_t* newFile)
{
    float scaling_factor = 1.0f / (scale * scale);
    int16_t scaled_width = scale * file.width;
    int16_t scaled_height = scale * file.height;
    for(int8_t channel = 0; channel < 3; channel++) {
        for (int x = 0; x < file.width; x++) {
            for (int y = 0; y < file.height; y++) {
                //aus jedem urspruenglichen Pixel wird ein Quadrat mit der Groesse scale * scale gefuellt
                uint8_t c00 = get_pixel(file.width, file.height, x, y, file.pixel, channel);
                uint8_t c01 = get_pixel(file.width, file.height, x, y + 1, file.pixel, channel);
                uint8_t c10 = get_pixel(file.width, file.height, x + 1, y, file.pixel, channel);
                uint8_t c11 = get_pixel(file.width, file.height, x + 1, y + 1, file.pixel, channel);
                for (int dx = 0; dx < scale; dx++) {
                    for (int dy = 0; dy < scale; dy++) {
						//Interpolationsergebnis
                       uint64_t new_color =
                                c00 * (scale - dx) * (scale - dy) +
                                c10 * dx * (scale - dy) +
                                c01 * (scale - dx) * dy +
                                c11 * dx * dy;
                        uint8_t pixel = new_color * scaling_factor;
                        set_pixel(scaled_width, scaled_height, x * scale + dx, y * scale + dy, newFile, channel, pixel);
                    }
                }
                set_pixel(scaled_width, scaled_height, x * scale, y * scale, newFile, channel, c00);
            }
        }
    }
}
