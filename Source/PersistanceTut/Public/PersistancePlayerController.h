// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PersistancePlayerController.generated.h"


UCLASS()
class PERSISTANCETUT_API APersistancePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APersistancePlayerController();

	virtual void BeginPlay() override;
};
