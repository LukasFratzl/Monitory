// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TcpClient_Mc_Lf.h"
#include "GameFramework/Actor.h"
#include "Debug_Mc_Lf.generated.h"

UCLASS()
class MONITORY_CLIENT_API ADebug_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADebug_Mc_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	EIsConnectedOverride IsConnectedOverride = EIsConnectedOverride::NONE;
};
