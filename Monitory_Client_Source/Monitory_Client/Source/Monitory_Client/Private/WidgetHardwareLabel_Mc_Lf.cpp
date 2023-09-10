// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHardwareLabel_Mc_Lf.h"


void UWidgetHardwareLabel_Mc_Lf::CacheHardwareLabel(UTextBlock* Label, UImage* ColorImage, UTextBlock* Value)
{
	LabelText = Label;
	ValueText = Value;
	ColorSeparatorImage = ColorImage;
}