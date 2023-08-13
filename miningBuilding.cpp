// Fill out your copyright notice in the Description page of Project Settings.


#include "miningBuilding.h"

// Sets default values
AminingBuilding::AminingBuilding() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

//Getters
float AminingBuilding::GetCurrentMinerals() {
	return this->currentMineralAmount;
}

//Setters
bool AminingBuilding::UpdateCurrentMinerals(float amount) {
	if (this->currentMineralAmount + amount < 0.f) {
		return false;
	}

	this->currentMineralAmount += amount;

	return true;
}

// Called when the game starts or when spawned
void AminingBuilding::BeginPlay() {
	Super::BeginPlay();
	
	float timer = 1 / this->miningSpeed;
	GetWorld()->GetTimerManager().SetTimer(miningTimerHandle, this, &AminingBuilding::OnAddMineral, timer, true);
}

void AminingBuilding::OnAddMineral() {
	this->currentMineralAmount ++;
}
