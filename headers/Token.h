#include "TokenType.h"

typedef struct Token{
    TokenType type;
     char *lexeme;
     //Object literal; // Not needed until sometime later
     int line;
};



struct Token defineToken(TokenType tType, char lexeme[],int line)
{
    struct Token readToken;
    readToken.type = tType;
    readToken.lexeme = lexeme;
    readToken.line = line;
    return readToken;
}

char * toString()
{
  return " Y CAN'T U READ JAVA";
}