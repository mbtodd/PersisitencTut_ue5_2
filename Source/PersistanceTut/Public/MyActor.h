// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Http.h"
#include "MyActor.generated.h"

USTRUCT(Blueprintable)
struct FMyActorData
{
	GENERATED_BODY()
	UPROPERTY()
	bool isvalid = false;
	float Xcoord = 0.0f;
	UPROPERTY()
	float Ycoord = 0.0f;
	UPROPERTY()
	float Zcoord = 0.0f;
	
};

UCLASS()
class PERSISTANCETUT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere)
	UShapeComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	void HandelServerEntry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FHttpModule* Http;
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

	FMyActorData ConvertToNewCubeData(const FString& ResponseString);


public:	


};
