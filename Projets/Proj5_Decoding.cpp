#include <iostream>
#include <cstring>
using namespace std;
int main();
void encode( unsigned char* src, unsigned char* dest );
int getposition(const char * array, size_t size, char c);


static char encodingKey[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                           'R','S','T','u','V','W','X','Y','Z','a','b','c','d','e','f','g','h',
                           'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y',
                           'z','0','1','2','3','4','5','6','7','8','9','+','/'};

int main()
{
	 // Declare arrays to store original and encoded strings.
	 unsigned char st[120];
	 unsigned char decoded[80];
	 int buffer = 0;
	 int string;


	 // Read in original string.
	 cout << "Enter text: ";
	 cin.getline( (char*)st, 120 );

	 // Print back out along with the # of characters.
	 int len = strlen((char*)st);
	 cout << "You typed in \"" << st << "\" (" << len << " characters)" << endl;

	 // Round length down to a multiple of 3.  Remove this to get the last odd chars
	 //len -= (len % 3);

	 // Encode the string - every 3 characters of original becomes
	 // 4 characters of result.
	 int dest_index = 0;
	 for (int i=0; i<len ; i+=4)
	 {
	   encode( st+i, decoded+dest_index );
	   dest_index += 3;
	 }

	// Null terminate destination string.
	decoded[dest_index] = 0;

	// Print encoded value.
	cout << "Decoded value: ";
	cout << decoded << endl;

	return 0;
}
//takes Different ascii characters and encodes it into base64
void encode( unsigned char* src, unsigned char* dest )
{
	//char that need to be turned into 8bit binary
	 unsigned char ch0 = src[0];
	 unsigned char ch1 = src[1];
	 unsigned char ch2 = src[2];
	 unsigned char ch3 = src[3];
	 int index1 = 0;
	 int index2 = 0;
	 int index3 = 0;
	 int index4 = 0;

	if (ch0 != '=')
	{
		index1 = (char)getposition(encodingKey,64,src[0]);
	}
	if(ch1 != '=')
	{
		index2 = (char)getposition(encodingKey,64,src[1]);
	}
	if(ch2 != '=')
	{
		index3 = (char)getposition(encodingKey,64,src[2]);
	}
	if(ch3 != '=')
	{
		index4 = (char)getposition(encodingKey,64,src[0]);
	}

	cout << index1 << endl;
	cout << index2 << endl;
	cout << index3 << endl;
	cout << index4 << endl;
	//variable to hold each 6-bit binary
	 unsigned char str0 = ' ';
	 unsigned char str1 = ' ';
	 unsigned char str2 = ' ';
	//used to convert to ascii
  char as1 = ' ';
	char as2 = ' ';
	char as3 = ' ';

	//convert from text to binary

	//checks if the second character is empty so that we can include the equal signs as buffer
	if(ch2 == '=')
	{
		//changes 6 bit binary to 8 bit binary and stores them within the intialized variables
		//casting the ascii character to an int to turn it into decimal and then preforming binary opertations on it.
		str0 = (index1 << 2) + ((int(index2) << 2) >>6);
		str1 = int(index2) << 6;
		str1 = index2 << 4 + 0 ;


		//takes the stored 8-bit binary and turns into decimal to find the ascii character using index
		as1 = int(str0);
		as2 = int(str1);
		as3 = 0 ;
	}
	//checks for how many bytes are entered
	else if(ch3 == '=')
	{


		//changes 8 bit binary to six bit binary and stores them within the intialized variables
		//casting the ascii character to an int to turn it into decimal and then preforming binary opertations on it.
		str0 = (index1 << 2) + ((int(index2) << 2) >>6);
		str1 = ((index2) << 4) + (((index3)<<2) >> 4);



		//takes the stored 8-bit binary and turns into decimal to find the ascii character using index
		as1 = int(str0);
		as2 = int(str1);
		as3 = 0;

	}else
	{
		//changes 6 bit binary to 8 bit binary and stores them within the intialized variables
		//casting the ascii character to an int to turn it into decimal and then preforming binary opertations on it.
		str0 = (index1 << 2) + ((int(index2) << 2) >>6);
		str1 = ((index2) << 4) + (((index3)<<2) >> 4);
		str2 = (index3 << 6)  + index4;
		//takes the stored 8-bit binary and turns into decimal to find the ascii character using index
		as1 = int(str0);
		as2 = int(str1);
		as3 = int(str2);


	}

	//exporting the decoded base64 characters to another function
	 dest[0] = as1;
	 dest[1] = as2;
	 dest[2] = as3;

}
int getposition(const char * array, size_t size, char c)
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i] == c)
            return (int)i;
    }
    return -1;
}
