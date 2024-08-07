// Fill out your copyright notice in the Description page of Project Settings.


#include "Monitory_Client/Public/Commands_Mc_Lf.h"


// Sets default values
ACommands_Mc_Lf::ACommands_Mc_Lf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACommands_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommands_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACommands_Mc_Lf::LimitFPS(const int32 Fps)
{
	const FString& MaxFps = FString::Printf(TEXT("t.MaxFPS %d"), Fps);
	GEngine->Exec(GetWorld(), *MaxFps);
}

bool ACommands_Mc_Lf::CommandsNeverSetThisSession()
{
	const bool bSet = bFreshCommands;
	bFreshCommands = false;
	return bSet;
}

bool ACommands_Mc_Lf::IsDesktop()
{
#if PLATFORM_DESKTOP
	return true;
#else
	return false;
#endif
}

