/* 
 * File:   output.h
 * Author: SteveBinary
 */

#ifndef OUTPUT_H
#define OUTPUT_H

void GenerateOutputPath(char o_outputPath[], char i_relativePath[], char i_fileName[], int i_numberOfPoints, char i_colorMode, int i_strokeWeight);
void PrintImageToConsole(byte** i_img);
void ExportToPPM(byte** i_img, int i_numberOfPoints, char i_colorMode, int i_strokeWeight);

#endif /* OUTPUT_H */
