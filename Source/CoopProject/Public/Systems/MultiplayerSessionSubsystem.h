// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Widgets/SWidget.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "MultiplayerSessionSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerCreateDelegate, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerJoinDelegate, bool, bWasSuccessful);

/**
 * 
 */


UCLASS()
class COOPPROJECT_API UMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	static void PrintString(const FString& Print, const FColor Color);


		//Variables

	// Session Interface
	IOnlineSessionPtr M_SessionPtr;

	// Should Reopen server after destroying
	UPROPERTY(BlueprintReadOnly)
	bool M_CreateServerAfterDestroy;

	// Name of destroyed server
	FString M_DestroyServerName;

	// Search Result for servers
	TSharedPtr<FOnlineSessionSearch> M_SessionSearch;

	FString M_ServerNameToFind;

	// Name of Session to Join
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName M_SessionName;

	UPROPERTY(BlueprintAssignable)
	FServerCreateDelegate M_ServerCreateDelegate;

	UPROPERTY(BlueprintAssignable)
	FServerJoinDelegate M_ServerJoinDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(DisplayName = SelectedMapString))
	FString M_MapString;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Open?"))
	bool M_bShouldAdvertise = true;
	

	
		//Functions

	UFUNCTION(BlueprintCallable)
	void FindServer(const FString& ServerName);

	UFUNCTION(BlueprintCallable)
	void CreateServer(const FString& ServerName);


	// Delegates Functions
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);


	
};
