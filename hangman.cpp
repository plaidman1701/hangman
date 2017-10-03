#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const string wordPool[] = { "buddy", "shark", "rates", "preset", "sleeve",
"widget", "agitate", "crowded", "amputate", "tenement" };
const string bodyParts[] = { " o", "\n/", "|", "\\", "\n |", "\n/", " \\" };

const char FILLERCHAR = '?';

// prototypes
char getChar(const string & outputString);
void printMan(int piecesToPrint);
void printGuesses(const string & guesses);
void updateOutputString(const string & wordToGuess, string & outputString, char valueToFind);
string uppercaseString(const string & stringToUppercase);
bool playAgain(void);

int main()
{
	// initialize random word
	srand(time(0));

	do
	{
		const string wordToGuess = wordPool[rand() % 10];

		string outputString(wordToGuess.size(), FILLERCHAR); // initialize player's correct guesses

		string guesses = ""; // initalize all of player's guesses
		bool gameWon = false;
		bool gameLost = false;
		int badGuesses = 0;

		cout << "\nGuess the word: ";
		for (int i = 0; i < wordToGuess.length(); ++i)
		{
			cout << "X";
		}
		cout << endl;

		while ((!gameWon) && (!gameLost))
		{
			char inputChar = getChar(outputString);

			size_t found = guesses.find(inputChar);
			if (found == string::npos) // not yet guessed
			{
				guesses += inputChar;

				if (wordToGuess.find(inputChar) == string::npos) // bad guess
				{
					++badGuesses;
				}
				else
				{
					updateOutputString(wordToGuess, outputString, inputChar);
				}

				printMan(badGuesses);
				printGuesses(guesses);
			}
 
			else // already guessed
			{
				cout << "'" << (char)toupper(inputChar) << "' was already guessed. Try another letter.\n" << endl;
			}

			if (badGuesses == 7) // check loss
			{
				gameLost = true;
			}

			if (outputString.find(FILLERCHAR) == string::npos) // check win
			{
				gameWon = true;
			}
		}

		if (gameWon)
		{
			cout << "You won!\nThe word was: " << uppercaseString(wordToGuess) << "\n" << endl;
		}
		else
		{
			cout << "Sorry - you have run out of guesses!\nThe word was: " << uppercaseString(wordToGuess) << "\n" << endl;
		}
	} while (playAgain());

	cout << endl;
}

// get a char from the player
char getChar(const string & outputString)
{
	char inputChar;
	do
	{
		cout << "Guess a letter: " << outputString << endl;
		cout << "? ";
		cin >> inputChar;

		if (!isalpha(inputChar))
		{
			cout << "Letters only, please.\n" << endl;
		}

	} while (!isalpha(inputChar));

	return tolower(inputChar);
}

// print the hanging man
void printMan(int piecesToPrint)
{
	cout << endl;
	if (piecesToPrint > 0)
	{
		for (int i = 0; i < piecesToPrint; ++i)
		{
			cout << bodyParts[i];
		}
		cout << "\n" << endl;
	}
}

 
// print the guesses so far
void printGuesses(const string & guesses)
{
	cout << "Your guesses:" << endl;
	string::const_iterator guessesIt = guesses.begin();

	string tempString = "";

	while (guessesIt != guesses.end())
	{
		tempString += toupper(*guessesIt);
		tempString += " ";
		++guessesIt;
	}
	cout << tempString << "\n" << endl;
}

// update the player's string of correct guesses
void updateOutputString(const string & wordToGuess, string & outputString, char valueToFind)
{
	string::const_iterator updateIt = wordToGuess.begin();

	size_t wordPosition = 0;

	while (updateIt != wordToGuess.end())
	{
		if ((*updateIt) == valueToFind)
		{
			outputString.at(wordPosition) = valueToFind;
		}

		++wordPosition;
		++updateIt;
	}
}

// uppercase all letters in a string
string uppercaseString(const string & stringToUppercase)
{
	string returnString = "";

	string::const_iterator upperIt = stringToUppercase.begin();

	while (upperIt != stringToUppercase.end())
	{
		returnString += toupper(*upperIt);
		++upperIt;
	}

	return returnString;
}

bool playAgain(void)
{
	char playAgainChar;
	do
	{
		cout << "\nPlay again? (y/n): ";
		cin >> playAgainChar;

		playAgainChar = tolower(playAgainChar);
	} while ((playAgainChar != 'y') && (playAgainChar != 'n'));

	return (playAgainChar == 'y');
}
