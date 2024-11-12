// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistancePlayerController.h"

#include "JsonObjectConverter.h"

APersistancePlayerController::APersistancePlayerController()
{
	Http = &FHttpModule::Get();
}

void APersistancePlayerController::BeginPlay()
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("RUNNING ON CLIENT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RUNNING ON SERVER"));
	}
}

void APersistancePlayerController::HandleServerEntry()
{
	if (!HasAuthority())
	{
		return;
	}

	FString PID = "1234";
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &APersistancePlayerController::OnProcessRequestComplete);
	Request->SetURL("http://localhost:8080/api/PlayerData/" + PID);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	/*FString JsonString;
	FPlayerData PlayerData;
	PlayerData.isvalid = true;
	PlayerData.Xcoord = 10.0f;
	PlayerData.Ycoord = 20.0f;
	PlayerData.Zcoord = 30.0f;

	FJsonObjectConverter::UStructToJsonObjectString(PlayerData, JsonString);
	Request->SetContentAsString(JsonString);*/
	
	
	// Get Request through API passing in PID
	
	Request->ProcessRequest();
}

void APersistancePlayerController::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool Success)
{
	if (Success)
	{
		// setup pawn
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS %s"), *Response->GetContentAsString());
	}
	else
	{
		// spawn new pawn at default location and create entry in data table
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}
