#include <iostream>

using namespace std;

void printChars(char character, int numChars);

int main() {
	printChars(*, 34);

	return EXIT_SUCCESS;
}

void printChars(char character, int numChars) {
	for (int i = 0; i < numChars; i++) {
		cout << character;
	}
	cout << endl;
}