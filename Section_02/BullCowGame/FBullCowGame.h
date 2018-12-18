/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};


enum class EResetStatus
{
	No_Hidden_Word,
	OK
};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 LettersWords() const;
	void GameDifficulty();
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString);
	
	
	void Reset(); // TODO make a more rich return value;
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	int32 LettersInWords;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};

