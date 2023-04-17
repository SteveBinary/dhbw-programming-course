/* 
 * File:   image_processing.h
 * Author: SteveBinary
 */

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

byte** GetEmptyQuadraticImage();
void FreeQuadraticImage(byte** io_img);
int SetPixel(byte** io_img, int i_x, int i_y);
void SetPixelWithStrokeWeight(byte** io_img, int i_x, int i_y, int i_strokeWeight);
int* GetEvenlySpacedPointsOnCircle(int i_xCenter, int i_yCenter, int i_radius, int i_numberOfPoints);
void ConnectAllPoints(byte** io_img, int* i_p_points, int i_numberOfPoints, int i_strokeWeight);

#endif
