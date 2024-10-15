#include "TcpClient_Mc_Lf.h"

#include "DataTranslate_Mc_Lf.h"

ATcpClient_Mc_Lf::ATcpClient_Mc_Lf()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.2f;
}

void ATcpClient_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();
}

void ATcpClient_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const int32 NumAddresses = ADataTranslate_Mc_Lf::IPAddresses.Num();
	if (NumAddresses < TcpSockets.Num())
	{
		for (FTcpClient_Socket_Mc_Lf& Socket : TcpSockets)
		{
			CloseSocket(Socket.Socket);
		}
	}

	if (EIsConnectedOverride != EIsConnectedOverride::NONE)
	{
		bIsConnected = EIsConnectedOverride == EIsConnectedOverride::CONNECTED;
		if (!bIsConnected)
		{
			for (FTcpClient_Socket_Mc_Lf& Socket : TcpSockets)
			{
				CloseSocket(Socket.Socket);
			}
		}
		return;
	}

	// LastTcpSocketData = FString("");
	//bIsConnected = false;
	TcpSockets.SetNum(ADataTranslate_Mc_Lf::IPAddresses.Num());
	int32 IpIdx = 0;
	//int32 NumNotConnectedSockets = 0;
	for (FTcpClient_Socket_Mc_Lf& Socket : TcpSockets)
	{
		IpIdx++;
		if (Socket.bNeedWait)
		{
			Socket.WaitTime -= DeltaTime;
			if (Socket.WaitTime < 0)
			{
				Socket.bNeedWait = false;
			}
			continue;
		}

		FString Data = FString("");
		if (!bIsConnected || !Socket.Socket || Socket.Socket && Socket.Socket->GetConnectionState() != SCS_Connected)
		{
			if (!Socket.Socket || Socket.Socket && Socket.Socket->GetConnectionState() != SCS_Connected)
			{
				CloseSocket(Socket.Socket);
				Socket.Socket = ConnectToServer_Mc(ADataTranslate_Mc_Lf::IPAddresses[IpIdx - 1]);
				if (!Socket.Socket)
				{
					CloseSocket(Socket.Socket);
					Socket.bNeedWait = true;
					Socket.WaitTime = 1;
					continue;
				}
			}

			if (Socket.Socket && Socket.Socket->GetConnectionState() == SCS_Connected)
			{
				if (Data = ReceiveData_Mc(Socket.Socket); Data.IsEmpty())
				{
					//NumNotConnectedSockets++;
					Socket.RetryConnection++;
					if (Socket.RetryConnection > 5)
					{
						Socket.RetryConnection = 0;
						CloseSocket(Socket.Socket);
						Socket.bNeedWait = true;
						Socket.WaitTime = 1;
						continue;
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Found Server...."))
				}
			}
		}

		if (Socket.LastTimeReceivedMessage < 0)
		{
			Socket.LastTimeReceivedMessage = 5;

			CloseSocket(Socket.Socket);
			UE_LOG(LogTemp, Warning, TEXT("Disconnect from Server"));

			Socket.bNeedWait = true;
			Socket.WaitTime = 1;

			//bNeedUIRebuild = true;
			//bIsConnected = false;
			//LastTcpSocketData = FString("");
			continue;
		}

		if (!Socket.Socket)
		{
			Socket.LastTimeReceivedMessage -= DeltaTime;
			continue;
		}

		LastTcpSocketData = Data;
		if (Data.IsEmpty() && Socket.Socket && Socket.Socket->GetConnectionState() == SCS_Connected)
		{
			LastTcpSocketData = ReceiveData_Mc(Socket.Socket);
		}

		if (!LastTcpSocketData.IsEmpty())
		{
			//LastTcpSocketData = Data;
			Socket.LastTimeReceivedMessage = 5;
			Socket.RetryConnection = 0;
			if (!bIsConnected)
			{
				bNeedUIRebuild = true;
			}
			bIsConnected = true;

			for (FTcpClient_Socket_Mc_Lf& Other : TcpSockets)
			{
				// Close all other sockets because the client can only handle 1 server at a time
				if (Other.Socket != Socket.Socket)
				{
					CloseSocket(Other.Socket);
				}
			}

			return;
		}

		Socket.LastTimeReceivedMessage -= DeltaTime;
	}

	bool bFoundConnectedSocket = false;
	for (const FTcpClient_Socket_Mc_Lf& Socket : TcpSockets)
	{
		if (Socket.Socket && Socket.Socket->GetConnectionState() == SCS_Connected)
		{
			bFoundConnectedSocket = true;
			break;
		}
	}
	if (!bFoundConnectedSocket)
	{
		bIsConnected = false;

		for (FTcpClient_Socket_Mc_Lf& Socket : TcpSockets)
		{
			CloseSocket(Socket.Socket);

			const int32 RetryConnection = Socket.RetryConnection;
			Socket = FTcpClient_Socket_Mc_Lf();
			Socket.RetryConnection = RetryConnection;
		}

		//TcpSockets.Empty();
	}

	//UE_LOG(LogTemp, Warning, TEXT("%d %s"), bIsConnected, *LastTcpSocketData);

	// if (!bIsConnected)
	// {
	// 	const FString& DummyData = ReceiveData_Mc();
	// }

	//FString ServerIP = TEXT("192.168.43.30"); // Replace with your server's IP


	// UE_LOG(LogTemp, Warning, TEXT("Data -> %s"), *Data);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *ConnectionStateToString(TcpSocket->GetConnectionState()));
}

FSocket* ATcpClient_Mc_Lf::ConnectToServer_Mc(const FString& ServerIP)
{
	constexpr uint16 ServerPort = 54000;

	FIPv4Address IPAddress;
	FIPv4Address::Parse(ServerIP, IPAddress);
	const FIPv4Endpoint Endpoint(IPAddress, ServerPort);

	FSocket* Socket = FTcpSocketBuilder(TEXT("Monitory_TCP_Socket")).AsReusable();

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	const TSharedRef<FInternetAddr> InternetAddr = SocketSubsystem->CreateInternetAddr();
	InternetAddr->SetIp(Endpoint.Address.Value);
	InternetAddr->SetPort(Endpoint.Port);

	//TcpSocket->SetNoDelay(true);
	//TcpSocket->SetNonBlocking(true);

	if (Socket->Connect(*InternetAddr))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Connected to server"));
		return Socket;
	}
	CloseSocket(Socket);
	return nullptr;
}

FString ATcpClient_Mc_Lf::ReceiveData_Mc(FSocket* Socket)
{
	if (Socket && Socket->GetConnectionState() == SCS_Connected)
	{
		if (uint32 Size; Socket->HasPendingData(Size))
		{
			TArray<uint8> ReceivedData;
			ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

			// Keep reading and discarding data until the buffer is empty
			while (Socket->HasPendingData(Size))
			{
				int32 Read = 0;
				Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			}

			if (ReceivedData.Num() > 0)
			{
				TArray<FString> SeparatorArray;
				FString(UTF8_TO_TCHAR(ReceivedData.GetData())).ParseIntoArray(SeparatorArray, TEXT("!"), false);
				if (SeparatorArray.Num())
				{
					return SeparatorArray[0];
				}
				return FString("");
			}
		}
	}
	return FString("");
}

void ATcpClient_Mc_Lf::CloseSocket(FSocket* Socket)
{
	if (Socket)
	{
		//TcpSocket->Shutdown(ESocketShutdownMode::ReadWrite);
		Socket->Close();
	}

	Socket = nullptr;
}


void ATcpClient_Mc_Lf::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//bNeedRunTcpTask = false;
	for (FTcpClient_Socket_Mc_Lf& Socket : TcpSockets)
	{
		CloseSocket(Socket.Socket);
	}
	//FPlatformProcess::Sleep(2);
	bIsConnected = false;
	LastTcpSocketData = FString("");
}
