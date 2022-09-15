#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "struct.h"
// Autor: Ihor Vovkodav.
// Version: 0.4
// Um diese Funktion zu verwenden, fügen Sie einfach #include "read_ppm.c" in main file ein.

struct ppm_file read_ppm(const char* filename) {
    struct ppm_file res;
    unsigned char character;
    int number;

    //Datei öffnen.
    FILE* file = fopen(filename, "rb");

    //Test, ob die Datei wirklich geöffnet wurde.
    if(!file) {
        fprintf(stderr, "File cannot be opened.\n");
        exit(1);
    }

    //Kodierungsformat einlesen.
    int test = fscanf(file, "%c%d\n", &character, &number);

    //Kodierungsformat bestimmen.
    if (test != 2 || character != 'P' || (number != 3 && number != 6)) {
        fprintf(stderr, "It is not a .ppm file or encoding format is wrong.\n");
        exit(1);
    } else {
        if (number == 3) res.ascii = true;
        else res.ascii = false;
    }

    //Kommentare löschen.
    character = getc(file);
    while (character == '#') {
        while (character != '\n') {
	        character = getc(file);
        }
        character = getc(file);
    }
    ungetc(character, file);

    //Breite, Höhe und Farbtiefe speichern.
    if (!fscanf(file, "%hu%hu\n%hu\n", &res.width, &res.height, &res.maxvalue)) {
        fprintf(stderr, "Width, height or color depth can't be read.\n");
        exit(1);
    }

    //Test, ob die Farbtiefe zu einem 24 Bit Format passt.
    if (res.maxvalue>255) {
        fprintf(stderr, "Dieses Bild hat eine falsche Farbtiefe.\n");
        exit(1);
    } 

    //Pixeldaten einlesen.
    size_t length = res.width*res.height*3;
    uint8_t* pixels = malloc(length);
    if (!res.ascii){
        if (fread(pixels, 3, res.height*res.width, file) != (size_t)res.height*res.width) {
            fprintf(stderr, "File cannot be read correctly.\n");
            exit(1);
        }
    } else {
    	char color_char[4];
        for (size_t i = 0; i<length; i++) {
            //bis zum nächsten whitespace lesen
            if (!fscanf(file, "%s", color_char)) {
                fprintf(stderr, "File cannot be read correctly.\n");
                exit(1);
            }
            //string parsen
            pixels[i] = atoi(color_char);
        }
    }

    //Pixeldaten speichern
    res.pixel = pixels;

    //Datei schließen.
    fclose(file);

    return res;
}
