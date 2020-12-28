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
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to the Bull Cows!"));

	HiddenWord = TEXT("cakes");
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Guess the %d letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %d Lives"), Lives);
	PrintLine(TEXT("Type in your guess \nand press enter to continue..."));

	const TCHAR HW[] = TEXT("plums");
	PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
	PrintLine(TEXT("The 4th character of HW is: %c"), HW[3]);
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}
	
	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %d letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %d lives remaining"), Lives);
		return;
	}
	
	if(!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again!"));
		return;
	}
	
	PrintLine(TEXT("Lost a life!"));
	--Lives;

	if (0 >= Lives)
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	PrintLine(TEXT("Guess again, you have %d lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	return true;
}
