// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetMainMenu_Mc_Lf.h"
#include "Components/Widget.h"
#include "GameFramework/Actor.h"

#include "UserInterface_Mc_Lf.generated.h"

UCLASS()
class MONITORY_CLIENT_API AUserInterface_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUserInterface_Mc_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void GenerateMainMenuWidget(); // TODO: Make it a level blueprint parent

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetMainMenu_Mc_Lf> MainWidget;
};
