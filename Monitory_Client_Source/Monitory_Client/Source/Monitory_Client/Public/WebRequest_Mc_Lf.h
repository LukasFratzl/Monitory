// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebRequest_Mc_Lf.generated.h"

UCLASS()
class MONITORY_CLIENT_API AWebRequest_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWebRequest_Mc_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DownloadAppVersion() const;

	inline static bool bIsUpdateAvailable = false;
};
