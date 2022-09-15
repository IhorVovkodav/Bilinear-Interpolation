#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "read_ppm.c"
#include "compare.c"
#include "struct.h"

// Author: Dominik Schwarz
// Version: 0.4

//Assembler Implementation (mit SIMD)
extern void scale(struct ppm_file file, int8_t scale, uint8_t* newFile);

extern void basic_scale(struct ppm_file file, int8_t scale, uint8_t* newFile);

extern void scale_intrinsics(struct ppm_file file, int scale, uint8_t* newFile);

int writeInOutput(uint8_t* values, struct ppm_file input, uint8_t scaleFac, int count, char* outputname) {
	
	// Erstellt den Namen der .ppm Datei
	char dest[60];
	char src[6];
	// Größe von outputname wurde am Anfang von main() überprüft
	strncpy(dest, outputname, 51);
	strcpy(src, ".ppm");
	
	strncat(dest, src, 6);
	
	// true -> ascii, false -> binär
	// Ascii
	if(input.ascii) {
		// Ausgabe Datei erstellen
		FILE* output;
		output = fopen(dest, "w");

		if(!output) {
			return 1;
		}
		
		fprintf(output, "P3\n");
		fprintf(output, "%d %d\n", input.width * scaleFac, input.height * scaleFac);
		fprintf(output, "%u\n", input.maxvalue);
		
		for(int i = 0; i < count; i++){
			fprintf(output, "%d\n", values[i]);
		}
		
		fclose(output);
	// Binär
	} else {
		// Ausgabe Datei erstellen
		FILE* output;
		output = fopen(dest, "wb");

		if(!output) {
			return 1;
		}
		
		int newWidth = input.width * scaleFac;
		int newHeight = input.height * scaleFac;

		fprintf(output, "P6\n");
		fprintf(output, "%d %d\n", newWidth, newHeight);
		fprintf(output, "%u\n", input.maxvalue);

		fwrite(values, 3, newHeight * newWidth, output);
		
		fclose(output);
	}
	// Sucess
	return 0;
}


int main(int argc, char** argv) {

	if(argc == 2) {
		// Ausgabe für --help oder -h
		if(!strcmp("--help", argv[1]) || !strcmp("-h", argv[1])) {
			printf("HELP for %s:\n\n", argv[0]);
			printf("Usage:\n\t%s [filename] [scaleFac] [variant] [outputname] [timing]\n\n", argv[0]);
			printf("Filename:\n\tWrite the .ppm file to upscale in there.\n\n");
			printf("ScaleFac:\n\tUse a positive integer (without 0) to specify the output size of the result.\n\n");
			printf("Variant:\n\tChoose between four different implementations:\n");
			printf("\tc (implementation in C)\n");
			printf("\tasm (implementation in assembler)\n");
			printf("\tsimd (implementation in C with simd)\n");
			printf("\tall (all three implementations; each output is compared with c variant; output-file gets created with values of simd)\n\n");
			printf("Outputname:\n\tWrite the outputfile name in here (max. 50 characters).\n\n");
			printf("Timing:\n\tFor time measurements of the implementation choosen use:\n");
			printf("\tture (time measurement)\n\tfalse (no time measurement)\n\n");
			printf("Examples:\n\t%s input.ppm 3 c output false\n", argv[0]);
			printf("\t%s lena.ppm 5 all lena_out true\n", argv[0]);
			return 0;
		}
	}

	// Zu viele oder zu wenige Eingaben
	if(argc < 6 || argc > 6) {
		fprintf(stderr, "Usage: %s [filename] [scaleFac] [variant] [outputname] [timing]\n\tUse -h or --help for more informations!\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Skalierungsfaktor holen
	uint8_t scaleFac = atoi(argv[2]);
	if(scaleFac <= 0) {
		fprintf(stderr, "Illegal value for scaleFac!\nUsage: %s [filename] [scaleFac] [variant] [outputname] [timing]\n\tUse -h or --help for more informations!\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Prüfen, ob die Zeit für die Funktionen gemessen werden soll
	bool timing;
	if(!strcmp("true", argv[5])) {
		timing = true;
	} else if(!strcmp("false", argv[5])) {
		timing = false;
	} else {
		fprintf(stderr, "Illegal value for timing!\nUsage: %s [filename] [scaleFac] [variant] [outputname] [timing]\n\tUse -h or --help for more informations!\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Prüfen, ob der Ausgabe Name zu lang ist
	// (Wegen strcpy in writeInOutput())
	if(strlen(argv[4]) > 50) {
		fprintf(stderr, "Outputname to long!\nUsage: %s [filename] [scaleFac] [variant] [outputname] [timing]\n\tUse -h or --help for more informations!\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// Überprüfen ob Datei existiert
	FILE* input_file = fopen(argv[1], "r");

	if(!input_file) {
		fprintf(stderr, "Input file does not exist!\n");
		return EXIT_FAILURE;
	}


	// Datei einlesen
	const char* file = argv[1];
	struct ppm_file input = read_ppm(file);

	// Speicher allokieren für die Funktionen
	int sizeOfValues = input.width * scaleFac * input.height * scaleFac * 3;
	uint8_t* values = (uint8_t *) malloc(sizeOfValues);

	if(!values) {
		fprintf(stderr, "Unable to allocate heap storage for new file!\n");
		return EXIT_FAILURE;
	}

	// Mit Zeitmessung
	if(timing) {
		double time = 0;
		double average = 0;
		int iterations = 4;
	
		// Auswahl, welche Funktion benutzt werden soll
		// Funktion in c
		if(!strcmp("c", argv[3])) {
		
			// Funktion wird viermal gemessen für ein genauere Ergebnis
			for (int i = 0; i < iterations; i++) {
				struct timespec start;
				clock_gettime(CLOCK_MONOTONIC, &start);
			
				// Funktion in C
				basic_scale(input, scaleFac, values);
			
				struct timespec end;
				clock_gettime(CLOCK_MONOTONIC, &end);
			
				time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
				average += time;
				printf("%d. run took %f seconds!\n", i+1, time);
			}
			average /= iterations;
			printf("On average the function took %f seconds!\n\n", average);


		// Funktion in assembler
		} else if(!strcmp("asm", argv[3])) {
		
			// Funktion wird viermal gemessen für ein genauere Ergebnis
			for (int i = 0; i < iterations; i++) {
				struct timespec start;
				clock_gettime(CLOCK_MONOTONIC, &start);
			
				// Funktion in Assembler
				scale(input, scaleFac, values);
			
				struct timespec end;
				clock_gettime(CLOCK_MONOTONIC, &end);
			
				time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
				average += time;
				printf("%d. run took %f seconds!\n", i+1, time);
			}
			average /= iterations;
			printf("On average the function took %f seconds!\n\n", average);
	
	
		// Funktion in simd
		} else if(!strcmp("simd", argv[3])) {
		
			// Funktion wird viermal gemessen für ein genauere Ergebnis
			for (int i = 0; i < iterations; i++) {
				struct timespec start;
				clock_gettime(CLOCK_MONOTONIC, &start);
			
				// Funktion mit SIMD Befehlen
				scale_intrinsics(input, scaleFac, values);
			
				struct timespec end;
				clock_gettime(CLOCK_MONOTONIC, &end);
			
				time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
				average += time;
				printf("%d. run took %f seconds!\n", i+1, time);
			}
			average /= iterations;
			printf("On average the function took %f seconds!\n\n", average);
		
		
		// Alle Funktionen
		} else if(!strcmp("all", argv[3])) {
			uint8_t* ref = (uint8_t *) malloc(sizeOfValues);

			if(!ref) {
				fprintf(stderr, "Unable to allocate heap storage for new file!\n");
				return EXIT_FAILURE;
			}
		
			// Alle Funktion werden viermal gemessen für ein genauere Ergebnis
			for (int i = 0; i < iterations; i++) {
				struct timespec start;
				clock_gettime(CLOCK_MONOTONIC, &start);
			
				// Funktion in C
				basic_scale(input, scaleFac, ref);
			
				struct timespec end;
				clock_gettime(CLOCK_MONOTONIC, &end);
			
				time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
				average += time;
				printf("%d. run with c implementation took %f seconds!\n", i+1, time);
			}
			average /= iterations;
			printf("On average the c function took %f seconds!\n\n", average);
		
			average = 0;
			for (int i = 0; i < iterations; i++) {
				struct timespec start;
				clock_gettime(CLOCK_MONOTONIC, &start);
			
				// Funktion in Assembler
				scale(input, scaleFac, values);
			
				struct timespec end;
				clock_gettime(CLOCK_MONOTONIC, &end);
			
				time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
				average += time;
				printf("%d. run with assembler implementation took %f seconds!\n", i+1, time);
			}
			average /= iterations;
			printf("On average the assembler function took %f seconds!\n", average);
			printf("Matching reference: %f%%\n\n", compare_percent(input.width, input.height, ref, values));
		
			average = 0;
			for (int i = 0; i < iterations; i++) {
				struct timespec start;
				clock_gettime(CLOCK_MONOTONIC, &start);
			
				// Funktion mit SIMD Befehlen
				scale_intrinsics(input, scaleFac, values);
			
				struct timespec end;
				clock_gettime(CLOCK_MONOTONIC, &end);
			
				time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
				average += time;
				printf("%d. run with simd implementation took %f seconds!\n", i+1, time);
			}
			average /= iterations;
			printf("On average the simd function took %f seconds!\n", average);
			printf("Matching reference: %f%%\n\n", compare_percent(input.width, input.height, ref, values));
	
	
		// Falsche Eingabe für die Auswahl der Funktion
		} else {
			free(values);
			fprintf(stderr, "Illegal value for variant!\nUsage: %s [filename] [scaleFac] [variant] [outputname] [timing]\n\tUse -h or --help for more informations!\n", argv[0]);
			return EXIT_FAILURE;
		}
	
	
	
	// Ohne Zeitmessung
	} else {
		// Auswahl, welche Funktion benutzt werden soll
		// Funktion in C
		if(!strcmp("c", argv[3])) {
			basic_scale(input, scaleFac, values);

		// Funktion in assembler
		} else if(!strcmp("asm", argv[3])) {
			scale(input, scaleFac, values);
	
		// Funktion in simd
		} else if(!strcmp("simd", argv[3])) {
			scale_intrinsics(input, scaleFac, values);
	
		// Alle Funktionen
		} else if(!strcmp("all", argv[3])) {
			// Funktion in C
			basic_scale(input, scaleFac, values);
			// Funktion in Assembler
			scale(input, scaleFac, values);
			// Funktion mit SIMD Befehlen
			scale_intrinsics(input, scaleFac, values);
	
		// Falsche Eingabe für die Auswahl der Funktion
		} else {
			free(values);
			fprintf(stderr, "Illegal value for variant!\nUsage: %s [filename] [scaleFac] [variant] [outputname] [timing]\n\tUse -h or --help for more informations!\n", argv[0]);
			return EXIT_FAILURE;
		}
	}

	// Werte von values in die Ausgabe Datei übetragen
	int sucess = writeInOutput(values, input, scaleFac, sizeOfValues, argv[4]);

	// Falls keine Ausgabe Datei erstellt werden konnte
	if(sucess) {
		free(values);
		fprintf(stderr, "Unable to create output-file!\n");
		return EXIT_FAILURE;
	}

	free(values);
	printf("Finished sucessfully!\n");

	return 0;
}

