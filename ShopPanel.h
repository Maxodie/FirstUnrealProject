// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ShopPanel.generated.h"

class APlayerMovement;
class PlayerData;

UCLASS()
class GESTIONGAME_API AShopPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShopPanel();

	bool SetPlayerMovement(APlayerMovement* playerMove_);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gestion")
		TSubclassOf<UUserWidget> userWidget;

	UUserWidget* currentShopPanelUserWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion")
		bool isPanelActived = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion", meta = (EditCondition = 0))
		APlayerMovement* playerMove;

public:
	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void TogglePanel(bool forcedState = false, bool state = false);

	//To transport the minerals from the building to the player
	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void SellPlayerMineral();

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void OnSellPlayerMineralIEvent();
	//---

private:
	void ActivePanel(bool isActive);

	PlayerData* playerData;
};
