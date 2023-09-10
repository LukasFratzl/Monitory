// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WidgetIPAddress_Mc_Lf.generated.h"

/**
 * 
 */
UCLASS()
class MONITORY_CLIENT_API UWidgetIPAddress_Mc_Lf : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UButton> DeleteButton;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextBlock> IPAddressText;

	UFUNCTION(BlueprintCallable)
	void OnDeleteButtonPressed();

	UFUNCTION(BlueprintCallable)
	void CacheIPAddressLabel(UTextBlock* IPAddress, UButton* Delete);
};
