/* 
 * File:   main.c
 * Author: SteveBinary
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "types.h"
#include "definitions.h"
#include "bresenham.h"
#include "image_processing.h"
#include "output.h"

void DrawFigure(int i_numberOfPoints, char i_colorMode, int i_strokeWeight);

int main()
{
    int numberOfPoints, strokeWeight;
    char colorMode, confirmation;
    bool error = false;
    
    // explanation
    printf("Die exportierten Bilder finden Sie im selben Ordner der source files oder der .exe (vielleicht in: ...\\src\\dist\\Debug\\Cygwin-Windows)\n");
    printf("Den Output-Ordner können Sie ggf. im Header-File \"definitions.h\" ändern.\n");
    printf("Die Namen der Dateien sind wie folgt zu verstehen:\n");
    printf("   n:   Anzahl der Punkte auf dem Kreis, die verbunden werden sollen\n");
    printf("   col: color\n");
    printf("        n=normal -> schwarze Linien mit weißem Hintergrund\n");
    printf("        d=dark   -> weiße Linien mit schwarzem Hintergrund\n");
    printf("        f=funky  -> jeder gesetzte Pixel bekommt eine zufällige Farbe\n");
    printf("   sw:  stroke weight -> die Dicke der Linien (tatsächliche Dicke in Pixeln ist 2*sw-1)\n\n");

    do
    {
        error = false;
        int c;

        // number of points
        printf("Anzahl der Punkte auf dem Kreis [0 ... 100]: ");
        if (!scanf("%d", &numberOfPoints))
        {
            printf("Das sollte eine ganze Zahl >= 0 und <= 100 sein!\n");
            error = true;
        }
        while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
        if (0 > numberOfPoints || 100 < numberOfPoints)
        {
            printf("Das sollte eine ganze Zahl >= 0 und <= 100 sein!\n");
            error = true;
        }

        if (error) continue;

        // stroke weight
        printf("Linienstärke [1 ... 100]  ->  entspricht 2*Stärke-1 Pixel echte Pixel: ");
        if (!scanf("%d", &strokeWeight))
        {
            printf("Das sollte eine ganze Zahl >= 1 und <= 100 sein!\n");
            error = true;
        }
        while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
        if (1 > strokeWeight || 100 < strokeWeight)
        {
            printf("Das sollte eine ganze Zahl >= 1 und <= 100 sein!\n");
            error = true;
        }
        
        if (error) continue;

        // color mode
        printf("Farbmodus [n=normal  d=dark  f=funky]: ");
        if (!scanf("%c", &colorMode))
        {
            printf("Das sollte n, d oder f sein!\n");
            error = true;
        }
        while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
        if ('n' != colorMode && 'd' != colorMode && 'f' != colorMode)
        {
            printf("Das sollte n, d oder f sein!\n");
            error = true;
        }

        if (error) continue;

        // confirmation
        printf("Das Bild mit den eingegebenen Werten exportieren? [j/n]: ");
        if (!scanf("%c", &confirmation))
        {
            printf("Das sollte j oder n sein!\n");
            error = true;
        }
        while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
        if ('j' != confirmation && 'n' != confirmation)
        {
            printf("Das sollte j oder n sein!\n");
            error = true;
        }
    }
    while (error);

    if ('j' == confirmation)
    {
        DrawFigure(numberOfPoints, colorMode, strokeWeight);
    }
    else
    {
        printf("Sie haben den Vorgang abgebrochen!\n");
    }
    
    // wait for user interaction -> user can see the information on the screen
    printf("\nDrücke ENTER zum Beenden.");
    scanf("%c");
    
    return 0;
}

void DrawFigure(int i_numberOfPoints, char i_colorMode, int i_strokeWeight)
{
    byte** img = GetEmptyQuadraticImage();
    int halfSize = SIZE / 2;
    int circleRadius = halfSize - i_strokeWeight - 10;

    DrawCircle(img, halfSize, halfSize, circleRadius, i_strokeWeight);

    int* pointsOnCircleToConnect = GetEvenlySpacedPointsOnCircle(
            halfSize,
            halfSize,
            circleRadius,
            i_numberOfPoints
        );

    ConnectAllPoints(img, pointsOnCircleToConnect, i_numberOfPoints, i_strokeWeight);

    ExportToPPM(img, i_numberOfPoints, i_colorMode, i_strokeWeight);

    FreeQuadraticImage(img);
}
