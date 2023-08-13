// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Building.h"

#include "miningBuilding.generated.h"

UCLASS()
class GESTIONGAME_API AminingBuilding : public ABuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AminingBuilding();

	//Getters
	float GetCurrentMinerals();

	//Updaters can't go under 0.f
	bool UpdateCurrentMinerals(float amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//event called by a timer to add a mineral
	UFUNCTION()
		void OnAddMineral();

	//number of mineral each seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gestion")
		float miningSpeed = 0.f;

	FTimerHandle miningTimerHandle;

private:
	float currentMineralAmount = 0.f;
};
