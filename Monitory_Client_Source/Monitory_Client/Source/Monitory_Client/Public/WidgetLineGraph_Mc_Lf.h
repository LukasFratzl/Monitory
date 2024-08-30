// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Components/Widget.h"

#include "WidgetLineGraph_Mc_Lf.generated.h"

class MONITORY_CLIENT_API SGraphLineWidget_Mc_Lf : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGraphLineWidget_Mc_Lf)
		{
		}

		SLATE_ARGUMENT(FSlateBrush*, Brush)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	                      FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                      bool bParentEnabled) const override;

	void SetBrush(FSlateBrush* InBrush);

	void SetLinePoints(const TArray<FVector2f>& Points)
	{
		LinePoints = Points;
		const int32 NumPoints = Points.Num();
		LinePoints.AddUninitialized(NumPoints);
		int32 Index = 0;
		for (int32 i = NumPoints - 1; i >= 0; --i)
		{
			FVector2f PointA = Points[Index];
			if (Index)
			{
				PointA = Points[Index - 1];
			}
			FVector2f PointB = Points[Index];
			if (Index < NumPoints - 1)
			{
				PointB = Points[Index + 1];
			}
			FVector2f Direction = FVector2f(1, 0);
			if (PointA != PointB)
			{
				Direction = PointB - PointA;
			}
			const FQuat2f& Rotation = FQuat2f(FMath::DegreesToRadians(-90));
			constexpr int32 LineThickness = 3;
			const FVector2f& Border = Rotation.TransformVector(Direction).GetSafeNormal() * LineThickness;
			LinePoints[NumPoints + i] = Points[Index] + Border;
			Index++;
		}
	}

	const TArray<FVector2f>& GetLinePoints() const
	{
		return LinePoints;
	}

	FVector2f ParentPanelSize = FVector2f::UnitVector;

protected:
	FInvalidatableBrushAttribute Brush;

	TArray<FVector2f> LinePoints;
};


UCLASS()
class MONITORY_CLIENT_API UWidgetGraphLine_Mc_Lf : public UWidget
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	void SetLinePoints(const TArray<FVector2f>& Points)
	{
		if (GraphPointSlateWidget)
		{
			GraphPointSlateWidget->SetLinePoints(Points);
		}
		SynchronizeProperties();
	}

	int32 GetNumLinePoints() const
	{
		if (GraphPointSlateWidget)
		{
			return GraphPointSlateWidget->GetLinePoints().Num() / 2;
		}
		return 0;
	}

	FVector2f GetLinePointPosition(const int32 Index) const
	{
		if (GraphPointSlateWidget)
		{
			return GraphPointSlateWidget->GetLinePoints()[Index];
		}
		return FVector2f::ZeroVector;
	}

	void SetParentPanelSize(const FVector2f& PanelSize) const
	{
		if (GraphPointSlateWidget)
		{
			GraphPointSlateWidget->ParentPanelSize = PanelSize;
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	FSlateBrush Brush;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SGraphLineWidget_Mc_Lf> GraphPointSlateWidget;
};
