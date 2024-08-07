// Fill out your copyright notice in the Description page of Project Settings.


#include "WebRequest_Mc_Lf.h"

#include "DataTranslate_Mc_Lf.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


// Sets default values
AWebRequest_Mc_Lf::AWebRequest_Mc_Lf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 500;
}

// Called when the game starts or when spawned
void AWebRequest_Mc_Lf::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWebRequest_Mc_Lf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DownloadAppVersion();
}

void AWebRequest_Mc_Lf::DownloadAppVersion() const
{
	// Create an HTTP request
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL("https://lukas-fratzl.com/Monitory/Version.txt");

	// Set up a lambda to handle the response
	HttpRequest->OnProcessRequestComplete().BindLambda([this](const FHttpRequestPtr& Request, const FHttpResponsePtr& Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			const int32 StatusCode = Response->GetResponseCode();
			const FString& Content = Response->GetContentAsString();

			const FString& ProjectVersion = ADataTranslate_Mc_Lf::GetAppVersion();
			
			bIsUpdateAvailable = ProjectVersion != Content;
			if (bIsUpdateAvailable)
			{
				UE_LOG(LogTemp, Display, TEXT("Update %s available, current version is -> %s"), *Content, *ProjectVersion);

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Update %s available, current version is -> %s"), *Content, *ProjectVersion));
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Client Version %s up to date"), *Content);
			}
		}
		else
		{
			// Handle the error
			UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
		}
	});

	// Send the request
	HttpRequest->ProcessRequest();
}

