// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTranslate_Mc_Lf.h"
#include "MediaSource.h"
#include "SplineWidget.h"
#include "WidgetHardwareLabel_Mc_Lf.h"
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
	TObjectPtr<USplineWidget> Line;
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
struct MONITORY_CLIENT_API FGraph_Mc_Lf
{
	GENERATED_BODY()

	FGraph_Mc_Lf(){}
	~FGraph_Mc_Lf(){}

	UPROPERTY(EditAnywhere)
	TArray<FShapedLine_Mc_Lf> Graph;

	UPROPERTY(EditAnywhere)
	FStraightLine_Mc_Lf HighLine;

	UPROPERTY(EditAnywhere)
	FStraightLine_Mc_Lf LowLine;

	UPROPERTY(EditAnywhere)
	FStraightLine_Mc_Lf AverageLine;

	// UPROPERTY(EditAnywhere)
	// int32 NumGraphLines = 1;

	UPROPERTY(EditAnywhere)
	FVector2D CurrentCanvasSize = FVector2D::ZeroVector;
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

	//double UpdateRateRuntime = 0;

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
	TObjectPtr<UTextBlock> TimeNowTextBlock;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> DateNowTextBlock;

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

	UFUNCTION(BlueprintCallable)
	void OnAddIPButtonPressed();
	

	UFUNCTION(BlueprintCallable)
	void CacheCanvasPanels(UCanvasPanel* CpuUtilization, UCanvasPanel* RamUtilization, UCanvasPanel* GpuUtilization, UCanvasPanel* GpuRamUtilization, UCanvasPanel* WattageCanvas, UCanvasPanel* TemperatureCanvas, UCanvasPanel* DriveUtilization, UCanvasPanel* NetUtilization, UCanvasPanel* IPPanel, UCanvasPanel* MonitoringPanel);

	UFUNCTION(BlueprintCallable)
	void CacheBoxes(UVerticalBox* WattageParentContainer, UVerticalBox* TemperatureParentContainer, UVerticalBox* IPAddresses);

	UFUNCTION(BlueprintCallable)
	void CacheTextBlocks(UTextBlock* CpuUtilizationTotal, UTextBlock* CpuClockTotal, UTextBlock* RamUtilizationPercent, UTextBlock* RamUtilizationGB, UTextBlock* RamUtilizationGB_50PercentGB, UTextBlock* RamUtilizationGB_100PercentGB, UTextBlock* GpuUtilizationTotal, UTextBlock* GpuClockTotal, UTextBlock* GpuRamUtilizationPercent, UTextBlock* GpuRamUtilizationGB, UTextBlock* GpuRamUtilizationGB_50PercentGB, UTextBlock* GpuRamUtilizationGB_100PercentGB, UTextBlock* WattageValue, UTextBlock* WattageValueMax, UTextBlock* WattageValue_50Percent, UTextBlock* WattageValue_100Percent, UTextBlock* TemperatureValue, UTextBlock* TemperatureValueMax, UTextBlock* TemperatureValue_50Percent, UTextBlock* TemperatureValue_100Percent, UTextBlock* DriveUtilizationTotal, UTextBlock* TimeNow, UTextBlock* DateNow, UTextBlock* NetUpSpeedMax, UTextBlock* NetDownSpeedMax, UTextBlock* NetMaxSpeed_50Percent, UTextBlock* NetMaxSpeed_100Percent);

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


	void InitGraph(FGraph_Mc_Lf& Graph, const int32& NumPoints, const int32& NumLines, const TObjectPtr<UCanvasPanel> CanvasPanel) const;

	void InitLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const TObjectPtr<UVerticalBox>& Parent) const;
	void AdvanceLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const EPrecisionPoint& Precision, const TObjectPtr<UVerticalBox>& Parent) const;

	FVector2D AdvanceGraph(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const bool& bIsRelativeGraph, const TObjectPtr<UCanvasPanel> CanvasPanel) const;
	static void AdvanceText(const TObjectPtr<UTextBlock> Text, const double& Value, const EPrecisionPoint& Precision, const FString& FormatMessage);

	UFUNCTION(BlueprintCallable)
	void FitBackgroundImageToScreen(UScaleBox* BgImage, const FVector2D TextureSize);

	UFUNCTION(BlueprintCallable)
	FTheme_Mc_Lf LoadTheme(float& Blur, float& Blackness);
	
	UFUNCTION(BlueprintCallable)
	void ApplyTheme(FTheme_Mc_Lf Theme, float BlurStrength, float BlacknessAmount);
};
