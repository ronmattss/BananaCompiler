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
bool matchIfDelimiter(char *token);
bool matchIfSentence(char *token);
bool matchIfRelationalOperator(char *token);
bool matchIfArithmeticOperator(char *token);
bool keywordType();
void showLexemes();
char **tokens;
const int numberOfOperators = 15;
const int keywordsLength = 24;
// ~~ Pool Of Keywords Used in Character Matching ~~
const char *keywords[24] = {"if", "else", "otherwise", "do", "while", "for", "switch", "case",
                            "default", "stop", "resume", "none", "Number", "Sentence", "Tralse", "Collection", "Comp", "Item", "return", "AND", "OR", "NOT", "true", "false"};
const int keywordID[24] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 12, 12};
const char *operators[21] = {"+", "-", "*", "/", "!", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ";", "[", "]", "(", ")", "{", "}"}; // do something about the backslash
const int operatorID[21] = {9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11};
const int MAXIMUM_TOKENS = 5000;
int lexemeCounter = 0;
int totalLexemes = 0;
int tokenIDCounter = 0;
int spaceCounter = 0; // index of last space
bool isLineFinished = false;
int *tokensID;
FILE *wf;
FILE *fp;

bool keywordType()
{

printf("%d",tokensID[tokenIDCounter]);
  switch (tokensID[tokenIDCounter])
  {
  case 1:
    fprintf(wf, "Conditional");
    return true;
  case 2:
    fprintf(wf, "Loop");
    return true;
  case 3:
    fprintf(wf, "Switch Control");
    return true;
  case 4:
    fprintf(wf, "Flow Control");
    return true;
  case 5:
    fprintf(wf, "Null");
    return true;
  case 6:
    fprintf(wf, "Data Type");
    return true;
  case 7:
    fprintf(wf, "Return Value");
    return true;
  case 8:
    fprintf(wf, "Logical Operators");
    return true;
  case 12:
    fprintf(wf, "Tralse Value");
    return true;
  default:
    return false;
  }
}

// give tokens some ID for future use :>
bool matchIfArithmeticOperator(char *token)
{
  char c = token[0];
  switch (c)
  {
  case '+':
    fprintf(wf, "Arithmetic Operator: Addition");
    return true;
  case '-':
    fprintf(wf, "Arithmetic Operator: Subtraction");
    return true;
  case '*':
    fprintf(wf, "Arithmetic Operator: Multiply");
    return true;
  case '/': // how to know if comment or not, later
    if (token[1] == '/')
    {
      fprintf(wf, "Comment Operator");
      return true;
    }
    fprintf(wf, "Arithmetic Operator: Division");
    return true;
  default:
    return false;
  }
}

bool matchIfRelationalOperator(char *token)
{
  char c = token[0];
  switch (c)
  {
  case '=': // == !=?
    if (token[1] == '=')
    {
      fprintf(wf, "Relational Operator: equals to");
      return true;
    }
    fprintf(wf, "Relational Operator: assignment operator");
    return true;
  case '!':
    if (token[1] == '=')
    {
      fprintf(wf, "Relational Operator: not equals to");
      return true;
    }
    fprintf(wf, "Relational Operator: not");
    return true;
  case '>':
    if (token[1] == '=')
    {
      fprintf(wf, "Relational Operator: greater than equal to");
      return true;
    }
    fprintf(wf, "Relational Operator: greater than");
    return true;
  case '<':
    if (token[1] == '=')
    {
      fprintf(wf, "Relational Operator: less than equal to");
      return true;
    }
    fprintf(wf, "Relational Operator: less than");
    return true;
  }
  return false;
}

bool matchIfSentence(char *token)
{
  char c = token[0];
  int counter = 0;
  if (token[0] == '"' /*&& token[1] != '"'*/)
  {
    counter++;
    c = token[counter];
    while (c != '"' || counter != strlen(token))
    {
      c = token[counter];
      counter++;
    }
    fprintf(wf, "Sentence");
    return true;
  }
  return false;
}

bool matchIfDelimiter(char *token)
{
  char c = token[0];
  switch (c)
  {
  case ';':
    fprintf(wf, "Delimiter: semicolon");
    return true;
  case '(':
    fprintf(wf, "Delimiter: open parenthesis");
    return true;
  case ')':
    fprintf(wf, "Delimiter: close parenthesis");
    return true;
  case '{':
    fprintf(wf, "Delimiter: open curly bracket");
    return true;
  case '}':
    fprintf(wf, "Delimiter: close curly bracket");
    return true;
  case '[':
    fprintf(wf, "Delimiter: open square bracket");
    return true;
  case ']':
    fprintf(wf, "Delimiter: close square bracket");
    return true;
  case ',':
    fprintf(wf, "Delimiter: comma");
    return true;
  }
  return false;
}

bool isDelimiter(char ch)
{
  if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
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

// --Compares the given character to it's ascii value--
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
bool manualMatching(char *c)
{
  //Manual Matching
  // if
  if (c[0] == 'i')
    if (c[1] == 'f')
      return true;
  if (c[0] == 'e')
    if (c[1] == 'l')
      if (c[2] == 's')
        if (c[3] == 'e')
          return true;
}

bool matchWithKeywords(char *token)
{
  // printf("Token: %s", token);
  bool flag = false;

  // ~~~~~ Matches token to a Keyword per character
  for (int i = 0; i < keywordsLength; i++)
  {

    if (strlen(keywords[i]) == strlen(token))
    {
      for (int j = 0; j < strlen(keywords[i]); j++)
      {
        if (token[j] != keywords[i][j])
        {
          flag = false;
          break;
        }
        else if (token[j] == keywords[i][j])
        {

          flag = true;
        }
      }
      if (flag)
      {
        printf("\nKeyword: %s ", keywords[i]);
        tokensID[tokenIDCounter] = keywordID[i]; //Assigning ID's to Tokens for future use
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
      if (c = '.' && !hasPeriod && strlen(token) > 2)
      {
        hasPeriod = true;
      }
      else
      {
        return false; //
      }
    }
  }
  return flag;
}

bool matchiIfVariableName(char *token)
{
  char c = token[0];
  if (isAlphabet(c))
    return true;
  return false;
}
void tokenMatcher(char *token)
{
  if (matchIfArithmeticOperator(token))
  {
    return;
  }
  if (matchIfDelimiter(token))
  {
    return;
  }
  if (matchIfRelationalOperator(token))
  {
    return;
  }

  if (matchIfNumber(token))
  {
    fprintf(wf, "Number");
    return;
  }
  if (matchWithKeywords(token))
  {
    keywordType();
    return;
  }
  if (matchIfSentence(token))
  {
    return;
  }
  if (matchiIfVariableName(token))
  {
    fprintf(wf, "variableName");
    return;
  }
  else
  {
    fprintf(wf, "Undefined Symbol");
    return;
  }
}
//Read a sentence
void ReadLexeme(char *LongLine)
{
  //allocateTokenArray();
  // tokens = malloc(MAXIMUM_TOKENS * sizeof(char));
  // printf("\n%s", LongLine);
  // there should be a while loop here for to
  while (!isLineFinished)
  {
    setToken(LongLine);
  }

  // allocate tokenID
  tokensID = malloc(lexemeCounter * sizeof(tokensID));
  // set TokenId to Lexeme ID

  // for (int i = 0; i < lexemeCounter; i++)
  // {
  //   printf("\n %s | ",tokens[i]);
  //   tokenIDCounter = i;
  //   tokenMatcher(tokens[i]);
  // }
  //  free(tokens);
  isLineFinished = false;
  spaceCounter = 0;
  // lexemeCounter = 0;
}
void showLexemes()
{

  wf = fopen("LexicalAnalyzerOutput.sc", "w");
  if (wf == NULL)
  {
    printf("\n\nno output file\n\n");
  }
  printf("Total Lexemes: %d\n", lexemeCounter);
  fprintf(wf, "Lexeme\t\t\t\t\t\t\tToken");

  for (int i = 0; i < lexemeCounter; i++)
  {
    fprintf(wf, "\n%s \t\t\t\t\t\t", tokens[i]);
    tokenIDCounter = i;
    tokenMatcher(tokens[i]);
  }
  fclose(wf);
}

void writeTokensAndLexemes()
{
}

//read a character until whitespace or delimiter or symbols
int readAWord(char *word)
{
  // printf("SpaceCOunter: %d", spaceCounter);
  int internalCounter = 0;
  char c;
  bool sentenceEncountered = false;
  for (int i = spaceCounter; i < strlen(word); i++)
  {
    int k = strlen(word);
    c = word[i];

    // this if means that if the next character is a delimiter then return
    if (c == '"' && !sentenceEncountered)
    {
      sentenceEncountered = true;
      internalCounter++;
      continue;
    }
    if (sentenceEncountered)
    {
      if (c == '\n' || c == '\0')
        return internalCounter;
      if (c == '"')
        return internalCounter;
      internalCounter++;
      continue;
    }

    if (word[i + 1] == '\n' || word[i + 1] == '\0') // if delimiter is the next character return the
    {
      isLineFinished = true;
      return internalCounter;
    }
    else if (isDelimiter(word[i + 1]) && c != ' ')
    {
      return internalCounter;
    }
    else if (isDelimiter(c) || isOperator(c))
    {
      if (isDelimiter(word[i + 1])) //== != >=
        return ++internalCounter;
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
        if (c == ';' || c == '\n')
        {
          isLineFinished = true;
          return internalCounter + 1;
        }
        return internalCounter; // for null terminator
      }
    }
    else if (c != ' ' && word[i + 1] == ' ') // if c ='a' and c+1 = ' 'return
    {
      return internalCounter;
    }
    internalCounter++;
  }
}

//read word will be stored in a char[]
void setToken(char *word)
{
  int length = readAWord(word);
  if (length == 0 && word[spaceCounter] == ' ')
    return;
  int tokenLength = length + 1;
  int internalCounter = 0;
  int startCharacter = spaceCounter;
  bool isSentence = false;
  //  printf("\n length: %d\n", tokenLength);

  char c;
  char *token = malloc(tokenLength + 1 * sizeof(char *));

  for (int i = 0; i < tokenLength; i++)
  {
    c = word[startCharacter + i];
    if (c == '"' && !isSentence) // beginning of sentence
    {
      isSentence = true;
    }
    else if (c == '"' && isSentence)
    {
      isSentence = false;
    }
    if ((c == ' ' || c == '\n') && isSentence == false) // if not a sentence
    {
      continue;
    }
    else
    {
      token[internalCounter] = c;
      //    printf("%c %c\n", c, token[internalCounter]);
      internalCounter++;
    }
  }
  token[internalCounter] = '\0'; // add null terminator

  // Assignment Part;
  tokens[lexemeCounter] = malloc(tokenLength + 1 * sizeof(tokens[lexemeCounter]));
  memcpy(tokens[lexemeCounter], token, strlen(token) + 1);
  // printf_s("Token: %s %s\n", tokens[lexemeCounter], token);

  free(token);
  spaceCounter += tokenLength; // goes to the next word
  lexemeCounter++;
  totalLexemes++;
}

void allocateTokenArray()
{
  tokens = malloc(MAXIMUM_TOKENS * sizeof(char));
}

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
