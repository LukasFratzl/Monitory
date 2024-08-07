#pragma once

#include "CoreMinimal.h"


#include "SGraphFillWidget_Mc_Lf.h"
#include "Components/Widget.h"
#include "GraphFillWidget_Mc_Lf.generated.h"

UCLASS()
class MONITORY_CLIENT_API UGraphFillWidget_Mc_Lf : public UWidget
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

	void SetParentPanelSize(const FVector2D& PanelSize) const
	{
		if (GraphFillSlateWidget)
		{
			GraphFillSlateWidget->ParentPanelSize = FVector2f(PanelSize);
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
