#pragma region Headers
#include <stdio.h>
#include <conio.h>
//#include "Token.h"
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
#pragma endregion

FILE *wf;
FILE *rf;

void ReadString(string input);
bool whiteSpace(char c);

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
    case '\t':
        return true;
    case '\n':
        return true;
    case '\0':
        return true;
    }
    return false;
}

/*
Alphabet [reserved word] X
AND [keywords]           X
Case [keywords]          X
Collection [keywords]    X
Comp [keywords]
Default [keywords]
Do [keywords]
Else [keywords]
Euler [reserved word]
False [reserved word]
For [keywords]
If [keywords]
Int32 [reserved word]
Item [keywords]
Kelvin [reserved word]
None [reserved word]
NOT [keywords]
Number [keywords]
Odd [reserved word]
OR [keywords]
Otherwise [keywords]
Pi [reserved word]
Resume [reserved word]
Return [reserved word]
Sentence [keywords]
Stop [reserved word]
Switch [keywords]
Then [reserved word]
Tralse [keywords]
True [reserved word]
While [keywords]
*/

int main()
{
    string stringInput = "123.31AND A23 +qw!e";
    string textFileName;
    stringstream streamOfData;
    ifstream file;
    printf("Enter the Filename you want to read:\n");
    cin >> textFileName;
    int fileNameLength = textFileName.size();
    if (textFileName[fileNameLength - 4] == '.')
    {
        if (textFileName[fileNameLength - 3] == 'c')
            if (textFileName[fileNameLength - 2] == 'm')
                if (textFileName[fileNameLength - 1] == 'p')
                    file.open(textFileName.c_str());
    }
    else
    {
        printf("file not found");
        exit(0);
    }

    if (!file.is_open())
    {
        printf("File not found. \n");
    }
    else
    {
        streamOfData << file.rdbuf();
        stringInput = streamOfData.str();
    }

    ReadString(stringInput);
    return 0;
}
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
bool isDelimiter(char ch)
{
    if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
        return (true);
    return (false);
}
void ReadString(string input)
{
    std::string printString; // only used for printing
    wf = fopen("Symbol Table.txt", "w");
    if (wf == NULL)
    {
        printf("\n\nno output file\n\n");
    }
    for (int i = 0; i < input.size(); i++)
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
                fprintf(wf, "Delimiter: semicolon\t\t%c\n", input[i]);
                continue;
            case '(':
                fprintf(wf, "Delimiter: open parenthesis\t\t%c\n", input[i]);
                continue;
            case ')':
                fprintf(wf, "Delimiter: close parenthesis\t\t%c\n", input[i]);
                continue;
            case '{':
                fprintf(wf, "Delimiter: open curly bracket\t\t%c\n", input[i]);
                continue;
            case '}':
                fprintf(wf, "Delimiter: close curly bracket\t\t%c\n", input[i]);
                continue;
            case '[':
                fprintf(wf, "Delimiter: open square bracket\t\t%c\n", input[i]);
                continue;
            case ']':
                fprintf(wf, "Delimiter: close square bracket\t\t%c\n", input[i]);
                continue;
            case ',':
                fprintf(wf, "Delimiter: comma\t\t%c\n", input[i]);
                continue;
            }
        }
        // If current character is an Arithmetic Operator
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
            input[i] == '/' || input[i] == '%')
        {
            if (input[i] == '*')
            {
                fprintf(wf, "Arithmetic Operator: Multiply\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '%')
            {
                fprintf(wf, "Arithmetic Operator: Modulo\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '/' && whiteSpace(input[i + 1]))
            {
                fprintf(wf, "Arithmetic Operator: Division\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '+')
            {
                if (input[i + 1] == '+') // peek
                {
                    ++i;
                    fprintf(wf, "Arithmetic Operator: Increment\t\t%c%c\n", input[i], input[i]);
                    continue;
                }

                fprintf(wf, "Arithmetic Operator: Addition\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '-')
            {
                if (input[i + 1] == '-') // peek
                {
                    ++i;
                    fprintf(wf, "Arithmetic Operator: Decrement\t\t%c%c\n", input[i], input[i]);
                    continue;
                }

                fprintf(wf, "Arithmetic Operator: Subtraction\t\t%c\n", input[i]);
                continue;
            }
        }

        //if Relational/logical
        if (input[i] == '>' || input[i] == '<' ||
            input[i] == '=' || input[i] == '!')
        {
            if (input[i] == '>')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator: Greater Than equal to\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Relational Operator: Greater Than\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '<')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator: Less Than equal to\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Relational Operator: Less Than\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '=')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator:  equal to\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Assignment Operator: equal\t\t%c\n", input[i]);
                continue;
            }
            // CONDITIONAL AND OR NOT??? REVERT TO && ! ||
        }

        // Single Line Comment
        else if (input[i] == '/')
        {
            ++i;
            printString = "";
            if (input[i] == '/')
            {
                printString += input[i - 1];
                printString += input[i];
                ++i;
                while (input[i] != '\n' || input[i] != '\0')
                {
                    printString += input[i];
                    ++i;
                }
                fprintf(wf, "Comment:\t\t%s\n",printString.c_str());
            }
        }

        else if (isNumeric(input[i]) || (input[i] == '.' && isNumeric(input[i + 1]))) // checks if current Character is a number a period or a negative number
        {
            bool hasPeriod = false;
            // while numeric
            printString = ""; // resetBufferString
            for (i; input[i] == '.' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' || input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9' || input[i] == '0'; i++)
            {
                if (input[i] == '.' && hasPeriod == false)
                {
                    hasPeriod = true;
                    printString += input[i];
                }
                else if (input[i] == '.' && hasPeriod == true)
                {
                    ++i;
                    break;
                }
                else
                {
                    printString += input[i];
                }
            }
            if (hasPeriod)
            {
                fprintf(wf, "Numeric: float\t\t%s\n", printString.c_str());
            }
            else
            {
                fprintf(wf, "Numeric: int\t\t%s\n", printString.c_str());
            }
            --i;
        }

        // Keyword Matching, Identifiers, Unknown Symbols Alphabetized
        else
        {
            // reset printString:
            printString = "";
            for (i; (!isAlphabet(input[i]) || !isNumeric(input[i])); i++) // Reads each character while a special case is not detected
            {
                if (isAlphabet(input[i]) || isNumeric(input[i]))
                    printString += input[i];
                else
                {
                    --i; // this means that if not acceptable keyword revert to read that again
                    break;
                }
            }

            // If Alphabet || AND
            if (printString[0] == 'A')
            {
                if (printString[1] == 'l')
                {
                    if (printString[2] == 'p')
                        if (printString[3] == 'h')
                            if (printString[4] == 'a')
                                if (printString[5] == 'b')
                                    if (printString[6] == 'e')
                                        if (printString[7] == 't' && printString[8] == '\0') // final state
                                        {
                                            fprintf(wf, "Reserved Word: Alphabet\t\t%s\n", printString.c_str());
                                        }
                }
                // IF AND
                else if (printString[1] == 'N')
                {
                    if (printString[2] == 'D' && printString[3] == '\0')
                    {
                        fprintf(wf, "Keyword: AND\t\t%s\n", printString.c_str());
                    }
                }
            }
            //IF case
            if (printString[0] == 'c')
            {
                if (printString[1] == 'a')
                {
                    if (printString[2] == 's')
                        if (printString[3] == 'e' && printString[4] == '\0')
                        {
                            fprintf(wf, "Keyword: case\t\t%s\n", printString.c_str());
                        }
                }
            }
            // If Collection < Upper case C
            if (printString[0] == 'C')
            {
                if (printString[1] == 'o')
                    if (printString[2] == 'l')
                        if (printString[3] == 'l')
                            if (printString[4] == 'e')
                                if (printString[5] == 'c')
                                    if (printString[6] == 't')
                                        if (printString[7] == 'i')
                                            if (printString[8] == 'o')
                                                if (printString[9] == 'n' && printString[10] == '\0')
                                                {
                                                    fprintf(wf, "Keyword: Data type: Collection\t\t%s\n", printString.c_str());
                                                }
            }

            // Add more Here and Below

            // Check if Identifier || Unknown Symbol
            else
            {
                bool isAnIdentifier = false;
                for (int ii = 0; ii < printString.size(); ii++)
                {
                    if (isAlphabet(printString[0]))
                    {
                        if (isAlphabet(printString[ii]) || isNumeric(printString[ii]) || printString[ii] == '_')
                        {
                            isAnIdentifier = true;
                        }
                        else
                        {
                            isAnIdentifier = false;
                            break;
                        }
                    }
                    else
                    {
                        isAnIdentifier = false;
                        break;
                    }
                }
                if (isAnIdentifier)
                {
                    fprintf(wf, "Identifier\t\t%s\n", printString.c_str());
                }
                else
                {
                    fprintf(wf, "Unknown Symbol\t\t%s\n", printString.c_str());
                }
            }
        }
        // Keywords/ ReservedWords/ variableName / Undefined Symbols
        // Read until Whitespace,or symbols
    }
}
