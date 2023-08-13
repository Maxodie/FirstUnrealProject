// Fill out your copyright notice in the Description page of Project Settings.
#include "Blueprint/UserWidget.h"

#include "PlayerMovement.h"
#include "PlayerData.h"

#include "PlayerStatsUIManager.h"

// Sets default values
APlayerStatsUIManager::APlayerStatsUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlayerStatsUIManager::BeginPlay()
{
	Super::BeginPlay();
	
	//Create canvas items
	if (IsValid(GetGameInstance())) {
		this->currentPlayerStatsUserWidget = CreateWidget<UUserWidget>(GetGameInstance(), this->userWidget);
		this->currentPlayerStatsUserWidget->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error::PlayerStatsUIManager can't find gameInstance"));
		return;
	}

	Cast<APlayerMovement>(GetParentActor())->GetPlayerData()->SetPlayerStatsUIManager(this);
}