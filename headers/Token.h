#include "TokenType.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool characterChecker(char ch);
void checkCharacters(char *string);
//void splitLexemes(char *c);
char *getString(char *string);
void split(char **target,char *from);
void stringSplitter(char *toBeSplitted,char *destination);
void reallocateString(char *string,int size);
int countNonWhiteSpaceInString(char *string);
void assignNewString(char *oldString,char *new);
void justPrintf(char * string);
int readAWord(char *word);
void ReadLexeme(char *LongLine);
void setToken(char *word);
char *tokens[5000];
const char arraykw[5000][1000] = {"if", "else", "otherwise", "do", "while", "for", "switch", "case",
                              "default", "stop", "resume", "none", "Number", "Sentence", "Tralse", "Collection", "Comp", "Item", "break", "return"};


#define MAXIMUM_TOKENS = 5000;
int lexemeCounter= 0;
int spaceCounter = 0; // index of last space

bool isDelimiter(char ch)
{
  if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
      ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
      ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
      ch == '[' || ch == ']' || ch == '{' || ch == '}')
    return (true);
  return (false);
}

bool isOperator(char ch)
{
  if (ch == '+' || ch == '-' || ch == '*' ||
      ch == '/' || ch == '>' || ch == '<' ||
      ch == '=')
    return (true);
  return (false);
}

bool isAlphabet(char ch)
{

  if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
  {
    //  printf("%c  character is Alphabet: True", ch);
    return true;
  }
  return false;
}

bool isNumeric(char ch)
{
  if (ch >= '0' && ch <= '9')
  {
    //  printf("%c  character is digit True", ch);
    return true;
  }
  return false;
}

void checkCharacters(char *string)
{
  //String init
  int length = strlen(string);
  char *lexeme;
  lexeme = (char *)malloc(sizeof(char) * length);

  strcpy(lexeme, string);
 char* newString =  (char *)malloc(sizeof(char) * 255);
split(&newString,lexeme);

//strcpy(&newString,split(lexeme));
printf("%d\n",strlen(newString));
  printf("%s\n", newString);
  for (int i = 0; i < length; i++)
  {
    char c= newString[i];
    printf("%c\n",c);
    characterChecker(c);
  }
  stringSplitter(lexeme,newString);
}

//&toBeSplitted[i] to access individual character

// Split via whitespace




  void reallocateString(char *string,int size)
  {
    printf("%d",size);
    int length = size+1;
    string = malloc(length);
    printf("new size of String: %d",strlen(string));
     printf("new String: %s",string);
  }


void assignNewString(char *oldString,char *new)
{
  int length = strlen(oldString);
  int counter = 0;
  char *newString = malloc(countNonWhiteSpaceInString(oldString));
  char c;
  newString[0] =0;
  for(int i =0; i<length;i++)
  {
     c = oldString[i];
    if(characterChecker(c))
    {
      printf("%c",c);
      strncat(newString,&c,1);
       counter++;
     }         
  }
  justPrintf(newString);
}
void justPrintf(char * string)
{
  printf("Just Print: %s\n",string);
  printf("Just Print Length: %zu",strlen(string));

}


//Read a sentence
void ReadLexeme(char *LongLine)
{
 printf("Reading LongLine: \n");
 printf(" %s \n",LongLine);
 printf("\n wordSize: %d \n",readAWord(LongLine));
 //printf(" character at 4: %c \n",LongLine[5]);
 printf("Word: \n");

 setToken(LongLine);
printf(" %s ",tokens[0]);
char c = LongLine[lexemeCounter];

}



//read a character until whitespace or delimiter
int readAWord(char *word)
{
 for(int i=0; i<strlen(word);i++)
 {
   char c = word[i];

   if( c == ' ')
   {
     //printf("Space\n");
     return i;
   }
 }
}
//read word will be stored in a string well char[]
void setToken(char *word)
{
  int length = readAWord(word);
  char c;
  char *token = malloc(readAWord(word)* sizeof *token);
for(int i=0; i<length;i++)
{
  c = word[i];
strncat(token,&c,1);
}
tokens[0] = token;
}








int countNonWhiteSpaceInString(char *string)
{
  int length = strlen(string);
  int counter = 0;

  for(int i =0; i<length;i++)
  {
    char c = string[i];
    if(characterChecker(c))
    {
       counter++;
     }
         
  }
  printf("nonWhiteSpace: %d\n",counter);
  return counter +1;
}
















void split(char **target,char *from)
{

    char* newString = (char*)malloc(sizeof(char) * strlen(from));
    char* string = (char*)malloc(sizeof(char) * strlen(from));

    strcpy(string, from);
    for (int i = 0; i < strlen(string); i++)
    {
        char c = string[i];
        // printf("%c ", string[i]);
        strncat(newString, &c, 1);
    }
//    free(string);
    printf("New String: ");
    printf("\n\n %s: DAFAQ", newString);
    strcpy(*target,newString);

}

void stringSplitter(char *toBeSplitted,char *destination)
{
 for(int i=0; i<strlen(toBeSplitted);i++)
 {
   char c = toBeSplitted[i];

   if( c == ' ')
   {
     printf("Space\n");
     return;
   }
   printf("%c",toBeSplitted[i]);
   strncat(destination,&c,1);
 }
}

/*void splitLexemes(char *c)
{
  // read until whitespace
  char *string;
  int n;
  int counter = 0;

  char newString[] = (char *)malloc(sizeof(char) * strlen(string));
  string = (char *)malloc(sizeof(char) * 255);
  strcpy(string, c);

  if (string == NULL)
  {
    printf("read error");
    return;
  }

  for (int i = 0; i < strlen(string); i++)
  {
    if (string[i] == ' ')
      break;
    else
    {
      char temp=string[i];

     // strcat(newString,&temp,1);
    }
  }
  printf("string: %s ", newString);
}
*/
bool characterChecker(char ch)
{
  if (isAlphabet(ch))
  {
   return true;
  }
  else if (isNumeric(ch))
  {
    return true;
  }
  else
  {
     return false;
  }
}


// given a string
// check if string is AlphaNumeric
// split each string when a white space is encountered

char *toString()
{
  return " Y CAN'T U READ JAVA";
}