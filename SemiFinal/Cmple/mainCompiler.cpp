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
    printf("Output file: Symbol Table.txt");
    return 0;
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
bool isOperator(char ch)
{
    if (ch == '!' || ch == '+' || ch == '-' || ch == '=' || ch == '/' || ch == '|' || ch == '*' || ch == '%' || ch == '<' || ch == '>' || ch == '&')
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
    fprintf(wf, "Token           \t\t\t\t\tLexeme\n");
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
                fprintf(wf, "Delimiter: semicolon           \t\t\t\t\t%c\n", input[i]);
                continue;
            case '(':
                fprintf(wf, "Delimiter: open parenthesis    \t\t\t\t\t%c\n", input[i]);
                continue;
            case ')':
                fprintf(wf, "Delimiter: close parenthesis   \t\t\t\t\t%c\n", input[i]);
                continue;
            case '{':
                fprintf(wf, "Delimiter: open curly bracket  \t\t\t\t\t%c\n", input[i]);
                continue;
            case '}':
                fprintf(wf, "Delimiter: close curly bracket \t\t\t\t\t%c\n", input[i]);
                continue;
            case '[':
                fprintf(wf, "Delimiter: open square bracket \t\t\t\t\t%c\n", input[i]);
                continue;
            case ']':
                fprintf(wf, "Delimiter: close square bracket\t\t\t\t\t%c\n", input[i]);
                continue;
            case ',':
                fprintf(wf, "Delimiter: comma               \t\t\t\t\t%c\n", input[i]);
                continue;
            }
        }
        // If current character is an Arithmetic Operator
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
            input[i] == '/' || input[i] == '%')
        {
            if (input[i] == '*')
            {
                fprintf(wf, "Arithmetic Operator: Multiply\t\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '%')
            {
                fprintf(wf, "Arithmetic Operator: Modulo\t\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '/' && (whiteSpace(input[i + 1]) || input[i + 1] != '/'))
            {
                fprintf(wf, "Arithmetic Operator: Division\t\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '+')
            {
                if (input[i + 1] == '+') // peek
                {
                    ++i;
                    fprintf(wf, "Arithmetic Operator: Increment\t\t\t\t\t%c%c\n", input[i], input[i]);
                    continue;
                }

                fprintf(wf, "Arithmetic Operator: Addition\t\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '-')
            {
                if (input[i + 1] == '-') // peek
                {
                    ++i;
                    fprintf(wf, "Arithmetic Operator: Decrement\t\t\t\t\t%c%c\n", input[i], input[i]);
                    continue;
                }

                fprintf(wf, "Arithmetic Operator: Subtraction\t\t\t\t%c\n", input[i]);
                continue;
            }
        }

        //if Relational/logical
        if (input[i] == '>' || input[i] == '<' ||
            input[i] == '=' || input[i] == '!' ||
            input[i] == '|' || input[i] == '&')
        {
            if (input[i] == '>')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator: Greater Than equal to\t\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Relational Operator: Greater Than\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '!')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator: Not equal to\t\t\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Logical Operator: Not\t\t\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '&')
            {
                if (input[i + 1] == '&') // peek
                {
                    ++i;
                    fprintf(wf, "Logical Operator: And\t\t\t\t\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }
            }
            if (input[i] == '|')
            {
                if (input[i + 1] == '|') // peek
                {
                    ++i;
                    fprintf(wf, "Logical Operator: Or\t\t\t\t\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }
            }
            if (input[i] == '<')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator: Less Than equal to\t\t\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Relational Operator: Less Than\t\t\t\t\t%c\n", input[i]);
                continue;
            }
            if (input[i] == '=')
            {
                if (input[i + 1] == '=') // peek
                {
                    ++i;
                    fprintf(wf, "Relational Operator:  equal to\t\t\t\t\t%c%c\n", input[i - 1], input[i]);
                    continue;
                }

                fprintf(wf, "Assignment Operator: equal\t\t\t\t\t%c\n", input[i]);
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
                while (input[i] != '\n' && input[i] != '\0')
                {
                    printString += input[i];
                    ++i;
                }
                fprintf(wf, "Comment:\t\t\t\t\t\t\t%s\n", printString.c_str());
            }
        }
        // if Multi Line Content
        else if (input[i] == '~')
        {
            printString = "";
            printString += input[i];
            ++i;
            while (input[i] != '~')
            {
                printString += input[i];
                ++i;
            }
            printString += input[i];
            fprintf(wf, "Multi Line Comment: \t\t\t\t\t\t%s\n", printString.c_str());
            continue;
        }
        // if Sentence literal
        else if (input[i] == '"')
        {
            printString = "";
            //  printString += input[i];
            ++i;
            while (input[i] != '"')
            {
                printString += input[i];
                ++i;
            }
            fprintf(wf, "Sentence Literal: \t\t\t\t\t\t%s\n", printString.c_str());
            continue;
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
                fprintf(wf, "Numeric: float\t\t\t\t\t\t\t%s\n", printString.c_str());
            }
            else
            {
                fprintf(wf, "Numeric: int\t\t\t\t\t\t\t%s\n", printString.c_str());
            }
            --i;
        }

        // Keyword Matching, Identifiers, Unknown Symbols Alphabetized
        else
        {
            // reset printString:
            printString = "";
            for (i; !whiteSpace(input[i]) || !isDelimiter(input[i]) || !isOperator(input[i]); i++) // Reads each character while a special case is not detected //(!isAlphabet(input[i]) || !isNumeric(input[i]))
            {
                if (whiteSpace(input[i]) || isDelimiter(input[i]) || isOperator(input[i])) //isAlphabet(input[i]) || isNumeric(input[i])
                {
                    break;
                }
                else
                {
                    printString += input[i]; // this means that if not acceptable keyword revert to read that again
                    if (whiteSpace(input[i + 1]) || isDelimiter(input[i + 1]) || isOperator(input[i + 1]))
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
                                            fprintf(wf, "Reserved Word: Alphabet\t\t\t\t\t\t%s\n", printString.c_str());
                                            continue;
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
                            fprintf(wf, "Keyword: case\t\t\t\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                }
                else if (printString[1] == 'o')
                {
                    if (printString[2] == 'm')
                    {
                        if (printString[3] == 'p' && printString[4] == '\0')
                        {
                            fprintf(wf, "Keywords: comp\t\t\t\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
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
                                                    fprintf(wf, "Keyword: Data type: Collection\t\t\t\t\t%s\n", printString.c_str());
                                                    continue;
                                                }
            }
            // if default
            if (printString[0] == 'd')
            {
                if (printString[1] == 'e')
                {
                    if (printString[2] == 'f')
                    {
                        if (printString[3] == 'a')
                        {
                            if (printString[4] == 'u')
                            {
                                if (printString[5] == 'l')
                                {
                                    if (printString[6] == 't' && printString[7] == '\0')
                                    {
                                        fprintf(wf, "Keywords: Flow Control: default\t\t\t\t\t%s\n", printString.c_str());
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }

                //IF do
                else if (printString[1] == 'o' && printString[2] == '\0')
                {
                    fprintf(wf, "Keywords: Iteration Control: do\t\t\t\t\t%s\n", printString.c_str());
                    continue;
                }
            }
            //IF else
            if (printString[0] == 'e')
            {
                if (printString[1] == 'l')
                {
                    if (printString[2] == 's')
                    {
                        if (printString[3] == 'e' && printString[4] == '\0')
                        {
                            fprintf(wf, "Keywords: Flow Control: else\t\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                    }
                }
                //IF euler
                else if (printString[1] == 'u')
                {
                    if (printString[2] == 'l')
                    {
                        if (printString[3] == 'e')
                        {
                            if (printString[4] == 'r' && printString[5] == '\0')
                            {
                                fprintf(wf, "euler Constant: 2.71828\t\t\t\t\t\t%s\n", printString.c_str());
                                continue;
                            }
                        }
                    }
                }
            }
            //IF false & for
            if (printString[0] == 'f')
            {
                if (printString[1] == 'a')
                {
                    if (printString[2] == 'l')
                    {
                        if (printString[3] == 's')
                        {
                            if (printString[4] == 'e' && printString[5] == '\0')
                            {
                                fprintf(wf, "Reserved Word: Tralse Value: false\t\t\t\t%s\n", printString.c_str());
                                continue;
                            }
                        }
                    }
                }
                else if (printString[1] == 'o')
                {
                    if (printString[2] == 'r' && printString[3] == '\0')
                    {
                        fprintf(wf, "Keyword: Iteration Control: for\t\t\t\t\t%s\n", printString.c_str());
                        continue;
                    }
                }
            }

            //IF Item
            if (printString[0] == 'I')
            {
                if (printString[1] == 't')
                {
                    if (printString[2] == 'e')
                    {
                        if (printString[3] == 'm' && printString[4] == '\0')
                        {
                            fprintf(wf, "Reserved Word: Data type: Item\t\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                    }
                }
            }

            //IF if   -- HOORAY! & int32

            if (printString[0] == 'i')
            {
                if (printString[1] == 'f' && printString[2] == '\0')
                {
                    fprintf(wf, "Keyword: Flow Control: if\t\t\t\t\t%s\n", printString.c_str());
                    continue;
                }

                else if (printString[1] == 'n')
                {
                    if (printString[2] == 't')
                    {
                        if (printString[3] == '3')
                        {
                            if (printString[4] == '2' && printString[5] == '\0')
                            {
                                fprintf(wf, "Constant Value: 2,147,483,647\t\t\t\t\t%s\n", printString.c_str());
                                continue;
                            }
                        }
                    }
                }
            }

            //IF Kelvin
            if (printString[0] == 'k')
            {
                if (printString[1] == 'e')
                {
                    if (printString[2] == 'l')
                    {
                        if (printString[3] == 'v')
                        {
                            if (printString[4] == 'i')
                            {
                                if (printString[5] == 'n' && printString[6] == '\0')
                                {
                                    fprintf(wf, "Constant Value: 273\t\t\t\t\t\t%s\n", printString.c_str());
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

            //IF None & NOT & Number

            if (printString[0] == 'N')
            {
                if (printString[1] == 'o')
                {
                    if (printString[2] == 'n')
                    {
                        if (printString[3] == 'e' && printString[4] == '\0')
                        {
                            fprintf(wf, "Reserved Word: Null Value: None\t\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                    }
                }
                else if (printString[1] == 'u')
                {
                    if (printString[2] == 'm')
                    {
                        if (printString[3] == 'b')
                        {
                            if (printString[4] == 'e')
                            {
                                if (printString[5] == 'r' && printString[6] == '\0')
                                {
                                    fprintf(wf, "Reserved Word: Data Type: Number\t\t\t\t%s\n", printString.c_str());
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

            //IF otherwise & odd
            if (printString[0] == 'o')
            {
                if (printString[1] == 't')
                {
                    if (printString[2] == 'h')
                    {
                        if (printString[3] == 'e')
                        {
                            if (printString[4] == 'r')
                            {
                                if (printString[5] == 'w')
                                {
                                    if (printString[6] == 'i')
                                    {
                                        if (printString[7] == 's')
                                        {
                                            if (printString[8] == 'e' && printString[9] == '\0')
                                            {
                                                fprintf(wf, "Keyword: Flow Control: otherwise\t\t\t\t%s\n", printString.c_str());
                                                continue;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if (printString[1] == 'd')
                {
                    if (printString[2] == 'd' && printString[3] == '\0')
                    {
                        fprintf(wf, "Constant Value: 1,3,5,7,9\t\t\t\t\t%s\n", printString.c_str());
                        continue;
                    }
                }
            }

            //IF pi

            if (printString[0] == 'p')
            {
                if (printString[1] == 'i' && printString[2] == '\0')
                {
                    fprintf(wf, "Constant Value: 3.14\t\t\t\t\t\t%s\n", printString.c_str());
                    continue;
                }
            }

            //IF resume & return

            if (printString[0] == 'r')
            {
                if (printString[1] == 'e')
                {
                    if (printString[2] == 's')
                    {
                        if (printString[3] == 'u')
                        {
                            if (printString[4] == 'm')
                            {
                                if (printString[5] == 'e' && printString[6] == '\0')
                                {
                                    fprintf(wf, "Reserved Word: Iteration Control: resume\t\t\t%s\n", printString.c_str());
                                    continue;
                                }
                            }
                        }
                    }
                    else if (printString[2] == 't')
                    {
                        if (printString[3] == 'u')
                        {
                            if (printString[4] == 'r')
                            {
                                if (printString[5] == 'n' && printString[6] == '\0')
                                {
                                    fprintf(wf, "Reserved Word: return\t\t\t\t\t\t%s\n", printString.c_str());
                                    continue;
                                }
                            }
                        }
                    }
                    else if (printString[2] = 'a')
                    {
                        if (printString[3] = 'd' && printString[4] == '\0')
                            fprintf(wf, "Reserved Word: read\t\t\t\t\t\tread\n");
                        continue;
                    }
                }
            }

            //IF Sentence
            if (printString[0] == 'S')
            {
                if (printString[1] == 'e')
                {
                    if (printString[2] == 'n')
                    {
                        if (printString[3] == 't')
                        {
                            if (printString[4] == 'e')
                            {
                                if (printString[5] == 'n')
                                {
                                    if (printString[6] == 'c')
                                    {
                                        if (printString[7] == 'e' && printString[8] == '\0')
                                        {
                                            fprintf(wf, "Reserved Word: Data Type: Sentence\t\t\t\t%s\n", printString.c_str());
                                            continue;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //IF stop & switch
            if (printString[0] == 's')
            {
                if (printString[1] == 't')
                {
                    if (printString[2] == 'o')
                    {
                        if (printString[3] == 'p' && printString[4] == '\0')
                        {
                            fprintf(wf, "Reserved Word: Iteration Control: stop\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                    }
                }
                else if (printString[1] == 'w')
                {
                    if (printString[2] == 'i')
                    {
                        if (printString[3] == 't')
                        {
                            if (printString[4] == 'c')
                            {
                                if (printString[5] == 'h' && printString[6] == '\0')
                                {
                                    fprintf(wf, "Keyword: Flow Control: switch\t\t\t\t\t%s\n", printString.c_str());
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

            //IF then & true
            if (printString[0] == 't')
            {
                if (printString[1] == 'h')
                {
                    if (printString[2] == 'e')
                    {
                        if (printString[3] == 'n' && printString[4] == '\0')
                        {
                            fprintf(wf, "Noise Word: then\t\t\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                    }
                }
                else if (printString[1] == 'r')
                {
                    if (printString[2] == 'u')
                    {
                        if (printString[3] == 'e' && printString[4] == '\0')
                        {
                            fprintf(wf, "Reserved Word: Tralse Value: true\t\t\t\t%s\n", printString.c_str());
                            continue;
                        }
                    }
                }
            }

            //IF Tralse
            if (printString[0] == 'T')
            {
                if (printString[1] == 'r')
                {
                    if (printString[2] == 'a')
                    {
                        if (printString[3] == 'l')
                        {
                            if (printString[4] == 's')
                            {
                                if (printString[5] == 'e' && printString[6] == '\0')
                                {
                                    fprintf(wf, "Reserved Word: Data type: Tralse\t\t\t\t%s\n", printString.c_str());
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

            //IF while
            if (printString[0] == 'w')
            {
                if (printString[1] == 'h')
                {
                    if (printString[2] == 'i')
                    {
                        if (printString[3] == 'l')
                        {
                            if (printString[4] == 'e' && printString[5] == '\0')
                            {
                                fprintf(wf, "Keyword: Iteration Control: while\t\t\t\t%s\n", printString.c_str());
                                continue;
                            }
                        }
                    }
                }
                else if (printString[1] == 'r')
                {
                    if (printString[2] == 'i')
                        if (printString[3] == 't')
                            if (printString[4] == 'e' && printString[5] == '\0')
                            {
                                fprintf(wf, "Reserved word: write\t\t\t\t\t\t%s\n", printString.c_str());
                                continue;
                            }
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
                    fprintf(wf, "Identifier\t\t\t\t\t\t\t%s\n", printString.c_str());
                    continue;
                }
                else
                {
                    fprintf(wf, "Unknown Symbol\t\t\t\t\t\t\t\t%s\n", printString.c_str());
                    printf("Unknown Symbol\t\t\t\t\t\t\t\t%s\n", printString.c_str());

                    continue;
                }
            }
        }
        // Keywords/ ReservedWords/ variableName / Undefined Symbols
        // Read until Whitespace,or symbols
    }
}
