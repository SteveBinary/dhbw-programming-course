/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: SteveBinary
 *
 * Created on 31. Dezember 2020, 11:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

void A23(void);
void A24(void);
void A25(void);
void A26(void);
void A27(void);
void A28(void);
void A29(void);
void A30(void);

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char gender;
    int age;
    int shoeSize;
    float height;
} Person;

int main()
{
    //A23();
    //A24();
    //A25();
    //A26();
    //A27();
    //A28();
    //A29();
    A30();

    return (EXIT_SUCCESS);
}

int mypow(int a, int b)
{
    // a^b
    int result = 1;
    for (int i = 0; i < b; ++i)
    {
        result *= a;
    }
    return result;
}

double myexp(double x)
{
    // e^x
    double summe = 1.0, summand = 1.0;

    for (int n = 1; n <= 10; ++n)
    {
        summand *= x / n;
        summe += summand;
    }

    return summe;
}

unsigned long fak(unsigned long n)
{
    if (n < 2) return 1;
    return n * fak(n - 1);
}

void hanoi(int n, int p1, int p2)
{
    int parkplatz;

    if (n > 1)
    {
        parkplatz = 6 - p1 - p2;
        hanoi(n - 1, p1, parkplatz);
    }

    printf("1 Scheibe von %d nach %d\n", p1, p2);

    if (n > 1)
    {
        hanoi(n - 1, parkplatz, p2);
    }
}

void A23()
{
    printf("#--A23- Unterprogramme --#\n");

    //printf("2^10 = %d\n", mypow(2, 10));
    //printf("e^3  = %lf\n", myexp(3));
    //printf("20!  = %lu\n", fak(20)); // 20 ist maximum
    hanoi(5, 1, 2);
}

int getNumberFromConsole()
{
    int number;

    printf("Enter a whole number: ");
    int valid = scanf("%d", &number);

    if (!valid)
    {
        printf("Please enter a valid number!\n");
        while ((getchar()) != '\n'); // clear input buffer
        return getNumberFromConsole();
    }
    else
    {
        return number;
    }
}

int* getPrimeFactorization(int num)
{
    static int factors[sizeof (int) * 8];
    // impossible for a number <= 2^(bits of int)-1 to have more than 2^(bits of int) prime factor
    // static, because the local variable has to be returned

    // handling special case 1 (loop wouldn't be executed, and for 0 the array is initialized with all zeros)
    if (1 == num)
    {
        factors[0] = 1;
        return factors;
    }

    int numberOfPrimeFactors = 0;

    for (int possiblePrime = 2; possiblePrime <= num; ++possiblePrime)
    {
        int isPrime = 1;

        for (int tester = 2; tester * tester <= possiblePrime && isPrime; ++tester)
        {
            if (possiblePrime % tester == 0)
            {
                isPrime = 0;
            }
        }

        if (isPrime)
        {
            // number could be divisible multiple times by this prime
            while (num % possiblePrime == 0)
            {
                factors[numberOfPrimeFactors] = possiblePrime;
                num /= possiblePrime;
                ++numberOfPrimeFactors;
            }
        }
    }

    return factors;
}

void A24()
{
    printf("#-- A24 Primfaktorzerlegung --#\n");

    int num = getNumberFromConsole();
    int* factors = getPrimeFactorization(num);

    printf("%d = %d", num, factors[0]);
    // first factor, because if num is 0 loop wouldn't be executed and
    // there is no * in front of the first factor

    for (int i = 1; 0 != factors[i] && i < sizeof (int) * 8; ++i)
    {
        printf("*%d", factors[i]);
    }

    printf("\n");
}

double f(double x)
{
    return myexp(-x * x);
}

double integral(double a, double b, int n)
{
    double value = 0.0;
    double dx = (b - a) / n;
    double currentX = a;

    for (int i = 0; i < n; ++i)
    {
        value += f(currentX) * dx;
        currentX += dx;
    }

    return value;
}

void A25()
{
    printf("#-- A25- numerische Integration --#\n");

    double a, b;
    int n;

    a = 0.0;
    b = 1.0;
    n = 1000000;

    double integralValue = integral(a, b, n);

    printf("integral value: %g\n", integralValue);
}

int palin(char* c, int erstes, int letztes)
{
    if (letztes <= erstes)
    {
        return 1;
    }
    else if (c[erstes] == c[letztes]) // Auch Leerzeichen UND Groß-Kleinschreibung werden beachtet!
    {
        return palin(c, erstes + 1, letztes - 1);
    }
    else
    {
        return 0;
    }
}

void A26()
{
    printf("#-- A26 Palindrom --#\n");

    char text1[] = "hallo";
    char text2[] = "lagerregal";

    int text1IsPalindrom = palin(text1, 0, strlen(text1) - 1);
    int text2IsPalindrom = palin(text2, 0, strlen(text2) - 1);

    printf("\"%s\" ist %s Palindrom.\n", text1, (text1IsPalindrom ? "ein" : "kein"));
    printf("\"%s\" ist %s Palindrom.\n", text2, (text2IsPalindrom ? "ein" : "kein"));
}

int treppenproblem(int stufenanzahl)
{
    if (stufenanzahl < 3)
    {
        return stufenanzahl;
    }
    else
        return treppenproblem(stufenanzahl - 1) + treppenproblem(stufenanzahl - 2);
}

int treppenproblem_iterativ(int stufenanzahl)
{
    int a = 0, b = 1, c = 0;

    for (int i = 0; i < stufenanzahl; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}

void A27()
{
    printf("#-- A27 Treppenproblem --#\n");

    // Sehr langsam, da diese Rekursion explodiert (2^stufen Aufrufe)
    // Entweder schon gelöste Zwischenschritte merken (dynamische Programmierung)
    // oder einen iterativen Ansatz finden.

    int treppenstufen = 25;
    int moeglichkeiten = treppenproblem_iterativ(treppenstufen);

    printf("Für eine Treppe mit %d Stufen gibt es %d Möglichkeiten.\n", treppenstufen, moeglichkeiten);
}

double wurzel(int n, double x)
{
    if (0 >= n)
    {
        return 1;
    }
    else
    {
        double newW = wurzel(n - 1, x);
        return 0.5 * (newW + x / newW);
    }
}

void A28()
{
    printf("#-- A28 Wurzel --#\n");

    double x = 2.0;
    double sqroot = wurzel(5, x); // real: 1.41421356237

    printf("sqrt(%g) = %g\n", x, sqroot);
}

int a(int m, int n)
{
    if (0 == m)
    {
        return n + 1;
    }
    else if (0 == n)
    {
        return a(m - 1, 1);
    }
    else
    {
        return a(m - 1, a(m, n - 1));
    }
}

void A29()
{
    printf("#-- A29 Ackermann --#\n");

    int m = 3, n = 8;
    int ackermann = a(m, n);

    printf("a(%d,%d) = %d\n", m, n, ackermann);
}

Person eingabe()
{
    Person somePerson;

    printf("Vorname: ");
    scanf("%s", somePerson.name);
    printf("Nachname: ");
    scanf("%s", somePerson.lastName);
    printf("Geschlecht: ");
    scanf(" %c", &somePerson.gender);
    printf("Alter: ");
    scanf("%d", &somePerson.age);
    printf("Schuhgröße: ");
    scanf("%d", &somePerson.shoeSize);
    printf("Größe in m: ");
    scanf("%f", &somePerson.height);

    return somePerson;
}

void A30()
{
    printf("#-- A30 struct person --#\n");

    Person person1 = eingabe();
    Person person2 = eingabe();

    if (person1.age > person2.age)
    {
        printf("%s %s ist die ältere Person.\n", person1.name, person1.lastName);
    }
    else if (person2.age > person1.age)
    {
        printf("%s %s ist die ältere Person.\n", person2.name, person2.lastName);
    }
    else
    {
        printf("%s %s und %s %s sind gleich alt.\n",
               person1.name, person1.lastName,
               person2.name, person2.lastName);
    }
}
