// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Settings_Mc_Lf.generated.h"

UCLASS()
class MONITORY_CLIENT_API ASettings_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASettings_Mc_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Set3DWorldEnabled(bool bEnabled) const;

	void SetShowMouseEnabled(bool bEnabled) const;
};
