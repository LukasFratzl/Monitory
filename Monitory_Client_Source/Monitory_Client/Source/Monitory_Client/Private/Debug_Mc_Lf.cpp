// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug_Mc_Lf.h"


// Sets default values
ADebug_Mc_Lf::ADebug_Mc_Lf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADebug_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADebug_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATcpClient_Mc_Lf::EIsConnectedOverride = IsConnectedOverride;
}

