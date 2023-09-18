// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Networking.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tasks/Task.h"

#include "DataTranslate_Mc_Lf.generated.h"

USTRUCT()
struct MONITORY_CLIENT_API FDataMinMaxCurrent_Mc_Lf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Index = -1;

	UPROPERTY(EditAnywhere)
	double Current = 0;

	UPROPERTY(EditAnywhere)
	double Min = 0;

	UPROPERTY(EditAnywhere)
	double Max = 0;

	UPROPERTY(EditAnywhere)
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere)
	FString Name = FString("");
};


USTRUCT()
struct MONITORY_CLIENT_API FPCData_Mc_Lf
{
	GENERATED_BODY()

	FPCData_Mc_Lf()
	{
	}

	~FPCData_Mc_Lf()
	{
	}

	//UPROPERTY(EditAnywhere)
	//bool bEditedSometimeInThePast = false;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf CpuLoadTotal;

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> CpuLoadThreads;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf CpuClockSpeedTotal;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf CpuRamUsed;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf CpuRamAvailable;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf CpuRamPercentage;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf CpuMaxRam;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf GpuLoadTotal;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf GpuClockSpeedTotal;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf GpuRamUsed;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf GpuRamAvailable;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf GpuRamPercentage;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf GpuMaxRam;

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> Wattage;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf WattageTotalCurrent;

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> Temperature;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf TemperatureMaxCurrent;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf DrivesMaxLoad;

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> DrivesLoad;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf TimeNow; // Using Unit

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf DateNow; // Using Unit

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> DownloadSpeeds;

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> UploadSpeeds;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf DownloadMaxSpeed;

	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf UploadMaxSpeed;
	
	UPROPERTY(EditAnywhere)
	FDataMinMaxCurrent_Mc_Lf DownloadUploadMaxSpeed;

	UPROPERTY(EditAnywhere)
	TArray<FDataMinMaxCurrent_Mc_Lf> DownloadUploadSpeedsGraph;
};


UCLASS()
class MONITORY_CLIENT_API ADataTranslate_Mc_Lf : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADataTranslate_Mc_Lf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	inline static FPCData_Mc_Lf PcData;

	inline static const FString IPAddressesFileName = FString("WhiteListedIPAddresses.txt");
	inline static const FString ThemeSettingsFileName = FString("ThemeSettings.txt");
	
	inline static TArray<FString> IPAddresses;
	inline static bool bChangedIPAddresses = false;
	inline static bool bCachedIPAddresses = false;

	// UPROPERTY(EditAnywhere)
	// FString AppVersion = FString("1.0");

	// UE::Tasks::FTask WriteTask;
	// bool bNeedRunWriteTask = false;
	
	static void CreatePCData(FPCData_Mc_Lf& FromData, const FString& FromString);
	static FString ReadOneLineFromFile(const int32& LineIndex);
	static FLinearColor HSVToRGB(float H, float S, float V);

	static FLinearColor GenerateDistinctColors(int32 Index);
	static FString FormatDoubleWithOneDecimal(const double& ValueToFormat);
	static FString FormatDoubleWithTwoDecimals(const double& ValueToFormat);
	static FString FormatDoubleWithoutDecimals(double ValueToFormat);

	static FString GetAppVersion();

	static bool SaveDataToInternalStorage(const FString& DataToSave, const FString& FileName);
	static FString ReadDataFromInternalStorage(const FString& FileNameToRead);
	
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
