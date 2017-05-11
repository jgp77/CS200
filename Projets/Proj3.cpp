#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <stdlib.h>

void compress( char* data, int count, FILE* outfile );
void decompress( char* data, int count, FILE* outfile );
char* readFileData( char* filename, int* count_ptr );
int main( int num_args, char* arg_values[] )
{
        if (num_args != 2)
        {
                printf( "Usage: rle filename (produces filename.rle)\n" );
                printf( " rle filename.rle (produces filename.plain)\n" );
                exit(1);
        }
        char* input_filename = arg_values[1];
        // read the file data into an array
        int count;
        char* data = readFileData(input_filename,&count);
        // Call compress() or decompress().
        FILE* outfile;
        int len = strlen(input_filename);
        if (len < 4 || strcmp(input_filename+(len-4),".rle") != 0)
        {
                char output_filename[80];
                strcpy( output_filename, input_filename );
                strcat( output_filename, ".rle" );
                printf( "Compressing %s to %s\n", input_filename, output_filename );
                outfile = fopen( output_filename, "wb" );
                compress( data, count, outfile );
        }
        else
        {
                char output_filename[80];
                strncpy( output_filename, input_filename, len-4 );
                output_filename[len-4] = 0;
                strcat( output_filename, ".plain" );
                printf( "Decompressing %s to %s\n", input_filename, output_filename );
                outfile = fopen( output_filename, "wb" );
                decompress( data, count, outfile );
        }
        // Close the output file to ensure data is saved.
        fclose(outfile);
        // Free the array we allocated
        delete data;
        return 0;
}
void compress( char* data, int count, FILE* outfile )
{
        std::string finalOut("");
        // Creates string for final output
        char charac=data[0];
        // Uses the first character to count all consequtive characters
        int charCount=1;
        // Creates a counter that starts at 1
        for(int i=1; i<count; i++)
        // For all characters in the array
        {
                if(charCount==9&&charac==data[i])
                // If the count is 9 and we have the same character
                {
                        finalOut+=charac;
                        finalOut+=std::to_string(charCount);
                        // Outputs the character and the count
                        charCount=1;
                        // Sets the character count back to 1
                }
                else if(charac==data[i])
                // If the counter has not hit 9 and the characters are the same
                {
                        charCount++;
                }
                else
                {
                        finalOut+=charac;
                        finalOut+=std::to_string(charCount);
                        // Adds the character and the count to the output
                        charac=data[i];
                        charCount=1;
                        // Resets count to 1 and changes the characters to the new data[i]
                }
        }
        finalOut=finalOut.substr(0,finalOut.size()-2);
        //Substrings out the '\n' at the end which appears as "1 "
        for(char& c : finalOut)
        {
                putc(c,outfile);
                // For each of the characters in the output, puts them into the new file
        }
        putc('\n',outfile);
        // creates a new line
}

void decompress( char* data, int count, FILE* outfile )
{
        std::string numb("0");
        char previousChar=data[0];
        for(int i=1; i<count; i++)
        {
                if(i%2==1)
                {
                        numb=data[i];
                }
                else
                {
                        for(int i=0; i<stoi(numb); i++)
                        {
                                putc(previousChar,outfile);
                        }
                        previousChar=data[i];
                }
        }
        putc('\n',outfile);
}

char* readFileData( char* filename, int* count_ptr )
{
        // Returns a pointer to an array storing the file data.
        // Sets the variable pointed to by 'count' to contain the file size.
        // Exits the program if the filename doesn't exist.
        FILE* infile = fopen(filename,"rb");
        if ( !infile )
        {
                printf( "No such file \"%s\"!\n", filename );
                exit(1);
        }
        // Get file size by going to the end of the file, getting the
        // position, and then going back to the start of the file.
        fseek( infile, 0, SEEK_END );
        int count = ftell(infile);
        fseek( infile, 0, SEEK_SET );
        // read the data from the file
        char* data = new char[count];
        fread( data, 1, count, infile );
        fclose(infile);
        *count_ptr = count;
        return data;
}
