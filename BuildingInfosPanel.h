// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"

#include "BuildingInfosPanel.generated.h"

UCLASS()
class GESTIONGAME_API ABuildingInfosPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingInfosPanel();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ActivePanel(bool isActive);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gestion")
		TSubclassOf<UUserWidget> userWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion")
		UUserWidget* currentPanelWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion")
		bool isPanelActived = false;

public:	
	//Set the position of the panel with a building transform
	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void TogglePanel(bool forcedState = false, bool state = false);
};
