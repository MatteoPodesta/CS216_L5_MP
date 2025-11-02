#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

class Fraction {
public:

	Fraction();
	Fraction(int newWholeNumber);
	Fraction(int newNumerator, int newDenominator);
	Fraction(int newWholeNumber, int newNumerator, int newDenominator);
	Fraction(const Fraction& copyFromThisFraction);
	
	~Fraction();

	void setFraction(int newWholeNumber);
	void setFraction(int newNumerator, int newDenominator);
	void setFraction(int newWholeNumber, int newNumerator, int newDenominator);

	string toString();
	void printToConsole() { 

		cout << right << setw(6) << toString() << " ";
	}
	int returnFractionObjects() { 
		return fractionCount; 
	}

private:

	static const int DEFAULT_NUMERATOR = 1;
	static const int DEFAULT_DENOMINATOR = 1;

	int numerator = DEFAULT_NUMERATOR;
	int denominator = DEFAULT_DENOMINATOR;

	static int fractionCount;

};
class FractionExeption {

public:
	FractionExeption() { 
		message = "Unknown Error"; 
	}
	FractionExeption(int value) { 
		message = value; 
	}
	string what() { 
		return message; 
	}
private:

	string message = "";

};

void defaultMenuOption();

void assignLists(Fraction**& array, int size);
void deAllocateMemory(Fraction**& array, int size);
void printArray(Fraction**& array, int size);

void createAndPrintArray(Fraction**& array);

Fraction** ppFractions = nullptr;

int main()
{
	int userInput = 0;
	enum {

		PRINT = 1,
		QUIT

	};

	while (userInput != QUIT) {

		cout << "\nMenu:\n"
			<< "1. Print table based off input\n"
			<< "2. Exit\n"
			<< "\nInput: ";

		cin >> userInput;

		switch (userInput) {
		case PRINT:
			createAndPrintArray(ppFractions);
			break;
		case QUIT:
			break;
		default:
			defaultMenuOption();
			break;
		}
	}

	


	return 0;
}

Fraction::Fraction() {

	setFraction(0, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);

}
Fraction::Fraction(int newWholeNumber) {

	setFraction(0,newWholeNumber, 1);

}
Fraction::Fraction::Fraction(int newNumerator, int newDenominator) {

	setFraction(0, newNumerator, newDenominator);

}
Fraction::Fraction(int newWholeNumber, int newNumerator, int newDenominator) {

	setFraction(newWholeNumber, newNumerator, newDenominator);

}
Fraction::Fraction(const Fraction& copyFromThisFraction) {

	setFraction(0, copyFromThisFraction.numerator, copyFromThisFraction.denominator);

}
Fraction::~Fraction() {

	setFraction(0, 0, 1);

}

void Fraction::setFraction(int newWholeNumber) {

	setFraction(0, newWholeNumber, 1);
}
void Fraction::setFraction(int newNumerator, int newDenominator) {

	setFraction(0, newNumerator, newDenominator);
}
void Fraction::setFraction(int newWholeNumber, int newNumerator, int newDenominator) {
	try {
		 
		int errorNumber = 0;

		if (newNumerator > newDenominator) {

			cout << "ERROR: NUMERATOR IS LARGER THAN DENOMINATOR\n ERROR HERE: ";
			errorNumber = newNumerator;
			throw(FractionExeption(errorNumber));

		}
		if (newNumerator <= 0) {

			cout << "ERROR: NUMERATOR IS LESS THAN OR EQUAL TO 0\n ERROR HERE: ";
			errorNumber = newNumerator;
			throw(FractionExeption(errorNumber));

		}
		if (newDenominator <= 0) {

			cout << "ERROR: DENOMINATOR IS LESS THAN OR EQUAL TO 0\n ERROR HERE: ";
			errorNumber = newDenominator;
			throw(FractionExeption(errorNumber));

		}
		if (newWholeNumber < 0) {

			cout << "ERROR: FRACTION IS LESS THAN OR EQUAL TO 0\n ERROR HERE: ";
			errorNumber = newWholeNumber;
			throw(FractionExeption(errorNumber));

		}

		numerator = newWholeNumber * newDenominator + newNumerator;
		denominator = newDenominator;
	}
	catch (FractionExeption ex) {

		cout << ex.what() << endl;

	}
	catch (...) {

		cout << "UNKNOWN ERROR!\n";

	}

}

string Fraction::toString() {

	return (to_string(numerator)) + "/" + (to_string(denominator));

}

int Fraction::fractionCount = 0;

void defaultMenuOption() {

	cout << "Invalid choice, try again\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void assignLists(Fraction**& array, int size) {

	try {
		// Makes the rows
		array = new Fraction * [size] {nullptr};

		// makes the columns
		for (int i = 0; i < size; ++i) {
			array[i] = new Fraction[size];
		}

		for (int rows = 0; rows < size; ++rows) {

			for (int columns = 0; columns < size; ++columns) {
				if (rows == 0 && columns == 0) {

				}
				else if (rows == 0) {

					array[rows][columns].setFraction(columns, size);

				}
				else if (columns == 0) {

					array[rows][columns].setFraction(rows, size);

				}
				else {

					array[rows][columns].setFraction(columns * rows, size * size);

				}

			}
		}


	}
	catch (bad_alloc& ex)
	{

		deAllocateMemory(array, size);
	
	}

}
void deAllocateMemory(Fraction**& array, int size) {

	if (array != nullptr)
	{
		for (int i = 0; i < size; ++i) {

			delete[] array[i];
			array[i] = nullptr;
		
		}

		delete[] array;
		array = nullptr;
	}

}
void printArray(Fraction**& array, int size) {

	if (array) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {

				array[i][j].printToConsole();
			}

			cout << endl;
		}

	}
	else {

	}

}

void createAndPrintArray(Fraction**& array) {

	int denominator = 0;

	while (denominator <= 0)
	{
		cout << "\nInput denominator: ";
		cin >> denominator;

		if (denominator <= 0) {

			cout << "ERROR: " << denominator << " IS INVALID, INPUT AN INTEGER LARGER THAN 0";
			defaultMenuOption();
		}

	}
	
	assignLists(array, denominator);
	printArray(array, denominator);

}

//TEST RUN
/*


Menu:
1. Print table based off input
2. Exit

Input: 1

Input denominator: 12
   1/1   1/12   2/12   3/12   4/12   5/12   6/12   7/12   8/12   9/12  10/12  11/12
  1/12  1/144  2/144  3/144  4/144  5/144  6/144  7/144  8/144  9/144 10/144 11/144
  2/12  2/144  4/144  6/144  8/144 10/144 12/144 14/144 16/144 18/144 20/144 22/144
  3/12  3/144  6/144  9/144 12/144 15/144 18/144 21/144 24/144 27/144 30/144 33/144
  4/12  4/144  8/144 12/144 16/144 20/144 24/144 28/144 32/144 36/144 40/144 44/144
  5/12  5/144 10/144 15/144 20/144 25/144 30/144 35/144 40/144 45/144 50/144 55/144
  6/12  6/144 12/144 18/144 24/144 30/144 36/144 42/144 48/144 54/144 60/144 66/144
  7/12  7/144 14/144 21/144 28/144 35/144 42/144 49/144 56/144 63/144 70/144 77/144
  8/12  8/144 16/144 24/144 32/144 40/144 48/144 56/144 64/144 72/144 80/144 88/144
  9/12  9/144 18/144 27/144 36/144 45/144 54/144 63/144 72/144 81/144 90/144 99/144
 10/12 10/144 20/144 30/144 40/144 50/144 60/144 70/144 80/144 90/144 100/144 110/144
 11/12 11/144 22/144 33/144 44/144 55/144 66/144 77/144 88/144 99/144 110/144 121/144

Menu:
1. Print table based off input
2. Exit

Input: 4
Invalid choice, try again

Menu:
1. Print table based off input
2. Exit

Input: a
Invalid choice, try again

Menu:
1. Print table based off input
2. Exit

Input: 1

Input denominator: a
ERROR: 0 IS INVALID, INPUT AN INTEGER LARGER THAN 0Invalid choice, try again

Input denominator: -1
ERROR: -1 IS INVALID, INPUT AN INTEGER LARGER THAN 0Invalid choice, try again

Input denominator: 1.5
   1/1

Menu:
1. Print table based off input
2. Exit

Input: Invalid choice, try again

Menu:
1. Print table based off input
2. Exit

Input: 1

Input denominator: 12
   1/1   1/12   2/12   3/12   4/12   5/12   6/12   7/12   8/12   9/12  10/12  11/12
  1/12  1/144  2/144  3/144  4/144  5/144  6/144  7/144  8/144  9/144 10/144 11/144
  2/12  2/144  4/144  6/144  8/144 10/144 12/144 14/144 16/144 18/144 20/144 22/144
  3/12  3/144  6/144  9/144 12/144 15/144 18/144 21/144 24/144 27/144 30/144 33/144
  4/12  4/144  8/144 12/144 16/144 20/144 24/144 28/144 32/144 36/144 40/144 44/144
  5/12  5/144 10/144 15/144 20/144 25/144 30/144 35/144 40/144 45/144 50/144 55/144
  6/12  6/144 12/144 18/144 24/144 30/144 36/144 42/144 48/144 54/144 60/144 66/144
  7/12  7/144 14/144 21/144 28/144 35/144 42/144 49/144 56/144 63/144 70/144 77/144
  8/12  8/144 16/144 24/144 32/144 40/144 48/144 56/144 64/144 72/144 80/144 88/144
  9/12  9/144 18/144 27/144 36/144 45/144 54/144 63/144 72/144 81/144 90/144 99/144
 10/12 10/144 20/144 30/144 40/144 50/144 60/144 70/144 80/144 90/144 100/144 110/144
 11/12 11/144 22/144 33/144 44/144 55/144 66/144 77/144 88/144 99/144 110/144 121/144

Menu:
1. Print table based off input
2. Exit

Input: 1

Input denominator: 5
   1/1    1/5    2/5    3/5    4/5
   1/5   1/25   2/25   3/25   4/25
   2/5   2/25   4/25   6/25   8/25
   3/5   3/25   6/25   9/25  12/25
   4/5   4/25   8/25  12/25  16/25

Menu:
1. Print table based off input
2. Exit

Input: 1

Input denominator: 6
   1/1    1/6    2/6    3/6    4/6    5/6
   1/6   1/36   2/36   3/36   4/36   5/36
   2/6   2/36   4/36   6/36   8/36  10/36
   3/6   3/36   6/36   9/36  12/36  15/36
   4/6   4/36   8/36  12/36  16/36  20/36
   5/6   5/36  10/36  15/36  20/36  25/36

Menu:
1. Print table based off input
2. Exit

Input: 5
Invalid choice, try again

Menu:
1. Print table based off input
2. Exit

Input: 2

C:\Users\Matteo\source\repos\Fraction thing\x64\Debug\Fraction thing.exe (process 31708) exited with code 0.
Press any key to close this window . . .

*/
