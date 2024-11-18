// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"
#include "JsonObjectConverter.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
UCubeActor::UCubeActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;
	
	Http = &FHttpModule::Get();
	
	// ...
}


// Called when the game starts
void UCubeActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("CUBE DOING SOMETHING YES SERRRRRR"));


	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UCubeActor::OnProcessRequestComplete);
	Request->SetURL("http://localhost:8080/api/CubeData");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString JsonString;
	// FCubeData CubeData;
	// // CubeData.Xcoord = 40.0f;
	// // CubeData.Ycoord = 50.0f;
	// // CubeData.Zcoord = 60.0f;
	// FJsonObjectConverter::UStructToJsonObjectString(CubeData, JsonString);
	// Request->SetContentAsString(JsonString);
	UE_LOG(LogTemp, Warning, TEXT("Json string: %s"), *JsonString);
	
	Request->ProcessRequest();
	
}

void UCubeActor::HandelServerEntry()
{
UE_LOG(LogTemp, Warning, TEXT("Handle Server Entry Working %s"));
}


void UCubeActor::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	FVector Location = FVector::ZeroVector;
	Location.Z = 400;
	
	if (Success)
	{
		// Setup Pawn
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS %s"), *Response->GetContentAsString());

		FCubeData CubeData = ConvertToCubeData(Response->GetContentAsString());
		if (CubeData.isvalid)
		{
			UE_LOG(LogTemp, Warning, TEXT("CUBE DATA VALID"), CubeData.Zcoord);
			Location.X = CubeData.Xcoord;
			Location.Y = CubeData.Ycoord;
			Location.Z = CubeData.Zcoord;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}

FCubeData UCubeActor::ConvertToCubeData(const FString& ResponseString)
{
	FCubeData CubeData;
	if (ResponseString.Contains("timestamp"))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct(*ResponseString, &CubeData, 0, NULL, 0);
	}
	return CubeData;
}


