// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "PersistanceTutGameMode.generated.h"

USTRUCT(Blueprintable)
struct FPlayerData
{
	GENERATED_BODY()
	UPROPERTY()
	float Xcoord = 0.0f;
	UPROPERTY()
	float Ycoord = 0.0f;
	UPROPERTY()
	float Zcoord = 0.0f;
};

UCLASS(minimalapi)
class APersistanceTutGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APersistanceTutGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	FHttpModule* Http;
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);
};



