// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistancePlayerController.h"

#include "JsonObjectConverter.h"
#include "PersistanceTut/PersistanceTutGameMode.h"

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

	FString PID = "1235";
	
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
	FVector Location = FVector::ZeroVector;
	Location.Z = 400.0f;
	
	if (Success)
	{
		// setup pawn
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS %s"), *Response->GetContentAsString());

		FPlayerData PlayerData = ConvertToPlayerData(Response->GetContentAsString());
		if (PlayerData.isvalid)
		{
			UE_LOG(LogTemp, Warning, TEXT("SUCCESS %f"), PlayerData.Zcoord);
			Location.X = PlayerData.Xcoord;
			Location.Y = PlayerData.Ycoord;
			Location.Z = PlayerData.Zcoord;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}

	if (APersistanceTutGameMode* GM = GetWorld()->GetAuthGameMode<APersistanceTutGameMode>())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (APawn* NewPawn = GetWorld()->SpawnActor<APawn>(GM->DefaultPawnClass, Location, FRotator::ZeroRotator, SpawnParams))
		{
			Possess(NewPawn);	
		}
	}
}

FPlayerData APersistancePlayerController::ConvertToPlayerData(const FString& ResponseString)
{
	FPlayerData PlayerData;
	if (!ResponseString.Contains("timestamp"))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct(*ResponseString, &PlayerData, 0, 0);
		// FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &PlayerData, 0, 0);
	}
	
	return PlayerData;
}
