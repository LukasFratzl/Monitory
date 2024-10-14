// Fill out your copyright notice in the Description page of Project Settings.


#include "Monitory_Client/Public/WidgetMainMenu_Mc_Lf.h"
#include "DataTranslate_Mc_Lf.h"
#include "TcpClient_Mc_Lf.h"
#include "WidgetIPAddress_Mc_Lf.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBoxSlot.h"
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

			if (const TObjectPtr<UUserWidget> IPWidget = CreateWidget<UUserWidget>(GetWorld(), IPAddressLabel);
				IsValid(IPWidget))
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

void UWidgetMainMenu_Mc_Lf::CacheCanvasPanels(UCanvasPanel* CpuUtilization, UCanvasPanel* RamUtilization,
                                              UCanvasPanel* GpuUtilization, UCanvasPanel* GpuRamUtilization,
                                              UCanvasPanel* WattageCanvas, UCanvasPanel* TemperatureCanvas,
                                              UCanvasPanel* DriveUtilization, UCanvasPanel* NetUtilization,
                                              UCanvasPanel* IPPanel, UCanvasPanel* MonitoringPanel)
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

void UWidgetMainMenu_Mc_Lf::CacheBoxes(UVerticalBox* WattageParentContainer, UVerticalBox* TemperatureParentContainer,
                                       UVerticalBox* IPAddresses)
{
	WattageLayoutBox = WattageParentContainer;

	TemperatureLayoutBox = TemperatureParentContainer;

	IPAddressContainer = IPAddresses;
}

void UWidgetMainMenu_Mc_Lf::CacheTextBlocks(UTextBlock* CpuUtilizationTotal, UTextBlock* CpuClockTotal,
                                            UTextBlock* RamUtilizationPercent, UTextBlock* RamUtilizationGB,
                                            UTextBlock* RamUtilizationGB_50PercentGB,
                                            UTextBlock* RamUtilizationGB_100PercentGB, UTextBlock* GpuUtilizationTotal,
                                            UTextBlock* GpuClockTotal, UTextBlock* GpuRamUtilizationPercent,
                                            UTextBlock* GpuRamUtilizationGB,
                                            UTextBlock* GpuRamUtilizationGB_50PercentGB,
                                            UTextBlock* GpuRamUtilizationGB_100PercentGB,
                                            UTextBlock* WattageValue, UTextBlock* WattageValueMax,
                                            UTextBlock* WattageValue_50Percent, UTextBlock* WattageValue_100Percent,
                                            UTextBlock* TemperatureValue, UTextBlock* TemperatureValueMax,
                                            UTextBlock* TemperatureValue_50Percent,
                                            UTextBlock* TemperatureValue_100Percent, UTextBlock* DriveUtilizationTotal,
                                            UTextBlock* TimeNow_Server, UTextBlock* DateNow_Server,
                                            UTextBlock* TimeNow_Client, UTextBlock* DateNow_Client,
                                            UTextBlock* NetUpSpeedMax, UTextBlock* NetDownSpeedMax,
                                            UTextBlock* NetMaxSpeed_50Percent,
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

	TimeNowTextBlock_Server = TimeNow_Server;
	DateNowTextBlock_Server = DateNow_Server;

	TimeNowTextBlock_Client = TimeNow_Client;
	DateNowTextBlock_Client = DateNow_Client;

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
		bool bInitThisFrame = TickIPSelectionPanel(DeltaTime);

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
				if (const TObjectPtr<UUserWidget> IPWidget = CreateWidget<UUserWidget>(GetWorld(), IPAddressLabel);
					IsValid(IPWidget))
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

	if (IsValid(TimeNowTextBlock_Client))
	{
		TimeNowTextBlock_Client->SetText(FText::FromString(FDateTime::Now().ToString(TEXT("%H:%M"))));
	}

	if (IsValid(DateNowTextBlock_Client))
	{
		DateNowTextBlock_Client->SetText(FText::FromString(FDateTime::Now().ToString(TEXT("%d/%m/%Y"))));
	}

	// CPU -> Start
	ResetGraph(CpuUtilizationGraph);
	// CPU -> End

	// RAM -> Start
	ResetGraph(CpuRamUtilizationGraph);
	// RAM -> End

	// Gpu -> Start
	ResetGraph(GpuUtilizationGraph);

	// GPU RAM -> Start
	ResetGraph(GpuRamUtilizationGraph);
	// GPU RAM -> End
	// Gpu -> End

	// Wattage -> Start
	ResetGraph(WattageUtilizationGraph);
	// Wattage -> End

	// Temperature -> Start
	ResetGraph(TemperatureUtilizationGraph);
	// Temperature -> End

	// Drive -> Start
	ResetGraph(DriveUtilizationGraph);
	// Drive -> End

	// Net -> Start
	ResetGraph(NetUtilizationGraph);
	// Net -> End

	return bInitThisFrame;
}

void UWidgetMainMenu_Mc_Lf::TickMonitoringPanel(float DeltaTime)
{
	FString Data = "";
	ADataTranslate_Mc_Lf::PcData = FPCData_Mc_Lf();

	if (ATcpClient_Mc_Lf::bIsConnected)
	{
		Data = ATcpClient_Mc_Lf::LastTcpSocketData;
	}
	else
	{
		ATcpClient_Mc_Lf::LastTcpSocketData = "";
		// PcData = FPCData_Mc_Lf();
	}
	// if (ADataTranslate_Mc_Lf::LastPreviousTcpSocketData != Data || Data == "")
	// {
	// 	ADataTranslate_Mc_Lf::LastPreviousTcpSocketData = Data;
	// 	PcData = FPCData_Mc_Lf();
	// }

	ADataTranslate_Mc_Lf::CreatePCData(ADataTranslate_Mc_Lf::PcData, Data);

	if (!ADataTranslate_Mc_Lf::PcData.CpuLoadThreads.Num())
	{
		return;
	}

	const FLinearColor& HiddenFillAreaColor = FLinearColor::Transparent;

	// CPU -> Start
	FLinearColor CpuFillColor = FLinearColor::Red;
	CpuFillColor.A = 0.15f;
	AdvanceGraph(CpuUtilizationGraph, ADataTranslate_Mc_Lf::PcData.CpuLoadThreads, false, CpuFillColor,
	             CpuUtilizationCanvasPanel);

	AdvanceText(CpuUtilizationTotalTextBlock, ADataTranslate_Mc_Lf::PcData.CpuLoadTotal.GetCurrent(), EPrecisionPoint::Zero,
	            TEXT("{0} %"));
	AdvanceText(CpuClockTotalTextBlock, ADataTranslate_Mc_Lf::PcData.CpuClockSpeedTotal.GetCurrent() / 1000,
	            EPrecisionPoint::Two, TEXT("{0} GHz"));
	// CPU -> End

	// RAM -> Start
	FLinearColor CpuRamFillColor = ADataTranslate_Mc_Lf::PcData.CpuRamPercentage.Color;
	CpuRamFillColor.A = 0.15f;
	AdvanceGraph(CpuRamUtilizationGraph,
	             TArray<FDataMinMaxCurrent_Mc_Lf>{ADataTranslate_Mc_Lf::PcData.CpuRamPercentage}, false,
	             CpuRamFillColor,
	             CpuRamUtilizationCanvasPanel);

	AdvanceText(CpuRamUtilizationGBTextBlock, ADataTranslate_Mc_Lf::PcData.CpuRamUsed.GetCurrent(), EPrecisionPoint::Two,
	            TEXT("{0} GB"));
	AdvanceText(CpuRamUtilizationPercentageTextBlock, ADataTranslate_Mc_Lf::PcData.CpuRamPercentage.GetCurrent(),
	            EPrecisionPoint::Zero, TEXT("{0} %"));
	AdvanceText(CpuRamUtilizationGB_50PercentTextBlock, ADataTranslate_Mc_Lf::PcData.CpuMaxRam.GetCurrent() * 0.5,
	            EPrecisionPoint::One, TEXT("{0}"));
	AdvanceText(CpuRamUtilizationGB_100PercentTextBlock, ADataTranslate_Mc_Lf::PcData.CpuMaxRam.GetCurrent(),
	            EPrecisionPoint::One, TEXT("{0}"));
	// RAM -> End

	// Gpu -> Start
	FLinearColor GpuUtilFillColor = ADataTranslate_Mc_Lf::PcData.GpuLoadTotal.Color;
	GpuUtilFillColor.A = 0.15f;
	AdvanceGraph(GpuUtilizationGraph, TArray<FDataMinMaxCurrent_Mc_Lf>{ADataTranslate_Mc_Lf::PcData.GpuLoadTotal},
	             false, GpuUtilFillColor, GpuUtilizationCanvasPanel);

	AdvanceText(GpuUtilizationTotalTextBlock, ADataTranslate_Mc_Lf::PcData.GpuLoadTotal.GetCurrent(), EPrecisionPoint::Zero,
	            TEXT("{0} %"));
	AdvanceText(GpuClockTotalTextBlock, ADataTranslate_Mc_Lf::PcData.GpuClockSpeedTotal.GetCurrent() / 1000,
	            EPrecisionPoint::Two, TEXT("{0} GHz"));

	// GPU RAM -> Start
	FLinearColor GpuRamFillColor = ADataTranslate_Mc_Lf::PcData.GpuRamPercentage.Color;
	GpuRamFillColor.A = 0.15f;
	AdvanceGraph(GpuRamUtilizationGraph,
	             TArray<FDataMinMaxCurrent_Mc_Lf>{ADataTranslate_Mc_Lf::PcData.GpuRamPercentage}, false,
	             GpuRamFillColor,
	             GpuRamUtilizationCanvasPanel);

	AdvanceText(GpuRamUtilizationGBTextBlock, ADataTranslate_Mc_Lf::PcData.GpuRamUsed.GetCurrent(), EPrecisionPoint::Two,
	            TEXT("{0} GB"));
	AdvanceText(GpuRamUtilizationPercentageTextBlock, ADataTranslate_Mc_Lf::PcData.GpuRamPercentage.GetCurrent(),
	            EPrecisionPoint::Zero, TEXT("{0} %"));
	AdvanceText(GpuRamUtilizationGB_50PercentTextBlock, ADataTranslate_Mc_Lf::PcData.GpuMaxRam.GetCurrent() * 0.5,
	            EPrecisionPoint::One, TEXT("{0}"));
	AdvanceText(GpuRamUtilizationGB_100PercentTextBlock, ADataTranslate_Mc_Lf::PcData.GpuMaxRam.GetCurrent(),
	            EPrecisionPoint::One, TEXT("{0}"));
	// GPU RAM -> End
	// Gpu -> End

	// Wattage -> Start
	const FVector2D& MaxWattage = AdvanceGraph(WattageUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Wattage, true,
	                                           HiddenFillAreaColor,
	                                           WattageCanvasPanel);

	AdvanceText(WattageValueMaxTextBlock, MaxWattage.X, EPrecisionPoint::Zero, TEXT("{0} Max"));
	AdvanceText(WattageValueTextBlock, ADataTranslate_Mc_Lf::PcData.WattageTotalCurrent.GetCurrent(), EPrecisionPoint::Zero,
	            TEXT("{0} W"));
	AdvanceText(WattageValue_100PercentTextBlock, MaxWattage.Y * 1.25f, EPrecisionPoint::Zero, TEXT("{0}"));
	AdvanceText(WattageValue_50PercentTextBlock, MaxWattage.Y * 0.5 * 1.25f, EPrecisionPoint::Zero, TEXT("{0}"));

	AdvanceLabels(WattageUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Wattage, EPrecisionPoint::Zero,
	              WattageLayoutBox);
	// Wattage -> End


	// Temperature -> Start
	const FVector2D& MaxTemperature = AdvanceGraph(TemperatureUtilizationGraph,
	                                               ADataTranslate_Mc_Lf::PcData.Temperature, true, HiddenFillAreaColor,
	                                               TemperatureCanvasPanel);

	AdvanceText(TemperatureValueMaxTextBlock, MaxTemperature.Y, EPrecisionPoint::One, TEXT("{0} Max"));
	AdvanceText(TemperatureValueTextBlock, ADataTranslate_Mc_Lf::PcData.TemperatureMaxCurrent.GetCurrent(),
	            EPrecisionPoint::One, TEXT("{0} C"));
	AdvanceText(TemperatureValue_100PercentTextBlock, MaxTemperature.Y * 1.25f, EPrecisionPoint::One, TEXT("{0}"));
	AdvanceText(TemperatureValue_50PercentTextBlock, MaxTemperature.Y * 0.5 * 1.25f, EPrecisionPoint::One, TEXT("{0}"));

	AdvanceLabels(TemperatureUtilizationGraph, ADataTranslate_Mc_Lf::PcData.Temperature, EPrecisionPoint::One,
	              TemperatureLayoutBox);
	// Temperature -> End

	// Drive -> Start
	FLinearColor DriveFillColor = FLinearColor::Red;
	DriveFillColor.A = 0.15f;
	AdvanceGraph(DriveUtilizationGraph, ADataTranslate_Mc_Lf::PcData.DrivesLoad, false, DriveFillColor,
	             DriveUtilizationCanvasPanel);

	AdvanceText(DriveUtilizationTotalTextBlock, ADataTranslate_Mc_Lf::PcData.DrivesMaxLoad.GetCurrent(),
	            EPrecisionPoint::One, TEXT("{0} %"));
	// Drive -> End

	// Time -> Start
	if (IsValid(TimeNowTextBlock_Server))
	{
		TimeNowTextBlock_Server->SetText(FText::FromString(ADataTranslate_Mc_Lf::PcData.TimeNow.Name));
	}
	if (IsValid(DateNowTextBlock_Server))
	{
		DateNowTextBlock_Server->SetText(FText::FromString(ADataTranslate_Mc_Lf::PcData.DateNow.Name));
	}
	// Time -> End

	// Net -> Start
	FLinearColor NetFillColor = FLinearColor::Blue;
	NetFillColor.A = 0.15f;
	const FVector2D& MaxSpeed = AdvanceGraph(NetUtilizationGraph,
	                                         ADataTranslate_Mc_Lf::PcData.DownloadUploadSpeedsGraph, true, NetFillColor,
	                                         NetUtilizationCanvasPanel);

	AdvanceText(NetMaxSpeed_100PercentTextBlock, MaxSpeed.Y * 1.25f, EPrecisionPoint::Two, TEXT("{0}"));
	AdvanceText(NetMaxSpeed_50PercentTextBlock, MaxSpeed.Y * 0.5 * 1.25f, EPrecisionPoint::Two, TEXT("{0}"));

	AdvanceText(NetMaxDownSpeedTextBlock, ADataTranslate_Mc_Lf::PcData.DownloadMaxSpeed.GetCurrent(), EPrecisionPoint::Two,
	            TEXT("{0} MB/s"));
	if (IsValid(NetMaxDownSpeedTextBlock))
	{
		NetMaxDownSpeedTextBlock->SetColorAndOpacity(ADataTranslate_Mc_Lf::PcData.DownloadMaxSpeed.Color);
	}

	AdvanceText(NetMaxUpSpeedTextBlock, ADataTranslate_Mc_Lf::PcData.UploadMaxSpeed.GetCurrent(), EPrecisionPoint::Two,
	            TEXT("{0} MB/s"));
	if (IsValid(NetMaxUpSpeedTextBlock))
	{
		NetMaxUpSpeedTextBlock->SetColorAndOpacity(ADataTranslate_Mc_Lf::PcData.UploadMaxSpeed.Color);
	}

	// Net -> End
}

void UWidgetMainMenu_Mc_Lf::ResetGraph(FGraph_Mc_Lf& Graph)
{
	if (IsValid(Graph.FillArea.FillWidget))
	{
		Graph.FillArea.FillWidget->RemoveFromRoot();
		Graph.FillArea.FillWidget->RemoveFromParent();
		Graph.FillArea.FillWidget = nullptr;
	}
	if (IsValid(Graph.HighLine.Line))
	{
		Graph.HighLine.Line->RemoveFromRoot();
		Graph.HighLine.Line->RemoveFromParent();
		Graph.HighLine.Line = nullptr;
	}
	if (IsValid(Graph.LowLine.Line))
	{
		Graph.LowLine.Line->RemoveFromRoot();
		Graph.LowLine.Line->RemoveFromParent();
		Graph.LowLine.Line = nullptr;
	}
	for (FShapedLine_Mc_Lf& Line : Graph.Graph)
	{
		if (IsValid(Line.Line))
		{
			Line.Line->RemoveFromRoot();
			Line.Line->RemoveFromParent();
			Line.Line = nullptr;
		}
		if (IsValid(Line.Label))
		{
			Line.Label->RemoveFromRoot();
			Line.Label->RemoveFromParent();
			Line.Label = nullptr;
		}
	}
	Graph.Graph.Empty();

	FLinearColor FillColor = Graph.FillColor;
	FLinearColor HighLineColor = Graph.HighLineColor;
	FLinearColor LowLineColor = Graph.LowLineColor;
	FLinearColor LineColorOverride = Graph.LineColorOverride;

	Graph = FGraph_Mc_Lf();
	Graph.FillColor = FillColor;
	Graph.HighLineColor = HighLineColor;
	Graph.LowLineColor = LowLineColor;
	Graph.LineColorOverride = LineColorOverride;
}

void UWidgetMainMenu_Mc_Lf::InitGraph(FGraph_Mc_Lf& Graph, const int32 NumPoints, const int32 NumLines,
                                      const TObjectPtr<UCanvasPanel> CanvasPanel) const
{
	const FGeometry& Geometry = CanvasPanel->GetCachedGeometry();
	const FVector2f& CanvasPanelSize = FVector2f(USlateBlueprintLibrary::GetLocalSize(Geometry));

	if (!IsValid(Graph.FillArea.FillWidget))
	{
		Graph.FillArea.FillWidget = WidgetTree->ConstructWidget<UWidgetGraphFill_Mc_Lf>();
		CanvasPanel->AddChildToCanvas(Graph.FillArea.FillWidget);
		Cast<UCanvasPanelSlot>(Graph.FillArea.FillWidget->Slot)->SetZOrder(1);
		if (IsValid(Graph.FillMaterialOverride))
		{
			Graph.FillArea.FillWidget->Brush.SetResourceObject(Graph.FillMaterialOverride);
		}
		else
		{
			Graph.FillArea.FillWidget->Brush.SetResourceObject(GraphFillAreaMaterial);
		}
		Graph.FillArea.FillWidget->SetParentPanelSize(CanvasPanelSize);
		Graph.FillArea.FillWidget->SynchronizeProperties();
	}

	if (!IsValid(Graph.HighLine.Line))
	{
		Graph.HighLine.Line = WidgetTree->ConstructWidget<UWidgetGraphLine_Mc_Lf>();
		CanvasPanel->AddChildToCanvas(Graph.HighLine.Line);
		Cast<UCanvasPanelSlot>(Graph.HighLine.Line->Slot)->SetZOrder(3);
		Graph.HighLine.Line->Brush.SetResourceObject(GraphLinesMaterial);
		Graph.HighLine.Line->Brush.TintColor = Graph.HighLineColor;
		Graph.HighLine.Line->SynchronizeProperties();
	}

	TArray<FVector2f> HighLinePoints;
	HighLinePoints.Add(FVector2f::ZeroVector);
	HighLinePoints.Add(FVector2f(CanvasPanelSize.X, 0));
	Graph.HighLine.Line->SetLinePoints(HighLinePoints);
	Graph.HighLine.Line->SetParentPanelSize(CanvasPanelSize);

	if (!IsValid(Graph.LowLine.Line))
	{
		Graph.LowLine.Line = WidgetTree->ConstructWidget<UWidgetGraphLine_Mc_Lf>();
		CanvasPanel->AddChildToCanvas(Graph.LowLine.Line);
		Cast<UCanvasPanelSlot>(Graph.LowLine.Line->Slot)->SetZOrder(3);
		Graph.LowLine.Line->Brush.SetResourceObject(GraphLinesMaterial);
		Graph.LowLine.Line->Brush.TintColor = Graph.LowLineColor;
		Graph.LowLine.Line->SynchronizeProperties();
	}

	TArray<FVector2f> LowLinePoints;
	LowLinePoints.Add(FVector2f(0, CanvasPanelSize.Y));
	LowLinePoints.Add(CanvasPanelSize);
	Graph.LowLine.Line->SetLinePoints(LowLinePoints);
	Graph.LowLine.Line->SetParentPanelSize(CanvasPanelSize);

	Graph.CurrentCanvasSize = CanvasPanelSize;

	if (!Graph.Graph.Num())
	{
		for (FShapedLine_Mc_Lf& Line : Graph.Graph)
		{
			if (IsValid(Line.Line))
			{
				Line.Line->RemoveFromRoot();
				Line.Line->RemoveFromParent();
				Line.Line = nullptr;
			}
		}

		Graph.Graph.SetNum(NumLines);

		for (int32 i = 0; i < NumLines; ++i)
		{
			FShapedLine_Mc_Lf& Line = Graph.Graph[i];

			Line.Line = WidgetTree->ConstructWidget<UWidgetGraphLine_Mc_Lf>();
			CanvasPanel->AddChildToCanvas(Line.Line);
			Cast<UCanvasPanelSlot>(Line.Line->Slot)->SetZOrder(2);

			Line.Line->SetParentPanelSize(CanvasPanelSize);
			Line.Line->Brush.SetResourceObject(GraphLinesMaterial);

			Line.ValueHistory.Empty();
			TArray<FVector2f> Points;
			Points.SetNum(NumPoints);

			for (int32 p = 0; p < NumPoints; ++p)
			{
				FVector2f Location = Graph.CurrentCanvasSize;
				Location.X *= (static_cast<double>(p) / static_cast<double>(NumLines - 1));
				Points[p] = Location;
				Line.ValueHistory.Add(0.01);
			}

			Line.Line->SetLinePoints(Points);
		}
	}
}

// void UWidgetMainMenu_Mc_Lf::ResetLabels(FGraph_Mc_Lf& Graph)
// {
// 	const int32 NumGraphLines = Graph.Graph.Num();
// 	for (int32 i = 0; i < NumGraphLines; ++i)
// 	{
// 		FShapedLine_Mc_Lf& Line = Graph.Graph[i];
// 		if (IsValid(Line.Label))
// 		{
// 			Line.Label->RemoveFromParent();
// 		}
// 	}
// }

void UWidgetMainMenu_Mc_Lf::InitLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data,
                                       const TObjectPtr<UVerticalBox>& Parent) const
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

	const int32 NumGraphLines = Graph.Graph.Num();
	for (int32 i = 0; i < NumGraphLines; ++i)
	{
		FShapedLine_Mc_Lf& Line = Graph.Graph[i];
		bool bAddedLabel = false;
		if (!IsValid(Line.Label))
		{
			bAddedLabel = true;
			if (const TObjectPtr<UUserWidget> LabelWidget = CreateWidget<UUserWidget>(GetWorld(), HardwareLabel);
				IsValid(LabelWidget))
			{
				Line.Label = Cast<UWidgetHardwareLabel_Mc_Lf>(LabelWidget);
				const TObjectPtr<UVerticalBoxSlot> LabelSlot = Parent->AddChildToVerticalBox(Line.Label);

				if (IsValid(LabelSlot))
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

void UWidgetMainMenu_Mc_Lf::AdvanceLabels(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data,
                                          const EPrecisionPoint& Precision,
                                          const TObjectPtr<UVerticalBox>& Parent)
{
	if (!Data.Num())
	{
		return;
	}

	InitLabels(Graph, Data, Parent);

	// if (Data.Num() != Graph.Graph.Num())
	// {
	// 	ResetGraph(Graph);
	// 	return;
	// }

	const int32 NumGraphLines = Graph.Graph.Num();
	for (int32 i = 0; i < NumGraphLines; ++i)
	{
		if (Data.IsValidIndex(i))
		{
			const FShapedLine_Mc_Lf& Line = Graph.Graph[i];
			const FDataMinMaxCurrent_Mc_Lf& Value = Data[i];

			if (IsValid(Line.Label))
			{
				if (IsValid(Line.Label->ValueText))
				{
					FString Text;
					const double WantedValue = Value.GetCurrent();
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
}


FVector2D UWidgetMainMenu_Mc_Lf::AdvanceGraph(FGraph_Mc_Lf& Graph, const TArray<FDataMinMaxCurrent_Mc_Lf>& Data,
                                              bool bIsRelativeGraph, const FLinearColor& FillAreaColor,
                                              const TObjectPtr<UCanvasPanel> CanvasPanel) const
{
	if (!Data.Num())
	{
		return FVector2D::ZeroVector;
	}

	InitGraph(Graph, 100, Data.Num(), CanvasPanel);

	double MaxValuePerUnit = 0;
	double MaxValue = 0;
	const int32 NumGraphLines = Graph.Graph.Num();
	const int32 FullNumPoints = Graph.Graph[0].Line->GetNumLinePoints();
	for (int32 p = 1; p < FullNumPoints; ++p)
	{
		double MaxPointValue = 0;

		bool bIsLastIteration = p == FullNumPoints - 1;

		for (int32 i = 0; i < NumGraphLines; ++i)
		{
			if (!Data.IsValidIndex(i))
			{
				continue;
			}

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
				if (Data[i].GetCurrent() > MaxValuePerUnit)
				{
					MaxValuePerUnit = Data[i].GetCurrent();
				}

				MaxPointValue += Data[i].GetCurrent();
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

		if (!Data.IsValidIndex(i))
		{
			continue;
		}

		TArray<FVector2f> Points;
		Points.AddUninitialized(FullNumPoints);
		Line.ValueHistory.RemoveAt(0);

		const int32 PointMaxIndex = FullNumPoints - 1;

		for (int32 p = 0; p < PointMaxIndex; ++p)
		{
			FVector2f Location = Line.Line->GetLinePointPosition(p + 1);
			Location.X = Graph.CurrentCanvasSize.X * (static_cast<double>(p) / static_cast<double>(FullNumPoints - 1));
			if (bIsRelativeGraph)
			{
				const double Percentage = Line.ValueHistory[p] / MaxValuePerUnit;
				Location.Y = Graph.CurrentCanvasSize.Y - Graph.CurrentCanvasSize.Y * Percentage * 0.75f; // 0.75f for better view
			}
			Points[p] = Location;
		}

		FVector2f LastPointLocation = Graph.CurrentCanvasSize;
		if (bIsRelativeGraph)
		{
			const double Percentage = Data[i].GetCurrent() / MaxValuePerUnit;
			LastPointLocation.Y -= Graph.CurrentCanvasSize.Y * Percentage * 0.75f; // 0.75f for better view;
		}
		else
		{
			LastPointLocation.Y -= LastPointLocation.Y * Data[i].GetCurrent() * 0.01f;
		}
		Points.Last() = LastPointLocation;
		Line.ValueHistory.Add(Data[i].GetCurrent());

		if (Graph.bUseLineColorOverride)
		{
			Line.Line->Brush.TintColor = Graph.LineColorOverride;
		}
		else
		{
			Line.Line->Brush.TintColor = Data[i].Color;
		}
		Line.Line->SetParentPanelSize(Graph.CurrentCanvasSize);
		Line.Line->SetLinePoints(Points);
	}


	// Handle Fill Areas
	if (IsValid(Graph.FillArea.FillWidget))
	{
		TArray<FVector2f> FillPoints;
		for (int32 p = 1; p < FullNumPoints; ++p)
		{
			double MaxPointValue = 0;
			FVector2f BestPoint = FVector2f(0, 1); // 1 Up because of the intersection to ground line

			for (int32 i = 0; i < NumGraphLines; ++i)
			{
				FShapedLine_Mc_Lf& Line = Graph.Graph[i];
				if (Line.ValueHistory[p] >= MaxPointValue)
				{
					MaxPointValue = Line.ValueHistory[p];
					BestPoint = Line.Line->GetLinePointPosition(p);
					if (BestPoint.Y == Graph.CurrentCanvasSize.Y)
					{
						BestPoint.Y = Graph.CurrentCanvasSize.Y - 1;
					}
				}
			}

			FillPoints.Add(BestPoint);
		}
		Graph.FillArea.FillWidget->Brush.TintColor = Graph.FillColor;

		FillPoints.Add(Graph.CurrentCanvasSize);
		FillPoints.Add(FVector2f(0, Graph.CurrentCanvasSize.Y));

		Graph.FillArea.FillWidget->SetParentPanelSize(Graph.CurrentCanvasSize);
		Graph.FillArea.FillWidget->SetEdgePoints(FillPoints);
	}

	return FVector2D(MaxValue, MaxValuePerUnit);
}

void UWidgetMainMenu_Mc_Lf::AdvanceText(const TObjectPtr<UTextBlock> Text, const double Value,
                                        const EPrecisionPoint& Precision, const FString& FormatMessage)
{
	if (IsValid(Text))
	{
		FString Message;
		double WantedValue = Value;
		if (FMath::IsNaN(WantedValue))
		{
			WantedValue = 0.0;
		}
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
		const double ScaleFactor = FMath::Max(ViewportSize.X / TextureSize.X, ViewportSize.Y / TextureSize.Y);

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

	const int32 Index = FCString::Atoi(*DataArray[0]);
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
	if (const int32 Index = CachedThemes.FindLastByPredicate([&Theme](const FTheme_Mc_Lf& Other)
	{
		return Other.Background == Theme.Background;
	}); Index != INDEX_NONE)
	{
		FString Data = FString::Printf(TEXT("%s|"), *FString::FormatAsNumber(Index));
		Data += FString::Printf(TEXT("%f|"), BlurStrength);
		Data += FString::Printf(TEXT("%f|"), BlacknessAmount);
		Data += FString::Printf(TEXT("%d|"), (int32)bAnimated);

		// Add more settings -> It's currently without separator
		ADataTranslate_Mc_Lf::SaveDataToInternalStorage(Data, ADataTranslate_Mc_Lf::ThemeSettingsFileName);
	}
}

FString UWidgetMainMenu_Mc_Lf::GetDeviceTime()
{
	const auto& Time = FDateTime::Now();

	return Time.ToString();
}
