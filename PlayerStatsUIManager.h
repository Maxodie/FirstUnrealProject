// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStatsUIManager.generated.h"

class PlayerData;
class APlayerMovement;

UCLASS()
class GESTIONGAME_API APlayerStatsUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStatsUIManager();

	//Getters used in the playerStats widget
	UFUNCTION(BlueprintImplementableEvent, Category = "Gestion")
		void OnUpdateMoneyUI(float amount);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Gestion")
		void OnUpdateMineralUI(float amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gestion")
		TSubclassOf<UUserWidget> userWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion")
		UUserWidget* currentPlayerStatsUserWidget;
};
