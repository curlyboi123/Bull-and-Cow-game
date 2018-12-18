#pragma once
#include "FBullCowGame.h"
#include <map>
#include <iostream>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset();} // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::LettersWords() const { return LettersInWords; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::GameDifficulty()
{
	std::cout << "Please choose the number of letters you want in your word (3-7): ";
	std::cin >> LettersInWords;
	std::cin.ignore();

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "\nThat was not a valid entry, please enter a number between 3 and 7: ";
		std::cin >> LettersInWords;
	}

	return;
}


int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}



void FBullCowGame::Reset()
{
	TMap<int32, FString> NumberToWord;
	NumberToWord[3] = "can";
	NumberToWord[4] = "drag";
	NumberToWord[5] = "white";
	NumberToWord[6] = "planet";
	NumberToWord[7] = "abdomen";

	const FString HIDDEN_WORD = NumberToWord[LettersInWords];
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	} 
	else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase; // TODO write function
	}
	else if (Guess.length() != LettersWords()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

/* get user to enter a number corresponding to length of word they want to guess
FString FBullCowGame::UserWordLength()
{
	const FString HIDDEN_WORD_3 = "dog";
	const FString HIDDEN_WORD_4 = "road";
	const FString HIDDEN_WORD_5 = "joker";
	const FString HIDDEN_WORD_6 = "planet";
	const FString HIDDEN_WORD_7 = "abdomen";

	std::cout << "Enter the length of word you want to guess (3-7)" << std::endl;
	int Word_Length = 0;
	std::cin >> Word_Length;
	if (Word_Length = 3)
	{
		std::cout << "You have selected a 3 letter word." << std::endl;
		return HIDDEN_WORD_3;
	}
	if (Word_Length = 4)
	{
		std::cout << "You have selected a 4 letter word." << std::endl;
		return HIDDEN_WORD_4;
	}
	if (Word_Length = 5)
	{
		std::cout << "You have selected a 5 letter word." << std::endl;
		return HIDDEN_WORD_5;
	}
	if (Word_Length = 6)
	{
		std::cout << "You have selected a 6 letter word." << std::endl;
		return HIDDEN_WORD_6;
	}
	if (Word_Length = 7)
	{
		std::cout << "You have selected a 7 letter word." << std::endl;
		return HIDDEN_WORD_7;
	}
	else
	{
		std::cout << "You have entered an incorrect value so we have selected the default" << std::endl;
		std::cout << "5 letter word." << std::endl;
		return HIDDEN_WORD_5;
	}
}
*/ 

// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// if they're in the same place
				if (MHWChar == GChar) {
					// increment bulls
					BullCowCount.Bulls++;
				}

				// else 
				else {
					// increment cows
					BullCowCount.Cows++;
				}		
			}
				
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])
		{ // if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter 
		{
			return false;
		}
	}
	return true;
}
