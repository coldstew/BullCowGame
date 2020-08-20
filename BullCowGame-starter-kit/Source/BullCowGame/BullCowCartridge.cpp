// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	PrintLine("Welcome to the Bull Cows Game!\nPress Enter to continue...");
	PrintLine("");
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
	ClearScreen();
	FString HiddenWord;
}