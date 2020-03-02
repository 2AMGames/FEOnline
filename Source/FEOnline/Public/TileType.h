// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETileType : uint8 {
	TT_Open UMETA(DisplayName = "OpenTile"),
	TT_Blocked UMETA(DisplayName = "BlockedTile"),
	TT_AirOnly UMETA(DisplayName = "AirOnlyTile"),
	TT_Ignore UMETA(DisplayName= "Ignore")
};
