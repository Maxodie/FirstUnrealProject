// Fill out your copyright notice in the Description page of Project Settings.
#include "Blueprint/UserWidget.h"

#include "PlayerMovement.h"

#include "ShopPanel.h"

// Sets default values
AShopPanel::AShopPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool AShopPanel::SetPlayerMovement(APlayerMovement* playerMove_) {
	if (!IsValid(this->playerMove = playerMove_)) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error::SetPlayerMovement can't find playerMove_"));
		return false;
	}

	this->playerData = playerMove_->GetPlayerData();
	return true;
}

// Called when the game starts or when spawned
void AShopPanel::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(GetGameInstance())) {
		this->currentShopPanelUserWidget = CreateWidget<UUserWidget>(GetGameInstance(), this->userWidget);
		this->ActivePanel(false);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error::ShopPanel can't find gameInstance"));
		return;
	}
}

void AShopPanel::TogglePanel(bool forcedState, bool state) {
	if (forcedState) {
		if (state != this->isPanelActived)
			ActivePanel(state);
	}
	else {
		ActivePanel(!this->isPanelActived);
	}
}

void AShopPanel::ActivePanel(bool isActive) {
	if (isActive) {
		this->currentShopPanelUserWidget->AddToViewport();
	}
	else {
		this->currentShopPanelUserWidget->RemoveFromParent();
	}

	this->isPanelActived = isActive;
}

void AShopPanel::SellPlayerMineral() {
	this->playerData->UpdateMoney(this->playerData->GetCurretMineralAmount());
	this->playerData->UpdateMineralAmount(-this->playerData->GetCurretMineralAmount());
}

void AShopPanel::OnSellPlayerMineralIEvent() {
	this->SellPlayerMineral();
}