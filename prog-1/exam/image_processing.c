/*
 * File:   image_processing.c
 * Author: SteveBinary
 */

#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "bresenham.h"
#include "definitions.h"
#include "image_processing.h"

#define PI 3.1415926536

/**
 * Returns a pointer to an array of arrays of byte values - the pixel values.
 * It is basically a 2D-array representing the image. Dimension is: SIZExSIZE
 * 
 * @return a pointer to an array of arrays of byte values
 */
byte** GetEmptyQuadraticImage()
{
    byte** img;

    img = (byte**) malloc(SIZE * sizeof (*img));
    for (int i = 0; i < SIZE; ++i)
    {
        img[i] = (byte*) malloc(SIZE * sizeof (*img[i]));
    }

    return img;
}

/**
 * It frees the memory used by the quadratic image of that specific edge length
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 */
void FreeQuadraticImage(byte** io_img)
{
    for (int i = 0; i < SIZE; ++i)
    {
        free(io_img[i]);
    }
    free(io_img);
}

/**
 * Sets the Pixel of the given image if x and y are valid. If so, it returns
 * success (1), else it returns failure (0).
 * (0, 0) is in the top left corner.
 * (SIZE - 1, SIZE - 1) is in the bottom right corner.
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 * @param i_x : the x-coordinate (column) of the pixel to be drawn
 * @param i_y : the y-coordinate (row) of the pixel to be drawn
 * @return whether the pixel to set is inside the image bounds and could be 
 *      set (1) or the pixel is outside the image bounds and couldn't be set (0)
 */
int SetPixel(byte** io_img, int i_x, int i_y)
{
    if (i_x < 0 || i_x >= SIZE || i_y < 0 || i_y >= SIZE)
    {
        return 0;
    }

    io_img[i_y][i_x] = (byte) 1;
    // Array is [row][column] but in order to have the origin at the top left
    // corner, the x-direction horizontally and the y-direction vertically, the
    // coordinates must be swapped.

    return 1;
}

/**
 * Basically, it draws a filled circle at (i_x, i_y) in the given image. This
 * ensures that skew lines don't appear thicker as the horizontal or vertical ones.
 * The real thickness in terms of actual pixels will be 2*i_strokeWeight - 1.
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 * @param i_x : the x-coordinate (column) of the pixel to be drawn
 * @param i_y : the y-coordinate (row) of the pixel to be drawn
 * @param i_strokeWeight : the thickness of the pixel; the real thickness in terms
 *      of actual pixels will be 2*i_strokeWeight - 1
 */
void SetPixelWithStrokeWeight(byte** io_img, int i_x, int i_y, int i_strokeWeight)
{
    --i_strokeWeight;

    for (int x = -i_strokeWeight; x <= i_strokeWeight; ++x)
    {
        for (int y = -i_strokeWeight; y <= i_strokeWeight; ++y)
        {
            if (x * x + y * y <= i_strokeWeight * i_strokeWeight)
            {
                SetPixel(io_img, i_x + x, i_y + y);
            }
        }
    }
}

/**
 * Evenly spaced points on a circle means, all points are on the circle and
 * the angle between them (measured from the circle center) or respectively
 * the arc between two adjacend points is always the same.
 * Returns a pointer to a region in memory where the points are located, of 
 * the form: x0, y0, x1, y1, x2, y2, ...
 * So the first two addresses store the first point (x0, y0), the
 * next two addresses store the second point (x1, y1) and so on.
 * There are numberOfPoints points, so the region has a size of 2 times that
 * because each point consists of an x-coordinate and a y-coordinate.
 * 
 * @param i_xCenter : the x-coordinate of the center of the circle
 * @param i_yCenter : the y-coordinate of the center of the circle
 * @param i_radius : the radius of the circle
 * @param i_numberOfPoints : the number of points to space evenly on the circle
 * @return a pointer to a region in memory containing the points
 */
int* GetEvenlySpacedPointsOnCircle(int i_xCenter, int i_yCenter, int i_radius, int i_numberOfPoints)
{
    int* o_p_pointsToConnect = (int*) malloc(2 * i_numberOfPoints * sizeof (int));
    double angleBetweenPoints = 2 * PI / i_numberOfPoints;
    double angle = -PI / 2; // -90° to start at the top
    double x, y;

    for (int i = 0; i < i_numberOfPoints * 2; i += 2)
    {
        x = i_radius * cos(angle) + i_xCenter;
        y = i_radius * sin(angle) + i_yCenter;

        o_p_pointsToConnect[i + 0] = (int) round(x);
        o_p_pointsToConnect[i + 1] = (int) round(y);

        angle += angleBetweenPoints;
    }

    return o_p_pointsToConnect;
}

/**
 * Draws a line in the given image from each point to all the other points.
 * For efficiency, no line gets drawn twice.
 * 
 * @param io_img : represents a 2d array where the pixels should be set
 * @param i_p_points : a pointer to a region in memory where the points are located, 
 *      of the form: x0, y0, x1, y1, x2, y2, ...
 *      So the first two addresses store the first point (x0, y0), the
 *      next two addresses store the second point (x1, y1) and so on.
 *      There are numberOfPoints points, so the region has a size of 
 *      2 times that because each point consists of an x-value and a y-value.
 * @param i_numberOfPoints : the number of points to connect to each other
 * @param i_strokeWeight : the thickness of the connection lines; the real thickness 
 *      in terms of actual pixels will be 2*i_strokeWeight - 1
 */
void ConnectAllPoints(byte** io_img, int* i_p_points, int i_numberOfPoints, int i_strokeWeight)
{
    for (int i = 0; i < i_numberOfPoints * 2; i += 2)
    {
        int x0 = i_p_points[i + 0];
        int y0 = i_p_points[i + 1];

        for (int j = i + 2; j < i_numberOfPoints * 2; j += 2)
        {
            int x1 = i_p_points[j + 0];
            int y1 = i_p_points[j + 1];

            DrawLine(io_img, x0, y0, x1, y1, i_strokeWeight);
        }
    }
}
