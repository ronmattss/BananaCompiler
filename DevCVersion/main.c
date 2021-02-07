#include <stdio.h>
#include <conio.h>
#include "Token.h"

void readSource();
int SIZE_OF_LINE = 1000;
int bufferLength = 255;
int numberOfLines = 0;
char filename[250];
char outFile[250];
char *ch;
char **stringOfLine;

int main()
{ // bananalyzer entry point
    // read file per line
    //
    //checkCharacters("HELLO WORLD");
    //checkCharacters("AB123 Escape");
    //   printf("%s",toString());
    readSource();
//TODO: Cleanup
    printf("Lexeme      Token");
    tokens = malloc(MAXIMUM_TOKENS * sizeof(char));
    for (int i = 0; i < numberOfLines; i++)
    {
        char *ptrTest = malloc((strlen(stringOfLine[i]) + 1) * sizeof *ptrTest);
        strcpy(ptrTest, stringOfLine[i]);
        //  printf("\nfirst String: %s ", ptrTest);
        ReadLexeme(ptrTest);
        free(ptrTest);
    }
    showLexemes();
    free(tokens);
    fclose(wf);
    return 0;
}

void readSource()
{

    int counter = 0;

    stringOfLine = malloc(SIZE_OF_LINE * sizeof(char *));
    ch = malloc(SIZE_OF_LINE * sizeof(ch));

    printf("Enter the Filename you want to read:\n");
    gets(filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found. \n");
    }
    else
    {

        while (fgets(ch, bufferLength, fp))
        {

            // printf("%s \n",ch);
            stringOfLine[counter] = malloc(strlen(ch) + 1 * sizeof(stringOfLine[counter]));
            strcpy(stringOfLine[counter], ch);
            //strcat(stringOfLine[counter],'\0');
            //      printf(" [%d][%d] %s", counter, strlen(stringOfLine[counter]), stringOfLine[counter]);
            // ReadLexeme(ch);
            counter++;
        }
        numberOfLines = counter;
        //    printf("\n Number of lines: %d", counter);
    }

    fclose(fp);
}

