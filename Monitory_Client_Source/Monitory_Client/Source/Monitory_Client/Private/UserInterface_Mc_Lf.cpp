// Fill out your copyright notice in the Description page of Project Settings.


#include "Monitory_Client/Public/UserInterface_Mc_Lf.h"

#include "Blueprint/UserWidget.h"


// Sets default values
AUserInterface_Mc_Lf::AUserInterface_Mc_Lf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUserInterface_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();

	GenerateMainMenuWidget();
}

// Called every frame
void AUserInterface_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AUserInterface_Mc_Lf::GenerateMainMenuWidget()
{
	MainWidget = CreateWidget<UWidgetMainMenu_Mc_Lf>(GetWorld(), UWidgetMainMenu_Mc_Lf::StaticClass());
		// Add the widget to the viewport
		MainWidget->AddToViewport();
}

