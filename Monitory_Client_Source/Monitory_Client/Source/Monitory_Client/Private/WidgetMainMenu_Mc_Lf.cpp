// Fill out your copyright notice in the Description page of Project Settings.


#include "Monitory_Client/Public/WidgetMainMenu_Mc_Lf.h"

#include "DataTranslate_Mc_Lf.h"
//#include "OpenGLDrv.h"
#include "TcpClient_Mc_Lf.h"
#include "WidgetIPAddress_Mc_Lf.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"

void UWidgetMainMenu_Mc_Lf::NativeConstruct()
{
	Super::NativeConstruct();

	// Here is where I typically bind delegates,
	// and set up default appearance
}

void UWidgetMainMenu_Mc_Lf::OnAddIPButtonPressed()
{
	if (!IsValid(IPAddressAddTextBox))
	{
		return;
	}
	const FString IPToAdd = IPAddressAddTextBox->GetText().ToString();
	if (!IPToAdd.IsEmpty())
	{
		const int32 NumAddresses = ADataTranslate_Mc_Lf::IPAddresses.Num();
		bool bContains = false;
		for (int32 i = NumAddresses - 1; i >= 0; --i)
		{
			if (ADataTranslate_Mc_Lf::IPAddresses[i] == IPToAdd)
			{
				bContains = true;
				break;
			}
		}
		if (!bContains)
		{
			ADataTranslate_Mc_Lf::IPAddresses.Add(IPToAdd);

			ADataTranslate_Mc_Lf::bChangedIPAddresses = true;
			FString Data = FString("");
			for (const FString& IPAddress : ADataTranslate_Mc_Lf::IPAddresses)
			{
				Data += FString::Printf(TEXT("%s|"), *IPAddress);
			}
			ADataTranslate_Mc_Lf::SaveDataToInternalStorage(Data, ADataTranslate_Mc_Lf::IPAddressesFileName);

			if (const TObjectPtr<UUserWidget> IPWidget = CreateWidget<UUserWidget>(GetWorld(), IPAddressLabel); IsValid(IPWidget))
			{
				const TObjectPtr<UWidgetIPAddress_Mc_Lf> IPAddressWidget = Cast<UWidgetIPAddress_Mc_Lf>(IPWidget);
				if (IsValid(IPAddressContainer))
				{
					IPAddressContainer->AddChildToVerticalBox(IPAddressWidget);
					if (IsValid(IPAddressWidget->IPAddressText))
					{
						IPAddressWidget->IPAddressText->SetText(FText::FromString(IPToAdd));
					}
				}
			}
		}
	}
}

void UWidgetMainMenu_Mc_Lf::CacheCanvasPanels(UCanvasPanel* CpuUtilization, UCanvasPanel* RamUtilization, UCanvasPanel* GpuUtilization, UCanvasPanel* GpuRamUtilization, UCanvasPanel* WattageCanvas, UCanvasPanel* TemperatureCanvas, UCanvasPanel* DriveUtilization, UCanvasPanel* NetUtilization, UCanvasPanel* IPPanel, UCanvasPanel* MonitoringPanel)
{
	CpuUtilizationCanvasPanel = CpuUtilization;

	CpuRamUtilizationCanvasPanel = RamUtilization;

	GpuUtilizationCanvasPanel = GpuUtilization;

	GpuRamUtilizationCanvasPanel = GpuRamUtilization;

	WattageCanvasPanel = WattageCanvas;

	TemperatureCanvasPanel = TemperatureCanvas;

	DriveUtilizationCanvasPanel = DriveUtilization;

	NetUtilizationCanvasPanel = NetUtilization;

	IPSelectionPanel_Full = IPPanel;
	HardwareMonitoringPanel_Full = MonitoringPanel;
}

void UWidgetMainMenu_Mc_Lf::CacheBoxes(UVerticalBox* WattageParentContainer, UVerticalBox* TemperatureParentContainer, UVerticalBox* IPAddresses)
{
	WattageLayoutBox = WattageParentContainer;

	TemperatureLayoutBox = TemperatureParentContainer;

	IPAddressContainer = IPAddresses;
}

void UWidgetMainMenu_Mc_Lf::CacheTextBlocks(UTextBlock* CpuUtilizationTotal, UTextBlock* CpuClockTotal, UTextBlock* RamUtilizationPercent, UTextBlock* RamUtilizationGB, UTextBlock* RamUtilizationGB_50PercentGB, UTextBlock* RamUtilizationGB_100PercentGB, UTextBlock* GpuUtilizationTotal, UTextBlock* GpuClockTotal, UTextBlock* GpuRamUtilizationPercent, UTextBlock* GpuRamUtilizationGB, UTextBlock* GpuRamUtilizationGB_50PercentGB, UTextBlock* GpuRamUtilizationGB_100PercentGB,
                                            UTextBlock* WattageValue, UTextBlock* WattageValueMax, UTextBlock* WattageValue_50Percent, UTextBlock* WattageValue_100Percent, UTextBlock* TemperatureValue, UTextBlock* TemperatureValueMax, UTextBlock* TemperatureValue_50Percent, UTextBlock* TemperatureValue_100Percent, UTextBlock* DriveUtilizationTotal, UTextBlock* TimeNow, UTextBlock* DateNow, UTextBlock* NetUpSpeedMax, UTextBlock* NetDownSpeedMax, UTextBlock* NetMaxSpeed_50Percent,
                                            UTextBlock* NetMaxSpeed_100Percent)
{
	CpuUtilizationTotalTextBlock = CpuUtilizationTotal;
	CpuClockTotalTextBlock = CpuClockTotal;

	CpuRamUtilizationPercentageTextBlock = RamUtilizationPercent;
	CpuRamUtilizationGBTextBlock = RamUtilizationGB;
	CpuRamUtilizationGB_50PercentTextBlock = RamUtilizationGB_50PercentGB;
	CpuRamUtilizationGB_100PercentTextBlock = RamUtilizationGB_100PercentGB;

	GpuClockTotalTextBlock = GpuClockTotal;
	GpuUtilizationTotalTextBlock = GpuUtilizationTotal;

	GpuRamUtilizationPercentageTextBlock = GpuRamUtilizationPercent;
	GpuRamUtilizationGBTextBlock = GpuRamUtilizationGB;
	GpuRamUtilizationGB_50PercentTextBlock = GpuRamUtilizationGB_50PercentGB;
	GpuRamUtilizationGB_100PercentTextBlock = GpuRamUtilizationGB_100PercentGB;


	WattageValueTextBlock = WattageValue;
	WattageValueMaxTextBlock = WattageValueMax;
	WattageValue_50PercentTextBlock = WattageValue_50Percent;
	WattageValue_100PercentTextBlock = WattageValue_100Percent;

	TemperatureValueTextBlock = TemperatureValue;
	TemperatureValueMaxTextBlock = TemperatureValueMax;
	TemperatureValue_50PercentTextBlock = TemperatureValue_50Percent;
	TemperatureValue_100PercentTextBlock = TemperatureValue_100Percent;

	DriveUtilizationTotalTextBlock = DriveUtilizationTotal;

	TimeNowTextBlock = TimeNow;
	DateNowTextBlock = DateNow;

	NetMaxDownSpeedTextBlock = NetDownSpeedMax;
	NetMaxUpSpeedTextBlock = NetUpSpeedMax;
	NetMaxSpeed_100PercentTextBlock = NetMaxSpeed_100Percent;
	NetMaxSpeed_50PercentTextBlock = NetMaxSpeed_50Percent;
}

void UWidgetMainMenu_Mc_Lf::CacheButtons(UButton* IpAddressAdd)
{
	IPAddressAddButton = IpAddressAdd;
}

void UWidgetMainMenu_Mc_Lf::CacheTextBoxes(UEditableTextBox* IpAddressAdd)
{
	IPAddressAddTextBox = IpAddressAdd;
}

void UWidgetMainMenu_Mc_Lf::CacheThemes(TArray<FTheme_Mc_Lf> Themes)
{
	CachedThemes = Themes;
}

void UWidgetMainMenu_Mc_Lf::TickComponent(float DeltaTime)
{
	//LastUpdateRateSeconds = UpdateRateSeconds;

	if (ATcpClient_Mc_Lf::bIsConnected)
	{
		TickMonitoringPanel(DeltaTime);

		if (IsValid(IPSelectionPanel_Full))
		{
			IPSelectionPanel_Full->SetVisibility(ESlateVisibility::Hidden);
		}
		if (IsValid(HardwareMonitoringPanel_Full))
		{
			HardwareMonitoringPanel_Full->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		const bool& bInitThisFrame = TickIPSelectionPanel(DeltaTime);

		if (!bInitThisFrame)
		{
			if (IsValid(IPSelectionPanel_Full))
			{
				IPSelectionPanel_Full->SetVisibility(ESlateVisibility::Visible);
			}
			if (IsValid(HardwareMonitoringPanel_Full))
			{
				HardwareMonitoringPanel_Full->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

bool UWidgetMainMenu_Mc_Lf::TickIPSelectionPanel(float DeltaTime)
{
	bool bInitThisFrame = false;
	if (ADataTranslate_Mc_Lf::bCachedIPAddresses)
	{
		ADataTranslate_Mc_Lf::bCachedIPAddresses = false;

		for (const FString& IPAddress : ADataTranslate_Mc_Lf::IPAddresses)
		{
			if (!IPAddress.IsEmpty())
			{
				if (const TObjectPtr<UUserWidget> IPWidget = CreateWidget<UUserWidget>(GetWorld(), IPAddressLabel); IsValid(IPWidget))
				{
					const TObjectPtr<UWidgetIPAddress_Mc_Lf> IPAddressWidget = Cast<UWidgetIPAddress_Mc_Lf>(IPWidget);
					if (IsValid(IPAddressContainer))
					{
						IPAddressContainer->AddChildToVerticalBox(IPAddressWidget);
						if (IsValid(IPAddressWidget->IPAddressText))
						{
							IPAddressWidget->IPAddressText->SetText(FText::FromString(IPAddress));
						}
					}
				}
			}
		}

		bInitThisFrame = true;
	}

	if (ADataTranslate_Mc_Lf::bChangedIPAddresses)
	{
		ADataTranslate_Mc_Lf::bChangedIPAddresses = false;
	}

	return bInitThisFrame;
}

void UWidgetMainMenu_Mc_Lf::TickMonitoringPanel(float DeltaTime)
{
	if (!ADataTranslate_Mc_Lf::PcData.CpuLoadThreads.Num())
	{
		return;
	}

	// CPU -> Start
	AdvanceGraph(CpuUtilizationGraph, ADataTranslate_Mc_Lf::PcData.CpuLoadThreads, false, CpuUtilizationCanvasPanel);

	AdvanceText(CpuUtilizationTotalTextBlock, ADataTranslate_Mc_Lf::PcData.CpuLoadTotal.Current, EPrecisionPoint::Zero, TEXT("{0} %"));
	AdvanceText(CpuClockTotalTextBlock, ADataTranslate_Mc_Lf::PcData.CpuClockSpeedTotal.Current / 1000, EPrecisionPoint::Two, TEXT("{0} GHz"));
	// CPU -> End

	// RAM -> Start
	AdvanceGraph(CpuRamUtilizationGraph, TArray<FDataMinMaxCurrent_Mc_Lf>{ADataTranslate_Mc_Lf::PcData.CpuRamPercentage}, false, CpuRamUtilizationCanvasPanel);

	AdvanceText(CpuRamUtilizationGBTextBlock, ADataTranslate_Mc_Lf::PcData.CpuRamUsed.Current, EPrecisionPoint::Two, TEXT("{0} GB"));
	AdvanceText(CpuRamUtilizationPercentageTextBlock, ADataTranslate_Mc_Lf::PcData.CpuRamPercentage.Current, EPrecisionPoint::Zero, TEXT("{0} %"));
	AdvanceText(CpuRamUtilizationGB_50PercentTextBlock, ADataTranslate_Mc_Lf::PcData.CpuMaxRam.Current * 0.5, EPrecisionPoint::One, TEXT("{0}"));
	AdvanceText(CpuRamUtilizationGB_100PercentTextBlock, ADataTranslate_Mc_Lf::PcData.CpuMaxRam.Current, EPrecisionPoint::One, TEXT("{0}"));
	// RAM -> End

	// Gpu -> Start
	AdvanceGraph(GpuUtilizationGraph, TArray<FDataMinMaxCurrent_Mc_Lf>{ADataTranslate_Mc_Lf::PcData.GpuLoadTotal}, false, GpuUtilizationCanvasPanel);

	AdvanceText(GpuUtilizationTotalTextBlock, ADataTranslate_Mc_Lf::PcData.GpuLoadTotal.Current, EPrecisionPoint::Zero, TEXT("{0} %"));
	AdvanceText(GpuClockTotalTextBlock, ADataTranslate_Mc_Lf::PcData.GpuClockSpeedTotal.Current / 1000, EPrecisionPoint::Two, TEXT("{0} GHz"));

	// GPU RAM -> Start
	AdvanceGraph(GpuRamUtilizationGraph, TArray<FDataMinMaxCurrent_Mc_Lf>{ADataTranslate_Mc_Lf::PcData.GpuRamPercentage}, false, GpuRamUtilizationCanvasPanel);

	AdvanceText(GpuRamUtilizationGBTextBlock, ADataTranslate_Mc_Lf::PcData.GpuRamUsed.Current, EPrecisionPoint::Two, TEXT("{0} GB"));
	AdvanceText(GpuRamUtilizationPercentageTextBlock, ADataTranslate_Mc_Lf::PcData.GpuRamPercentage.Current, EPrecisionPoint::Zero, TEXT("{0} %"));
	AdvanceText(GpuRamUtilizationGB_50PercentTextBlock, ADataTranslate_Mc_Lf::PcData.GpuMaxRam.Current * 0.5, EPrecisionPoint::One, TEXT("{0}"));
	AdvanceText(GpuRamUtilizationGB_100PercentTextBlock, ADataTranslate_Mc_Lf::PcData.GpuMaxRam.Current, EPrecisionPoint::One, TEXT("{0}"));
	// GPU RAM -> End
	// Gpu -> End

	// Wattage -> Start
	const FVector2D& MaxWattage = AdvanceGraph(WattageUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Wattage, true, WattageCanvasPanel);

	AdvanceText(WattageValueMaxTextBlock, MaxWattage.X, EPrecisionPoint::Zero, TEXT("{0} Max"));
	AdvanceText(WattageValueTextBlock, ADataTranslate_Mc_Lf::PcData.WattageTotalCurrent.Current, EPrecisionPoint::Zero, TEXT("{0} W"));
	AdvanceText(WattageValue_100PercentTextBlock, MaxWattage.Y, EPrecisionPoint::Zero, TEXT("{0}"));
	AdvanceText(WattageValue_50PercentTextBlock, MaxWattage.Y * 0.5, EPrecisionPoint::Zero, TEXT("{0}"));

	AdvanceLabels(WattageUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Wattage, EPrecisionPoint::Zero, WattageLayoutBox);
	// Wattage -> End


	// Temperature -> Start
	const FVector2D& MaxTemperature = AdvanceGraph(TemperatureUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Temperature, true, TemperatureCanvasPanel);

	AdvanceText(TemperatureValueMaxTextBlock, MaxTemperature.Y, EPrecisionPoint::One, TEXT("{0} Max"));
	AdvanceText(TemperatureValueTextBlock, ADataTranslate_Mc_Lf::PcData.TemperatureMaxCurrent.Current, EPrecisionPoint::One, TEXT("{0} C"));
	AdvanceText(TemperatureValue_100PercentTextBlock, MaxTemperature.Y, EPrecisionPoint::One, TEXT("{0}"));
	AdvanceText(TemperatureValue_50PercentTextBlock, MaxTemperature.Y * 0.5, EPrecisionPoint::One, TEXT("{0}"));

	AdvanceLabels(TemperatureUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Temperature, EPrecisionPoint::One, TemperatureLayoutBox);
	// Temperature -> End

	// Drive -> Start
	AdvanceGraph(DriveUtilizationGraph, ADataTranslate_Mc_Lf::PcData.DrivesLoad, false, DriveUtilizationCanvasPanel);

	AdvanceText(DriveUtilizationTotalTextBlock, ADataTranslate_Mc_Lf::PcData.DrivesMaxLoad.Current, EPrecisionPoint::One, TEXT("{0} %"));
	// Drive -> End

	// Time -> Start
	if (IsValid(TimeNowTextBlock))
	{
		TimeNowTextBlock->SetText(FText::FromString(ADataTranslate_Mc_Lf::PcData.TimeNow.Name));
	}
	if (IsValid(DateNowTextBlock))
	{
		DateNowTextBlock->SetText(FText::FromString(ADataTranslate_Mc_Lf::PcData.DateNow.Name));
	}
	// Time -> End

	// Net -> Start
	const FVector2D& MaxSpeed = AdvanceGraph(NetUtilizationGraph, ADataTranslate_Mc_Lf::PcData.DownloadUploadSpeedsGraph, true, NetUtilizationCanvasPanel);

	AdvanceText(NetMaxSpeed_100PercentTextBlock, MaxSpeed.Y, EPrecisionPoint::Two, TEXT("{0}"));
	AdvanceText(NetMaxSpeed_50PercentTextBlock, MaxSpeed.Y * 0.5, EPrecisionPoint::Two, TEXT("{0}"));

	AdvanceText(NetMaxDownSpeedTextBlock, ADataTranslate_Mc_Lf::PcData.DownloadMaxSpeed.Current, EPrecisionPoint::Two, TEXT("{0} MB/s"));
	if (IsValid(NetMaxDownSpeedTextBlock))
	{
		NetMaxDownSpeedTextBlock->SetColorAndOpacity(ADataTranslate_Mc_Lf::PcData.DownloadMaxSpeed.Color);
	}

	AdvanceText(NetMaxUpSpeedTextBlock, ADataTranslate_Mc_Lf::PcData.UploadMaxSpeed.Current, EPrecisionPoint::Two, TEXT("{0} MB/s"));
	if (IsValid(NetMaxUpSpeedTextBlock))
	{
		NetMaxUpSpeedTextBlock->SetColorAndOpacity(ADataTranslate_Mc_Lf::PcData.UploadMaxSpeed.Color);
	}

	// Net -> End
}

void UWidgetMainMenu_Mc_Lf::InitGraph(FGraph_Mc_Lf& Graph, const int32& NumPoints, const int32& NumLines, const TObjectPtr<UCanvasPanel> CanvasPanel) const
{
	const FGeometry& Geometry = CanvasPanel->GetCachedGeometry();

	//const FVector2D& CanvasCenter = PanelSlot->Padding.;
	//UE_LOG(LogTemp, Warning, TEXT("[Abs=%s, Size=%s, Left=%s]"), *USlateBlueprintLibrary::GetAbsoluteSize(Geometry).ToString(), *USlateBlueprintLibrary::GetLocalSize(Geometry).ToString(), *USlateBlueprintLibrary::GetLocalTopLeft(Geometry).ToString());

	const FVector2D& CanvasPanelSize = USlateBlueprintLibrary::GetLocalSize(Geometry);

	if (!IsValid(Graph.HighLine.Line))
	{
		Graph.HighLine.Line = WidgetTree->ConstructWidget<USplineWidget>();
		CanvasPanel->AddChildToCanvas(Graph.HighLine.Line);
	}

	Graph.HighLine.Line->RemoveAllSplinePoint(true);
	Graph.HighLine.Line->AddSplinePoint(FUMGSplinePoint(FVector2D::ZeroVector, FVector2D::ZeroVector), true);
	Graph.HighLine.Line->AddSplinePoint(FUMGSplinePoint(FVector2D(CanvasPanelSize.X, 0), FVector2D::ZeroVector), true);
	Graph.HighLine.Line->SetSplineType(EUMGSplineType::Linear);
	Graph.HighLine.Line->UpdateSpline();

	if (!IsValid(Graph.LowLine.Line))
	{
		Graph.LowLine.Line = WidgetTree->ConstructWidget<USplineWidget>();
		CanvasPanel->AddChildToCanvas(Graph.LowLine.Line);
	}

	Graph.LowLine.Line->RemoveAllSplinePoint(true);
	Graph.LowLine.Line->AddSplinePoint(FUMGSplinePoint(FVector2D(0, CanvasPanelSize.Y), FVector2D::ZeroVector), true);
	Graph.LowLine.Line->AddSplinePoint(FUMGSplinePoint(CanvasPanelSize, FVector2D::ZeroVector), true);
	Graph.LowLine.Line->SetSplineType(EUMGSplineType::Linear);
	Graph.HighLine.Line->UpdateSpline();

	Graph.CurrentCanvasSize = CanvasPanelSize;

	if (!Graph.Graph.Num())
	{
		for (const FShapedLine_Mc_Lf& Line : Graph.Graph)
		{
			if (IsValid(Line.Line))
			{
				Line.Line->RemoveFromParent();
			}
		}

		Graph.Graph.SetNum(NumLines);

		for (int32 i = 0; i < NumLines; ++i)
		{
			FShapedLine_Mc_Lf& Line = Graph.Graph[i];

			Line.Line = WidgetTree->ConstructWidget<USplineWidget>();
			CanvasPanel->AddChildToCanvas(Line.Line);

			Line.Line->SetSplineType(EUMGSplineType::Linear); // Might give it as option

			Line.Line->RemoveAllSplinePoint(true);
			Line.ValueHistory.Empty();

			for (int32 p = 0; p < NumPoints; ++p)
			{
				FVector2D Location = Graph.CurrentCanvasSize;
				Location.X *= (static_cast<double>(p) / static_cast<double>(NumLines - 1));
				Line.Line->AddSplinePoint(FUMGSplinePoint(Location, FVector2D::ZeroVector), true);
				Line.ValueHistory.Add(0);
			}

			Line.Line->UpdateSpline();
		}
	}
}

void UWidgetMainMenu_Mc_Lf::InitLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const TObjectPtr<UVerticalBox>& Parent) const
{
	if (!Data.Num())
	{
		return;
	}

	// bool bOneNotValid = false;
	// for (const FShapedLine_Mc_Lf& Line : Graph.Graph)
	// {
	// 	if (!IsValid(Line.Label))
	// 	{
	// 		bOneNotValid = true;
	// 		break;
	// 	}
	// }

	const int32& NumGraphLines = Graph.Graph.Num();
	for (int32 i = 0; i < NumGraphLines; ++i)
	{
		FShapedLine_Mc_Lf& Line = Graph.Graph[i];
		bool bAddedLabel = false;
		if (!IsValid(Line.Label))
		{
			bAddedLabel = true;
			if (const TObjectPtr<UUserWidget> LabelWidget = CreateWidget<UUserWidget>(GetWorld(), HardwareLabel); IsValid(LabelWidget))
			{
				Line.Label = Cast<UWidgetHardwareLabel_Mc_Lf>(LabelWidget);
				Parent->AddChildToVerticalBox(Line.Label);

				if (const TObjectPtr<UVerticalBoxSlot> LabelSlot = Cast<UVerticalBoxSlot>(Line.Label->Slot); IsValid(LabelSlot))
				{
					FMargin LabelPadding = LabelSlot->GetPadding();
					LabelPadding.Bottom = 5;
					LabelSlot->SetPadding(LabelPadding);
				}
			}
		}

		if (bAddedLabel)
		{
			if (IsValid(Line.Label->LabelText))
			{
				Line.Label->LabelText->SetText(FText::FromString(Data[i].Name));
			}

			if (IsValid(Line.Label->ColorSeparatorImage))
			{
				FSlateBrush Brust = Line.Label->ColorSeparatorImage->GetBrush();
				Brust.TintColor = Data[i].Color;
				Line.Label->ColorSeparatorImage->SetBrush(Brust);
			}	
		}
	}
}

void UWidgetMainMenu_Mc_Lf::AdvanceLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const EPrecisionPoint& Precision, const TObjectPtr<UVerticalBox>& Parent) const
{
	if (!Data.Num())
	{
		return;
	}

	InitLabels(Graph, Data, Parent);

	const int32& NumGraphLines = Graph.Graph.Num();
	for (int32 i = 0; i < NumGraphLines; ++i)
	{
		const FShapedLine_Mc_Lf& Line = Graph.Graph[i];
		const FDataMinMaxCurrent_Mc_Lf& Value = Data[i];

		if (IsValid(Line.Label))
		{
			if (IsValid(Line.Label->ValueText))
			{
				FString Text;
				const double& WantedValue = Value.Current;
				switch (Precision)
				{
				case EPrecisionPoint::One:
					Text = ADataTranslate_Mc_Lf::FormatDoubleWithOneDecimal(WantedValue);
					break;
				case EPrecisionPoint::Two:
					Text = ADataTranslate_Mc_Lf::FormatDoubleWithTwoDecimals(WantedValue);
					break;
				case EPrecisionPoint::Zero:
					Text = ADataTranslate_Mc_Lf::FormatDoubleWithoutDecimals(WantedValue);
					break;
				default:
					Text = ADataTranslate_Mc_Lf::FormatDoubleWithoutDecimals(WantedValue);
					break;
				}
				Line.Label->ValueText->SetText(FText::FromString(Text));
			}
		}
	}
}


FVector2D UWidgetMainMenu_Mc_Lf::AdvanceGraph(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data, const bool& bIsRelativeGraph, const TObjectPtr<UCanvasPanel> CanvasPanel) const
{
	if (!Data.Num())
	{
		return FVector2D::ZeroVector;
	}

	InitGraph(Graph, 100, Data.Num(), CanvasPanel);

	double MaxValuePerUnit = 0;
	double MaxValue = 0;
	const int32& NumGraphLines = Graph.Graph.Num();
	const int32& FullNumPoints = Graph.Graph[0].Line->GetNumberOfSplinePoints();
	for (int32 p = 1; p < FullNumPoints; ++p)
	{
		double MaxPointValue = 0;

		const bool& bIsLastIteration = p == FullNumPoints - 1;

		for (int32 i = 0; i < NumGraphLines; ++i)
		{
			FShapedLine_Mc_Lf& Line = Graph.Graph[i];
			if (!bIsLastIteration)
			{
				if (Line.ValueHistory[p] > MaxValuePerUnit)
				{
					MaxValuePerUnit = Line.ValueHistory[p];
				}

				MaxPointValue += Line.ValueHistory[p];
			}
			else
			{
				if (Data[i].Current > MaxValuePerUnit)
				{
					MaxValuePerUnit = Data[i].Current;
				}

				MaxPointValue += Data[i].Current;
			}
		}

		if (MaxPointValue > MaxValue)
		{
			MaxValue = MaxPointValue;
		}
	}

	for (int32 i = 0; i < NumGraphLines; ++i)
	{
		FShapedLine_Mc_Lf& Line = Graph.Graph[i];

		Line.Line->RemoveSplinePoint(0, true);
		Line.ValueHistory.RemoveAt(0);

		const int32& PointMaxIndex = Graph.Graph[i].Line->GetNumberOfSplinePoints();

		for (int32 p = 0; p < PointMaxIndex; ++p)
		{
			FVector2D Location = Line.Line->GetLocationAtSplinePoint(p, EUMGSplineCoordinateSpace::Local);
			Location.X = Graph.CurrentCanvasSize.X * (static_cast<double>(p) / static_cast<double>(FullNumPoints - 1));
			if (bIsRelativeGraph)
			{
				const double& Percentage = Line.ValueHistory[p] / MaxValuePerUnit;
				Location.Y = Graph.CurrentCanvasSize.Y - Graph.CurrentCanvasSize.Y * Percentage;
			}
			Line.Line->ChangeSplinePointAtIndex(FUMGSplinePoint(Location, FVector2D::ZeroVector), p, true);

			//UE_LOG(LogTemp, Warning, TEXT("Loc Old Points -> %s"), *Location.ToString());
		}

		FVector2D LastPointLocation = Graph.CurrentCanvasSize;
		if (bIsRelativeGraph)
		{
			const double& Percentage = Data[i].Current / MaxValuePerUnit;
			LastPointLocation.Y -= Graph.CurrentCanvasSize.Y * Percentage;
		}
		else
		{
			LastPointLocation.Y -= LastPointLocation.Y * Data[i].Current * 0.01f;
		}
		Line.Line->AddSplinePoint(FUMGSplinePoint(LastPointLocation, FVector2D::ZeroVector), true);
		Line.ValueHistory.Add(Data[i].Current);

		Line.Line->SplineInfo.TintColor = Data[i].Color;
		Line.Line->UpdateSpline();

		//UE_LOG(LogTemp, Warning, TEXT("Loc New Point -> %s"), *LastPointLocation.ToString());

		//FVector2D LocationTest = Line.Line->GetLocationAtSplinePoint(NumPoints, EUMGSplineCoordinateSpace::Local);

		//UE_LOG(LogTemp, Warning, TEXT("Loc Removed Point -> %s"), *LocationTest.ToString());
	}
	return FVector2D(MaxValue, MaxValuePerUnit);
}

void UWidgetMainMenu_Mc_Lf::AdvanceText(const TObjectPtr<UTextBlock> Text, const double& Value, const EPrecisionPoint& Precision, const FString& FormatMessage)
{
	if (IsValid(Text))
	{
		FString Message;
		const double& WantedValue = Value;
		switch (Precision)
		{
		case EPrecisionPoint::One:
			Message = ADataTranslate_Mc_Lf::FormatDoubleWithOneDecimal(WantedValue);
			break;
		case EPrecisionPoint::Two:
			Message = ADataTranslate_Mc_Lf::FormatDoubleWithTwoDecimals(WantedValue);
			break;
		case EPrecisionPoint::Zero:
			Message = ADataTranslate_Mc_Lf::FormatDoubleWithoutDecimals(WantedValue);
			break;
		default:
			Message = ADataTranslate_Mc_Lf::FormatDoubleWithoutDecimals(WantedValue);
			break;
		}
		//const FString TestString = TEXT("Test");
		Text->SetText(FText::FromString(FString::Format(*FormatMessage, {*Message})));
	}
}

void UWidgetMainMenu_Mc_Lf::FitBackgroundImageToScreen(UScaleBox* BgImage, const FVector2D TextureSize)
{
	if (!IsValid(BgImage))
	{
		return;
	}

	// Update the image's size
	if (const TObjectPtr<UCanvasPanelSlot> ImageSlot = Cast<UCanvasPanelSlot>(BgImage->Slot); IsValid(ImageSlot))
	{
		// Get the current viewport size
		const FVector2D& ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

		// Calculate the scaling factor to fit the image within the viewport while maintaining aspect ratio
		const double& ScaleFactor = FMath::Max(ViewportSize.X / TextureSize.X, ViewportSize.Y / TextureSize.Y);

		// Calculate the new size of the image
		const FVector2D& NewImageSize = TextureSize * ScaleFactor;

		FVector2D NewSize;
		if (TextureSize.X / TextureSize.Y > 1)
		{
			NewSize.Y = NewImageSize.Y; //FMath::Max(NewImageSize.Y, NewImageSize.X);
			NewSize.X = 10000;
		}
		else
		{
			NewSize.X = NewImageSize.X; //FMath::Max(NewImageSize.X, ViewportSize.Y);
			NewSize.Y = 10000;
		}

		if (ImageSlot->GetSize() != NewSize)
		{
			ImageSlot->SetSize(NewSize);
		}
	}
}

FTheme_Mc_Lf UWidgetMainMenu_Mc_Lf::LoadTheme(float& Blur, float& Blackness, bool& bAnimations)
{
	const FString Data = ADataTranslate_Mc_Lf::ReadDataFromInternalStorage(ADataTranslate_Mc_Lf::ThemeSettingsFileName);

	Blur = 1;
	Blackness = 0.25f;
	bAnimations = false;

	if (Data.IsEmpty())
	{
		constexpr int32 FallbackIndex = 1;
		if (CachedThemes.IsValidIndex(FallbackIndex))
		{
			return CachedThemes[FallbackIndex];
		}
		return FTheme_Mc_Lf();
	}

	TArray<FString> DataArray;
	Data.ParseIntoArray(DataArray, TEXT("|"), false);

	const int32& Index = FCString::Atoi(*DataArray[0]);
	if (DataArray.IsValidIndex(1) && DataArray.IsValidIndex(2) && DataArray.IsValidIndex(3))
	{
		Blur = FCString::Atof(*DataArray[1]);
		Blackness = FCString::Atof(*DataArray[2]);
		bAnimations = (bool)FCString::Atoi(*DataArray[3]);
	}

	if (CachedThemes.IsValidIndex(Index))
	{
		return CachedThemes[Index];
	}
	return FTheme_Mc_Lf();
}

void UWidgetMainMenu_Mc_Lf::ApplyTheme(FTheme_Mc_Lf Theme, float BlurStrength, float BlacknessAmount, bool bAnimated)
{
	if (const int32& Index = CachedThemes.FindLastByPredicate([&Theme](const FTheme_Mc_Lf& Other) { return Other.Background == Theme.Background; }); Index != INDEX_NONE)
	{
		FString Data = FString::Printf(TEXT("%s|"), *FString::FormatAsNumber(Index));
		Data += FString::Printf(TEXT("%f|"), BlurStrength);
		Data += FString::Printf(TEXT("%f|"), BlacknessAmount);
		Data += FString::Printf(TEXT("%d|"), (int32)bAnimated);
		
		// Add more settings -> It's currently without separator
		ADataTranslate_Mc_Lf::SaveDataToInternalStorage(Data, ADataTranslate_Mc_Lf::ThemeSettingsFileName);
	}
}
