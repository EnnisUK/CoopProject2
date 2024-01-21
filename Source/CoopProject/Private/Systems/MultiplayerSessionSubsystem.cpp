// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/MultiplayerSessionSubsystem.h"

#include "FindSessionsCallbackProxy.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FindSessionsCallbackProxy.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerSessionSubsystem::UMultiplayerSessionSubsystem()
{
	M_CreateServerAfterDestroy = false;
	M_DestroyServerName = "";
	M_ServerNameToFind = "";
	M_SessionName = FName("Session Name");
}

void UMultiplayerSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	
	if (const IOnlineSubsystem* OnlineSubsystem =  IOnlineSubsystem::Get())
	{
		const FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
		PrintString(SubsystemName, FColor::Blue);

		M_SessionPtr =  OnlineSubsystem->GetSessionInterface();
		if (M_SessionPtr.IsValid())
		{
			M_SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionSubsystem::OnCreateSessionComplete);
			M_SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionSubsystem::OnDestroySessionComplete);
			M_SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerSessionSubsystem::OnFindSessionComplete);
			M_SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionSubsystem::OnJoinSessionComplete);
		}
	}
	
}

void UMultiplayerSessionSubsystem::Deinitialize()
{
	Super::Deinitialize();

	
}

void UMultiplayerSessionSubsystem::PrintString(const FString& Print, const FColor Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, Color, Print);
	}
	
}

void UMultiplayerSessionSubsystem::FindServer(const FString& ServerName)
{
	if (ServerName.IsEmpty())
	{
		PrintString("ServerName Cannot Be Empty", FColor::Red);
		M_ServerJoinDelegate.Broadcast(false);
		return;
	}

	M_SessionSearch = MakeShareable(new FOnlineSessionSearch());
	bool bIsLan = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		bIsLan = true;
	}
	M_SessionSearch->bIsLanQuery = bIsLan;
	M_SessionSearch->MaxSearchResults = 50;
	M_SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	PrintString("Looking For Session", FColor::Cyan);
	
	M_ServerNameToFind = ServerName;
	M_SessionPtr->FindSessions(0, M_SessionSearch.ToSharedRef());
}

void UMultiplayerSessionSubsystem::CreateServer(const FString& ServerName)
{
	if (ServerName.IsEmpty())
	{
		PrintString("Server Name Cannot Be Empty", FColor::Red);
		M_ServerCreateDelegate.Broadcast(false);
		return;
	}
	FNamedOnlineSession* ExistingSession = M_SessionPtr->GetNamedSession(M_SessionName);
	if (ExistingSession)
	{
		PrintString(FString::Printf(TEXT("Session Is Being Destroyed %s"), *M_SessionName.ToString()), FColor::Red);
		M_CreateServerAfterDestroy = true;
		M_DestroyServerName = ServerName;
		M_SessionPtr->DestroySession(M_SessionName);
		return;
	}

	FOnlineSessionSettings SessionSetting;
	
	SessionSetting.bIsDedicated = false;
	SessionSetting.bShouldAdvertise = M_bShouldAdvertise;
	SessionSetting.NumPublicConnections = 2;
	SessionSetting.bUseLobbiesIfAvailable = true;
	SessionSetting.bUsesPresence = true;
	SessionSetting.bAllowJoinViaPresence = true;
	SessionSetting.bAllowJoinInProgress = true;
	SessionSetting.bAllowInvites = true;
	
	bool bIsLan = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		bIsLan = true;
	}
	SessionSetting.bIsLANMatch = bIsLan;
	SessionSetting.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	M_SessionPtr->CreateSession(0, M_SessionName, SessionSetting);
	
}



void UMultiplayerSessionSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	M_ServerCreateDelegate.Broadcast(bWasSuccessful);

	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Orange, TEXT("Create Server Success"));

	if (bWasSuccessful == true)
	{
		FString DefaultPath = "/Game/ThirdPerson/Maps/ThirdPersonMap?listen";
		

		if (!M_MapString.IsEmpty())
		{
			DefaultPath =  FString::Printf(TEXT("%s?listen"), *M_MapString);
		}
		if (GetWorld()->ServerTravel(DefaultPath))
		{
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Orange, TEXT("Server Travel Success"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Orange, TEXT("Server Travel Failed"));
		}
		
		
	}
	else
	{
		PrintString("Session Did Not Complete", FColor::Red);
	}
}

void UMultiplayerSessionSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	PrintString("On Destroy Session Complete", FColor::Red);
	if (M_CreateServerAfterDestroy)
	{
		M_CreateServerAfterDestroy = false;
		CreateServer(M_DestroyServerName);
	}

	
}

void UMultiplayerSessionSubsystem::OnFindSessionComplete(bool bWasSuccessful)
{
	
	if (!bWasSuccessful) return;
	if (M_ServerNameToFind.IsEmpty()) return;

	TArray<FOnlineSessionSearchResult> Results = M_SessionSearch->SearchResults;
	FOnlineSessionSearchResult* CorrectResult = nullptr;
	
	if (Results.Num() > 0)
	{
		FString Msg = FString::Printf(TEXT("%d Sessions Found"), Results.Num());
		PrintString(Msg, FColor::Orange);

		for (FOnlineSessionSearchResult FoundServer : Results)
		{
			if (FoundServer.IsValid())
			{
				FString ServerName = "No-Name";
				FoundServer.Session.SessionSettings.Get(FName("SERVER_NAME"), ServerName);

				if (ServerName.Equals(M_ServerNameToFind))
				{
					CorrectResult = &FoundServer;
					break;
				}
			}
		}

		if (CorrectResult)
		{
			M_SessionPtr->JoinSession(0, M_SessionName, *CorrectResult);
		}
		else
		{
			M_ServerJoinDelegate.Broadcast(false);
			PrintString("Cound Not Find Server", FColor::Red);
			M_ServerNameToFind = "";
		}
	}
	else
	{
		M_ServerJoinDelegate.Broadcast(false);
		PrintString("0 Sessions Found", FColor::Red);
	}
}

void UMultiplayerSessionSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
	M_ServerJoinDelegate.Broadcast(JoinResult == EOnJoinSessionCompleteResult::Success);

	if (JoinResult == EOnJoinSessionCompleteResult::Success)
	{
		FString Address = "";
		
		if (bool Success =  M_SessionPtr->GetResolvedConnectString(M_SessionName,Address ))
		{
			if (APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController())
			{
				PlayerController->ClientTravel(Address, TRAVEL_Absolute);
			}
			
		}
		else
		{
			PrintString("GetResolvedConnectString returned false", FColor::Black);
		}
	}
	else
	{
		FString MSg = FString::Printf(TEXT("Error Code: %d"), static_cast<EOnJoinSessionCompleteResult::Type>(JoinResult));
		PrintString(MSg, FColor::Red);
	}
}
