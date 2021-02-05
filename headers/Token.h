#include "TokenType.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void allocateTokenArray();
bool characterChecker(char ch);
void checkCharacters(char *string);
//void splitLexemes(char *c);
char *getString(char *string);
//void split(char **target,char *from);
void stringSplitter(char *toBeSplitted, char *destination);
void reallocateString(char *string, int size);
int countNonWhiteSpaceInString(char *string);
void assignNewString(char *oldString, char *new);
void justPrintf(char *string);
int readAWord(char *word);
void ReadLexeme(char *LongLine);
void setToken(char *word);
bool matchWithKeywords(char *token);
bool matchWithOperators(char *token);
void tokenMatcher(char *token);
char **tokens;
const int numberOfOperators = 15;
const char *keywords[20] = {"if", "else", "otherwise", "do", "while", "for", "switch", "case",
                            "default", "stop", "resume", "none", "Number", "Sentence", "Tralse", "Collection", "Comp", "Item", "break", "return"};
const int keywordID[20] = {1, 1, 1, 2, 2, 2};
const char *operators[15] = {"+", "-", "*", "/", "!", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ";"}; // do something about the backslash

const int MAXIMUM_TOKENS = 5000;
int lexemeCounter = 0;
int spaceCounter = 0; // index of last space
bool isLineFinished = false;

/*void keywordType(char *token)
{
  switch(token)
  {
    case 
  }
}*/
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

//&toBeSplitted[i] to access individual character

// Split via whitespace

bool matchWithKeywords(char *token)
{
  // printf("Token: %s", token);
  bool flag = false;

  // ~~~~~ Matches token to a Keyword
  for (int i = 0; i < 20; i++)
  {

    if (strlen(keywords[i]) == strlen(token))
    {
      for (int j = 0; j < strlen(keywords[i]); j++)
      {
        if (token[j] != keywords[i][j])
        {
          flag = false;
          continue;
        }
        else if (token[j] == keywords[i][j])
        {

          flag = true;
        }
      }
      if (flag)
      {
        //printf("\nKeyword: %s ", keywords[i]);
        return flag;
      }
    }
  }
  return flag;
  // check if operator
  // check if delimiter
  // check if variable Name
}

bool matchWithOperators(char *token)
{
  bool flag = false;

  // ~~~~~ Matches token to a Keyword
  for (int i = 0; i < numberOfOperators; i++)
  {

    if (strlen(operators[i]) == strlen(token))
    {
      for (int j = 0; j < strlen(operators[i]); j++)
      {
        if (token[j] != operators[i][j])
        {
          flag = false;
          continue;
        }
        else if (token[j] == operators[i][j])
        {

          flag = true;
        }
      }
      if (flag)
      {
        //printf("\nKeyword: %s ", keywords[i]);
        return flag;
      }
    }
  }
  return flag;
}

bool matchIfNumber(char *token)
{
  bool hasPeriod = false;
  bool flag = false;
  char c;
  for (int i = 0; i < strlen(token); i++)
  {
    c = token[i];
    if (isNumeric(c))
    {
      flag = true;
    }
    else
    {
      flag = false;
      if (c = '.' && !hasPeriod)
      {
        hasPeriod = true;
      }
      else
      {
        return false; //
      }
    }
  }
  return true;
}

void tokenMatcher(char *token)
{
  if (matchWithOperators(token))
  {
    printf(" Token is an Operator\n");
    return;
  }

  if (matchIfNumber(token))
  {
    printf("\nToken is a Number\n");
    return;
  }
  if (matchWithKeywords(token))
  {
    printf("\nToken is a Keyword\n");
    return;
  }
  else
  {
    printf("\nToken is a variableName\n");
    return;
  }
}
//Read a sentence
void ReadLexeme(char *LongLine)
{
  allocateTokenArray();
  printf("\n%s", LongLine);
  // there should be a while loop here for to
  while (!isLineFinished)
  {
    setToken(LongLine);
  }

  for (int i = 0; i < lexemeCounter; i++)
  {
    printf("\ntoken[%d] %s ", i, tokens[i]);
    tokenMatcher(tokens[i]);
  }
  free(tokens);
}

//read a character until whitespace or delimiter or symbols
int readAWord(char *word)
{
  printf("SpaceCOunter: %d", spaceCounter);
  int internalCounter = 0;
  for (int i = spaceCounter; i < strlen(word); i++)
  {
    char c = word[i];
  
    if (word[i + 1] == ' ' || word[i + 1] == ';') // if delimiter is the next character return the
    {
      return internalCounter;
    }
    if (c == ' ' || c == ';' || c == '\0') // change to list of delimiters
    {
      if (word[i + 1] == ' ' && c == ' ') // peek
      {
        internalCounter++;
        continue;
      }
      else if (c == ' ')
      {
        internalCounter++;
        continue;
      }
      else
      {
        //printf("Space\n");
        if (i + 1 == strlen(word)) // this means that it is the end of the line
        {
          isLineFinished = true;
          return internalCounter; // for null terminator
        }
        if(c ==';')
        {
            isLineFinished = true;
          return internalCounter+1; 
        }
        return internalCounter; // for null terminator
      }
    }
    internalCounter++;
  }
}

//read word will be stored in a char[]
void setToken(char *word)
{
  int length = readAWord(word);
  if (length == 0)
    return;
  int tokenLength = length + 1;
  int internalCounter = 0;
  int startCharacter = spaceCounter;
  printf("\n length: %d\n", tokenLength);

  char c;
  char *token = malloc(tokenLength + 1 * sizeof(char *));

  for (int i = 0; i < tokenLength; i++)
  {
    c = word[startCharacter + i];
    if (c == ' '||c=='\n')
    {
      continue;
    }
    else
    {
      token[internalCounter] = c;
      printf("%c %c\n", c, token[internalCounter]);
      internalCounter++;
    }
  }
  token[internalCounter] = '\0'; // add null terminator

  // Assignment Part;
  tokens[lexemeCounter] = malloc(tokenLength + 1 * sizeof(tokens[lexemeCounter]));
  memcpy(tokens[lexemeCounter], token, strlen(token) + 1);
  printf_s("Token: %s %s\n", tokens[lexemeCounter], token);

  free(token);
  spaceCounter += tokenLength; // goes to the next word
  lexemeCounter++;
}

void allocateTokenArray()
{
  tokens = malloc(MAXIMUM_TOKENS * sizeof(char));
}

int countNonWhiteSpaceInString(char *string)
{
  int length = strlen(string);
  int counter = 0;

  for (int i = 0; i < length; i++)
  {
    char c = string[i];
    if (characterChecker(c))
    {
      counter++;
    }
  }
  printf("nonWhiteSpace: %d\n", counter);
  return counter + 1;
}

void stringSplitter(char *toBeSplitted, char *destination)
{
  for (int i = 0; i < strlen(toBeSplitted); i++)
  {
    char c = toBeSplitted[i];

    if (c == ' ')
    {
      printf("Space\n");
      return;
    }
    printf("%c", toBeSplitted[i]);
    strncat(destination, &c, 1);
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
