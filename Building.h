// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BuildingInfosPanel.h"

#include "Building.generated.h"

UCLASS()
class GESTIONGAME_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Gestion")
		float sellPrice = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gestion")
		ABuildingInfosPanel* currentBuildingInfosPanel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetSellPrice() const;

	ABuildingInfosPanel* GetCurrentBuildingInfosPanel() const;
};
