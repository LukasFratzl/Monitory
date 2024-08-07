#include "SGraphFillWidget_Mc_Lf.h"
#include "SlateOptMacros.h"
#include "CompGeom/PolygonTriangulation.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGraphFillWidget_Mc_Lf::Construct(const FArguments& InArgs)
{
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SGraphFillWidget_Mc_Lf::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	const FPaintGeometry& PaintGeometry = AllottedGeometry.ToPaintGeometry();
	PaintGeometry.CommitTransformsIfUsingLegacyConstructor();
	const FSlateRenderTransform& SlateRenderTransform = PaintGeometry.GetAccumulatedRenderTransform();

	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	FLinearColor LinearColor = InWidgetStyle.GetColorAndOpacityTint() * SlateBrush->GetTint(InWidgetStyle);
	FColor FinalColorAndOpacity = LinearColor.ToFColor(true);

	const int NumPoints = EdgePoints.Num();
	TArray<FSlateVertex> Vertices;

	TArray<UE::Geometry::FIndex3i> Triangles;
	PolygonTriangulation::TriangulateSimplePolygon(EdgePoints, Triangles, true);

	for (int32 Index = 0; Index < NumPoints; Index++)
	{
		FSlateVertex Vertex = FSlateVertex();
		Vertex.Color = FinalColorAndOpacity;
		Vertex.Position = SlateRenderTransform.TransformPoint(EdgePoints[Index]);

		FVector2f UV0 = FVector2f::ZeroVector;
		if (ParentPanelSize.X > 0.0f && ParentPanelSize.Y > 0.0f)
		{
			UV0 = EdgePoints[Index] / ParentPanelSize;
		}
		Vertex.TexCoords[0] = UV0.X;
		Vertex.TexCoords[1] = UV0.Y;

		Vertices.Add(Vertex);
	}

	TArray<SlateIndex> Indices;
	for (int32 Index = 0; Index < Triangles.Num(); Index++)
	{
		Indices.Add(Triangles[Index].A);
		Indices.Add(Triangles[Index].B);
		Indices.Add(Triangles[Index].C);
	}


	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle( *SlateBrush );
	FSlateDrawElement::MakeCustomVerts(
        OutDrawElements,
        LayerId,
        Handle,
        Vertices,
        Indices,
        nullptr,
        0,
        0
    );
	return LayerId;
}

void SGraphFillWidget_Mc_Lf::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

