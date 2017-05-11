#include "string.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

int printArray(int arg[],int length);
int checkForZero(int arg1[],int length1,int arg2[],int length2,int sign);

float fp;
// Float that the user enters
int bits;
// Float as a binary
int count=0;
// Counter for use in main
int sign;
// Positive or negative for the number
int significandArray[23];
unsigned significand;
// Array to store the significand
int exponentArray[8];
// Array to stor the exponent
int exponent;
// Exponent in decimal form

int main(int argc,char* argv[])
{
        printf("Enter a real number: ");
        // Asks for user input
        cin>>fp;
        // Stores user input as fp (floating point)
        cout<<"\n";
        // New line char for visuals
        bits =*((int*)&fp);
        // Takes float pattern and turns to bit representation
        exponent=(bits>>23&0xff);
        // assigns variable to integer form of exponent
        for(int i=31; i>=0; i--)
        {
                printf("%d", (bits >> i) & 0x1);

                if(i==31)
                // If i is 31
                {
                        sign=(bits >> i) & 0x1;
                        printf(" ");
                        // Prints a space in between sign and exponent
                }
                if(i==23)
                // if i is 23
                {
                        printf(" ");
                        // prints space in between exponent and significand
                }
                if(i>23&&i<31)
                // if i is currently on the exponent location
                {
                        exponentArray[count]=(bits >> i) & 0x1;
                        // Adds the value to the exponent array at count position
                        count++;
                        // Adds 1 to count
                }
                if(i<23&&i>=0)
                // if i is currently on the significand position
                {
                        if(i==22) count=0;
                        // resets the counter before executing
                        significandArray[count]=(bits >> i) & 0x1;
                        // adds the value to the significand array at count positon
                        count++;
                        // Adds 1 to count
                }
        }
        printf("\nS Exponent Significand/Mantissa\n");
        checkForZero(exponentArray,8,significandArray,23,sign);
        printf("\nSign: %d",sign);
        // Prints the sign
        if(sign==0)
        // if the sign is positive
        {
                printf(" (positve)\n");
                // prints postivie
        }
        else
        {
                printf(" (negative)\n");
                // prints negative
        }
        printf("Exponent: ");
        printArray(exponentArray,8);
        // Prints the exponent in binary form
        cout<<" = "<<exponent<<"; w/ bias 127 -> ("<<exponent<<"-127) = "<<(exponent-127)<<"\n";
        // Prints the exponent decimal
        printf("Significand: ");
        printArray(significandArray,23);
        // Prints significand in binary form
        cout<<"\nw/ Implied 1: 1.";
        printArray(significandArray,23);
        // Prints significand with implied 1 at the begining
        cout<<"\n";
        return 0;
}
int printArray(int arg[],int length)
// void to print out an array
{
        for (int i=0; i<length; i++)
        // while i is less than lenght of array
        {
                cout << arg[i];
                // Prints out array element i
        }
        return 0;
}

int checkForZero(int arg1[],int length1,int arg2[],int length2,int sign)
{
        int onesCount=0;
        // Counter for amount of ones
        for(int i=0; i<length1; i++)
        {
                if(arg1[i])
                // If arg1 contains a one
                {
                        onesCount++;
                        // Add one to onesCount
                }
        }
        for(int i=0; i<length2; i++)
        {
                if(arg2[i]&&i!=0)
                // If arg2 contains a one
                {
                        onesCount++;
                        // Add one to onesCount
                }
        }
        if(onesCount==0)
        // If onescount is zero
        {
                if(sign==1)
                // If sign is negative
                {
                        cout<<"This is a special pattern for negative zero\n";
                }
                else
                {
                        cout<<"This is a special pattern for zero\n";
                }
        }

        return 0;
}
