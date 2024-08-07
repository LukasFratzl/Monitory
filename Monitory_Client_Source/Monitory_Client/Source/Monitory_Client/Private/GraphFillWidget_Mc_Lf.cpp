#include "GraphFillWidget_Mc_Lf.h"

#define LOCTEXT_NAMESPACE "UMG"

void UGraphFillWidget_Mc_Lf::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	GraphFillSlateWidget->SetBrush(&Brush);
}

void UGraphFillWidget_Mc_Lf::ReleaseSlateResources(bool bReleaseChildren)
{
	GraphFillSlateWidget.Reset();
}

#if WITH_EDITOR
const FText UGraphFillWidget_Mc_Lf::GetPaletteCategory()
{
	return LOCTEXT("Monitory Client", "Monitoring App Custom Widget");
}
#endif

TSharedRef<SWidget> UGraphFillWidget_Mc_Lf::RebuildWidget()
{
	GraphFillSlateWidget = SNew(SGraphFillWidget_Mc_Lf)
		.Brush(&Brush);
	return GraphFillSlateWidget.ToSharedRef();
}
