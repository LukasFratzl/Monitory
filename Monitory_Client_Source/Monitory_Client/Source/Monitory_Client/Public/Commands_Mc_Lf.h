// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Commands_Mc_Lf.generated.h"

UCLASS()
class MONITORY_CLIENT_API ACommands_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACommands_Mc_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Commands")
	void LimitFPS(const int32& Fps);

	inline static bool bFreshCommands = true;

	UFUNCTION(BlueprintCallable, Category = "Commands")
	bool CommandsNeverSetThisSession();

	UFUNCTION(BlueprintCallable, Category = "Commands")
	bool IsDesktop();
};
