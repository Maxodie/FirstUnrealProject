// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStatsUIManager.h"

#include "PlayerData.h"

PlayerData::PlayerData() {
}

PlayerData::~PlayerData() {
	delete this->playerStatsUI;
}

#pragma region Updaters
//Updaters
bool PlayerData::UpdateMoney(float amount) {
	if (this->currentMoney + amount < 0.f) {
		return false;
	}

	this->currentMoney += amount;
	this->playerStatsUI->OnUpdateMoneyUI(this->currentMoney);

	return true;
}

bool PlayerData::UpdateMineralAmount(float amount) {
	if (this->mineralAmount + amount < 0.f) {
		return false;
	}

	this->mineralAmount += amount;
	this->playerStatsUI->OnUpdateMineralUI(this->mineralAmount);

	return true;
}

bool PlayerData::UpdateTransformedMineralAmount(float amount) {
	if (this->transformedMineralAmount + amount < 0.f) {
		return false;
	}

	this->transformedMineralAmount += amount;

	return true;
}
//----
#pragma endregion

#pragma region Getters
//Getters
float PlayerData::GetCurrentMoney() {
	return this->currentMoney;
}

float PlayerData::GetCurretMineralAmount() {
	return this->mineralAmount;
}

float PlayerData::GetCurretTransformedMineralAmount() {
	return this->transformedMineralAmount;
}
//----
#pragma endregion

#pragma region Setters
void PlayerData::SetPlayerStatsUIManager(APlayerStatsUIManager* playerStatsUI_) {
	this->playerStatsUI = playerStatsUI_;
}
#pragma endregion