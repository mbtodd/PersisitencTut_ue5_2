// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Http.h"
#include "CubeActor.generated.h"


USTRUCT(Blueprintable)
struct FCubeData
{
	GENERATED_BODY()
	UPROPERTY()
	bool isvalid = false;
	UPROPERTY()
	int pid = -1;
	float Xcoord = 0.0f;
	UPROPERTY()
	float Ycoord = 0.0f;
	UPROPERTY()
	float Zcoord = 0.0f;
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSISTANCETUT_API UCubeActor : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UCubeActor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void HandelServerEntry();

	
	// Called every frame
	// 	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	FHttpModule* Http;
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

	FCubeData ConvertToCubeData(const FString& ResponseString);

};

