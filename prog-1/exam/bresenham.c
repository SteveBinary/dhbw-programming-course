/*
 * File:   bresenham.c
 * Author: SteveBinary
 */

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "types.h"
#include "definitions.h"
#include "image_processing.h"

/**
 * Draws a line in the given image from the point (x0, y0) to (x1, y1).
 * The coordinates can be outside the picture (the setPixel function checks 
 * the values, so the index will never be out of bounds) so that even if the 
 * start and end point are both outside the image, a part of the line could 
 * be visible in the picture. Thus, the drawing will always be successful, 
 * even if nothing was drawn actually.
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 * @param i_x0 : the x-coordinate of the start point of the line
 * @param i_y0 : the y-coordinate of the start point of the line
 * @param i_x1 : he x-coordinate of the end point of the line
 * @param i_y1 : the y-coordinate of the end point of the line
 * @param i_strokeWeight : the thickness of the line; the real thickness in terms
 *      of actual pixels will be 2*i_strokeWeight - 1
 */
void DrawLine(byte** io_img, int i_x0, int i_y0, int i_x1, int i_y1, int i_strokeWeight)
{
    int dx = abs(i_x1 - i_x0);
    int dy = abs(i_y1 - i_y0);
    int sx = i_x0 < i_x1 ? 1 : -1;
    int sy = i_y0 < i_y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    bool end = false;

    while (!end)
    {
        SetPixelWithStrokeWeight(io_img, i_x0, i_y0, i_strokeWeight);

        if (i_x0 == i_x1 && i_y0 == i_y1)
        {
            // Whole line drawn from start to end
            end = true;
        }

        e2 = err;

        if (e2 >-dx)
        {
            err -= dy;
            i_x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            i_y0 += sy;
        }
    }
}

/**
 * Draws the 8 points / pixels in the given image, so that a circle can be 
 * drawn by the drawCircle function.
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 * @param i_xCenter : the x-coordinate of the center of the circle
 * @param i_yCenter : the y-coordinate of the center of the circle
 * @param i_xOffset : the x-offset
 * @param i_yOffset : the y-offset
 * @param i_strokeWeight : the thickness of the pixels; the real thickness in terms
 *      of actual pixels will be 2*i_strokeWeight - 1
 */
static void Draw8Tuple(byte** io_img, int i_xCenter, int i_yCenter, int i_xOffset, int i_yOffset, int i_strokeWeight)
{
    SetPixelWithStrokeWeight(io_img, i_xCenter + i_xOffset, i_yCenter + i_yOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter + i_xOffset, i_yCenter - i_yOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter - i_xOffset, i_yCenter + i_yOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter - i_xOffset, i_yCenter - i_yOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter + i_yOffset, i_yCenter + i_xOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter + i_yOffset, i_yCenter - i_xOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter - i_yOffset, i_yCenter + i_xOffset, i_strokeWeight);
    SetPixelWithStrokeWeight(io_img, i_xCenter - i_yOffset, i_yCenter - i_xOffset, i_strokeWeight);
}

/**
 * Draws a circle in the given picture with the center at (xCenter, yCenter)
 * and a radius of radius. Like the drawLine function, the drawCircle function
 * draws all points / pixels which are visible in the picture, even if some
 * parts are outside the actual picture. Thanks to the setPixel function 
 * checking if a possible point / pixel is inside the bounds of the picture.
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 * @param i_xCenter : the x-coordinate of the center of the circle
 * @param i_yCenter : the y-coordinate of the center of the circle
 * @param i_radius : the radius of the circle
 * @param i_strokeWeight : the thickness of the circle line; the real thickness 
 *      in terms of actual pixels will be 2*i_strokeWeight - 1
 */
void DrawCircle(byte** io_img, int i_xCenter, int i_yCenter, int i_radius, int i_strokeWeight)
{
    int x = 0, y = i_radius;
    int d = 3 - 2 * i_radius;

    Draw8Tuple(io_img, i_xCenter, i_yCenter, x, y, i_strokeWeight);

    while (y >= x)
    {
        x++;

        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }

        Draw8Tuple(io_img, i_xCenter, i_yCenter, x, y, i_strokeWeight);
    }
}
