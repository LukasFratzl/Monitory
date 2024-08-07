#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

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
