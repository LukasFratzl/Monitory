// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTranslate_Mc_Lf.h"

#include "TcpClient_Mc_Lf.h"
#include "WidgetMainMenu_Mc_Lf.h"


// Sets default values
ADataTranslate_Mc_Lf::ADataTranslate_Mc_Lf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.TickInterval = 0.1f;
}

// Called when the game starts or when spawned
void ADataTranslate_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();

	GenerateDistinctColors(128);

	IPAddresses.Empty();
	// Cache IPs from file
	const FString& IPAddressesFromFile = ReadDataFromInternalStorage(IPAddressesFileName);
	if (!IPAddressesFromFile.IsEmpty())
	{
		TArray<FString> DataArray;
		IPAddressesFromFile.ParseIntoArray(DataArray, TEXT("|"), false);

		for (const FString& Entry : DataArray)
		{
			if (!Entry.IsEmpty())
			{
				IPAddresses.Add(Entry);
				UE_LOG(LogTemp, Warning, TEXT("Added %s"), *Entry);
			}
		}
		bChangedIPAddresses = true;
	}

	bCachedIPAddresses = true;


	// const FString& Data =
	// 	"Cpu_Utility:0:15,557993:6,7117453:89,82752|Cpu_Utility:1:15,525704:0:26,91856|Cpu_Utility:2:11,417341:11,417341:47,226685|Cpu_Utility:3:10,104376:0:37,00373|Cpu_Utility:4:13,801252:5,4927645:47,00341|Cpu_Utility:5:10,723084:0:32,723003|Cpu_Utility:6:15,994996:6,4926567:56,127678|Cpu_Utility:7:16,774988:0:37,78848|Cpu_Utility:8:16,250414:6,6773357:36,040123|Cpu_Utility:9:9,873629:0:40,31513|Cpu_Utility:10:12,557209:4,7959685:53,40341|Cpu_Utility:11:9,688729:0:34,275948|Cpu_Utility:Total:13,189143:6,1984777:34,5123|";

	// CreatePCData(PcData, Data);
}

// Called every frame
void ADataTranslate_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FString Data = "";
	// PcData = FPCData_Mc_Lf();
	//
	// if (ATcpClient_Mc_Lf::bIsConnected)
	// {
	// 	Data = ATcpClient_Mc_Lf::LastTcpSocketData;
	// }
	// else
	// {
	// 	ATcpClient_Mc_Lf::LastTcpSocketData = "";
	// 	// PcData = FPCData_Mc_Lf();
	// }
	// // if (ADataTranslate_Mc_Lf::LastPreviousTcpSocketData != Data || Data == "")
	// // {
	// // 	ADataTranslate_Mc_Lf::LastPreviousTcpSocketData = Data;
	// // 	PcData = FPCData_Mc_Lf();
	// // }
	//
	// CreatePCData(PcData, Data);

	//FPlatformProcess::Sleep(UWidgetMainMenu_Mc_Lf::LastUpdateRateSeconds);
}

void ADataTranslate_Mc_Lf::CreatePCData(FPCData_Mc_Lf& FromData, const FString& FromString)
{
	// Type : Unit : Current : Min : Max -> | Separator
	// Cpu_Utility:Total:16,077965:8,868623:93,0459
	// Cpu_Utility:0:16,077965:8,868623:93,0459

	TArray<FDataMinMaxCurrent_Mc_Lf> CpuThreadsRaw;
	TArray<FDataMinMaxCurrent_Mc_Lf> WattageRaw;
	TArray<FDataMinMaxCurrent_Mc_Lf> TemperatureRaw;
	TArray<FDataMinMaxCurrent_Mc_Lf> DriveLoadRaw;
	TArray<FDataMinMaxCurrent_Mc_Lf> DownloadSpeedRaw;
	TArray<FDataMinMaxCurrent_Mc_Lf> UploadSpeedRaw;

	TArray<FString> DataArray;
	FromString.ParseIntoArray(DataArray, TEXT("|"), false);

	for (const FString& Entry : DataArray)
	{
		// Replace commas with periods for correct number formatting
		FString CorrectedEntry = Entry;
		for (int32 i = 0; i < CorrectedEntry.Len(); ++i)
		{
			if (CorrectedEntry[i] == ',')
			{
				CorrectedEntry[i] = '.';
			}
		}

		// Split the entry into parts using ":" separator
		TArray<FString> EntryParts;
		CorrectedEntry.ParseIntoArray(EntryParts, TEXT(":"), true);

		if (EntryParts.Num() >= 5)
		{
			const FString& Type = EntryParts[0];
			const FString& Unit = EntryParts[1];
			const double Current = FCString::Atod(*EntryParts[2]);
			const double Min = FCString::Atod(*EntryParts[3]);
			const double Max = FCString::Atod(*EntryParts[4]);

			if (Type == "Cpu_Utility")
			{
				int32 Index = INDEX_NONE;
				if (Unit != "Total")
				{
					Index = FCString::Atoi(*Unit);
				}

				if (Index >= 0)
				{
					FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
					Range.Index = Index;
					Range.SetCurrent(Current);
					Range.SetMin(Min);
					Range.SetMax(Max);

					CpuThreadsRaw.Add(Range);
					//FromData.bEditedSometimeInThePast = true;
				}
				else
				{
					FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
					Range.Index = Index;
					Range.SetCurrent(Current);
					Range.SetMin(Min);
					Range.SetMax(Max);
					Range.Color = GenerateDistinctColors(0);

					FromData.CpuLoadTotal = Range;
					//FromData.bEditedSometimeInThePast = true;

					// Now you have Type, Current (as double), Min (as double), and Max (as double)
					//UE_LOG(LogTemp, Warning, TEXT("Type: %s, Unit: %s, Current: %f, Min: %f, Max: %f"), *Type, *Unit, Current, Min, Max);
				}
			}

			if (Type == "Cpu_Clock")
			{
				int32 Index = INDEX_NONE;
				if (Unit != "Total")
				{
					Index = FCString::Atoi(*Unit);
				}

				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = Index;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);

				if (Index == INDEX_NONE) // For now we are only interested into the average
				{
					FromData.CpuClockSpeedTotal = Range;
				}
			}

			if (Type == "Cpu_Memory")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);

				if (Unit == "Available")
				{
					FromData.CpuRamAvailable = Range;
				}
				else if (Unit == "Used")
				{
					FromData.CpuRamUsed = Range;
				}
			}

			if (Type == "Gpu_Clock")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);
				Range.Color = GenerateDistinctColors(3);

				FromData.GpuClockSpeedTotal = Range;
			}

			if (Type == "Gpu_Utility")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);
				Range.Color = GenerateDistinctColors(4);

				FromData.GpuLoadTotal = Range;
			}

			if (Type == "Gpu_Memory")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);

				if (Unit == "Available")
				{
					FromData.GpuRamAvailable = Range;
				}
				else if (Unit == "Used")
				{
					FromData.GpuRamUsed = Range;
				}
			}

			if (Type == "Wattage")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);
				//Range.Color = GenerateDistinctColors(4);
				Range.Name = Unit;

				WattageRaw.Add(Range);
			}

			if (Type == "Temperature")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				if (Current < 273.15) // Probably Celsius
				{
					Range.SetCurrent(Current);
					Range.SetMin(Min);
					Range.SetMax(Max);
				}
				else
				{
					// Convert Kelvin to Celsius
					Range.SetCurrent(Current - 273.15);
					Range.SetMin(Min - 273.15);
					Range.SetMax(Max - 273.15);
				}
				//Range.Color = GenerateDistinctColors(4);
				Range.Name = Unit;

				TemperatureRaw.Add(Range);
			}

			if (Type == "Storage_Load")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);
				//Range.Color = GenerateDistinctColors(4);
				Range.Name = Unit;

				DriveLoadRaw.Add(Range);
			}

			if (Type == "Time_Now")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);
				//Range.Color = GenerateDistinctColors(4);

				Range.Name = Unit;
				for (int32 i = 0; i < Range.Name.Len(); ++i)
				{
					if (Range.Name[i] == '~')
					{
						Range.Name[i] = ':';
					}
				}

				FromData.TimeNow = Range;
			}

			if (Type == "Date_Now")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current);
				Range.SetMin(Min);
				Range.SetMax(Max);
				//Range.Color = GenerateDistinctColors(4);
				Range.Name = Unit;

				FromData.DateNow = Range;
			}

			if (Type == "Download_Speed")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current / 1024 / 1024); // It's in bytes
				Range.SetMin(Min / 1024 / 1024); // It's in bytes
				Range.SetMax(Max / 1024 / 1024); // It's in bytes
				Range.Name = Unit;

				DownloadSpeedRaw.Add(Range);
			}

			if (Type == "Upload_Speed")
			{
				FDataMinMaxCurrent_Mc_Lf Range = FDataMinMaxCurrent_Mc_Lf();
				Range.Index = INDEX_NONE;
				Range.SetCurrent(Current / 1024 / 1024); // It's in bytes
				Range.SetMin(Min / 1024 / 1024); // It's in bytes
				Range.SetMax(Max / 1024 / 1024); // It's in bytes
				Range.Name = Unit;

				UploadSpeedRaw.Add(Range);
			}
		}
	}

	if (const int32 NumThreads = CpuThreadsRaw.Num())
	{
		FromData.CpuLoadThreads.SetNum(NumThreads);
		for (int32 ThreadIdx = 0; ThreadIdx < NumThreads; ++ThreadIdx)
		{
			FDataMinMaxCurrent_Mc_Lf& Thread = FromData.CpuLoadThreads[ThreadIdx];
			const FDataMinMaxCurrent_Mc_Lf& Thread_Raw = CpuThreadsRaw[ThreadIdx];

			//Thread.Current = (Thread_Raw.Current + Thread.Current) / 2;
			Thread.SetCurrent(Thread_Raw.GetCurrent());
			Thread.Index = Thread_Raw.Index;
			Thread.SetMin(Thread_Raw.GetMin());
			Thread.SetMax(Thread_Raw.GetMax());
			Thread.Color = GenerateDistinctColors(Thread.Index + 1);
		}
	}

	if (const int32 NumWattage = WattageRaw.Num())
	{
		FromData.Wattage.SetNum(NumWattage);

		FromData.WattageTotalCurrent.SetCurrent(0);
		FromData.WattageTotalCurrent.SetMax(0);
		FromData.WattageTotalCurrent.SetMin(0);
		for (int32 WattageIdx = 0; WattageIdx < NumWattage; ++WattageIdx)
		{
			FDataMinMaxCurrent_Mc_Lf& Wattage = FromData.Wattage[WattageIdx];
			const FDataMinMaxCurrent_Mc_Lf& Wattage_Raw = WattageRaw[WattageIdx];

			Wattage = Wattage_Raw;

			Wattage.Color = GenerateDistinctColors(WattageIdx + 7);

			FromData.WattageTotalCurrent.SetCurrent(
				FromData.WattageTotalCurrent.GetCurrent() + Wattage_Raw.GetCurrent());
			FromData.WattageTotalCurrent.SetMax(FromData.WattageTotalCurrent.GetMax() + Wattage_Raw.GetMax());
			FromData.WattageTotalCurrent.SetMin(FromData.WattageTotalCurrent.GetMin() + Wattage_Raw.GetMin());
		}
	}

	if (const int32 NumTemps = TemperatureRaw.Num())
	{
		FromData.Temperature.SetNum(NumTemps);

		FromData.TemperatureMaxCurrent.SetCurrent(0);
		FromData.TemperatureMaxCurrent.SetMax(0);
		FromData.TemperatureMaxCurrent.SetMin(1000);
		for (int32 TempIdx = 0; TempIdx < NumTemps; ++TempIdx)
		{
			FDataMinMaxCurrent_Mc_Lf& Temp = FromData.Temperature[TempIdx];
			const FDataMinMaxCurrent_Mc_Lf& Temp_Raw = TemperatureRaw[TempIdx];

			Temp = Temp_Raw;

			Temp.Color = GenerateDistinctColors(TempIdx + 7);

			if (Temp_Raw.GetCurrent() > FromData.TemperatureMaxCurrent.GetCurrent())
			{
				FromData.TemperatureMaxCurrent.SetCurrent(Temp_Raw.GetCurrent());
			}
			if (Temp_Raw.GetMax() > FromData.TemperatureMaxCurrent.GetMax())
			{
				FromData.TemperatureMaxCurrent.SetMax(Temp_Raw.GetMax());
			}
			if (Temp_Raw.GetMin() < FromData.TemperatureMaxCurrent.GetMin())
			{
				FromData.TemperatureMaxCurrent.SetMin(Temp_Raw.GetMin());
			}
		}
	}

	if (const int32 NumDrives = DriveLoadRaw.Num())
	{
		FromData.DrivesLoad.SetNum(NumDrives);
		FromData.DrivesMaxLoad.SetCurrent(0);
		FromData.DrivesMaxLoad.SetMin(100);
		FromData.DrivesMaxLoad.SetMax(0);
		for (int32 DriveIdx = 0; DriveIdx < NumDrives; ++DriveIdx)
		{
			FDataMinMaxCurrent_Mc_Lf& Drive = FromData.DrivesLoad[DriveIdx];
			const FDataMinMaxCurrent_Mc_Lf& Drive_Raw = DriveLoadRaw[DriveIdx];

			Drive.SetCurrent(Drive_Raw.GetCurrent());
			Drive.Index = DriveIdx;
			Drive.SetMin(Drive_Raw.GetMin());
			Drive.SetMax(Drive_Raw.GetMax());
			Drive.Color = GenerateDistinctColors(DriveIdx + 7);

			if (Drive.GetCurrent() > FromData.DrivesMaxLoad.GetCurrent())
			{
				FromData.DrivesMaxLoad.SetCurrent(Drive.GetCurrent());
			}

			if (Drive.GetMax() > FromData.DrivesMaxLoad.GetMax())
			{
				FromData.DrivesMaxLoad.SetMax(Drive.GetMax());
			}

			if (Drive.GetMin() < FromData.DrivesMaxLoad.GetMin())
			{
				FromData.DrivesMaxLoad.SetMin(Drive.GetMin());
			}
		}
	}

	if (const int32 NumDownloadSpeeds = DownloadSpeedRaw.Num())
	{
		FromData.DownloadSpeeds.SetNum(NumDownloadSpeeds);
		FromData.DownloadMaxSpeed.SetCurrent(0);
		FromData.DownloadMaxSpeed.SetMin(10000000);
		FromData.DownloadMaxSpeed.SetMax(0);
		for (int32 DlIdx = 0; DlIdx < NumDownloadSpeeds; ++DlIdx)
		{
			FDataMinMaxCurrent_Mc_Lf& Speed = FromData.DownloadSpeeds[DlIdx];
			const FDataMinMaxCurrent_Mc_Lf& Speed_Raw = DownloadSpeedRaw[DlIdx];

			Speed = Speed_Raw;
			Speed.Index = DlIdx;

			Speed.Color = GenerateDistinctColors(Speed.Index + 1);

			if (Speed.GetCurrent() > FromData.DownloadMaxSpeed.GetCurrent())
			{
				FromData.DownloadMaxSpeed.SetCurrent(Speed.GetCurrent());
			}

			if (Speed.GetMax() > FromData.DownloadMaxSpeed.GetMax())
			{
				FromData.DownloadMaxSpeed.SetMax(Speed.GetMax());
			}

			if (Speed.GetMin() < FromData.DownloadMaxSpeed.GetMin())
			{
				FromData.DownloadMaxSpeed.SetMin(Speed.GetMin());
			}
		}
		FromData.DownloadMaxSpeed.Color = GenerateDistinctColors(5);
	}

	if (const int32 NumUploadSpeeds = UploadSpeedRaw.Num())
	{
		FromData.UploadSpeeds.SetNum(NumUploadSpeeds);
		FromData.UploadMaxSpeed.SetCurrent(0);
		FromData.UploadMaxSpeed.SetMin(10000000);
		FromData.UploadMaxSpeed.SetMax(0);
		for (int32 UlIdx = 0; UlIdx < NumUploadSpeeds; ++UlIdx)
		{
			FDataMinMaxCurrent_Mc_Lf& Speed = FromData.UploadSpeeds[UlIdx];
			const FDataMinMaxCurrent_Mc_Lf& Speed_Raw = UploadSpeedRaw[UlIdx];

			Speed = Speed_Raw;
			Speed.Index = UlIdx;

			Speed.Color = GenerateDistinctColors(Speed.Index + 1);

			if (Speed.GetCurrent() > FromData.UploadMaxSpeed.GetCurrent())
			{
				FromData.UploadMaxSpeed.SetCurrent(Speed.GetCurrent());
			}

			if (Speed.GetMax() > FromData.UploadMaxSpeed.GetMax())
			{
				FromData.UploadMaxSpeed.SetMax(Speed.GetMax());
			}

			if (Speed.GetMin() < FromData.UploadMaxSpeed.GetMin())
			{
				FromData.UploadMaxSpeed.SetMin(Speed.GetMin());
			}
		}
		FromData.UploadMaxSpeed.Color = GenerateDistinctColors(6);
	}

	FromData.CpuMaxRam.SetCurrent(FromData.CpuRamUsed.GetCurrent() + FromData.CpuRamAvailable.GetCurrent());
	FromData.CpuMaxRam.Index = INDEX_NONE;
	FromData.CpuMaxRam.Color = GenerateDistinctColors(1);
	FromData.CpuMaxRam.SetMax(FromData.CpuMaxRam.GetCurrent());
	FromData.CpuMaxRam.SetMin(0);

	FromData.CpuRamPercentage.SetCurrent(FromData.CpuRamUsed.GetCurrent() / FromData.CpuMaxRam.GetCurrent() * 100);
	FromData.CpuRamPercentage.Index = INDEX_NONE;
	FromData.CpuRamPercentage.Color = GenerateDistinctColors(1);
	FromData.CpuRamPercentage.SetMax(FromData.CpuRamUsed.GetMax() / FromData.CpuMaxRam.GetCurrent() * 100);
	FromData.CpuRamPercentage.SetMin(FromData.CpuRamUsed.GetMin() / FromData.CpuMaxRam.GetCurrent() * 100);

	FromData.GpuMaxRam.SetCurrent(FromData.GpuRamUsed.GetCurrent() + FromData.GpuRamAvailable.GetCurrent());
	FromData.GpuMaxRam.Index = INDEX_NONE;
	FromData.GpuMaxRam.Color = GenerateDistinctColors(2);
	FromData.GpuMaxRam.SetMax(FromData.GpuMaxRam.GetCurrent());
	FromData.GpuMaxRam.SetMin(0);

	FromData.GpuRamPercentage.SetCurrent(FromData.GpuRamUsed.GetCurrent() / FromData.GpuMaxRam.GetCurrent() * 100);
	FromData.GpuRamPercentage.Index = INDEX_NONE;
	FromData.GpuRamPercentage.Color = GenerateDistinctColors(5);
	FromData.GpuRamPercentage.SetMax(FromData.GpuRamUsed.GetMax() / FromData.GpuMaxRam.GetCurrent() * 100);
	FromData.GpuRamPercentage.SetMin(FromData.GpuRamUsed.GetMin() / FromData.GpuMaxRam.GetCurrent() * 100);

	FromData.DownloadUploadMaxSpeed.SetCurrent(FMath::Max(FromData.DownloadMaxSpeed.GetCurrent(),
	                                                      FromData.UploadMaxSpeed.GetCurrent()));
	FromData.DownloadUploadMaxSpeed.SetMax(FMath::Max(FromData.DownloadMaxSpeed.GetMax(),
	                                                  FromData.UploadMaxSpeed.GetMax()));
	FromData.DownloadUploadMaxSpeed.SetMin(FMath::Min(FromData.DownloadMaxSpeed.GetMin(),
	                                                  FromData.UploadMaxSpeed.GetMin()));
	FromData.DownloadUploadMaxSpeed.Index = INDEX_NONE;

	FromData.DownloadUploadSpeedsGraph.SetNum(2);
	FromData.DownloadUploadSpeedsGraph[0] = FromData.DownloadMaxSpeed;
	FromData.DownloadUploadSpeedsGraph[1] = FromData.UploadMaxSpeed;
}


FString ADataTranslate_Mc_Lf::ReadOneLineFromFile(const int32 LineIndex)
{
	// // Get the desktop directory path
	// if (TCHAR DesktopPath[MAX_PATH]; SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, DesktopPath) == S_OK)
	// {
	// 	const FString& FilePath = FPaths::Combine(DesktopPath, TEXT("sensor_data.txt"));
	//
	// 	// Check if the file exists
	// 	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	// 	{
	// 		// Read the file
	// 		FString FileContent;
	// 		FFileHelper::LoadFileToString(FileContent, *FilePath);
	//
	// 		// Split the content into lines
	// 		TArray<FString> Lines;
	// 		FileContent.ParseIntoArrayLines(Lines);
	//
	// 		if (Lines.IsValidIndex(LineIndex))
	// 		{
	// 			// Get the first line
	// 			return Lines[LineIndex];
	// 		}
	// 	}
	// }
	return FString("");
}

FLinearColor ADataTranslate_Mc_Lf::HSVToRGB(float H, float S, float V)
{
	int32 Hi = static_cast<int32>(H / 60.0f) % 6;
	float f = H / 60.0f - static_cast<float>(Hi);
	float p = V * (1.0f - S);
	float q = V * (1.0f - f * S);
	float t = V * (1.0f - (1.0f - f) * S);

	switch (Hi)
	{
	case 0:
		return FLinearColor(V, t, p);
	case 1:
		return FLinearColor(q, V, p);
	case 2:
		return FLinearColor(p, V, t);
	case 3:
		return FLinearColor(p, q, V);
	case 4:
		return FLinearColor(t, p, V);
	case 5:
		return FLinearColor(V, p, q);
	default:
		return FLinearColor(0.0f, 0.0f, 0.0f); // Handle an invalid Hue value
	}
}


FLinearColor ADataTranslate_Mc_Lf::GenerateDistinctColors(int32 Index)
{
	static FLinearColor DistinctColors[32] = {
		FLinearColor(1.0f, 0.0f, 0.0f), // Red
		FLinearColor(0.0f, 1.0f, 0.0f), // Green
		FLinearColor(0.0f, 0.0f, 1.0f), // Blue
		FLinearColor(1.0f, 1.0f, 0.0f), // Yellow
		FLinearColor(1.0f, 0.0f, 1.0f), // Magenta
		FLinearColor(0.0f, 1.0f, 1.0f), // Cyan
		FLinearColor(0.5f, 0.5f, 0.0f), // Olive
		FLinearColor(0.0f, 0.5f, 0.5f), // Teal
		FLinearColor(1.0f, 0.5f, 0.0f), // Orange
		FLinearColor(0.5f, 0.0f, 1.0f), // Purple
		FLinearColor(0.5f, 0.0f, 0.0f), // Maroon
		FLinearColor(0.0f, 0.5f, 0.0f), // Green (Dark Green)
		FLinearColor(0.0f, 0.0f, 0.5f), // Navy
		FLinearColor(0.5f, 0.5f, 0.5f), // Gray
		FLinearColor(0.3f, 0.3f, 0.3f), // Dark Gray
		FLinearColor(0.7f, 0.7f, 0.7f), // Light Gray

		// Additional distinct colors
		FLinearColor(0.8f, 0.2f, 0.2f), // Dark Red
		FLinearColor(0.2f, 0.8f, 0.2f), // Dark Green (Alternate)
		FLinearColor(0.2f, 0.2f, 0.8f), // Dark Blue
		FLinearColor(0.8f, 0.8f, 0.2f), // Dark Yellow
		FLinearColor(0.8f, 0.2f, 0.8f), // Dark Magenta
		FLinearColor(0.2f, 0.8f, 0.8f), // Dark Cyan
		FLinearColor(0.9f, 0.6f, 0.2f), // Gold
		FLinearColor(0.2f, 0.6f, 0.9f), // Sky Blue
		FLinearColor(0.9f, 0.2f, 0.6f), // Pink
		FLinearColor(0.6f, 0.9f, 0.2f), // Lime Green
		FLinearColor(0.6f, 0.2f, 0.9f), // Indigo
		FLinearColor(0.9f, 0.9f, 0.6f), // Light Yellow
		FLinearColor(0.9f, 0.6f, 0.9f), // Light Magenta
		FLinearColor(0.6f, 0.9f, 0.9f), // Light Cyan
	};

	const int32 ColorsMaxIndex = 31;

	const int32 MaxIndex = Index % ColorsMaxIndex;

	return DistinctColors[MaxIndex];
}

FString ADataTranslate_Mc_Lf::FormatDoubleWithOneDecimal(const double ValueToFormat)
{
	return FString::Printf(TEXT("%.1f"), ValueToFormat);
}

FString ADataTranslate_Mc_Lf::FormatDoubleWithTwoDecimals(const double ValueToFormat)
{
	return FString::Printf(TEXT("%.2f"), ValueToFormat);
}

FString ADataTranslate_Mc_Lf::FormatDoubleWithoutDecimals(double ValueToFormat)
{
	return FString::Printf(TEXT("%.0f"), ValueToFormat);
}

FString ADataTranslate_Mc_Lf::GetAppVersion()
{
	FString AppVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);

	return AppVersion;
}

bool ADataTranslate_Mc_Lf::SaveDataToInternalStorage(const FString& DataToSave, const FString& FileName)
{
	// Get the path to the internal storage directory
	const FString& SaveDirectory = FPaths::ProjectPersistentDownloadDir();

	// Combine with the desired file name
	const FString& SavePath = FPaths::Combine(SaveDirectory, FileName);

	// Create a new platform file manager

	// Write the data to the file
	if (IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile(); PlatformFile.
		CreateDirectoryTree(*SaveDirectory))
	{
		UE_LOG(LogTemp, Display, TEXT("Saving Data to: %s"), *SavePath);
		FFileHelper::SaveStringToFile(DataToSave, *SavePath);
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *SaveDirectory);
	return false;
}

FString ADataTranslate_Mc_Lf::ReadDataFromInternalStorage(const FString& FileNameToRead)
{
	FString DataRead;

	// Get the path to the internal storage directory
	const FString& SaveDirectory = FPaths::ProjectPersistentDownloadDir();

	// Combine with the desired file name

	// Read the contents of the file
	if (const FString& ReadFilePath = FPaths::Combine(SaveDirectory, FileNameToRead); FFileHelper::LoadFileToString(
		DataRead, *ReadFilePath))
	{
		// DataRead now contains the contents of the file
		return DataRead;
	}
	return FString(); // Return an empty string if reading fails
}


void ADataTranslate_Mc_Lf::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//bNeedRunWriteTask = false;

	IPAddresses.Empty();
	PcData = FPCData_Mc_Lf();
}
