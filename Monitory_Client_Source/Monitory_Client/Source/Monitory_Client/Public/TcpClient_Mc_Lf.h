// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "Networking.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "Tasks/Task.h"
#include "TcpClient_Mc_Lf.generated.h"

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
	int32 RetryConnection = 0;
	bool bNeedWait = false;
	float WaitTime = 2;
	
	FSocket* TcpSocket = nullptr;

	double LastTimeReceivedMessage = 5;
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

	bool ConnectToServer_Mc(const FString& ServerIP);
	FString ReceiveData_Mc() const;
	void CloseSocket();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
