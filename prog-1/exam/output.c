/*
 * File:   output.c
 * Author: SteveBinary
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "definitions.h"

/**
 * It generates the relative path inclusive the file name from the parameters
 * relativPath, fileName and numberOfPoints. The resulting path gets written
 * where ever the pointer "outputPath" points to.
 * 
 * @param o_outputPath : the pointer to which the resulting path gets written
 * @param i_relativePath : the relative path to the output file - excluding the file name
 * @param i_fileName : the file name of the generated image - excluding the file extension
 * @param i_numberOfPoints : the number of points will be indecated in the file name
 * @param i_colorMode : the color mode will be indecated in the file name
 * @param i_strokeWeight : the stroke weight will be indecated in the file name
 */
void GenerateOutputPath(char o_outputPath[], char i_relativePath[], char i_fileName[], int i_numberOfPoints, char i_colorMode, int i_strokeWeight)
{
    char numAsString[4];
    char strokeWeightAsString[4];
    char colorModeString[2] = {i_colorMode, '\0'};

    snprintf(numAsString, 4, "%d", i_numberOfPoints);
    snprintf(strokeWeightAsString, 4, "%d", i_strokeWeight);

    strncat(o_outputPath, i_relativePath, 130);
    strncat(o_outputPath, i_fileName, 75);
    strncat(o_outputPath, "_n=", 4);
    strncat(o_outputPath, numAsString, 5);
    strncat(o_outputPath, "_col=", 6);
    strncat(o_outputPath, colorModeString, 5);
    strncat(o_outputPath, "_sw=", 5);
    strncat(o_outputPath, strokeWeightAsString, 5);
    strncat(o_outputPath, ".ppm", 5);
}

/**
 * Prints the given image on the console.
 * Set pixels are marked with X and unset / empty pixels are marked with a .
 * Mostly for development and debug purposes.
 * 
 * @param i_img : represents a 2d array where the pixels should be set
 */
void PrintImageToConsole(byte** i_img)
{
    for (int x = 0; x < SIZE; ++x)
    {
        for (int y = 0; y < SIZE; ++y)
        {
            if (1 == i_img[x][y])
            {
                printf("X ");
            }
            else
            {
                printf(". ");
            }
        }

        printf("\n");
    }
}

/**
 * helper-function because of insufficient random functionality
 * srand() must initialize prng before use!
 * 
 * @param range : integer-range from 0 to range (excluding)
 * @return a random value between 0 and range (excluding)
 */
int randomInt(int range)
{
    return rand() % range;
}

/**
 * Exports the given image as a .ppm file. Each set pixel will be black and all
 * the others will be white.
 * 
 * @param i_img : represents a 2d array where the pixels should be set
 * @param i_numberOfPoints : the number of points will be indecated in the file name
 * @param i_colorMode : the color mode will be indecated in the file name
 * @param i_strokeWeight : the stroke weight will be indecated in the file name
 */
void ExportToPPM(byte** i_img, int i_numberOfPoints, char i_colorMode, int i_strokeWeight)
{
    char outputPath[250] = "";
    GenerateOutputPath(outputPath, RELATIVE_PATH, FILENAME, i_numberOfPoints, i_colorMode, i_strokeWeight);
    srand(time(NULL));

    FILE *p_file = fopen(outputPath, "w");

    if (NULL != p_file)
    {
        fprintf(p_file, "P3\n %d %d\n 255\n", SIZE, SIZE); // file header

        // writing actual pixel data
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                if (1 == i_img[x][y])
                {
                    switch (i_colorMode)
                    {
                    case 'd': fprintf(p_file, "255 255 255\n");
                        break;
                    case 'f':
                    {
                        char red[4], green[4], blue[4], pixelValue[12] = "";

                        snprintf(red, 4, "%d", randomInt(256));
                        snprintf(green, 4, "%d", randomInt(256));
                        snprintf(blue, 4, "%d", randomInt(256));

                        strncat(pixelValue, red, 4);
                        strncat(pixelValue, " ", 2);
                        strncat(pixelValue, green, 4);
                        strncat(pixelValue, " ", 2);
                        strncat(pixelValue, blue, 4);
                        strncat(pixelValue, "\n", 2);

                        fprintf(p_file, pixelValue);
                        break;
                    }
                    default: fprintf(p_file, "0 0 0\n");
                        break;
                    }
                }
                else
                {
                    switch (i_colorMode)
                    {
                    case 'd': fprintf(p_file, "0 0 0\n");
                        break;
                    default: fprintf(p_file, "255 255 255\n");
                        break;
                    }
                }
            }
        }

        fclose(p_file);
        printf("INFO: Bild gespeichert: %s\n", outputPath);
    }
    else
    {
        printf("FEHLER: Bild konnte nicht gespeichert werden: %s\n", outputPath);
    }
}
