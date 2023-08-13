// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManager.h"

// Sets default values
ABuildingManager::ABuildingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABuildingManager::BeginPlay()
{
	Super::BeginPlay();

	this->playerMove = Cast<APlayerMovement>(GetParentActor());

	if (!IsValid(this->playerMove)) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error::BuildingManager can't find PlayerMovement"));
		return;
	}
	
	this->playerData = this->playerMove->GetPlayerData();
}

//To sell a building---
void ABuildingManager::SellBuilding(ABuilding* building) {
	if (!this->playerData->UpdateMoney(building->GetSellPrice())) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You don't have enought of money to sell this building"));
	}

	building->Destroy();
	building->GetCurrentBuildingInfosPanel()->TogglePanel(true, false);
}
//----

void ABuildingManager::OnSellBuildingIEvent() {
	this->SellBuilding(this->playerMove->GetCurrentBuilding());
}

//To transport the minerals from the building to the player
void ABuildingManager::TransportMineralsToPlayer(AminingBuilding* building) {
	this->playerData->UpdateMineralAmount(building->GetCurrentMinerals());
	building->UpdateCurrentMinerals(-building->GetCurrentMinerals());
}

void ABuildingManager::OnTransportMineralsToPlayerIEvent() {
	this->TransportMineralsToPlayer(this->playerMove->GetCurrentMiningBuilding());
}
//----