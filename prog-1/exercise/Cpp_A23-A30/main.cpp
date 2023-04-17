/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: SteveBinary
 *
 * Created on 13. Januar 2021, 17:02
 */

#include <cstdlib>
#include <iostream>

using namespace std;

void A23(void);
void A24(void);
void A25(void);
void A26(void);
void A27(void);
void A28(void);
void A29(void);
void A30(void);

class Person
{
public:
    string name;
    string lastName;
    char gender;
    int age;
    int shoeSize;
    float height;

    Person(string _name, string _lastName, char _gender, int _age, int _shoeSize, float _height)
    {
        name = _name;
        lastName = _lastName;
        gender = _gender;
        age = _age;
        shoeSize = _shoeSize;
        height = _height;
    }

    Person()
    {
        name = "";
        lastName = "";
        gender = '-';
        age = 0;
        shoeSize = 0;
        height = 0;
    }
};

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

    cout << "1 Scheibe von " << p1 << " nach " << p2 << endl;

    if (n > 1)
    {
        hanoi(n - 1, parkplatz, p2);
    }
}

void A23()
{
    cout << "2^10 = " << mypow(2, 10) << endl;
    cout << "e^3  = " << myexp(3) << endl;
    cout << "20!  = " << fak(20) << endl; // 20 ist maximum
    hanoi(5, 1, 2);
}

int getNumberFromConsole()
{
    int number;

    cout << "Enter a whole number: ";
    cin >> number;

    return number;
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
    cout << "#-- A24 Primfaktorzerlegung --#" << endl;

    int num = getNumberFromConsole();
    int* factors = getPrimeFactorization(num);

    cout << num << " = " << factors[0];
    // first factor, because if num is 0 loop wouldn't be executed and
    // there is no * in front of the first factor

    for (int i = 1; 0 != factors[i] && i < sizeof (int) * 8; ++i)
    {
        cout << "*" << factors[i];
    }

    cout << endl;
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
    cout << "#-- A25- numerische Integration --#" << endl;

    double a, b;
    int n;

    a = 0.0;
    b = 1.0;
    n = 1000000;

    double integralValue = integral(a, b, n);

    cout << "integral value: " << integralValue << endl;
}

int palin(string c, int erstes, int letztes)
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
    cout << "#-- A26 Palindrom --#" << endl;

    std::string text1 = "hallo";
    string text2 = "lagerregal";

    int text1IsPalindrom = palin(text1, 0, text1.length() - 1);
    int text2IsPalindrom = palin(text2, 0, text2.length() - 1);

    cout << "\"" << text1 << "\"" << " ist " << (text1IsPalindrom ? "ein" : "kein") << " Palindrom." << endl;
    cout << "\"" << text2 << "\"" << " ist " << (text2IsPalindrom ? "ein" : "kein") << " Palindrom." << endl;
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
    cout << "#-- A27 Treppenproblem --#" << endl;

    // Sehr langsam, da diese Rekursion explodiert (2^stufen Aufrufe)
    // Entweder schon gelöste Zwischenschritte merken (dynamische Programmierung)
    // oder einen iterativen Ansatz finden.

    int treppenstufen = 25;
    int moeglichkeiten = treppenproblem_iterativ(treppenstufen);

    cout << "Für eine Treppe mit " << treppenstufen << " Stufen gibt es " << moeglichkeiten << " Möglichkeiten." << endl;
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
    cout << "#-- A28 Wurzel --#" << endl;

    double x = 2.0;
    double sqroot = wurzel(5, x); // real: 1.41421356237

    cout << "sqrt(" << x << ") = " << sqroot << endl;
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
    cout << "#-- A29 Ackermann --#" << endl;

    int m = 3, n = 8;
    int ackermann = a(m, n);

    cout << "a(" << m << "," << n << ") = " << ackermann << endl;
}

Person eingabe()
{
    Person somePerson;

    cout << "Vorname: ";
    cin >> somePerson.name;
    cout << "Nachname: ";
    cin >> somePerson.lastName;
    cout << "Geschlecht: ";
    cin >> somePerson.gender;
    cout << "Alter: ";
    cin >> somePerson.age;
    cout << "Schuhgröße: ";
    cin >> somePerson.shoeSize;
    cout << "Größe in m: ";
    cin >> somePerson.height;

    return somePerson;
}

void A30()
{
    cout << "#-- A30 class person --#" << endl;

    Person person1 = eingabe();
    Person person2 = eingabe();

    if (person1.age > person2.age)
    {
        cout << person1.name << " " << person1.lastName << " ist die ältere Person." << endl;
    }
    else if (person2.age > person1.age)
    {
        cout << person2.name << " " << person2.lastName << " ist die ältere Person." << endl;
    }
    else
    {

        cout << person1.name << " " << person1.lastName << " und " <<
                person2.name << " " << person2.lastName << " sind gleich alt." << endl;
    }
}
