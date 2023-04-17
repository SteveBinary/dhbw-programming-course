/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: SteveBinary
 *
 * Created on 23. Dezember 2020, 16:52
 */

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void Spezialauftrag_Raute(void);
void A6(void);
void A7(void);
void A8(void);
void A9(void);
void A10(void);
void A11(void);
void A12(void);
void A13(void);
void A14(void);
void A15(void);
void A16(void);
void A17(void);
void A18(void);
void A19(void);
void A20(void);
void Spezialauftrag_BMI(void);
void Spezialauftrag_Pruefziffern(void);
void A21(void);
void A22(void);

int main()
{
    //Spezialauftrag_Raute();
    //A6();
    //A7();
    //A8();
    //A9();
    //A10();
    //A11();
    //A12();
    //A13();
    //A14();
    //A15();
    //A16();
    //A17();
    //A18();
    //A19();
    //A20();
    //Spezialauftrag_BMI();
    //Spezialauftrag_Pruefziffern();
    A21();
    //A22();

    return (EXIT_SUCCESS);
}

void Spezialauftrag_Raute()
{
    printf("#--Spezialauftrag: Raute--#\n");

    int size;

    printf("Breite der Raute: ");
    scanf("%d", &size);

    int invertedDirection = size - 1;
    for (int i = 0; i < size; ++i)
    {
        int numberOfStars = size - abs(invertedDirection - i);
        int leftSpaces = abs(invertedDirection - i) / 2.0;

        for (int space = 0; space < leftSpaces; ++space)
        {
            printf(" ");
        }
        for (int star = 0; star < numberOfStars; ++star)
        {
            printf("*");
        }

        printf("\n");
        --invertedDirection;
    }
}

void A6()
{
    printf("#--A6- durch 7 teilbare Zahlen zwischen a..b -#\n");

    int a, b;

    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);

    if (b < a)
    {
        printf("\na cannot be less than b!\n");
        return;
    }

    for (int i = a; i <= b; ++i)
    {
        if (i % 7 == 0) printf("%d\n", i);
    }
}

void A7()
{
    printf("#--A7- Kapitalberechnung -#\n");

    float K, k0, p; // Zielsumme, Anfangskapital, Zinssatz
    int n = 0; // Jahre

    printf("Zielsumme:      ");
    scanf("%f", &K);
    printf("Anfangskapital: ");
    scanf("%f", &k0);
    printf("Zinssatz in %%:  ");
    scanf("%f", &p);

    if (K < k0)
    {
        printf("\nDie Zielsumme darf nicht kleiner als das Anfangskapital sein!\n");
        return;
    }

    while (k0 < K)
    {
        k0 = k0 * (p / 100.0 + 1);
        ++n;
    }

    printf("Es dauert %d Jahre, um die Zielsumme zu erreichen.\n", n);
}

void A8()
{
    printf("#--A8- Schachbrett -#\n");

    int size;

    printf("Schachbrettgröße: ");
    scanf("%d", &size);

    for (int i = 0; i < size; ++i)
    {
        int which = i % 2;
        for (int j = 0; j < size; ++j)
        {
            if (!which)
            {
                printf("**");
                which = 1;
            }
            else
            {
                printf("  ");
                which = 0;
            }
        }
        printf("\n");
    }
}

void A9()
{
    printf("#--A9- kleine 1x1 -#\n");

    for (int i = 1; i <= 10; ++i)
    {
        for (int j = 1; j <= 10; ++j)
        {
            printf("%4d", i * j);
        }
        printf("\n");
    }
}

void A10()
{
    printf("#--A10- Primzahlen -#\n");

    int a;

    printf("Primzahlen bis: ");
    scanf("%d", &a);

    if (a < 2)
    {
        printf("a muss >= 2 sein!");
        return;
    }

    printf("2\n");

    for (int i = 3; i <= a; ++i)
    {
        int isPrime = 1;

        for (int j = 2; j < i; ++j)
        {
            if (i % j == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if (isPrime) printf("%d\n", i);
    }
}

void A11()
{
    printf("#--A11- Christbaum -#\n");

    int sections;

    printf("sections: ");
    scanf("%d", &sections);

    // tree
    for (int i = 0; i < sections; ++i)
    {
        for (int j = 0; j <= 2 * i + 1; ++j)
        {
            for (int k = 0; k < (sections * 4) - (2 * j + 2); ++k)
            {
                printf(" ");
            }
            for (int k = 0; k <= 4 * j + 1; ++k)
            {
                printf("*");
            }
            if (j != 2 * i + 1) printf("\n");
        }
        printf("\n");
    }

    // tree trunk
    for (int i = 0; i < sections; ++i)
    {
        for (int j = 0; j <= 3 * sections - 2; ++j)
        {
            printf(" ");
        }
        for (int j = 0; j < 2 * sections; ++j)
        {
            printf("*");
        }
        printf("\n");
    }
}

int isLeapYear(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

void A12()
{
    printf("#--A12- Schaltjahr -#\n");

    int year;

    printf("Jahr: ");
    scanf("%d", &year);

    if (isLeapYear(year))
    {
        printf("ist ein Schaltjahr.\n");
    }
    else
    {
        printf("ist kein Schaltjahr.\n");
    }
}

void A13()
{
    printf("#--A13- Zahlenraten -#\n");

    srand(time(NULL));

    int number, correct = 0;
    int generatedNumber = rand() % 100 + 1;

    while (!correct)
    {
        printf("Number: ");
        scanf("%d", &number);

        if (number < 1 || number > 100)
        {
            printf("Number must be in range 1..100!\n");
        }
        else
        {
            if (number == generatedNumber)
            {
                printf("CORRECT! %d is the correct number.", generatedNumber);
                correct = 1;
            }
            else if (number < generatedNumber)
            {
                printf("Your number was less than the sought-after number! Try again...\n");
            }
            else
            {
                printf("Your number was greater than the sought-after number! Try again...\n");
            }
        }
    }
}

void A14()
{
    printf("#--A14- Quadratische Gleichung -#\n");

    float a, b, c;

    printf("ax^2 + bx + c = 0\n");
    printf("a: ");
    scanf("%f", &a);
    printf("b: ");
    scanf("%f", &b);
    printf("c: ");
    scanf("%f", &c);

    if (a == 0.0)
    {
        if (b == 0.0)
        {
            if (c == 0.0)
            {
                printf("Lösungsmenge ist unendlich.\n");
                return;
            }
            else
            {
                printf("Lösungsmenge ist leer.\n");
                return;
            }
        }
        else
        {
            printf("x = %f", -(c / b));
            return;
        }
    }

    float diskriminante = b * b - 4 * a * c;

    if (diskriminante == 0.0)
    {
        // eine Lösung
        printf("x = %f\n", -b / (2.0 * a));
    }
    else if (diskriminante > 0.0)
    {
        // 2 Lösungen
        float x1 = (-b - sqrtf(diskriminante)) / (2.0 * a);
        float x2 = (-b + sqrtf(diskriminante)) / (2.0 * a);
        printf("x1 = %f\n", x1);
        printf("x2 = %f\n", x2);
    }
    else
    {
        // komplexe Lösung
        float re = -b / (2.0 * a);
        float im = sqrtf(-diskriminante) / (2.0 * a);
        printf("x1 = %f - %fi\n", re, im);
        printf("x2 = %f + %fi\n", re, im);
    }
}

void A15()
{
    printf("#--A15- Mini-Taschenrechner -#\n");

    float num1, num2;
    char operator;


    printf("Aufgabe der Form:  num1 (+, -, *, /) num2:\n");
    scanf("%f %c %f", &num1, &operator, &num2);

    switch (operator)
    {
    case '+':
        printf("= %f\n", num1 + num2);
        break;
    case '-':
        printf("= %f\n", num1 - num2);
        break;
    case '*':
        printf("= %f\n", num1 * num2);
        break;
    case '/':
        if (num2 == 0.0) printf("num2 darf bei der Division nicht 0 sein!\n");
        else printf("= %f\n", num1 / num2);
        break;
    default:
        printf("Das Operationszeichen wurde nicht korrekt eingegeben!\n");
        break;
    }
}

void A16()
{
    printf("#--A16- Primzahlen mit Sieb-Verfahren -#\n");

    int from = 2, to = 100, size = to - from + 1;
    int numbers[size];

    int index = 0;
    for (int i = from; i <= to; ++i)
    {
        numbers[index] = i;
        ++index;
    }

    for (int i = 0; i < size; ++i)
    {
        if (numbers[i] == 0) continue;

        int currentTerstNumber = numbers[i];

        for (int j = 1; i + j * currentTerstNumber < size; ++j)
        {
            numbers[i + j * currentTerstNumber] = 0;
        }
    }

    for (int i = 0; i < size; ++i)
    {
        printf("%d\n", numbers[i]);
    }
}

void A17()
{
    printf("#--A17- int in binär -#\n");

    int num;

    printf("num: ");
    scanf("%d", &num);

    for (int i = sizeof (int) * 8 - 1; i >= 0; --i)
    {
        if (num & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }

        if (0 == i % 8)
        {
            printf(" ");
        }
    }

    printf("\n");
}

void A18()
{
    printf("#--A18- Primfaktorzerlegung -#\n");

    int num, first = TRUE;

    printf("num: ");
    scanf("%d", &num);

    printf("%d = ", num);

    for (int possiblePrime = 2; possiblePrime <= num; ++possiblePrime)
    {
        int isPrime = TRUE;

        for (int tester = 2; tester * tester <= possiblePrime; ++tester)
        {
            if (possiblePrime % tester == 0)
            {
                isPrime = FALSE;
                break;
            }
        }

        if (isPrime)
        {
            while (num % possiblePrime == 0)
            {
                if (!first) printf("*");
                printf("%d", possiblePrime);
                first = FALSE;
                num /= possiblePrime;
            }
        }
    }
    printf("\n");
}

void bubbleSort(int* array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void A19()
{
    printf("#--A19- Bubble-Sort -#\n");

    srand(time(NULL));
    int size = (int) (rand() % 100 + 1);

    int array[size];

    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100 + 1;
    }

    bubbleSort(array, size);

    for (int i = 0; i < size; ++i)
    {
        printf("%d\n", array[i]);
    }
}

void selectionSort(int* array, int size)
{
    int minIndex = 0;

    for (int i = 1; i < size; ++i)
    {
        if (array[i] < array[minIndex])
        {
            minIndex = i;
        }
    }

    int temp = array[minIndex];
    array[minIndex] = array[0];
    array[0] = temp;

    if (size > 0) selectionSort(&array[1], size - 1);
}

void A20()
{
    printf("#--A20- Selection-Sort -#\n");

    srand(time(NULL));
    int size = (int) (rand() % 100 + 1);

    int array[size];

    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100 + 1;
    }

    // Effizienter als Boubble-Sort, da mit jedem Durchgang das zu sortierende Rest-Array kleiner wird.
    // Bei Bouble-Sort wird bei jedem Durchgang das komplette Array durchlaufen.
    selectionSort(array, size);

    for (int i = 0; i < size; ++i)
    {
        printf("%d\n", array[i]);
    }
}

void Spezialauftrag_BMI()
{
    printf("#--Spezialauftrag: BMI--#\n");

    float height, weight, bmi;

    printf("Größe in Meter: ");
    scanf("%f", &height);
    printf("Gewicht in kg:  ");
    scanf("%f", &weight);

    bmi = weight / (height * height);

    if (bmi < 19)
    {
        printf("BMI = %.2f  -> Untergewicht\n", bmi);
    }
    else if (bmi < 25)
    {
        printf("BMI = %.2f  -> Normalgewicht\n", bmi);
    }
    else if (bmi < 30)
    {
        printf("BMI = %.2f  -> leichtes Übergewicht\n", bmi);
    }
    else
    {
        printf("BMI = %.2f  -> Mehr Bewegung!\n", bmi);
    }
}

int getISBNcheckNumber(const char* isbn)
{
    int sum = 0;

    for (int i = 1; i <= strlen(isbn); ++i)
    {
        sum += (isbn[i - 1] - '0') * i; // ascii trick to get the number
    }

    return sum % 11;
}

void printISBNwithCheckNumber(const char* isbn)
{
    int checkISBN = getISBNcheckNumber(isbn);
    if (checkISBN != 10) printf("ISBN: %s %d\n", isbn, checkISBN);
    else printf("ISBN: %s X\n", isbn);
}

int getEANcheckNumber(const char* ean)
{
    int sum = 0;

    for (int i = 1; i <= strlen(ean); ++i)
    {
        sum += (ean[i - 1] - '0') * ((i % 2) ? 1 : 3);
    }

    return (10 - (sum % 10)) % 10;
}

void printEANwithCheckNumber(const char* ean)
{
    int checkEAN = getEANcheckNumber(ean);
    printf("EAN: %s %d\n", ean, checkEAN);
}

void Spezialauftrag_Pruefziffern()
{
    printf("#--Spezialauftrag: Prüfziffern berechnen--#\n");

    printISBNwithCheckNumber("013110362"); // 8
    printISBNwithCheckNumber("383624114"); // 5
    printISBNwithCheckNumber("381380514"); // X

    printEANwithCheckNumber("401209602322"); // 7
    printEANwithCheckNumber("019294097125"); // 7
    printEANwithCheckNumber("076094703742"); // 1

}

void A21()
{
    printf("#--A21- Familie Müller -#\n");

    // 4 Bits -> each bit corresponds to a family member | e.g. 1000 -> Anton goes but the others don't
    // Starting with 1 because at least one family member has to go to the party.
    for (int combination = 1; combination <= 15; ++combination)
    {
        int anton = combination & 8; // checks the 2^3 bit
        int berta = combination & 4; // checks the 2^2 bit
        int claus = combination & 2; // checks the 2^1 bit
        int doris = combination & 1; // checks the 2^0 bit

        int allRulesSatisfied =
                !(anton && doris) && // Anton geht nicht mit Doris.
                !(berta && !claus) && // Wenn Berta geht, geht Claus mit (nicht unbedingt umgekehrt -> Claus kann auch ohne Berta gehen?).
                !(anton && berta && claus) && // Wenn Anton und Claus gehen, dann bleibt Berta zu Hause.
                !(!anton && !claus && !doris) && // Wenn Anton zu Hause bleibt, dann geht entweder
                !(!anton && claus && doris); //     Doris oder Claus.

        if (allRulesSatisfied)
        {
            if (anton) printf("Anton  ");
            if (berta) printf("Berta  ");
            if (claus) printf("Claus  ");
            if (doris) printf("Doris  ");
            printf("\n");
        }
    }
}

int sign(double x)
{
    if (x > 0)
    {
        return 1;
    }
    else if (x < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

double function(double x)
{
    return x * x * x - x * x - x + 0.04;
}

double zeroBisection(double start, double end)
{
    int iterations = 0;
    double middle;

    while (iterations < 20)
    {
        middle = (end + start) * 0.5;

        if (sign(function(start)) != sign(function(middle)))
        {
            end = middle;
        }
        else if (sign(function(middle)) != sign(function(end)))
        {
            start = middle;
        }
        else
        {
            break;
        }

        ++iterations;
    }

    return middle;
}

void A22()
{
    printf("#--A22- Nullstellen -#\n");

    double start, end;

    printf("lower bound: ");
    scanf("%lf", &start);
    printf("upper bound: ");
    scanf("%lf", &end);

    // function as parameter by passing the pointer to the function - it's name
    double zero = zeroBisection(start, end);
    printf("zero: x = %lf\n", zero);
}
