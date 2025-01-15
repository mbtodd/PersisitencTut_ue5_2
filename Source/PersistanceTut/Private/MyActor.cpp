// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "GameFramework/Actor.h"
#include "JsonObjectConverter.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->IsAttachedTo(RootComponent);



}

void AMyActor::HandelServerEntry()
{
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();


	
	// FVector NewLocation = GetActorLocation();
	// float DeltaHeight = 300.0f;
	// NewLocation.Z = DeltaHeight;
	//
	// SetActorLocation(NewLocation);
	// UE_LOG(LogTemp, Warning, TEXT("New Location: %f"), NewLocation.Z);
	//
	// UE_LOG(LogTemp, Warning, TEXT("CUBE DOING SOMETHING ON GETACTOR LOCATION"));
	//
	//
	// TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	//
	// Request->OnProcessRequestComplete().BindUObject(this, &AMyActor::OnProcessRequestComplete);
	// Request->SetURL("http://localhost:8080/api/CubeData");
	// Request->SetVerb("GET");
	// Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	//
	// FString JsonString;
	// // FCubeData CubeData;
	// // // CubeData.Xcoord = 40.0f;
	// // // CubeData.Ycoord = 50.0f;
	// // // CubeData.Zcoord = 60.0f;
	// // FJsonObjectConverter::UStructToJsonObjectString(CubeData, JsonString);
	// // Request->SetContentAsString(JsonString);
	// UE_LOG(LogTemp, Warning, TEXT("Json string: %s"), *JsonString);
	//
	// Request->ProcessRequest();

	

	
	// FVector Pos = GetActorLocation();
	// UE_LOG(LogTemp, Warning, TEXT("Pos: %f"), Pos.X);
	

	// FVector NewLocation = GetActorLocation();
	// float RunningTime = 5.0f;
	// float DeltaTime = 5.0f / 60.0f;
	// float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(DeltaTime));
	// NewLocation.Z += DeltaHeight * 20.0f;
	//
	// SetActorLocation(NewLocation);
	// UE_LOG(LogTemp, Display, TEXT("New Location: %f"), NewLocation.Z);


	
}

void AMyActor::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	// FVector Location = FVector::ZeroVector;
	FVector Location = GetActorLocation();
	Location.Z = 400;
	
	if (Success)
	{
		// Setup Pawn
		UE_LOG(LogTemp, Warning, TEXT("SUCCESS %s"), *Response->GetContentAsString());
	
		FMyActorData MyActorData = ConvertToNewCubeData(Response->GetContentAsString());
		if (MyActorData.isvalid)
		{
			UE_LOG(LogTemp, Warning, TEXT("CUBE DATA VALID"), MyActorData.Zcoord);
			Location.X = MyActorData.Xcoord;
			Location.Y = MyActorData.Ycoord;
			Location.Z = MyActorData.Zcoord;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}
};


FMyActorData AMyActor::ConvertToNewCubeData(const FString& ResponseString)
{
	FMyActorData MyActorData;
	if (ResponseString.Contains("timestamp"))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct(*ResponseString, &MyActorData, 0, NULL, 0);
	}
	return MyActorData;
}



