//*****************************************************************************
// File:				main.cpp
// Author:			Cayden Wagner
// Date:				Ferbruary 21, 2021
// Class:				CS250
// Assignment:	Cytography
// Purpose:			To read in a message from the user. If the message is in plain
//							text form, the program will output the message into a file
//							in encrypted form. If the message is encrypted, the program 
//							will output the message in plain text.
// Hours:				5
//*****************************************************************************

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int LETTERS_IN_ALPHABET = 26;
const int ASCII_VALUE_OF_A = 65;
const int ASCII_VALUE_OF_Z = 91;

void drawHeading(string title, char borderChar, int padding);
char getUserInput();
void getMappingData(int& numberOfMappings, string& keys);
void openFileForRead(ifstream& inputFile, string message);
void openFileForWrite(ofstream& outputFile, string message);
void closeFileForRead(ifstream& inputFile);
void closeFileForWrite(ofstream& outputFile);
void constructMappingArray(char mappingArray[][LETTERS_IN_ALPHABET],
					   							 string keys,
												   int numberOfMappings);
void printMappingArray(const char mappingArray[][LETTERS_IN_ALPHABET], 
										   int numberOfMappings);
char encodeCharacter(char plaintextCharacter,
										 const char mappingArray[][LETTERS_IN_ALPHABET],
										 int numberOfMappings);
char decodeCharacter(char ciphertextCharacter,
									 	 const char mappingArray[][LETTERS_IN_ALPHABET],
										 int numberOfMappings); 

//*****************************************************************************
// Function:			main
//
// Description:		Driver function to read in text from a file and encrypt or
//							  decrypt it based on user choice
//
// Parameters:	  None
//	
// Returned:		  Exit Status
//*****************************************************************************

int main() {
	const char ENCRYPT_OPTION = 'E', DECRYPT_OPTION = 'D', QUIT_OPTION = 'Q';
	const string TITLE_STRING = "CRYPTOGRAPHY";
	const string DECRYPT_MESSAGE = "Enter cyphertext filename: ";
	const string ENCRYPT_MESSAGE = "Enter plaintext filename: ";
	
	char input, userInput = 'N';
	char aMappingArray[LETTERS_IN_ALPHABET][LETTERS_IN_ALPHABET];
	string keys, line;
	int numberOfMappings;
	
	ifstream inputFile;
	ofstream outputFile;
	
	drawHeading(TITLE_STRING, '*', 10);

	do {
		do {
			input = getUserInput();
		} while (!(ENCRYPT_OPTION == input || DECRYPT_OPTION == input 
					 || QUIT_OPTION == input));

		if (input == 'E' || input == 'D') {
			getMappingData(numberOfMappings, keys);
			constructMappingArray(aMappingArray, keys, numberOfMappings);

			if (input == 'D') {
				openFileForRead(inputFile, DECRYPT_MESSAGE);
				openFileForWrite(outputFile, ENCRYPT_MESSAGE);

				while (!inputFile.eof()) {
					getline(inputFile, line);
					for (int i = 0; i < line.length(); i++) {
						outputFile << decodeCharacter(line.at(i), aMappingArray,
																					numberOfMappings);
					}
				}
				cout << endl << "Your message has been decrypted!" << endl << endl;
			}

			else if (input == 'E') {
				openFileForRead(inputFile, ENCRYPT_MESSAGE);
				openFileForWrite(outputFile, DECRYPT_MESSAGE);

				while (!inputFile.eof()) {
					getline(inputFile, line);
					for (int i = 0; i < line.length(); i++) {
						outputFile << encodeCharacter(line.at(i), aMappingArray,
																					numberOfMappings);
					}
				}
				cout << endl << "Your message has been encrypted!" << endl << endl;

			}

			closeFileForRead(inputFile);
			closeFileForWrite(outputFile);

			cout << "Would you like to encrypt or decrypt another file (Y or N)?: ";
			cin >> userInput;
			cout << endl;
		} 
	} while (userInput == 'Y');

	return EXIT_SUCCESS;
}

//*****************************************************************************
// Function:     drawHeading
//
// Description:  Displays a title encompassed by a border character
//
// Parameters:	 title - Title of the program
//							 borderChar - Character to encompass the title
//							 padding - The amount of spaces surrounding the title
//	
// Returned:		 None
//*****************************************************************************

void drawHeading(string title, char borderChar, int padding) {
	int totalLength;
	totalLength = title.length() + padding * 2 + 2;
	for (int i = 0; i < totalLength; i++) {
		cout << borderChar;
	}
	
	cout << endl << borderChar;

	for (int i = 0; i < padding; i++) {
		cout << " ";
	}

	cout << title;

	for (int i = 0; i < padding; i++) {
		cout << " ";
	}

	cout << borderChar << endl;

	for (int i = 0; i < totalLength; i++) {
		cout << borderChar;
	}
	cout << endl << endl;
}

//*****************************************************************************
// Function:     getUserInput
//
// Description:  Allows the user to choose wether they want to encrypt or 
//							 decrypt or quit
//
// Parameters:	 None
//	
// Returned:		 None
//*****************************************************************************

char getUserInput() {
	char input;
	cout << "Enter E) for encrypt, D) for decrypt, or Q) for quit: ";
	cin >> input;

	return input;
}

//*****************************************************************************
// Function:     getMappingData
//
// Description:  Allows the user to enter the number of mappings and keys
//							 that they want
//
// Parameters:	 numberOfMappings - The number of mappings chosen
//							 keys - The key letters chosen to configure the mapping array
//	
// Returned:		 None
//*****************************************************************************

void getMappingData(int& numberOfMappings, string& keys) {
	do {
		cout << "Enter the number of mappings to use (2-25): ";
		cin >> numberOfMappings;
	} while (!(numberOfMappings >= 2 && numberOfMappings <= 25));

	do {
		cout << "Enter the " << numberOfMappings << " keys: ";
		cin >> keys;
	} while (keys.length() != numberOfMappings);
}

//*****************************************************************************
// Function:     openFileForRead
//
// Description:  Allows the user to enter a text file to open for inputting
//
// Parameters:	 inputFile - Allows the input file to open
//							 message - A prompt displayed on screen to direct the user
//	
// Returned:		 None
//*****************************************************************************

void openFileForRead(ifstream& inputFile, string message) {
	string fileName;

	do {
		cout << message;
		cin >> fileName;
		inputFile.open (fileName);
	}  while (!inputFile.is_open());
}

//*****************************************************************************
// Function:     openFileForWrite
//
// Description:  Allows the user to enter a text file to open for outputting
//
// Parameters:	 outputFile - Allows the output file to open
//							 message - A prompt displayed on screen to direct the user
//	
// Returned:		 None
//*****************************************************************************

void openFileForWrite(ofstream& outputFile, string message) {
	string fileName;

	do {
		cout << message;
		cin >> fileName;
		outputFile.open(fileName);
	} while (!outputFile.is_open());
}

//*****************************************************************************
// Function:     closeFileForRead
//
// Description:  Closes the input file
//
// Parameters:	 inputFile - Allows the input file to close
//	
// Returned:		 None
//*****************************************************************************

void closeFileForRead(ifstream& inputFile) {
	inputFile.close();
}

//*****************************************************************************
// Function:     closeFileForWrite
//
// Description:  Closes the output file
//
// Parameters:	 outputFile - Allows the output file to close
//		
// Returned:		 None
//*****************************************************************************

void closeFileForWrite(ofstream& outputFile) {
	outputFile.close();
}

//*****************************************************************************
// Function:     constructMappingArray
//
// Description:  Constructs the mapping array by using the user's given keys
//							 to configure the alphabet
//
// Parameters:	 mappingArray - Array that contains the alphabet configured 
//							 by the user's inputted keys
//							 keys - The key letters chosen to configure the mapping array
//							 numberOfMappings - The number of mappings chosen
//	
// Returned:		 None
//*****************************************************************************

void constructMappingArray(char mappingArray[][LETTERS_IN_ALPHABET],
						   string keys,
						   int numberOfMappings) {
	char letter;

	for (int i = 0; i < numberOfMappings; i++) {
		letter = keys.at(i);
		for (int j = 0; j < LETTERS_IN_ALPHABET; j++) {
			mappingArray[i][j] = letter;
			letter++;
			if (letter == ASCII_VALUE_OF_Z) {
				letter = 'A';
			}
		}
	}
}

//*****************************************************************************
// Function:     printMappingArray
//
// Description:  Prints the mapping array that is configured by the user's
//							 key letters in order to ease the debugging process
//
// Parameters:	 mappingArray - Array that contains the alphabet configured 
//							 by the user's inputted keys
//							 numberOfMappings - The number of mappings chosen
//	
// Returned:		 None
//*****************************************************************************

void printMappingArray(const char mappingArray[][LETTERS_IN_ALPHABET],
					   int numberOfMappings) {
	for (int i = 0; i < numberOfMappings; i++) {
		for (int j = 0; j < LETTERS_IN_ALPHABET; j++) {
			cout << mappingArray[i][j] << " ";
		}
		cout << endl;
	}
}

//*****************************************************************************
// Function:     encodedCharacter
//
// Description:	 Takes a character and encodes it using the given keys
//
// Parameters:	 plaintextCharacter - A character in plain text from
//							 mappingArray - Array that contains the alphabet configured 
//							 by the user's inputted keys
//							 numberOfMappings - The number of mappings chosen
//	
// Returned:		 encodedCharacter - The character in encoded form
//*****************************************************************************

char encodeCharacter(char plaintextCharacter,
									 	 const char mappingArray[][LETTERS_IN_ALPHABET],
										 int numberOfMappings) {
	char encodedCharacter;
	int charNumber;

	encodedCharacter = plaintextCharacter;
	if (plaintextCharacter >= 'A' && plaintextCharacter <= 'Z') {
		for (int i = 0; i < numberOfMappings; i++) {
			charNumber = encodedCharacter - ASCII_VALUE_OF_A;
			encodedCharacter = mappingArray[i][charNumber];
		}
	}
	return encodedCharacter;
}

//*****************************************************************************
// Function:     decodeCharacter
//
// Description:  Takes a character and decrypts it using the given keys
//
// Parameters:	 ciphertextCharacter - A character in encrypted text form
//							 mappingArray - Array that contains the alphabet configured 
//							 by the user's inputted keys
//							 numberOfMappings - The number of mappings chosen
//	
// Returned:		 decodedCharacter - The character in decrypted form
//*****************************************************************************

char decodeCharacter(char ciphertextCharacter,
									 	 const char mappingArray[][LETTERS_IN_ALPHABET],
									 	 int numberOfMappings) {
	char decodedCharacter;
	bool bIsMatch = false;

	decodedCharacter = ciphertextCharacter;
	if (ciphertextCharacter >= 'A' && ciphertextCharacter <= 'Z') {
		for (int i = numberOfMappings - 1; i >= 0; i--) {
			bIsMatch = false;
			for (int j = 0; j < LETTERS_IN_ALPHABET; j++) {
				if (decodedCharacter == mappingArray[i][j] && bIsMatch == false) {
					decodedCharacter = ASCII_VALUE_OF_A + j;
					bIsMatch = true;
				}
			}
		}
	}

	return decodedCharacter;
}
