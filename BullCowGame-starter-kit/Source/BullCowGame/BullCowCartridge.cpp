// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	//
	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	// FFileHelper::LoadFileToStringArray(Words, *WordListPath);
	FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, 
		[](const FString& Word)
	{
		return Word.Len() > 4 && Word.Len() < 8 && IsIsogram(Word);
	});

	// Isograms = GetValidWords(Words);
	
	SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
	if (bGameOver) 
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(PlayerInput);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to the Bull Cows!"));

	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Guess the %d letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %d Lives"), Lives);
	PrintLine(TEXT("Type in your guess \nand press enter to continue..."));
	PrintLine(TEXT("The hiddenword is: %s"), *HiddenWord);
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
	
	FBullCowCount Score = GetBullCows(Guess);

	PrintLine(TEXT("You have %d Bulls and %d Cows"), Score.Bulls, Score.Cows);
	
	PrintLine(TEXT("Guess again, you have %d lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word)
{
	for (int32 Index = 0; Index < Word.Len(); ++Index)
	{
		for (int32 Comparison = Index + 1; Comparison < Word.Len(); ++Comparison)
		{
			if (Word[Index] == Word[Comparison])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ValidWords;
	
	for (FString Word : WordList)
	{
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}
	return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBullCowCount Count;
	
	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); ++GuessIndex)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			++Count.Bulls;
			continue;
		}
		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); ++HiddenIndex)
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				++Count.Cows;
				break;
			}
		}
	}
	return Count;
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}