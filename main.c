#include <stdio.h>
#include <conio.h>
#include "headers/Token.h"

void readSource();
int SIZE_OF_LINE = 1000;
int bufferLength = 255;
int numberOfLines = 0;
char filename[250];
char outFile[250];
char *ch;
char **stringOfLine;

int main()
{

    readSource();
    //TODO: Cleanup
    printf("Lexeme      Token");
    tokens = malloc(MAXIMUM_TOKENS * sizeof(char));
    for (int i = 0; i < numberOfLines; i++)
    {
        char *ptrTest = malloc((strlen(stringOfLine[i]) + 1) * sizeof *ptrTest);
        strcpy(ptrTest, stringOfLine[i]);
        // printf("\nfirst String: %s ", ptrTest);     // debug test what string
        if(ptrTest[0] == '\n')
        continue;
        ReadLexeme(ptrTest);
        free(ptrTest);
    }
    showLexemes();
    free(tokens);
    fclose(wf);
    return 0;
}

// Read all strings and store it in a **char
void readSource()
{

    int counter = 0;

    stringOfLine = malloc(SIZE_OF_LINE * sizeof(char *));
    ch = malloc(SIZE_OF_LINE * sizeof(ch));

    printf("Enter the Filename you want to read:\n");
    gets(filename);
    int fileNameLength = strlen(filename);
    if (filename[fileNameLength - 4] == '.')
    {
        if (filename[fileNameLength - 3] == 'c')
            if (filename[fileNameLength - 2] == 'm')
                if (filename[fileNameLength - 1] == 'p')
                    fp = fopen(filename, "r");
    }
    else
    {
        printf("file not found");
        exit(0);
    }

    if (fp == NULL)
    {
        printf("File not found. \n");
    }
    else
    {

        while (fgets(ch, bufferLength, fp))
        {
            stringOfLine[counter] = malloc(strlen(ch) + 1 * sizeof(stringOfLine[counter]));
            strcpy(stringOfLine[counter], ch);
            counter++;
        }
        numberOfLines = counter;
        //    printf("\n Number of lines: %d", counter);
    }

    fclose(fp);
}
