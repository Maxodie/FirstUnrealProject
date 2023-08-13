// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include <string>

#include "PlayerData.h"

#include "PlayerMovement.generated.h"

class AShopPanel;
class AminingBuilding;


UCLASS()
class GESTIONGAME_API APlayerMovement : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerMovement();

	PlayerData* GetPlayerData();
	
private:
	/** Camera boom positioning the camera behind the character 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class USpringArmComponent* CameraBoom;

	Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* FollowCamera; */

	//BlueprintCallable, Category = "Movement"
	void Move(const FInputActionValue& Value);
	void LeftClick();
	void ToggleShopPanel();
	bool CloseCurrentBuildingInfosPanel();

	void DetectBuildingOnMousePos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		void StartInit();

	PlayerData* playerData;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* ToggleShopPanelAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		float playerSpeed = 10.f;

	//UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Gestion")
		//ABuilding* currentSelectedBuilding;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Gestion")
		FName buildingTag = "Building";

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Gestion")
		APlayerController* Playercontroller;

	//Buildings possibilities
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion")
		ABuilding* currentBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gestion")
		AminingBuilding* currentMiningBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class AShopPanel* shopPanel;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gestion")
	UFUNCTION(BlueprintImplementableEvent)
		void OnSelectBuilding();

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		bool SetCurrentBuilding(ABuilding* building);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		ABuilding* GetCurrentBuilding();

	UFUNCTION(BlueprintCallable, Category = "Gestion")
		AminingBuilding* GetCurrentMiningBuilding();
};