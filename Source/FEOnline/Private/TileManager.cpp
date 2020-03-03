// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UTileManager::UTileManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTileManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTileManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTileManager::CreateTiles(float bottomLeftX, float bottomLeftY)
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

	int xDimension = 0;
	while (xDimension < 10)
	{
		int yDimension = 0;
		while (yDimension < 10)
		{
			float xOffset = xDimension * TileDimensions.X * 9.5;
			float yOffset = yDimension * TileDimensions.Y * 9.5;

			FVector placement = FVector(xOffset + bottomLeftX, yOffset + bottomLeftY, 112.0f);
			FRotator rotation;
			rotation.Roll = 90.0f;
			rotation.Pitch = 0.00f;
			rotation.Yaw = 0.00f;

			FActorSpawnParameters spawnParameters;
			spawnParameters.Owner = this->GetOwner();

			FAttachmentTransformRules rules(EAttachmentRule::KeepWorld, false);

			FTransform tileTransform;
			tileTransform.SetLocation(placement);
			tileTransform.SetRotation(rotation.Quaternion());

			APaperSceneTile* sceneTile = GetWorld()->SpawnActor<APaperSceneTile>(SceneTileClass, tileTransform, spawnParameters);
			sceneTile->SetOwner(GetOwner());
			sceneTile->AttachToActor(GetOwner(), rules);
			sceneTile->SetTileIndex(xDimension, yDimension);
			SceneTiles.Add(sceneTile);
			++yDimension;
		}
		++xDimension;
	}
}

APaperSceneTile* UTileManager::GetTile(const FIntVector& tileIndex)
{
	int32 index = (TileDimensions.X * tileIndex.X) + tileIndex.Y;
	if (index >= 0 && index < SceneTiles.Num())
	{
		return SceneTiles[index];
	}
	return NULL;
}

void UTileManager::CheckValidTile(APaperSceneTile* currentTile, int movesLeft)
{
	TSet<APaperSceneTile*> sceneTilesVisited;
	CheckValidTileInternal(sceneTilesVisited, currentTile, movesLeft);
}

void UTileManager::CheckValidTileInternal(TSet<APaperSceneTile*>& tilesVisited, APaperSceneTile* currentTile, int movesLeft)
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

APaperSceneTile* UTileManager::GetTileUp(const FIntVector& tileIndex)
{
	int32 index = ((tileIndex.X + 1) * TileDimensions.X) + tileIndex.Y;
	if (index < SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}

APaperSceneTile* UTileManager::GetTileDown(const FIntVector& tileIndex)
{
	int32 index = ((tileIndex.X - 1) * TileDimensions.X) + tileIndex.Y;
	if (index >= 0 && index < SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}

APaperSceneTile* UTileManager::GetTileRight(const FIntVector& tileIndex)
{
	if (tileIndex.Y >= TileDimensions.X - 1)
		return NULL;
	int32 index = (tileIndex.X * TileDimensions.X) + (tileIndex.Y + 1);
	if (index < SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}

APaperSceneTile* UTileManager::GetTileLeft(const FIntVector& tileIndex)
{
	if (tileIndex.Y <= 0)
		return NULL;
	int32 index = (tileIndex.X * TileDimensions.X) + (tileIndex.Y - 1);
	if (index >= 0 && SceneTiles.Num())
		return SceneTiles[index];
	return NULL;
}
