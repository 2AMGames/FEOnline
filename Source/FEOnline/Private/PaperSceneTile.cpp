// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperSceneTile.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "PaperSpriteComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

APaperSceneTile::APaperSceneTile()
{
}

void APaperSceneTile::SetTileIndex(int xIndex, int yIndex) {
	TileIndex.X = xIndex;
	TileIndex.Y = yIndex;
}

void APaperSceneTile::SetMaterialColor(ETileType tileType)
{
	if (!DynamicMaterialInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Dynamic matierial instance not found!"));
		return;
	}

	float scalarValue = .6f;

	switch (tileType)
	{
	case ETileType::TT_Blocked:
		DynamicMaterialInstance->SetVectorParameterValue("TileOverlayColor", NonMovableColor);
		break;
	case ETileType::TT_Open:
		DynamicMaterialInstance->SetVectorParameterValue("TileOverlayColor", MovableColor);
		break;
	case ETileType::TT_Ignore:
		scalarValue = 0.0f;
	}

	DynamicMaterialInstance->SetScalarParameterValue("TileOverlayAlpha", scalarValue);
}

FIntVector APaperSceneTile::GetTileIndex()
{
	return TileIndex;
}
