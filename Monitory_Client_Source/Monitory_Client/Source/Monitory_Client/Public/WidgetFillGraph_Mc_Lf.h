// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Components/Widget.h"

#include "WidgetFillGraph_Mc_Lf.generated.h"

class MONITORY_CLIENT_API SGraphFillWidget_Mc_Lf : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGraphFillWidget_Mc_Lf)
	{}
	SLATE_ARGUMENT(FSlateBrush*, Brush)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
						  FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
						  bool bParentEnabled) const override;

	void SetBrush(FSlateBrush* InBrush);

	void SetEdgePoints(const TArray<FVector2f>& Points)
	{
		EdgePoints = Points;
	}

	FVector2f ParentPanelSize = FVector2f::UnitVector;

protected:
	FInvalidatableBrushAttribute Brush;

	TArray<FVector2f> EdgePoints;
};


UCLASS()
class MONITORY_CLIENT_API UWidgetGraphFill_Mc_Lf : public UWidget
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	void SetEdgePoints(const TArray<FVector2f>& Points)
	{
		if (GraphFillSlateWidget)
		{
			GraphFillSlateWidget->SetEdgePoints(Points);
		}
		SynchronizeProperties();
	}

	void SetParentPanelSize(const FVector2f& PanelSize) const
	{
		if (GraphFillSlateWidget)
		{
			GraphFillSlateWidget->ParentPanelSize = PanelSize;
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	FSlateBrush Brush;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SGraphFillWidget_Mc_Lf> GraphFillSlateWidget;
};
