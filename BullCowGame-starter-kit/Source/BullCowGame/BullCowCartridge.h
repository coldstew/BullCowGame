// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void ProcessGuess(const FString& Guess);
	static bool IsIsogram(FString Word);
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	void GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const;
	
	void EndGame();

	// Your declarations go below!
	private:
		UPROPERTY()
			FString HiddenWord;
		UPROPERTY()
			int32 Lives;
		UPROPERTY()
			bool bGameOver;
		UPROPERTY()
			TArray<FString> Words;
		UPROPERTY()
			TArray<FString> Isograms;
};
