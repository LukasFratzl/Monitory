// Fill out your copyright notice in the Description page of Project Settings.


#include "Monitory_Client/Public/Settings_Mc_Lf.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ASettings_Mc_Lf::ASettings_Mc_Lf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASettings_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();

#if PLATFORM_DESKTOP
	Set3DWorldEnabled(false);
#endif
	SetShowMouseEnabled(true);
}

// Called every frame
void ASettings_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASettings_Mc_Lf::Set3DWorldEnabled(const bool& bEnabled) const
{
	if (const TObjectPtr<ULocalPlayer> ClientPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer(); IsValid(ClientPlayer))
	{
		// Update player viewport state 
		if (const TObjectPtr<UGameViewportClient> ViewportClient = ClientPlayer->ViewportClient; IsValid(ViewportClient))
		{
			ViewportClient->bDisableWorldRendering = bEnabled;
			UE_LOG(LogTemp, Warning, TEXT("Set 3D World to -> %s"), bEnabled ? TEXT("true") : TEXT("false"));
		}
	}
}

void ASettings_Mc_Lf::SetShowMouseEnabled(const bool& bEnabled) const
{
	if (const TObjectPtr<APlayerController> PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(PlayerController))
	{
		PlayerController->bShowMouseCursor = bEnabled; 
		PlayerController->bEnableClickEvents = bEnabled; 
		PlayerController->bEnableMouseOverEvents = bEnabled;
		UE_LOG(LogTemp, Warning, TEXT("Set Mouse Control to -> %s"), bEnabled ? TEXT("true") : TEXT("false"));
	}
}

