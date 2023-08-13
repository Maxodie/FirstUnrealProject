// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInfosPanel.h"

// Sets default values
ABuildingInfosPanel::ABuildingInfosPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABuildingInfosPanel::BeginPlay() {
	Super::BeginPlay();

	if (IsValid(GetGameInstance())) {
		currentPanelWidget = CreateWidget<UUserWidget>(GetGameInstance(), this->userWidget);
		this->ActivePanel(false);
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error can't find gameInstance"));
		return;
	}
}

void ABuildingInfosPanel::TogglePanel(bool forcedState, bool state) {
	if (forcedState) {
		if (state != this->isPanelActived)
			ActivePanel(state);
	} else {
		ActivePanel(!this->isPanelActived);
	}
}

void ABuildingInfosPanel::ActivePanel(bool isActive) {
	if (isActive) {
		this->currentPanelWidget->AddToViewport();
	}
	else {
		this->currentPanelWidget->RemoveFromParent();
	}

	this->isPanelActived = isActive;
}
