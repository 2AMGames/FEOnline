// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
ATileManager::ATileManager()
{
	bool bShouldTick = false;
#if WITH_EDITOR
	bShouldTick = true;
#endif
	PrimaryActorTick.bCanEverTick = bShouldTick;
}

FPlaceableSceneTile::FPlaceableSceneTile()
{

}

// Called when the game starts
void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
#if !WITH_EDITOR
	if (StaticMeshActor)
	{
		FVector Origin;
		FVector BoxExtent;
		StaticMeshActor->GetActorBounds(false, Origin, BoxExtent);
		FVector Position(-BoxExtent.X - BoxExtent.Y, -BoxExtent.Y, Origin.Z);
		//CreateTiles(Position);
	}
	
#endif
}

void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if WITH_EDITOR

	for (FPlaceableSceneTile& PlacedSceneTile : PlacedSceneTiles)
	{
		DrawDebugBox(GetWorld(), PlacedSceneTile.WorldPosition, DebugTileDrawSize, FQuat(DebugTileRotation), FColor::Blue, false, -1.0f, 0.f);
	}

#endif
}

void ATileManager::CreateTiles(FVector& StartingPosition)
{

	if (!SceneTileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Scene tile class not found!"));
		return;
	}

	if (!StaticMeshActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Static mesh not found!"));
		return;
	}

}

APaperSceneTile* ATileManager::GetTile(const FIntVector& tileIndex)
{
	int32 index = (TileDimensions.X * tileIndex.X) + tileIndex.Y;
	if (index >= 0 && index < SceneTiles.Num())
	{
		return SceneTiles[index];
	}
	return NULL;
}

void ATileManager::CheckValidTile(APaperSceneTile* currentTile, int movesLeft)
{
	TSet<APaperSceneTile*> sceneTilesVisited;
	CheckValidTileInternal(sceneTilesVisited, currentTile, movesLeft);
}

void ATileManager::CheckValidTileInternal(TSet<APaperSceneTile*>& tilesVisited, APaperSceneTile* currentTile, int movesLeft)
{
	if (movesLeft < 0)
		return;
	tilesVisited.Add(currentTile);
	FIntVector tileIndex = currentTile->GetTileIndex();
	// TODO Added check for what characters are at the tile, if they are on our team, and can we inhabit that tile simultaneously
	currentTile->SetMaterialColor(ETileType::TT_Open);

	// Check Upwards
	if (APaperSceneTile* tileAbove = GetTileUp(tileIndex))
	{
		if (!tilesVisited.Contains(tileAbove))
		{
			CheckValidTileInternal(tilesVisited, tileAbove, movesLeft - 1);
		}
	}

	// Check Downwards
	if (APaperSceneTile* tileBelow = GetTileDown(tileIndex))
	{
		if (!tilesVisited.Contains(tileBelow))
		{
			CheckValidTileInternal(tilesVisited, tileBelow, movesLeft - 1);
		}
	}

	// Check Right
	if (APaperSceneTile* tileRight = GetTileRight(tileIndex))
	{
		if (!tilesVisited.Contains(tileRight))
		{
			CheckValidTileInternal(tilesVisited, tileRight, movesLeft - 1);
		}
	}

	// Check Left
	if (APaperSceneTile* tileLeft = GetTileLeft(tileIndex))
	{
		if (!tilesVisited.Contains(tileLeft))
		{
			CheckValidTileInternal(tilesVisited, tileLeft, movesLeft - 1);
		}
	}
	tilesVisited.Remove(currentTile);
}

APaperSceneTile* ATileManager::GetTileUp(const FIntVector& tileIndex)
{
	int32 index = ((tileIndex.X + 1) * TileDimensions.X) + tileIndex.Y;
	if (index < SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}

APaperSceneTile* ATileManager::GetTileDown(const FIntVector& tileIndex)
{
	int32 index = ((tileIndex.X - 1) * TileDimensions.X) + tileIndex.Y;
	if (index >= 0 && index < SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}

APaperSceneTile* ATileManager::GetTileRight(const FIntVector& tileIndex)
{
	if (tileIndex.Y >= TileDimensions.X - 1)
		return NULL;
	int32 index = (tileIndex.X * TileDimensions.X) + (tileIndex.Y + 1);
	if (index < SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}

APaperSceneTile* ATileManager::GetTileLeft(const FIntVector& tileIndex)
{
	if (tileIndex.Y <= 0)
		return NULL;
	int32 index = (tileIndex.X * TileDimensions.X) + (tileIndex.Y - 1);
	if (index >= 0 && SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}
