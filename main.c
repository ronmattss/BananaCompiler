#include <stdio.h>
#include <conio.h>
#include "headers/TokenType.h"
#include "headers/Token.h"

void readSource();
int SIZE_OF_LINE = 1000;
int bufferLength = 255;
char filename[250];
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
    char *ptrTest = malloc((strlen(stringOfLine[0]) + 1) * sizeof *ptrTest);
    strcpy(ptrTest, stringOfLine[0]);
    // printf("wtf\n");
//     matchWithKeywords(stringOfLine[0]);
    printf("\nfirst String: %s ", ptrTest);
    ReadLexeme(ptrTest);

    //stringSplitter("HELLO WORLD",ptrTest);

    //assignNewString(ptrTest,ptrTest);

    //free(ptrTest);
    return 0;
}

void readSource()
{
    FILE *fp;
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
            printf(" [%d][%d] %s", counter, strlen(stringOfLine[counter]), stringOfLine[counter]);
            // ReadLexeme(ch);
            counter++;
        }
        // ch[counter] = '\0';
        //  tokens[lexemeCounter] = malloc(tokenLength + 1 * sizeof(tokens[lexemeCounter]));
        // while ((fgets(ch,1000,fp)) != NULL)
        // {
        //     if(ch[counter] =='\n')
        //     {
        //         printf("\nNew line Encountered");
        //     }
        //     else
        //     {
        //     strcpy(stringOfLine,ch);
        //     }
        //     printf("%c", ch);
        //     counter++;
        // }
        // stringOfLine[counter] = '\0';
        //printf("\n %s",stringOfLine);
        printf("\n Number of lines: %d", counter);
    }

    fclose(fp);
}
