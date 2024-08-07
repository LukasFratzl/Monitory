// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "Tasks/Task.h"
#include "TcpClient_Mc_Lf.generated.h"


struct FTcpClient_Socket_Mc_Lf
{
	FSocket* Socket = nullptr;

	int32 RetryConnection = 0;
	bool bNeedWait = false;
	float WaitTime = 2;
	float LastTimeReceivedMessage = 5;
};


UCLASS()
class MONITORY_CLIENT_API ATcpClient_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATcpClient_Mc_Lf();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	// UE::Tasks::FTask TcpSocketTask;
	// bool bNeedRunTcpTask = false;
	
	//int32 IPAddressIndex = 0;
	
	TArray<FTcpClient_Socket_Mc_Lf> TcpSockets;
	
	inline static FString LastTcpSocketData = FString("");

	inline static bool bNeedUIRebuild = false;
	inline static bool bIsConnected = false;

	// FString ConnectionStateToString(ESocketConnectionState ConnectionState)
	// {
	// 	switch (ConnectionState)
	// 	{
	// 	case ESocketConnectionState::SCS_NotConnected:
	// 		return TEXT("Not Connected");
	// 	case ESocketConnectionState::SCS_Connected:
	// 		return TEXT("Connected");
	// 	case ESocketConnectionState::SCS_ConnectionError:
	// 		return TEXT("Connection Error");
	// 		// Add more cases for other states if needed
	// 		default:
	// 			return TEXT("Unknown");
	// 	}
	// }

	static FSocket* ConnectToServer_Mc(const FString& ServerIP);
	static FString ReceiveData_Mc(FSocket* Socket);
	static void CloseSocket(FSocket* Socket);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
