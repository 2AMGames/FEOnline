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
	UPaperSpriteComponent* renderComponent = GetRenderComponent();
	DynamicMaterialInstance = renderComponent->CreateDynamicMaterialInstance(0, MaterialInterfaceObject);
	renderComponent->SetMaterial(0, DynamicMaterialInstance);
	SetMaterialColor(ETileType::TT_Open);
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

	switch (tileType)
	{
	case ETileType::TT_Blocked:
		DynamicMaterialInstance->SetVectorParameterValue("TileOverlayColor", NonMovableColor);
		break;
	case ETileType::TT_Open:
		DynamicMaterialInstance->SetVectorParameterValue("TileOverlayColor", MovableColor);
		break;
	}

	DynamicMaterialInstance->SetScalarParameterValue("TileOverlayAlpha", .6f);
}
