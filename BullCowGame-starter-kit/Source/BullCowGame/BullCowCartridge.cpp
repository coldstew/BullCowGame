// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	//
	SetupGame();

	PrintLine(TEXT("The hiddenword is: %s"), *HiddenWord);
	
	// TODO : I need to prompt player for guess
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
	ClearScreen();

	if (bGameOver) 
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input, lives);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to the Bull Cows!"));

	HiddenWord = TEXT("cakes");
	lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Guess the %d letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %d Lives"), lives);
	PrintLine(TEXT("Type in your guess \nand press enter to continue..."));

	const TCHAR HW[] = TEXT("cakes");
	HW;
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess, int32 Counter)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}

	/*if(!bIsogram)
	{
		PrintLine(TEXT("No repeating letters, guess again!"));
	}*/
	
	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %d letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %d lives remaining"), lives);
		return;
	}

	
	PrintLine(TEXT("Lost a life!"));
	--lives;

	if (0 >= lives)
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	PrintLine(TEXT("Guess again, you have %d lives left."), lives);
}