#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1000
#define FILE_NAME "test.txt"

void A31(void);
void A32(void);
void A33(void);
void A34(void);

int main()
{
    //A31();
    //A32();
    //A33();
    A34();

    return (EXIT_SUCCESS);
}

void A31()
{
    printf("#--A31- Experimentieren mit Dateibearbeitung --#\n");

    FILE* file = fopen(FILE_NAME, "r");
    char buffer[BUFFER_SIZE];

    if (NULL == file)
    {
        return;
    }

    fread(buffer, sizeof (char) * 100, 10, file);
    printf("%s\n", buffer);
    fclose(file);
}

void A32()
{
    printf("#--A32- Groß-Kleinschreibung umkehren --#\n");

    FILE* file = fopen(FILE_NAME, "r");
    char buffer[BUFFER_SIZE];

    if (NULL == file)
    {
        return;
    }

    fread(buffer, sizeof (char) * 100, 10, file);

    int i = 0;
    char character = buffer[i];
    while (EOF != character)
    {
        if (isupper(character))
        {
            buffer[i] = tolower(character);
        }
        else if (islower(character))
        {
            buffer[i] = toupper(character);
        }

        ++i;
        character = buffer[i];
    }

    printf("%s\n", buffer);
    fclose(file);
}

void A33()
{
    printf("#--A33- Wie oft kommt der Buchtstabe vor? --#\n");

    FILE* file = fopen(FILE_NAME, "r");
    char buffer[BUFFER_SIZE];
    int n = -1;

    if (NULL == file)
    {
        return;
    }

    fread(buffer, sizeof (char) * 100, 10, file);

    const char character = buffer[0];

    int i = 0;
    while (EOF != buffer[i])
    {
        if (character == buffer[i])
        {
            ++n;
        }

        ++i;
    }

    printf("'%c' is %d times in the text.\n", character, n);

    fclose(file);
}

void A34()
{
    printf("#--A34- mehrfache Leerzeichen entfernen --#\n");

    FILE* file = fopen(FILE_NAME, "r");
    char buffer[BUFFER_SIZE];
    char destinationString[BUFFER_SIZE];

    if (NULL == file)
    {
        return;
    }

    fread(buffer, sizeof (char) * 100, 10, file);

    int i = 0;
    int destI = 0;
    char currentChar = buffer[i];

    while (EOF != currentChar)
    {
        while (' ' == currentChar && ' ' == buffer[i + 1])
        {
            ++i;
        }

        destinationString[destI] = currentChar;
        ++destI;
        currentChar = buffer[++i];
    }

    printf("%s\n", destinationString);
    fclose(file);
}

