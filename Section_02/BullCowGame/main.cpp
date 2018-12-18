/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame Class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside class
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

 // instantiate a new game, which we re-use across plays
FBullCowGame BCGame;

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0; // exit the application
}


void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game\n";
	std::cout << std::endl;
	std::cout << "    }______{         ______    " << std::endl;
	std::cout << "    ( *  * )        ( *  * )    " << std::endl;
	std::cout << "     ( oo )          ( oo )     " << std::endl;
	std::cout << "       --              --       " << std::endl;
	std::cout << std::endl;
	do {
		std::cout << std::endl;
		BCGame.GameDifficulty();
	} while (BCGame.LettersWords() < 3 || BCGame.LettersWords() > 10);
	std::cout << "\nCan you guess the " << BCGame.LettersWords();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) // TODO change from FOR to WHILE 
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}

	PrintGameSummary();
	return;
}


// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//  get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout<< ". Enter your guess : ";
		
		getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.LettersWords() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}



void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WON THE GAME!" << std::endl;
	}
	else
	{
		std::cout << "Unlucky! You lost. Would you like to play again with the same word?" << std::endl;
	}
}