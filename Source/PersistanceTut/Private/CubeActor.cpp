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
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString JsonString;
	FCubeData CubeData;
	CubeData.Xcoord = 40.0f;
	CubeData.Ycoord = 50.0f;
	CubeData.Zcoord = 60.0f;
	FJsonObjectConverter::UStructToJsonObjectString(CubeData, JsonString);
	Request->SetContentAsString(JsonString);
	UE_LOG(LogTemp, Warning, TEXT("Json string: %s"), *JsonString);
	
	Request->ProcessRequest();
	
}

void UCubeActor::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	if (Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
}


// // Called every frame
// void UCubeActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

