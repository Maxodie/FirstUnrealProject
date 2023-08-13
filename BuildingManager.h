// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PlayerMovement.h"
#include "miningBuilding.h"

#include "BuildingManager.generated.h"

UCLASS()
class GESTIONGAME_API ABuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	PlayerData* playerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gestion")
		APlayerMovement* playerMove;

	//To sell a building---
	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void SellBuilding(ABuilding* building);

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void OnSellBuildingIEvent();
	//---

	//To transport the minerals from the building to the player
	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void TransportMineralsToPlayer(AminingBuilding* building);

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void OnTransportMineralsToPlayerIEvent();
	//---
};
