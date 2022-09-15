#ifndef PPM_FILE
#define PPM_FILE
struct ppm_file {
    bool ascii;
    uint16_t width;
    uint16_t height;
    uint16_t maxvalue;
    uint8_t* pixel;
};

extern uint8_t get_pixel(int width, int height, int x, int y, uint8_t* ptr, int8_t channel);

extern void set_pixel(int width, int height, int x, int y, uint8_t* ptr, int8_t channel, uint8_t value);

#endif
