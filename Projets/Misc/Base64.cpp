//=============================================================================
	  //  Base64 Encoding Starter Framework
	  //  2011.02.16 by Abe Pralle
	  //
	  //  Reads a string of text and prints a resulting string of text where every
	  //  3 original characters have been transformed into 4 result characters
	  //  consisting of the first three characters reversed followed by a hypen.
	  //
	  //  Example output:
	  //    Enter text: ABCDEFGHIJKLMNOPQRSTUVWXYZ
	  //    You typed in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (26 characters)
	  //    Encoded value: CBA-FED-IHG-LKJ-ONM-RQP-UTS-XWV-
	  //=============================================================================
#include <iostream>
#include <cstring>

using namespace std;

int main();
void encode( unsigned char* src, unsigned char* dest );


static char encoding_table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
																'R','S','T','u','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i',
																'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0',
																'1','2','3','4','5','6','7','8','9','+','/'};

int main()
{
	 // Declare arrays to store original and encoded strings.
	 unsigned char st[80];
	 unsigned char encoded[120];
	 int padding = 0;
	 int string;


	 // Read in original string.
	 cout << "Enter text: ";
	 cin.getline( (char*)st, 80 );

	 // Print back out along with the # of characters.
	 int len = strlen((char*)st);
	 cout << "You typed in \"" << st << "\" (" << len << " characters)" << endl;

	 // Round length down to a multiple of 3.  Remove this to get the last odd chars
	 //len -= (len % 3);
	 if(len%3 == 1)
	 {
		 padding = 2;
	 }else if(len%3 == 2)
	 {
		 padding = 1;
	 }

	 // Encode the string - every 3 characters of original becomes
	 // 4 characters of result.
	 int dest_index = 0;
	 for (int i=0; i<len ; i+=3)
	 {
	   encode( st+i, encoded+dest_index );
	   dest_index += 4;
	 }

	// Null terminate destination string.
	encoded[dest_index] = 0;

	// Print encoded value.
	cout << "Encoded value: ";
	cout << encoded << endl;

	return 0;
}
//takes Different ascii characters and encodes it into base64
void encode( unsigned char* src, unsigned char* dest )
{
	//char that need to be turned into 8bit binary
	 unsigned char ch0 = src[0];
	 unsigned char ch1 = src[1];
	 unsigned char ch2 = src[2];

	//variable to hold each 6-bit binary
	 unsigned char str0 = ' ';
	 unsigned char str1 = ' ';
	 unsigned char str2 = ' ';
	 unsigned char str3 = ' ';


	//convert from text to binary

	//checks if the second character is empty so that we can include the equal signs as padding
	if(ch1 == '\0')
	{
		//changes 8 bit binary to six bit binary and stores them within the intialized variables
		//casting the ascii character to an int to turn it into decimal and then preforming binary opertations on it.
		str0 = int(ch0) >> 2;
		str1 = int(ch0) << 6;
		str1 = str1 >> 2;
		str1 = str1 + (int(ch1) >> 4);

		//takes the stored 6-bit binary and turns into decimal to find the base64 character using index
		str0 = encoding_table[str0];
		str1 = encoding_table[str1];
		//padding with equal signs
		str2 = '=';
		str3 = '=';
	}
	//checks if the third character is empty so that we can add the padding
	else if(ch2 == '\0')
	{


		//changes 8 bit binary to six bit binary and stores them within the intialized variables
		//casting the ascii character to an int to turn it into decimal and then preforming binary opertations on it.
		str0 = int(ch0) >> 2;
		str1 = int(ch0) << 6;
		str1 = str1 >> 2;
		str1 = str1 + (int(ch1) >> 4);
		str2 = int(ch1) << 4;
		str2 = str2 >> 2;
		str2 = str2 + (int(ch2) >> 6);


		//takes the stored 6-bit binary and turns into decimal to find the base64 character using index
		str0 = encoding_table[str0];
		str1 = encoding_table[str1];
		str2 = encoding_table[str2];
		str3 = '=';
	}else
	{
		//changes 8 bit binary to six bit binary and stores them within the intialized variables
		//casting the ascii character to an int to turn it into decimal and then preforming binary opertations on it.
		str0 = int(ch0) >> 2;
		str1 = int(ch0) << 6;
		str1 = str1 >> 2;
		str1 = str1 + (int(ch1) >> 4);
		str2 = int(ch1) << 4;
		str2 = str2 >> 2;
		str2 = str2 + (int(ch2) >> 6);
		str3 = int(ch2) << 2;
		str3 = str3 >>2;

		//takes the stored 6-bit binary and turns into decimal to find the base64 character using index
		str0 = encoding_table[str0];
		str1 = encoding_table[str1];
		str2 = encoding_table[str2];
		str3 = encoding_table[str3];
	}

	//exporting the encoded base64 characters to another function
	 dest[0] = str0;
	 dest[1] = str1;
	 dest[2] = str2;
	 dest[3] = str3;
}
