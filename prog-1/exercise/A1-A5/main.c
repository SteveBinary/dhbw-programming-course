/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: SteveBinary
 *
 * Created on 23. Dezember 2020, 15:44
 */

#include <stdio.h>
#include <stdlib.h>

#define STRLEN 100

void A1(void);
void A2(void);
void A3(void);
void A4(void);
void A5(void);

int main()
{

    //A1();
    //A2();
    //A3();
    //A4();
    A5();

    return (EXIT_SUCCESS);
}

void A1(void)
{
    printf("#--A1- Begrüßung -#\n");

    char name[STRLEN];

    printf("What's your name? ");
    scanf("%49s", name);
    printf("Hello, %s\n", name);
}

void A2(void)
{
    printf("#--A2- Wort, Zeichen, Fließkommazahl --#\n");

    char word[STRLEN];
    char character;
    float floatNumber;

    scanf("%s %c %f", word, &character, &floatNumber);
    printf("word:        %s\ncharacter:   %c\nfloatNumber: %f\n", word, character, floatNumber);
}

void A3(void)
{
    printf("#--A3- Summe, Produkt, Differenz, Division -#\n");

    int num1, num2;

    printf("num1: ");
    scanf("%d", &num1);
    printf("num2: ");
    scanf("%d", &num2);

    printf("sum:        %d\n", num1 + num2);
    printf("product:    %d\n", num1 * num2);
    printf("difference: %d\n", num1 - num2);
    if (num2 == 0.0)
    {
        printf("num2 darf bei der Division nicht 0 sein!\n");
        return;
    }
    else
    {
        printf("quotient:   %f\n", (float) num1 / (float) num2);
    }
}

void A4(void)
{
    printf("#--A4- Modulo -#\n");

    int num;

    printf("num: ");
    scanf("%d", &num);
    printf("last digit: %d\n", num % 10);
}

void A5(void)
{
    printf("#--A5- char als char, dezimal, hexadez. -#\n");

    char character;

    printf("enter some character: ");
    scanf(" %c", &character);
    printf("as char:    %c\n", character);
    printf("as deciaml: %d\n", (int) character);
    printf("as hex:     0x%X\n", (int) character);
}
