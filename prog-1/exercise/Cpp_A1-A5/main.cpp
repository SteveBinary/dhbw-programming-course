/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: SteveBinary
 *
 * Created on 13. Januar 2021, 10:56
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <ios>

using namespace std;

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

    return 0;
}

void A1()
{
    string name;

    cout << "What's your name? ";
    cin >> name;
    cout << "Hello " << name << endl;
}

void A2()
{
    string word;
    char character;
    double number;

    cout << "word: ";
    cin >> word;
    cout << "character: ";
    cin >> character;
    cout << "number: ";
    cin >> number;

    cout << endl << "the word: " << word << endl;
    cout << "the char: " << character << endl;
    cout << "the num:  " << number << endl;
}

void A3()
{
    int a, b;

    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;

    if (b == 0)
    {
        cout << "When dividing, b must not be zero!" << endl;
    }
    else
    {
        cout << a << " / " << b << " = " << (double) a / b << endl;
    }
}

void A4()
{
    int a;

    cout << "eine beliebige zufällige Zahl: ";
    cin >> a;
    cout << "letzte Ziffer: " << a % 10 << endl;
}

void A5()
{
    char character;

    cout << "ein Buchstabe: ";
    cin >> character;
    cout << "als char: " << character << endl;
    cout << "als dez:  " << (int) character << endl;
    cout << "als hex:  0x" << hex << (int) character << endl;
}
