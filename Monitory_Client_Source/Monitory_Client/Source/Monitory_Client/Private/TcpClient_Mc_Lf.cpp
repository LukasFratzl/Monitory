#include "TcpClient_Mc_Lf.h"

#include "DataTranslate_Mc_Lf.h"

ATcpClient_Mc_Lf::ATcpClient_Mc_Lf()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;
}

void ATcpClient_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();
}

void ATcpClient_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bNeedWait)
	{
		WaitTime -= DeltaTime;
		if (WaitTime < 0)
		{
			bNeedWait = false;
		}
	}

	// if (!bIsConnected)
	// {
	// 	const FString& DummyData = ReceiveData_Mc();
	// }
			
	//FString ServerIP = TEXT("192.168.43.30"); // Replace with your server's IP
	if (!TcpSocket)
	{
		for (const FString& IPAddress : ADataTranslate_Mc_Lf::IPAddresses)
		{
			if (!ConnectToServer_Mc(IPAddress))
			{
				CloseSocket();
				continue;
			}

			if (!TcpSocket)
			{
				CloseSocket();
				continue;
			}

			if (const FString& Data = ReceiveData_Mc(); !Data.IsEmpty())
			{
				break;
			}	
		}
		RetryConnection++;
		if (RetryConnection > 5)
		{
			RetryConnection = 0;
			CloseSocket();
			//UE_LOG(LogTemp, Display, TEXT("Not Connected, retry connection in 1000ms"));
			bNeedWait = true;
			WaitTime = 1;
			return;
		}
	}

	if (LastTimeReceivedMessage < 0)
	{
		LastTimeReceivedMessage = 5;

		CloseSocket();
		UE_LOG(LogTemp, Warning, TEXT("Disconnect from Server"));

		bNeedWait = true;
		WaitTime = 1;

		bNeedUIRebuild = true;
		bIsConnected = false;
		return;
	}

	if (!TcpSocket)
	{
		return;
	}

	if (const FString& Data = ReceiveData_Mc(); !Data.IsEmpty())
	{
		LastTcpSocketData = Data;
		LastTimeReceivedMessage = 5;
		RetryConnection = 0;
		if (!bIsConnected)
		{
			bNeedUIRebuild = true;
		}
		bIsConnected = true;
	}
	else
	{
		LastTimeReceivedMessage -= DeltaTime;
	}

	// UE_LOG(LogTemp, Warning, TEXT("Data -> %s"), *Data);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *ConnectionStateToString(TcpSocket->GetConnectionState()));
}

bool ATcpClient_Mc_Lf::ConnectToServer_Mc(const FString& ServerIP)
{
	constexpr uint16 ServerPort = 54000;

	FIPv4Address IPAddress;
	FIPv4Address::Parse(ServerIP, IPAddress);
	const FIPv4Endpoint Endpoint(IPAddress, ServerPort);

	TcpSocket = FTcpSocketBuilder(TEXT("Monitory_TCP_Socket")).AsReusable();

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	const TSharedRef<FInternetAddr> InternetAddr = SocketSubsystem->CreateInternetAddr();
	InternetAddr->SetIp(Endpoint.Address.Value);
	InternetAddr->SetPort(Endpoint.Port);

	//TcpSocket->SetNoDelay(true);
	//TcpSocket->SetNonBlocking(true);

	if (TcpSocket->Connect(*InternetAddr))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Connected to server"));
		return true;
	}
	return false;
}

FString ATcpClient_Mc_Lf::ReceiveData_Mc() const
{
	if (TcpSocket && TcpSocket->GetConnectionState() == SCS_Connected)
	{
		if (uint32 Size; TcpSocket->HasPendingData(Size))
		{
			TArray<uint8> ReceivedData;
			ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

			// Keep reading and discarding data until the buffer is empty
			while (TcpSocket->HasPendingData(Size))
			{
				int32 Read = 0;
				TcpSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			}

			if (ReceivedData.Num() > 0)
			{
				return FString(UTF8_TO_TCHAR(ReceivedData.GetData()));
			}
		}
	}
	return FString("");
}

void ATcpClient_Mc_Lf::CloseSocket()
{
	if (TcpSocket)
	{
		//TcpSocket->Shutdown(ESocketShutdownMode::ReadWrite);
		TcpSocket->Close();

		//ISocketSubsystem& Sockets = *(ISocketSubsystem::Get());
		//Sockets.DestroySocket(TcpSocket);
	}

	TcpSocket = nullptr;	
}


void ATcpClient_Mc_Lf::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//bNeedRunTcpTask = false;
	CloseSocket();
	//FPlatformProcess::Sleep(2);
	bIsConnected = false;
	LastTcpSocketData = FString("");
}
