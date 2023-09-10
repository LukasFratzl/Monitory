// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetIPAddress_Mc_Lf.h"

#include "DataTranslate_Mc_Lf.h"
#include "Blueprint/WidgetTree.h"

void UWidgetIPAddress_Mc_Lf::OnDeleteButtonPressed()
{
	if (!IsValid(IPAddressText))
	{
		return;
	}
	const FString IPToRemove = IPAddressText->GetText().ToString();
	const int32 NumAddresses = ADataTranslate_Mc_Lf::IPAddresses.Num();
	for (int32 i = NumAddresses - 1; i >= 0; --i)
	{
		if (ADataTranslate_Mc_Lf::IPAddresses[i] == IPToRemove)
		{
			ADataTranslate_Mc_Lf::IPAddresses.RemoveAt(i);
		}
	}
	if (NumAddresses != ADataTranslate_Mc_Lf::IPAddresses.Num())
	{
		ADataTranslate_Mc_Lf::bChangedIPAddresses = true;
		FString Data = FString("");
		for (const FString& IPAddress : ADataTranslate_Mc_Lf::IPAddresses)
		{
			Data += FString::Printf(TEXT("%s|"), *IPAddress);
		}
		ADataTranslate_Mc_Lf::SaveDataToInternalStorage(Data, ADataTranslate_Mc_Lf::IPAddressesFileName);
	}
	
	this->RemoveFromParent();
}


void UWidgetIPAddress_Mc_Lf::CacheIPAddressLabel(UTextBlock* IPAddress, UButton* Delete)
{
	IPAddressText = IPAddress;
	DeleteButton = Delete;
}