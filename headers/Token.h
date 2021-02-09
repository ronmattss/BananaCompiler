#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void allocateTokenArray();
bool characterChecker(char ch);
void checkCharacters(char *string);
char *getString(char *string);
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
bool isNumeric(char ch);
bool isAlphabet(char ch);

char **tokens; // Stores array of lexemes
const int numberOfOperators = 15;
// ~~ Pool Of Keywords Used in per-Character Matching ~~
// reduced code length, ONLY USED IN PER-CHARACTER-MATCHING
const int keywordsLength = 31;
const char *keywords[31] = {"if", "else", "otherwise", "do", "while", "for", "switch", "case",
                            "default", "stop", "resume", "none", "Number", "Sentence", "Tralse", "Collection", "Comp",
                            "Item", "return", "AND", "OR", "NOT", "true", "false", "pi", "int32", "euler", "kelvin", "then", "odd", "alphabet"};
const int keywordID[31] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 12, 13, 14, 15, 16, 17, 18, 19, 20}; // for printing purposes
//const char *operators[21] = {"+", "-", "*", "/", "!", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ";", "[", "]", "(", ")", "{", "}"}; // do something about the backslash
//const int operatorID[21] = {9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11};

const int MAXIMUM_TOKENS = 5000;
int lexemeCounter = 0;
int tokenIDCounter = 0;
int spaceCounter = 0; // index of last space
bool isLineFinished = false;
int *tokensID;
// File pointers stored are stored in this header
FILE *wf;
FILE *fp;

#pragma region Main Matcher
//  prints the Token type based on keyword index from tokensID
bool keywordType()
{
  printf("%d", tokensID[tokenIDCounter]);
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
    fprintf(wf, "Logical Operator");
    return true;
  case 12:
    fprintf(wf, "Tralse Constant: true");
    return true;
  case 13:
    fprintf(wf, "Tralse Constant: false");
    return true;
  case 14:
    fprintf(wf, "3.14");
    return true;
  case 15:
    fprintf(wf, "2147483647");
    return true;
  case 16:
    fprintf(wf, "2.71828");
    return true;
  case 17:
    fprintf(wf, "273");
    return true;
  case 18:
    fprintf(wf, "noise word");
    return true;
  case 19:
    fprintf(wf, "{1,3,5,7,9}");
    return true;
  case 20:
    fprintf(wf, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    return true;
  default:
    return false;
  }
}
// give tokens some ID for future use :>
bool matchIfArithmeticOperator(char *token) // All Arithmetic Operator Used
{
  char c = token[0];
  switch (c)
  {
  case '+':
    if (token[1] == '+')
    {
      fprintf(wf, "Arithmetic Operator: Increment");
      return true;
    }
    fprintf(wf, "Arithmetic Operator: Addition");
    return true;
  case '-':
    if (token[1] == '-' && isNumeric(token[2]))
    {
      //fprintf(wf, "Arithmetic Operator: Decrement");
      return false;
    }
    if (token[1] == '-')
    {
      fprintf(wf, "Arithmetic Operator: Decrement");
      return true;
    }
    if (isNumeric(token[1]))
    {
      //fprintf(wf, "Arithmetic Operator: Decrement");
      return false;
    }
    fprintf(wf, "Arithmetic Operator: Subtraction");
    return true;
  case '*':
    fprintf(wf, "Arithmetic Operator: Multiply");
    return true;
  case '%':
    fprintf(wf, "Arithmetic Operator: Modulo");
    return true;
  case '/': // how to know if comment or not, later
    if (token[1] == '/')
    {
      fprintf(wf, "Comment");
      return true;
    }
    fprintf(wf, "Arithmetic Operator: Division");
    return true;
  default:
    return false;
  }
}
bool matchIfRelationalOperator(char *token) // All Conditional Symbols Used (AND NOT OR is stored in Keywords)
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
    if (token[1] == '\0')
    {
      fprintf(wf, "Relational Operator: not");
      return true;
    }
    return false;
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
bool matchIfSentence(char *token) // Matches if current lexeme is a sentence with ""
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
bool matchIfDelimiter(char *token) // All Delimiters Used
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
bool isDelimiter(char ch) // Checks all Delimiters used in reading in a conditional statement
{
  if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',' || ch == '.')
    return (true);
  return (false);
}

bool isOperator(char ch) // Checks all Operators in a conditional Statement
{
  if (ch == '+' || ch == '-' || ch == '*' ||
      ch == '/' || ch == '>' || ch == '<' ||
      ch == '=' || ch == '%')
    return (true);
  return (false);
}
// --Compares the given character to it's ascii value--
bool isAlphabet(char ch) // Checks if current character is an alphabet via ASCII Value
{

  if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
  {
    return true;
  }
  return false;
}
bool isNumeric(char ch) // Checks if current character is a digit via ASCII Value
{
  if (ch >= '0' && ch <= '9')
  {
    //  printf("%c  character is digit True", ch);
    return true;
  }
  return false;
}
// Might be edited for Automata :<

bool matchWithKeywords(char *token) // Matches given input against a keyword, Matches each character one by one until rejected or accepted
{                                   // printf("Token: %s", token);
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
}
/*bool matchWithOperators(char *token)
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
*/
bool matchIfNumber(char *token) // Matches given input character one by one if it is an accepted numerical value
{
  bool hasPeriod = false;
  bool flag = false;
  char c;
  for (int i = 0; i < strlen(token); i++)
  {
    c = token[i];
    if (token[0] == '-' || isNumeric(token[0]) || (token[0] == '.' && strlen(token) > 1))
    {
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
  }
  if (hasPeriod && flag == true)
  {
    fprintf(wf, "float");
    return flag;
  }
  if (flag == true)
  {
    fprintf(wf, "integer");
    return true;
  }
  return false;
}
bool matchiIfVariableName(char *token) // Matches given input character one by one if it is a valid variableName
{
  char c = token[0];
  bool flag = false;
  if (strlen(token) == 1 && isAlphabet(c))
  {
    return true;
  }
  for (int i = 1; i < strlen(token); i++)
  {
    c = token[i];
    if (isAlphabet(token[0]))
    {
      flag = true;
      if (isAlphabet(c) || isNumeric(c) || '_')
      {
        flag = true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  return flag;
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
    // fprintf(wf, "Number");
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
#pragma endregion

//Read a sentence
// Function that Reads a Line Example : Number x = 23;
void ReadLexeme(char *LongLine)
{
  // printf("\n%s", LongLine); // Check Current Line
  while (!isLineFinished)
  {
    setToken(LongLine);
  }
  // allocate tokenID Array
  tokensID = malloc(lexemeCounter * sizeof(tokensID));
  isLineFinished = false;
  spaceCounter = 0;
}

void showLexemes()
{

  wf = fopen("Symbol Table.txt", "w");
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

// This function is responsible for splitting each read lexeme into pieces and stores it on to an array
/*
Example:Number x = 23;
[0] Number
[1] x
[2] =
[3] 23
[4] ;
*/
void setToken(char *word)
{
  int length = readAWord(word);
  if (length == 0 && word[spaceCounter] == ' ') // if read word is just a space
    return;
  int tokenLength = length + 1;
  int internalCounter = 0;
  int startCharacter = spaceCounter;
  bool isSentence = false;
  bool isComment = false;
  //  printf("\n length: %d\n", tokenLength);

  char c;
  char *token = malloc(tokenLength + 1 * sizeof(char *));

  for (int i = 0; i < tokenLength; i++)
  {
    c = word[startCharacter + i];
    if (c == '/' && word[startCharacter + i + 1] == '/' && !isComment)
    {
      isComment = true;
    }
    if (c == '"' && !isSentence) // beginning of sentence
    {
      isSentence = true;
    }
    else if (c == '"' && isSentence)
    {
      isSentence = false;
    }
    if ((c == ' ' || c == '\n') && (isSentence == false && isComment == false)) // if not a sentence
    {
      continue;
    }
    else
    {
      token[internalCounter] = c;
      //printf("%c %c\n", c, token[internalCounter]);
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
}

// This Function is responsible for accurately splitting each lexeme into pieces
// returns a length based on the given Line;
//read a character until whitespace or special delimiters
int readAWord(char *word)
{
  // printf("SpaceCOunter: %d", spaceCounter);
  int internalCounter = 0;
  char c;
  bool sentenceEncountered = false;
  bool commentEncountered = false;
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
    if (c == '/' && word[i + 1] == '/') // double slash is a comment
    {
      internalCounter += 2;
      i++;
      commentEncountered = true;
      continue;
    }
    if (commentEncountered == true)
    {
      if (word[i + 1] == '\n' || word[i + 1] == '\0')
      {

        isLineFinished = true;
        commentEncountered = false;
        return internalCounter;
      }
      internalCounter++;
      continue;
    }

    if (word[i + 1] == '\n' || word[i + 1] == '\0') // if delimiter is the next character return the
    {
      isLineFinished = true;
      return internalCounter;
    }
    else if (isNumeric(c) && word[i + 1] == '.') //---2
    {
      internalCounter += 2;
      i++;
      continue;
    }
    else if ((isOperator(word[i + 1]) || isDelimiter(word[i + 1])) && (isAlphabet(c) || isNumeric(c))) // if next character is a delimiter
    {
      return internalCounter;
    }
    else if (isDelimiter(word[i + 1]) && c != ' ') // if next character is a delimiter and c is not a space
    {
      return internalCounter;
    }
    else if (isOperator(c) && isOperator(word[i + 1]) && isNumeric(word[i + 2])) //---2
    {
      return internalCounter += 1;
    }
    else if (isOperator(c) && isNumeric(word[i + 1])) //---2
    {
      internalCounter += 1;
      continue;
    }
    else if (isDelimiter(c) || isOperator(c)) // if c is a known symbol
    {
      if (isDelimiter(c) && isDelimiter(word[i + 1])) //== != >=    // if c + 1 is also a symbol
        return ++internalCounter;
      if (isOperator(c) && isOperator(word[i + 1])) //== --    // if c + 1 is also a symbol
        return ++internalCounter;
      return internalCounter;
    }
    if (c == ' ' || c == ';' || c == '\0') // change to list of delimiters // forgot what this for
    {
      if (word[i + 1] == ' ' && c == ' ') // peek, if c is space and next c is also a space
      {
        internalCounter++;
        continue;
      }
      else if (c == ' ') // if c is space
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

// This function is responsible for splitting each lexeme and storing it in an array
//read word will be stored in a char[]

// given a string
// check if string is AlphaNumeric
// split each string when a white space is encountered
