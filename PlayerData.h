// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class APlayerStatsUIManager;

class GESTIONGAME_API PlayerData
{
public:
	PlayerData();
	~PlayerData();

	//If it's not possible to substract money then retrun false
	//Updaters can't go under 0.f
	bool UpdateMoney(float amount);
	bool UpdateMineralAmount(float amount);
	bool UpdateTransformedMineralAmount(float amount);

	//Getters
	float GetCurrentMoney();
	float GetCurretMineralAmount();
	float GetCurretTransformedMineralAmount();

	//Setters
	void SetPlayerStatsUIManager(APlayerStatsUIManager* playerStatsUI_);

private:
	float currentMoney = 0.f;
	float mineralAmount = 0.f;
	float transformedMineralAmount = 0.f;

	APlayerStatsUIManager* playerStatsUI;
};
