// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Application/NavigationConfig.h"

#include "ShopPanel.h"
#include "miningBuilding.h"

#include "PlayerMovement.h"

// Sets default values
APlayerMovement::APlayerMovement()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->playerData = new PlayerData();
}

// Called when the game starts or when spawned
void APlayerMovement::BeginPlay()
{
	Super::BeginPlay();
}

//Funtion called in blueprint after the referencing of actors
void APlayerMovement::StartInit() {
	//Get singletons
	if (IsValid(GetWorld()) && IsValid(GetWorld()->GetFirstPlayerController()))
		this->Playercontroller = GetWorld()->GetFirstPlayerController();
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error::PlayerMovement no player controller"));
		return;
	}

	//init mapping context
	if (IsValid(Playercontroller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Playercontroller->GetLocalPlayer())) {
			Subsystem->AddMappingContext(this->DefaultMappingContext, 0);
		}

		this->Playercontroller->bShowMouseCursor = true;
		this->Playercontroller->SetInputMode(FInputModeGameAndUI());
	}

	this->shopPanel->SetPlayerMovement(this);

	FNavigationConfig& NavigationConfig = *FSlateApplication::Get().GetNavigationConfig();

	NavigationConfig.bTabNavigation = false;
}

// Called to bind functionality to input
void APlayerMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (class UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Move
		EnhancedInputComponent->BindAction(this->MovementAction, ETriggerEvent::Triggered, this, &APlayerMovement::Move);
		EnhancedInputComponent->BindAction(this->LeftClickAction, ETriggerEvent::Started, this, &APlayerMovement::LeftClick);
		EnhancedInputComponent->BindAction(this->ToggleShopPanelAction, ETriggerEvent::Started, this, &APlayerMovement::ToggleShopPanel);
	}
}

ABuilding* APlayerMovement::GetCurrentBuilding() {
	return this->currentBuilding;
}

AminingBuilding* APlayerMovement::GetCurrentMiningBuilding() {
	return this->currentMiningBuilding;
}

void APlayerMovement::Move(const FInputActionValue& Value) {
	const FVector2D Mov = Value.Get<FVector2D>();
	this->AddActorWorldTransform(FTransform(FVector(Mov.X, Mov.Y, 0) * this->playerSpeed));
}

void APlayerMovement::LeftClick() {
	this->DetectBuildingOnMousePos();
}

void APlayerMovement::ToggleShopPanel() {
	this->shopPanel->TogglePanel();
}

//Close the panel of the current selected building
bool APlayerMovement::CloseCurrentBuildingInfosPanel() {
	if (this->currentBuilding != nullptr) {
		this->currentBuilding->GetCurrentBuildingInfosPanel()->TogglePanel(true, false);

		return true;
	}
	else return false;
}

//When the player clik somewhere
void APlayerMovement::DetectBuildingOnMousePos() {
	FHitResult hit;
	
	//getActor touched by the mouse
	Playercontroller->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, hit);
	AActor* touchedActor = hit.GetActor();
	
	//If the actor have a building tag
	if (IsValid(touchedActor) && touchedActor->ActorHasTag(this->buildingTag)) {

		//Save the current building  to check if the new building is the same
		ABuilding* newBuilding;

		if ((newBuilding = Cast<ABuilding>(touchedActor) ) != this->currentBuilding) {
			this->CloseCurrentBuildingInfosPanel();//Close the current building infos panel

			if (!this->SetCurrentBuilding(newBuilding)) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error::PlayerMove can't find a ABuilding script on actor"));
				return;
			}

			if (IsValid(this->currentMiningBuilding = Cast<AminingBuilding>(touchedActor))) {
				this->SetCurrentBuilding(this->currentMiningBuilding);
			}
		}

		//If a building is touched and registered set the panel on the building
		this->currentBuilding->GetCurrentBuildingInfosPanel()->TogglePanel();
	}
	else {//if the thing clicked is not a building 
		this->CloseCurrentBuildingInfosPanel();

		return;
	}
}

PlayerData* APlayerMovement::GetPlayerData() {
	return this->playerData;
}

//Setters
bool APlayerMovement::SetCurrentBuilding(ABuilding* newCurrentBuilding) {
	this->currentBuilding = newCurrentBuilding;
	return IsValid(this->currentBuilding);
}
