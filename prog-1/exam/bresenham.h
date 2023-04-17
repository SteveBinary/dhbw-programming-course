/* 
 * File:   bresenham.h
 * Author: SteveBinary
 */

#ifndef BRESENHAM_H
#define BRESENHAM_H

void DrawLine(byte** io_img, int i_x0, int i_y0, int i_x1, int i_y1, int i_strokeWeight);
void DrawCircle(byte** io_img, int i_xCenter, int i_yCenter, int i_radius, int i_strokeWeight);

#endif /* BRESENHAM_H */
