#include <stdint.h>
#include <math.h>

//Vergleicht zwei Pixelarrays und gibt die Übereinstimmung in Prozent zurück
double compare_percent(uint16_t width, uint16_t height, uint8_t* reference, uint8_t* actual){
    uint32_t pixels = width * height * 3;
    double match = 0.0;
    double diff = 100.0 / pixels;
    for (uint32_t i = 0; i < pixels; i++)
    {
        if(reference[i] == actual[i])
        {
            match += diff;
        }
    }
    return match;
}


//Vergleicht zwei Pixelarrays und schreibt die Differenz als neue Bilddatei an den vorgesehenen Pointer
void compare_diffmap(uint16_t width, uint16_t height, uint8_t* reference, uint8_t* actual, uint8_t* diffmap){
    uint32_t pixels = width * height * 3;
    for (uint32_t i = 0; i < pixels; i++)
    {
        diffmap[i] = abs(reference[i] - actual[i]);
    }
}