#include <immintrin.h>
#include <emmintrin.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "struct.h"

void scale_intrinsics(struct ppm_file file, int scale, uint8_t* newFile) {
	if(scale == 1) {
		newFile = file.pixel;
		return;
	}
	
	float increment = 1.0f / (scale);
    int scaled_width = scale * file.width;
    int scaled_height = scale * file.height;
	
	float a00, b00, c00, d00, a01, b01, c01, d01, a10, b10, c10, d10, a11, b11, c11, d11;
	
	__m128 _dx, _dy, _scaleDx, _scaleDy, _tmp, _tmp1, _tmp2, _result;
	float fx, fy;
for(int8_t channel = 0; channel < 3; channel++) {
	for (int y = 0; y < file.width; y++) {
		for (int x = 0; x < file.height; x += 4) {
			
			a00 = get_pixel(file.width, file.height, x, y, file.pixel, channel);
			a01 = get_pixel(file.width, file.height, x, y+1, file.pixel, channel);
			a10 = get_pixel(file.width, file.height, x+1, y, file.pixel, channel);
			a11 = get_pixel(file.width, file.height, x+1, y+1, file.pixel, channel);

			b00 = a10;
			b01 = a11;
			b10 = get_pixel(file.width, file.height, x+2, y, file.pixel, channel);
			b11 = get_pixel(file.width, file.height, x+2, y+1, file.pixel, channel);

			c00 = b10;
			c01 = b11;
			c10 = get_pixel(file.width, file.height, x+3, y, file.pixel, channel);
			c11 = get_pixel(file.width, file.height, x+3, y+1, file.pixel, channel);

			d00 = c10;
			d01 = c11;
			d10 = get_pixel(file.width, file.height, x+4, y, file.pixel, channel);
			d11 = get_pixel(file.width, file.height, x+4, y+1, file.pixel, channel);

			__m128 _x00 = _mm_setr_ps(a00, b00, c00, d00);
			__m128 _x01 = _mm_setr_ps(a01, b01, c01, d01);
			__m128 _x10 = _mm_setr_ps(a10, b10, c10, d10);
			__m128 _x11 = _mm_setr_ps(a11, b11, c11, d11);

			for (int dx = 0; dx < scale; dx++) {
                    for (int dy = 0; dy < scale; dy++) {
						_scaleDx = _mm_set_ps1(1.0f - fx);
						_scaleDy = _mm_set_ps1(1.0f - fy);
						_dx = _mm_set_ps1(fx);
						_dy = _mm_set_ps1(fy);
						
						_result = _mm_mul_ps(_mm_mul_ps(_x00, _scaleDy), _scaleDx);
						
						_tmp2 = _mm_mul_ps(_mm_mul_ps(_x10, _scaleDy), _dx);
						
						_tmp1 = _mm_mul_ps(_mm_mul_ps(_x01, _dy), _scaleDx);
						
						_tmp = _mm_mul_ps(_mm_mul_ps(_x11, _dy), _dx);
						
						
						_result = _mm_add_ps(_mm_add_ps(_tmp1, _tmp), _mm_add_ps(_tmp2, _result));
						

                        set_pixel(scaled_width, scaled_height, x * scale + dx, y * scale + dy, newFile, channel, _result[0]);
						set_pixel(scaled_width, scaled_height, (x+1) * scale + dx, y * scale + dy, newFile, channel, _result[1]);
						set_pixel(scaled_width, scaled_height, (x+2) * scale + dx, y * scale + dy, newFile, channel, _result[2]);
						set_pixel(scaled_width, scaled_height, (x+3) * scale + dx, y * scale + dy, newFile, channel, _result[3]);
						fy += increment;
                    }
					fy = 0.0f;
					fx += increment;
                }
				fx = 0.0f;
                set_pixel(scaled_width, scaled_height, x * scale, y * scale, newFile, channel, _x00[0]);
				set_pixel(scaled_width, scaled_height, (x+1) * scale, y * scale, newFile, channel, _x00[1]);
				set_pixel(scaled_width, scaled_height, (x+2) * scale, y * scale, newFile, channel, _x00[2]);
				set_pixel(scaled_width, scaled_height, (x+3) * scale, y * scale, newFile, channel, _x00[3]);
		


		}
	}
}
}