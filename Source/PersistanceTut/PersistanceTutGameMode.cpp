// Copyright Epic Games, Inc. All Rights Reserved.

#include "PersistanceTutGameMode.h"

#include "JsonObjectConverter.h"
#include "PersistanceTutCharacter.h"
#include "UObject/ConstructorHelpers.h"

APersistanceTutGameMode::APersistanceTutGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	Http = &FHttpModule::Get();
}

void APersistanceTutGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("POST LOGIN RUNNING"));

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &APersistanceTutGameMode::OnProcessRequestComplete);
	Request->SetURL("http://localhost:8080/api/PlayerData");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	FString JsonString;
	FPlayerData PlayerData;
	PlayerData.Xcoord = 10.0f;
	PlayerData.Ycoord = 20.0f;
	PlayerData.Zcoord = 30.0f;
	
	FJsonObjectConverter::UStructToJsonObjectString(PlayerData, JsonString);
	Request->SetContentAsString(JsonString);
	UE_LOG(LogTemp, Warning, TEXT("Json String: %s"), *JsonString);
	
	// Request->ProcessRequest();

	// Get Request through API passing in PID
	
	// If no result found construct new entry in database

	// If result found return completed struct
}

void APersistanceTutGameMode::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	if (Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}
