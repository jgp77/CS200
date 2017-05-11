#include <iostream>
#include <cstring>
using namespace std;
int main();
void encode(unsigned char* src,unsigned char* dest);
static char encodingKey[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                           'R','S','T','u','V','W','X','Y','Z','a','b','c','d','e','f','g','h',
                           'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y',
                           'z','0','1','2','3','4','5','6','7','8','9','+','/'};

int main()
{
        // Initializes two variables for use later on
        int string;
        int buffer;

        // Declare arrays to store original string, encoded strings, and decoded string.
        unsigned char st[80];
        unsigned char encoded[120];
        // Read in original string.
        cout<<"Enter text: ";
        cin.getline((char*)st, 80);
        // Print back out along with the # of characters.
        int len=strlen((char*)st);
        cout<<"You typed in \""<<st<<"\" ("<<len<<" characters)"<<endl;
        // Checks if length is odd or even and sets the correct buffer
        if(len%3==1)
        {
                buffer=2;
        }
        else if(len%3==2)
        {
                buffer=1;
        }
        // Encode the string - every 3 characters of original becomes
        // 4 characters of result.
        int dest_index=0;
        for (int i=0; i<len; i+=3)
        {
                encode(st+i, encoded+dest_index);
                dest_index += 4;
        }
        // Null terminate destination string.
        encoded[dest_index]=0;
        cout<<"\n"<<"Encoded value: ";
        // Print encoded value.
        cout<<encoded<<endl;
        return 0;
}
void encode(unsigned char* src,unsigned char* dest)
{
        unsigned char string0;
        unsigned char string1;
        unsigned char string2;
        unsigned char string3;
        // Creates 4 empy variables for storing the results

        unsigned char ch0=src[0];
        unsigned char ch1=src[1];
        unsigned char ch2=src[2];
        // Charcter to be turned in to a 8-bit binary number

        if(ch1=='\0')
        // Checks to see if the 2nd bit is empty
        // Adds two '='s if true
        {
                string0=int(ch0)>>2;

                string1=(int(ch0)<<6);
                string1=string1>>2;
                string1+=int(ch1)>>4;
                // Casts the characters into ints and does operations


                string0=encodingKey[string0];
                string1=encodingKey[string1];
                // Uses the encodingKey to determine what each stored number should translate to
                string2='=';
                string3='=';
                // Sets the last two variables to '='
        }

        else if(ch2=='\0')
        // Checks to see if the 3rd bit is empty
        // Adds 1 '='s if true
        {
                string0=int(ch0)>>2;

                string1=(int(ch0)<<6);
                string1=string1>>2;
                string1+=int(ch1)>>4;

                string2=int(ch1)<<4;
                string2=string2>>2;
                string2+=int(ch2)>>6;
                // Casts the characters into ints and does operations

                string0=encodingKey[string0];
                string1=encodingKey[string1];
                string2=encodingKey[string2];
                // Uses the encodingKey to determine what each stored number should translate to
                string3='=';
                // Sets the last variable to '='
        }


        else
        // else no bits are empty
        {
                string0=int(ch0)>>2;

                string1=(int(ch0)<<6);
                string1=string1>>2;
                string1+=int(ch1)>>4;

                string2=int(ch1)<<4;
                string2=string2>>2;
                string2+=int(ch2)>>6;

                string3=int(ch2)<<2;
                string3=string3>>2;
                // Casts the characters into ints and does operations

                string0=encodingKey[string0];
                string1=encodingKey[string1];
                string2=encodingKey[string2];
                string3=encodingKey[string3];
                // Uses the encodingKey to determine what each stored number should translate to
        }

        dest[0]=string0;
        dest[1]=string1;
        dest[2]=string2;
        dest[3]=string3;
        // Passes on the resulting characters to the function that called
}
