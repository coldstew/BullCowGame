// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	//

	PrintLine(TEXT("Welcome to the Bull Cows Game!"));
	PrintLine(TEXT("Guess the %d letter word!"), difficulty);
	PrintLine(TEXT("Press Tab to continue..."));

	InitGame();
	// TODO : I need to prompt player for guess
}


void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
	ClearScreen();
	if (Input == HiddenWord)
	{
		PrintLine(TEXT("You have Won!"));
	}
	else
	{
		if (Input.Len() != HiddenWord.Len() && 0 < lives)
		{
			PrintLine(TEXT("The Hidden Word is %d characters long, try again!"), HiddenWord.Len());
			PrintLine(TEXT("%d Lives left!"), lives);
		}
		else 
		{
			PrintLine(TEXT("You have Lost!"));
		}
		--lives;
	}
}

void UBullCowCartridge::InitGame()
{
	HiddenWord = TEXT("cake");
	lives = 5;
}
