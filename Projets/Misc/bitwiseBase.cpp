/* bitwise.cpp : Patrick Kelley 2016

   Takes two integers between 0 and 255 and performs some standard bitwise
   operations on them, printing the results in binary, hex, and decimal. It
   does not use the standard C conversions for decimal and binary and instead
   creates its own string output because why not?  Good practice for base
   conversions and needs to be done for binary anyway.

   This version does prompted input instead of command-line parameters. */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>

using namespace std;

// forward declarations for functions
void byteToDecimalStr(unsigned char, char*);
void byteToBinaryStr(unsigned char, char*);
void byteToHexStr(unsigned char, char*);

// global declarations for string space
char inputStr[5];
char decimalOut[4];
char binaryOut[9];
char hexOut[3];

/* The main function goes inputs and outputs, calling the helper functions
   as necessary to do formatting. */
int main(int argc, char* argv[])
{
        int num1, num2;
        unsigned char num1byte, num2byte, opresult;

        // Totally ignore the program arguments and launch right into prompts.
        cout << "Welcome to the Bitwise Operator Demonstrator." << endl << endl;
        while (1) // bad form but I promise I'll break out of the infinite loop
        {
                cout << "Would you like to continue? (y/n)";
                cin >> inputStr;
                // Common versions of 'no'
                if (!(strcmp(inputStr, "N")) || !(strcmp(inputStr, "n")) ||
                    !(strcmp(inputStr, "NO")) || !(strcmp(inputStr, "no")) ||
                    !(strcmp(inputStr, "No"))) break; // see, I promised to break out

                // Common versions of 'yes'
                if (!(strcmp(inputStr, "Y")) || !(strcmp(inputStr, "y")) ||
                    !(strcmp(inputStr, "YES")) || !(strcmp(inputStr, "yes")) ||
                    !(strcmp(inputStr, "Yes")))
                {
                        cout << "Ok, then let's get your first number between 0 and 255: ";
                        cin >> num1;

                        while(1) // he did it again!
                        {
                                // let's do some error checking before we move on
                                if ((num1 < 0) || (num1 > 255))
                                        cout << "Parameters must be between 0 and 255." << endl;
                                else break;

                                // If we didn't break, we need to try again...
                                cout << "Let's try that again ... Your first number? ";
                                cin >> num1;
                                while (num1 < 0 || num1 > 255)
                                {
                                        cin >> num1;
                                        // not a numeric character, probably
                                        // clear the failure and pull off the non-numeric character
                                        if (cin.fail())
                                        {
                                                cin.clear();
                                        }
                                }
                        }

                        cout << "Good! Now let's get your second number between 0 and 255: ";
                        cin >> num2;

                        while(1) // and again(!) with the infinite loop!
                        {
                                // let's do some error checking before we move on
                                if ((num2 < 0) || (num2 > 255))
                                        cout << "Parameters must be between 0 and 255." << endl;
                                else break;

                                // If we didn't break, we need to try again...
                                cout << "Let's try that again ... Your second number? ";
                                cin >> num2;
                                while (num2 < 0 || num2 > 255)
                                {
                                        cin >> num2;
                                        // not a numeric character, probably
                                        // clear the failure and pull off the non-numeric character
                                        if (cin.fail())
                                        {
                                                cin.clear();
                                        }
                                }
                        }

                        // We have two numbers, let's move on
                        cout << endl << "Terrific, let's see what happens when we apply bitwise operators:" << endl;

                        // force inputs to 8 bits
                        num1byte = (char)num1;
                        num2byte = (char)num2;

                        // print header
                        cout << "         Decimal    Hexidecimal    Binary" << endl;

                        // format input 1 and print
                        byteToDecimalStr(num1byte, (char*)&decimalOut);
                        byteToHexStr(num1byte, (char*)&hexOut);
                        byteToBinaryStr(num1byte, (char*)&binaryOut);
                        cout << "A =        " << decimalOut << "          ";
                        cout << hexOut << "h       " << binaryOut << "b" << endl;

                        // format input 2 and print
                        byteToDecimalStr(num2byte, (char*)&decimalOut);
                        byteToHexStr(num2byte, (char*)&hexOut);
                        byteToBinaryStr(num2byte, (char*)&binaryOut);
                        cout << "B =        " << decimalOut << "          ";
                        cout << hexOut << "h       " << binaryOut << "b" << endl;

                        // TODO - all the binary operations are output similarly
                        // to the above; you just have to do the math before you
                        // output it.

                }
                else // we didn't get a good response
                        cout << "??? I didn't understand that.  Please try again." << endl << endl;
        }

        return 0;
}

// void byteToDecimalStr( char, char*)
// This function takes an integer (forced to a byte length) and the address of a character
// string as its inputs.  It will convert the value of the integer to a decimal by dividing
// the number by the base 10 and adding extracted digits in the remainder to a string that is
// returned in the address passed in the inputs.  There is no error checking - any possible
// byte value is valid and it is up to the user to provide reasonable inputs.  The result
// string is padded with leading 0s up to a 3-digit field (255 is the max for one byte).
void byteToDecimalStr(unsigned char num, char* rstr)
{
        // declare some temporary variables to work with
        char resultStr[4];
        char tempStr[4];
        unsigned char tnum = num;
        unsigned char remainder;
        int cnt = 3; // this is for padding leading 0s

        strncpy(resultStr, "", 4); // start with a blank string
        while (cnt != 0) // loop until all digits are added
        {
                remainder = tnum % 10; // use modulo to get the digit
                tnum = tnum / 10; // reduce the number for the next iteration
                switch (remainder) // based on the digit, get a character
                {
                case 0:
                        strncpy(tempStr, "0", 4);
                        break;
                case 1:
                        strncpy(tempStr, "1", 4);
                        break;
                case 2:
                        strncpy(tempStr, "2", 4);
                        break;
                case 3:
                        strncpy(tempStr, "3", 4);
                        break;
                case 4:
                        strncpy(tempStr, "4", 4);
                        break;
                case 5:
                        strncpy(tempStr, "5", 4);
                        break;
                case 6:
                        strncpy(tempStr, "6", 4);
                        break;
                case 7:
                        strncpy(tempStr, "7", 4);
                        break;
                case 8:
                        strncpy(tempStr, "8", 4);
                        break;
                case 9:
                        strncpy(tempStr, "9", 4);
                        break;
                }

                strncat(tempStr, resultStr, 4); // add the digit to the front
                strncpy(resultStr, tempStr, 4);
                cnt--;
        }

        strncpy(rstr, resultStr, 4);
}

// TODO - The next two functions are dummies but the header comments tell you what they
// should do. They work exactly like the function above but pay attention to the length
// length of the expected string to adjust for the loops and lengths passed to string
// functions. Also pay attention to the base to set the number of cases and the modulo.

// void byteToBinaryStr( char, char*)
// This function takes an integer (forced to a byte length) and the address of a character
// string as its inputs.  It will convert the value of the integer to a binary by dividing
// the number by the base 2 and adding extracted digits in the remainder to a string that is
// returned in the address passed in the inputs.  There is no error checking - any possible
// byte value is valid and it is up to the user to provide reasonable inputs.  The result
// string is padded with leading 0s up to an 8-digit field (11111111 is the max for one byte).
void byteToBinaryStr(unsigned char num, char* rstr)
{
        // declare some temporary variables to work with

        strncpy(rstr, "00000000", 9);
}

// void byteToHexStr( char, char*)
// This function takes an integer (forced to a byte length) and the address of a character
// string as its inputs.  It will convert the value of the integer to a hexadecimal by dividing
// the number by the base 16 and adding extracted digits in the remainder to a string that is
// returned in the address passed in the inputs.  There is no error checking - any possible
// byte value is valid and it is up to the user to provide reasonable inputs.  The result
// string is padded with leading 0s up to a 2-digit field (FF is the max for one byte).
void byteToHexStr(unsigned char num, char* rstr)
{
        // declare some temporary variables to work with

        strncpy(rstr, "00", 3);
}
