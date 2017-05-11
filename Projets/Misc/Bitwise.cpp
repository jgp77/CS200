/*
 * Created by Joshua Pollock
 * Project 4 - Bitwise Ops
 * CS-200
 * 3 March 2017
 * Description - Takes in two numbers ranging 0-255 and prints out the
 * hexadecimal, bianary, and decimal equivalent.
 * Written using Atom and compiled using Windows 10 Unbuntu Terminal
 */
#include "string.h"
#include <iostream>
using namespace std;

// forward declarations for functions
int main(int argc,char* argv[]);
void byteToDecimalStr(unsigned char,char*);
void byteToBinaryStr(unsigned char,char*);
void byteToHexStr(unsigned char,char*);

// global declarations for string space
char inputStr[5];
char decimalOut[4];
char binaryOut[9];
char hexOut[3];

/* The main function goes inputs and outputs,calling the helper functions
   as necessary to do formatting. */
int main(int argc,char* argv[])
{
        int num1,num2;
        unsigned char num1byte,num2byte,opresult,result;
        // Totally ignore the program arguments and launch right into prompts.
        cout<<"Welcome to the Bitwise Operator Demonstrator."<<endl<<endl;
        while(1) // bad form but I promise I'll break out of the infinite loop
        {
                cout<<"Would you like to continue?(y/n)";
                cin>>inputStr;
                // Common versions of 'no'
                if(!(strcmp(inputStr,"N")) || !(strcmp(inputStr,"n")) ||
                   !(strcmp(inputStr,"NO")) || !(strcmp(inputStr,"no")) ||
                   !(strcmp(inputStr,"No"))) break;  // see,I promised to break out

                // Common versions of 'yes'
                if(!(strcmp(inputStr,"Y")) || !(strcmp(inputStr,"y")) ||
                   !(strcmp(inputStr,"YES")) || !(strcmp(inputStr,"yes")) ||
                   !(strcmp(inputStr,"Yes")))
                {
                        cout<<"Ok,then let's get your first number between 0 and 255: ";
                        cin>>num1;

                        while(1) // he did it again!
                        {
                                // let's do some error checking before we move on
                                if((num1 < 0) ||(num1 > 255))
                                        cout<<"Parameters must be between 0 and 255."<<endl;
                                else break;

                                // If we didn't break,we need to try again...
                                cout<<"Let's try that again ... Your first number? ";
                                cin>>num1;
                                while(num1 < 0 || num1 > 255)
                                {
                                        cin>>num1;
                                        // not a numeric character,probably
                                        // clear the failure and pull off the non-numeric character
                                        if(cin.fail())
                                        {
                                                cin.clear();
                                        }
                                }
                        }

                        cout<<"Good! Now let's get your second number between 0 and 255: ";
                        cin>>num2;

                        while(1) // and again(!) with the infinite loop!
                        {
                                // let's do some error checking before we move on
                                if((num2 < 0) ||(num2 > 255))
                                        cout<<"Parameters must be between 0 and 255."<<endl;
                                else break;

                                // If we didn't break,we need to try again...
                                cout<<"Let's try that again ... Your second number? ";
                                cin>>num2;
                                while(num2 < 0 || num2 > 255)
                                {
                                        cin>>num2;
                                        // not a numeric character,probably
                                        // clear the failure and pull off the non-numeric character
                                        if(cin.fail())
                                        {
                                                cin.clear();
                                        }
                                }
                        }

                        // We have two numbers,let's move on
                        cout<<endl<<"Terrific,let's see what happens when we apply bitwise operators:"<<endl;

                        // force inputs to 8 bits
                        num1byte=(char)num1;
                        num2byte=(char)num2;
                        result=num1byte & num2byte;

                        // print header
                        cout<<"         Decimal    Hexidecimal          Binary"<<endl;

                        // format input 1 and print
                        byteToDecimalStr(num1byte,(char*)&decimalOut);
                        byteToHexStr(num1byte,(char*)&hexOut);
                        byteToBinaryStr(num1byte,(char*)&binaryOut);
                        cout<<"A=           "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format input 2 and print
                        byteToDecimalStr(num2byte,(char*)&decimalOut);
                        byteToHexStr(num2byte,(char*)&hexOut);
                        byteToBinaryStr(num2byte,(char*)&binaryOut);
                        cout<<"B=           "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format input 1 AND input 2 and print
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"A&B=         "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format input 1 OR input 2 and print
                        result=num1byte|num2byte;
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"A|B=         "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format input 1 XOR input 2 and print
                        result=num1byte^num2byte;
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"A^B=         "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format input 1 shifted by input 2 to the left and print
                        result=num1byte<<num2byte;
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"A<<B=        "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format input 1 shifted by input 2 to the right and print
                        result=num1byte>>num2byte;
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"A>>B=        "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;
                        // format complementary of input 1 and print
                        result=~num1byte;
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"~A=          "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;

                        // format complementary of input 2 and print
                        result=~num2byte;
                        byteToDecimalStr(result,(char*)&decimalOut);
                        byteToHexStr(result,(char*)&hexOut);
                        byteToBinaryStr(result,(char*)&binaryOut);
                        cout<<"~B=          "<<decimalOut<<"           ";
                        cout<<hexOut<<"h       "<<binaryOut<<"b"<<endl;
                }
                else // we didn't get a good response
                        cout<<"??? I didn't understand that.  Please try again."<<endl<<endl;
        }

        return 0;
}

void byteToDecimalStr(unsigned char num,char* rstr)
{
        char resultStr[4];
        char tempStr[4];
        unsigned char tempNum=num;
        unsigned char remainder;
        // declare some temporary variables to work with
        int cnt=3;
        // this is for padding leading 0s
        strncpy(resultStr,"",4);
        // start with a blank string
        while(cnt!=0)
        // loop until all digits are added
        {
                remainder=tempNum%10;
                // use modulo to get the digit
                tempNum=tempNum/10;
                // reduce the number for the next iteration
                switch(remainder)
                // based on the digit,get a character
                {
                case 0:
                        strncpy(tempStr,"0",4);
                        break;
                case 1:
                        strncpy(tempStr,"1",4);
                        break;
                case 2:
                        strncpy(tempStr,"2",4);
                        break;
                case 3:
                        strncpy(tempStr,"3",4);
                        break;
                case 4:
                        strncpy(tempStr,"4",4);
                        break;
                case 5:
                        strncpy(tempStr,"5",4);
                        break;
                case 6:
                        strncpy(tempStr,"6",4);
                        break;
                case 7:
                        strncpy(tempStr,"7",4);
                        break;
                case 8:
                        strncpy(tempStr,"8",4);
                        break;
                case 9:
                        strncpy(tempStr,"9",4);
                        break;
                }

                strncat(tempStr,resultStr,4);
                // add the digit to the front
                strncpy(resultStr,tempStr,4);
                // Copies the tempStr to the resultStr
                cnt--;
        }

        strncpy(rstr,resultStr,4);
        // Copies the resultStr to rstr
}

// void byteToBinaryStr( char, char*)
// This function takes an integer (forced to a byte length) and the address of a character
// string as its inputs.  It will convert the value of the integer to a binary by dividing
// the number by the base 2 and adding extracted digits in the remainder to a string that is
// returned in the address passed in the inputs.  There is no error checking - any possible
// byte value is valid and it is up to the user to provide reasonable inputs.  The result
// string is padded with leading 0s up to an 8-digit field (11111111 is the max for one byte).
void byteToBinaryStr(unsigned char num,char* rstr)
{
        unsigned char tempNum=num;
        unsigned char rem;
        char resultStr[4];
        char tempStr[4];
        // Sets up temporary variables for use in byteToBinaryStr
        int cnt=8;
        // This is for padding leading 0s
        strncpy(resultStr,"",9);
        // Start with a blank string,9 positions for a byte
        while(cnt!=0)
        // Loop until all digits are added
        {
                rem=tempNum%2;
                // Use modulo to get the remainder
                switch(rem)
                // Based on the digit,get a character
                {
                case 0:
                        strncpy(tempStr,"0",9);
                        break;
                case 1:
                        strncpy(tempStr,"1",9);
                        break;
                }
                cnt-=1;
                // Subtracts 1 from the counter
                tempNum=tempNum/2;
                // Reduce the number for the next iteration
                strncat(tempStr,resultStr,9);
                // Add the digit to the front
                strncpy(resultStr,tempStr,9);
                // Copies the tempStr to the resultStr
        }
        strncpy(rstr,resultStr,9);
        // Copies the resultStr to rstr
}

// void byteToHexStr( char, char*)
// This function takes an integer (forced to a byte length) and the address of a character
// string as its inputs.  It will convert the value of the integer to a hexadecimal by dividing
// the number by the base 16 and adding extracted digits in the remainder to a string that is
// returned in the address passed in the inputs.  There is no error checking - any possible
// byte value is valid and it is up to the user to provide reasonable inputs.  The result
// string is padded with leading 0s up to a 2-digit field (FF is the max for one byte).
void byteToHexStr(unsigned char num,char* rstr)
{
        unsigned char tempNum=num;
        unsigned char rem;
        char resultStr[4];
        char tempStr[4];
        // Sets up temporary variables for use in byteToHexStr
        int cnt=3; //initializes a counter
        strncpy(resultStr,"",4); // start with a blank string,4 positions for a hexadecimal
        while(cnt!=0) // loop until all digits are added
        {
                rem=tempNum%16; // Sets rem to the modulo of tempNum and 16
                switch(rem) // Based on the remainder, get a character
                {
                //Cases based off given byteToDecimalStr
                // Ex: if it is 5, copies 5 to the tempStr
                case 0:
                        strncpy(tempStr,"0",4);
                        break;
                case 1:
                        strncpy(tempStr,"1",4);
                        break;
                case 2:
                        strncpy(tempStr,"2",4);
                        break;
                case 3:
                        strncpy(tempStr,"3",4);
                        break;
                case 4:
                        strncpy(tempStr,"4",4);
                        break;
                case 5:
                        strncpy(tempStr,"5",4);
                        break;
                case 6:
                        strncpy(tempStr,"6",4);
                        break;
                case 7:
                        strncpy(tempStr,"7",4);
                        break;
                case 8:
                        strncpy(tempStr,"8",4);
                        break;
                case 9:
                        strncpy(tempStr,"9",4);
                        break;
                case 10:
                        strncpy(tempStr,"A",4);
                        break;
                case 11:
                        strncpy(tempStr,"B",4);
                        break;
                case 12:
                        strncpy(tempStr,"C",4);
                        break;
                case 13:
                        strncpy(tempStr,"D",4);
                        break;
                case 14:
                        strncpy(tempStr,"E",4);
                        break;
                case 15:
                        strncpy(tempStr,"F",4);
                        break;
                }
                strncat(tempStr,resultStr,4);
                // add the digit to the front
                strncpy(resultStr,tempStr,4);
                // Copies the tempStr to the resultStr
                tempNum=tempNum/16;
                // Divides the tempNum by 16 for the next itteration
                cnt-=1;
                // subtracts 1 from counter
        }
        strncpy(rstr,resultStr,4);
        // Copies the resultStr to rstr
}
