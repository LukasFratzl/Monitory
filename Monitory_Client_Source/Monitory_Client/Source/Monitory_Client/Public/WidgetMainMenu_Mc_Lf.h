﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTranslate_Mc_Lf.h"
#include "MediaSource.h"
#include "WidgetFillGraph_Mc_Lf.h"
#include "WidgetHardwareLabel_Mc_Lf.h"
#include "WidgetLineGraph_Mc_Lf.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableTextBox.h"
#include "Components/ScaleBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "WidgetMainMenu_Mc_Lf.generated.h"

USTRUCT()
struct MONITORY_CLIENT_API FLine_Mc_Lf
{
	GENERATED_BODY()

	FLine_Mc_Lf()
	{
	}

	~FLine_Mc_Lf()
	{
	}

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetGraphLine_Mc_Lf> Line;
};

USTRUCT()
struct MONITORY_CLIENT_API FStraightLine_Mc_Lf : public FLine_Mc_Lf
{
	GENERATED_BODY()

	FStraightLine_Mc_Lf()
	{
	}

	~FStraightLine_Mc_Lf()
	{
	}
};

USTRUCT()
struct MONITORY_CLIENT_API FShapedLine_Mc_Lf : public FLine_Mc_Lf
{
	GENERATED_BODY()

	FShapedLine_Mc_Lf()
	{
	}

	~FShapedLine_Mc_Lf()
	{
	}

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetHardwareLabel_Mc_Lf> Label;

	UPROPERTY(EditAnywhere)
	TArray<double> ValueHistory;
};

USTRUCT()
struct MONITORY_CLIENT_API FFilledGraphArea_Mc_Lf
{
	GENERATED_BODY()

	FFilledGraphArea_Mc_Lf()
	{
	}

	~FFilledGraphArea_Mc_Lf()
	{
	}

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetGraphFill_Mc_Lf> FillWidget;

	// UPROPERTY(EditAnywhere)
	// TArray<double> ValueHistory;
};



USTRUCT()
struct MONITORY_CLIENT_API FGraph_Mc_Lf
{
	GENERATED_BODY()

	FGraph_Mc_Lf(){}
	~FGraph_Mc_Lf(){}

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> FillMaterialOverride;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> LineMaterialOverride;

	UPROPERTY(EditAnywhere)
	FLinearColor FillColor = FLinearColor(1, 1, 1, 0.5f);

	UPROPERTY(EditAnywhere)
	bool bUseLineColorOverride = false;

	UPROPERTY(EditAnywhere)
	FLinearColor LineColorOverride = FLinearColor::White;

	UPROPERTY(EditAnywhere)
	FLinearColor HighLineColor = FLinearColor::Transparent;

	UPROPERTY(EditAnywhere)
	FLinearColor LowLineColor = FLinearColor::White;

	UPROPERTY(EditAnywhere)
	TArray<FShapedLine_Mc_Lf> Graph;

	UPROPERTY(EditAnywhere)
	FStraightLine_Mc_Lf HighLine;

	UPROPERTY(EditAnywhere)
	FStraightLine_Mc_Lf LowLine;

	UPROPERTY(EditAnywhere)
	FStraightLine_Mc_Lf AverageLine;

	UPROPERTY(EditAnywhere)
	FFilledGraphArea_Mc_Lf FillArea;

	UPROPERTY(EditAnywhere)
	FVector2f CurrentCanvasSize = FVector2f::ZeroVector;
};

UENUM()
enum EPrecisionPoint : uint8
{
	Zero,
	One,
	Two
};

USTRUCT(BlueprintType)
struct MONITORY_CLIENT_API FTheme_Mc_Lf
{
	GENERATED_BODY()

	FTheme_Mc_Lf(){}
	~FTheme_Mc_Lf(){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMediaSource> Background = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> BackgroundFallback = nullptr;
};


UCLASS()
class MONITORY_CLIENT_API UWidgetMainMenu_Mc_Lf : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Doing setup in the C++ constructor is not as
	// useful as using NativeConstruct.
	virtual void NativeConstruct() override;

public:

	FVector2D CachedViewportSize = FVector2D::ZeroVector;

	//UPROPERTY(EditAnywhere, meta=(ClampMin="0.01", ClampMax="2"))
	//double UpdateRateSeconds = 0.3;

	//inline static double LastUpdateRateSeconds = 0.3;

	double PCDataUpdateRateRuntime = 0;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf CpuUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf CpuRamUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf GpuUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf GpuRamUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf WattageUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf TemperatureUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf DriveUtilizationGraph;

	UPROPERTY(EditAnywhere)
	FGraph_Mc_Lf NetUtilizationGraph;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> CpuUtilizationCanvasPanel;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> CpuUtilizationTotalTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> CpuClockTotalTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> CpuRamUtilizationCanvasPanel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> CpuRamUtilizationPercentageTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> CpuRamUtilizationGBTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> CpuRamUtilizationGB_50PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> CpuRamUtilizationGB_100PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> GpuUtilizationCanvasPanel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> GpuUtilizationTotalTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> GpuClockTotalTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> GpuRamUtilizationCanvasPanel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> GpuRamUtilizationPercentageTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> GpuRamUtilizationGBTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> GpuRamUtilizationGB_50PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> GpuRamUtilizationGB_100PercentTextBlock;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UVerticalBox> WattageLayoutBox;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> WattageCanvasPanel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> WattageValueTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> WattageValueMaxTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> WattageValue_50PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> WattageValue_100PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UVerticalBox> TemperatureLayoutBox;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> TemperatureCanvasPanel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> TemperatureValueTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> TemperatureValueMaxTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> TemperatureValue_50PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> TemperatureValue_100PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> DriveUtilizationCanvasPanel;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> DriveUtilizationTotalTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> TimeNowTextBlock_Server;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> DateNowTextBlock_Server;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> TimeNowTextBlock_Client;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> DateNowTextBlock_Client;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> NetUtilizationCanvasPanel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> NetMaxDownSpeedTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> NetMaxUpSpeedTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> NetMaxSpeed_50PercentTextBlock;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> NetMaxSpeed_100PercentTextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<UUserWidget> HardwareLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<UUserWidget> IPAddressLabel;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UVerticalBox> IPAddressContainer;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> IPSelectionPanel_Full;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCanvasPanel> HardwareMonitoringPanel_Full;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UButton> IPAddressAddButton;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEditableTextBox> IPAddressAddTextBox;

	UPROPERTY(EditAnywhere)
	TArray<FTheme_Mc_Lf> CachedThemes;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> GraphLinesMaterial;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> GraphFillAreaMaterial;

	UFUNCTION(BlueprintCallable)
	void OnAddIPButtonPressed();
	

	UFUNCTION(BlueprintCallable)
	void CacheCanvasPanels(UCanvasPanel* CpuUtilization, UCanvasPanel* RamUtilization, UCanvasPanel* GpuUtilization, UCanvasPanel* GpuRamUtilization, UCanvasPanel* WattageCanvas, UCanvasPanel* TemperatureCanvas, UCanvasPanel* DriveUtilization, UCanvasPanel* NetUtilization, UCanvasPanel* IPPanel, UCanvasPanel* MonitoringPanel);

	UFUNCTION(BlueprintCallable)
	void CacheBoxes(UVerticalBox* WattageParentContainer, UVerticalBox* TemperatureParentContainer, UVerticalBox* IPAddresses);

	UFUNCTION(BlueprintCallable)
	void CacheTextBlocks(UTextBlock* CpuUtilizationTotal, UTextBlock* CpuClockTotal, UTextBlock* RamUtilizationPercent, UTextBlock* RamUtilizationGB, UTextBlock* RamUtilizationGB_50PercentGB, UTextBlock* RamUtilizationGB_100PercentGB, UTextBlock* GpuUtilizationTotal, UTextBlock* GpuClockTotal, UTextBlock* GpuRamUtilizationPercent, UTextBlock* GpuRamUtilizationGB, UTextBlock* GpuRamUtilizationGB_50PercentGB, UTextBlock* GpuRamUtilizationGB_100PercentGB, UTextBlock* WattageValue, UTextBlock* WattageValueMax, UTextBlock* WattageValue_50Percent, UTextBlock* WattageValue_100Percent, UTextBlock* TemperatureValue, UTextBlock* TemperatureValueMax, UTextBlock* TemperatureValue_50Percent, UTextBlock* TemperatureValue_100Percent, UTextBlock* DriveUtilizationTotal, UTextBlock* TimeNow_Server, UTextBlock* DateNow_Server, UTextBlock* TimeNow_Client, UTextBlock* DateNow_Client, UTextBlock* NetUpSpeedMax, UTextBlock* NetDownSpeedMax, UTextBlock* NetMaxSpeed_50Percent, UTextBlock* NetMaxSpeed_100Percent);

	UFUNCTION(BlueprintCallable)
	void CacheButtons(UButton* IpAddressAdd);

	UFUNCTION(BlueprintCallable)
	void CacheTextBoxes(UEditableTextBox* IpAddressAdd);

	UFUNCTION(BlueprintCallable)
	void CacheThemes(TArray<FTheme_Mc_Lf> Themes);

	UFUNCTION(BlueprintCallable)
	void TickComponent(float DeltaTime);


	bool TickIPSelectionPanel(float DeltaTime);
	void TickMonitoringPanel(float DeltaTime);

	void ResetMonitorPanel();

	void ResetGraph(FGraph_Mc_Lf& Graph);
	void InitGraph(FGraph_Mc_Lf& Graph, const int32 NumPoints, const int32 NumLines, const TObjectPtr<UCanvasPanel> CanvasPanel) const;

	// void ResetLabels(FGraph_Mc_Lf& Graph);
	void InitLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const TObjectPtr<UVerticalBox>& Parent) const;
	void AdvanceLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const EPrecisionPoint& Precision, const TObjectPtr<UVerticalBox>& Parent);

	FVector2D AdvanceGraph(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, bool bIsRelativeGraph, const FLinearColor& FillAreaColor, const TObjectPtr<UCanvasPanel> CanvasPanel) const;

	static void AdvanceText(const TObjectPtr<UTextBlock> Text, const double Value, const EPrecisionPoint& Precision, const FString& FormatMessage);

	UFUNCTION(BlueprintCallable)
	void FitBackgroundImageToScreen(UScaleBox* BgImage, const FVector2D TextureSize);

	UFUNCTION(BlueprintCallable)
	FTheme_Mc_Lf LoadTheme(float& Blur, float& Blackness, bool& bAnimations);
	
	UFUNCTION(BlueprintCallable)
	void ApplyTheme(FTheme_Mc_Lf Theme, float BlurStrength, float BlacknessAmount, bool bAnimated);

	UFUNCTION(BlueprintCallable)
	FString GetDeviceTime();
};
