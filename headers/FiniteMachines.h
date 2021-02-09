#include <stdio.h>
#include <string.h>
#include <Token.h>
int lexemeCounter = 0;
int *tokenID;
//~~~~~~~~~~~~|| FSM || ~~~~~~~~~~~~~//

//~~~~~~~~~~~~|| Keyword Matching || ~~~~~~~~~~~~~~~~ //
bool MatchWithKeyword(char *c)
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
                {
                    printf("Banana");
                    return true;
                }
    return false;
}

bool whiteSpace(char c)
{
    switch (c)
    {
    case ' ':
        return true;
    case '\n':
        return true;
    case '\0':
        return true;
    }
    return false;
}

bool manualMatching(char *c)
{
}

void ReadString(char *input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        // Checking for null
        if (whiteSpace(input[i]))
        {
            continue; // continues to the next character
        }
        // If current character is a Delimiter
        if (input[i] == '(' || input[i] == ')' ||
            input[i] == '[' || input[i] == ']' ||
            input[i] == '{' || input[i] == '}' ||
            input[i] == ';' || input[i] == ',' ||
            input[i] == '.')
        {
            switch (input[i]) // if found a match give a token ID
            {
            case ';':
                fprintf(wf, "Delimiter: semicolon\t\t%c", input[i]);
                continue;
            case '(':
                fprintf(wf, "Delimiter: open parenthesis\t\t%c", input[i]);
                continue;
            case ')':
                fprintf(wf, "Delimiter: close parenthesis\t\t%c", input[i]);
                continue;
            case '{':
                fprintf(wf, "Delimiter: open curly bracket\t\t%c", input[i]);
                continue;
            case '}':
                fprintf(wf, "Delimiter: close curly bracket\t\t%c", input[i]);
                continue;
            case '[':
                fprintf(wf, "Delimiter: open square bracket\t\t%c", input[i]);
                continue;
            case ']':
                fprintf(wf, "Delimiter: close square bracket\t\t%c", input[i]);
                continue;
            case ',':
                fprintf(wf, "Delimiter: comma\t\t%c", input[i]);
                continue;
            }
        }
    }
}
