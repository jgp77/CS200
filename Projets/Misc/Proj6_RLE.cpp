// Proj6_RLE.cpp : Defines the entry point for the console application.
// C++ - Visual Studio 2015
//
// This program is used as a command prompt application which can compress and
// decompress text files.
//
// When a text file w/o the .rle file extension is passed in, the program opens the
// text document and uses RLE compression on the individual characters and saves the
// text document to a new file with the .rle extension. The opposite happens when a
// .rle file is passed in and a decompressed .plain text file is created.
//
// By: Joseph L. Remy Jr.
// CS200 001 - Patrick Kelley
// Project 6
// 2016 Apr. 1
//
// Change the compiler settings in Visual Studio 2015 and added the following argument:
// _CRT_SECURE_NO_WARNINGS - Fixes the "obsolate code" messages

// Include statements
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>

// Define the Namespace
using namespace std;


void compress(char* data, int count, FILE* outfile);
void decompress(char* data, int count, FILE* outfile);
char* readFileData(char* filename, int* count_ptr);
/*
int main()

The main entry point into the "Proj6_RLE" program. Takes in the number of arguments and declares the second
argument as the path to the text or RLE file.
*/
int main(int num_args, char* arg_values[])
{
	if (num_args != 2) // If there isn't exactly two parameters: the file location and the selected file
	{
		// Printo out an instructional text then quit the program
		printf("Usage: Proj6_RLE.exe filename (produces filename.rle)\n");
		printf("       Proj6_RLE.exe filename.rle (produces filename.plain)\n");
		exit(1);
	}

	// Get the name of the input file from the arg_values passed into the main method
	char* input_filename = arg_values[1];

	// Initialize count, the index or the number of chars in the file, and initlize all the chars into memeory
	// from the input file by calling the following function, "readFileData"
	int count;
	char* data = readFileData(input_filename, &count);

	// Creates a blank file and gets the string length of the file name
	FILE* outfile;
	int len = strlen(input_filename);


	// if the length is less than 4 i.e. ".rle" or less OR the file doesn't end with ".rle"
	if (len < 4 || strcmp(input_filename + (len - 4), ".rle") != 0)
	{
		// Create a char array to store the output file name
		char output_filename[200]; // and copy the input file name to the output file name char array
		strcpy(output_filename, input_filename);
		strcat(output_filename, ".rle"); // and add the file extension
		// Notify the user of what is going on via a console printout
		printf("Compressing %s to %s\n", input_filename, output_filename);

		// Initalize the output file for writing/overwriting
		outfile = fopen(output_filename, "wb");

		// Call the compress method
		compress(data, count, outfile);
	}

	// If we have a .rle file, let's create a decompressed .plain (text) file
	else
	{
		char output_filename[200]; // Setup an array to store the output file name
		strncpy(output_filename, input_filename, len - 4); // Copy the string minus the extension
		output_filename[len - 4] = 0;
		strcat(output_filename, ".plain"); // Concatinate the file name with the extension
										   // Notify the user of what's going on
		printf("Decompressing %s to %s\n", input_filename, output_filename);

		// Initialize an output file and call the decompress method
		outfile = fopen(output_filename, "wb");
		decompress(data, count, outfile);
	}

	// Close the file when we are done
	fclose(outfile);

	// Clear the memory of the input data
	delete data;

	// Quit with no errors
	return 0;
}
/*
void compress(char* data, int count, FILE* outfile)

This function takes in a text file and compresses it into a new file called the original file name
with a .rle extension. Uses RLE compression by counting repeating chars and outputting them in the file.

Example:
Original - WWBACCCCCE, .rle - W2A1C5E1
*/
void compress(char* data, int count, FILE* outfile)
{
	// Initialize a string to store the final file...
	string rleOutput = "";
	// grab the first character to start the counting of consequtive chars
	char conseqChar = data[0];
	// And since it is the first char, start the counter at 1
	int conseqCount = 1;

	// For all the chars in the data array, loop
	for (int i = 1; i < count; i++) {
		// If we have the same char and the count is already at 9
		if (conseqCount == 9 && conseqChar == data[i]) {
			// Output the char and the count
			rleOutput += conseqChar;
			rleOutput += to_string(conseqCount);
			// and continue counting and keep the conseqChar the same
			conseqCount = 1;
		} // If the counter hasn't hit 9 yet, but is the same char as the conseqChar, increment
		else if (conseqChar == data[i]) {
			conseqCount++;
		} // Otherwise, since the char has changed
		else {
			// Add the conseqChar and the number of occurances to the output string
			rleOutput += conseqChar;
			rleOutput += to_string(conseqCount);
			// Change the conseqChar to the new data[i] char and reset the counter to 1
			conseqChar = data[i];
			conseqCount = 1;
		}
	}
	// Substring out the new line char, '\n', which appears in the string as "1 "
	rleOutput = rleOutput.substr(0, rleOutput.size() - 2);

	// For each char in the output string, place the chars in the output file
	for each(char c in rleOutput) {
		putc(c, outfile);
	}

	// End with a new line char
	putc('\n', outfile);
}
/*
void decompress(char* data, int count, FILE* outfile)

The program passes in the .rle file that requires decompression. This method iterates through each
char in the input file and creates the original text file. The output file becomes a .plain text file
that uses RLE decompression.

Example:
RLE file - A1B2C3D4E3F2G1, Decompressed .plain file - ABBCCCDDDDEEEFFG
*/
void decompress(char* data, int count, FILE* outfile)
{
	// Initalize a string to store the number that we will later convert to an int 
	// The number string is used to translate A3 to AAA
	string num = "0";
	// Grab the first character
	char prevChar = data[0];

	// Prints the number of chars in the .rle file
	cout << "Original File: " << count << " char(s) long.";

	// For each char in the data array till i >= count
	for (int i = 1; i<count; i++)
	{
		// Example of character positioning
		// String:   A1B2C3D2E1
		// Pos's :   0123456789
		// Odd/Even: EOEOEOEOEO

		// Odd positions are the count of the previous char, prevChar
		if (i % 2 == 1) {
			num = data[i];
		}

		// Even positions are letters, numbers, symbols, etc.
		else {
			// Prints out the previous char and how many times we are going to print it to the file
			cout << " " << prevChar << " Times " << num;
			// For the value of num (1-9), print the current curChar num-times
			for (int i = 0; i < stoi(num); i++) {
				putc(prevChar, outfile);
			}
			// Then set the new curChar
			prevChar = data[i];
		} 
	}

	// End the file stream with a new line character
	putc('\n', outfile);
}


/*
char* readFileData(char* filename, int* count_ptr)

Provided from the skeleton code. Takes in the file path and name and th
*/
char* readFileData(char* filename, int* count_ptr)
{
	// Tries to open the file passed in as read only
	FILE* infile = fopen(filename, "rb");

	// If the infile was not generated/opened
	if (!infile)
	{
		// Tell the user it does not exist
		printf("No such file \"%s\"!\n", filename);
		exit(1); // and exit
	}

	// Start a file seek at the beginning and go to the end
	fseek(infile, 0, SEEK_END);
	// Record the number of characters in the file by assigning it to count
	int count = ftell(infile);
	// Start the file seeker/cursor back to the beginning
	fseek(infile, 0, SEEK_SET);

	// Create a new char array with the length of count
	char* data = new char[count];

	// Read the data array into memory
	fread(data, 1, count, infile);

	// Close the file
	fclose(infile);

	// Assign the count globally 
	*count_ptr = count;

	// Return the data array
	return data;
}
