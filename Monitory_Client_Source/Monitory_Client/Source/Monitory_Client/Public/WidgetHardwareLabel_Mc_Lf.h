// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "WidgetHardwareLabel_Mc_Lf.generated.h"

/**
 * 
 */
UCLASS()
class MONITORY_CLIENT_API UWidgetHardwareLabel_Mc_Lf : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> LabelText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> ValueText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UImage> ColorSeparatorImage;
	
	UFUNCTION(BlueprintCallable)
	void CacheHardwareLabel(UTextBlock* Label, UImage* ColorImage, UTextBlock* Value);
	
};
