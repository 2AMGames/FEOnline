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

void UTileManager::CreateTiles(float bottomLeftX, float bottomLeftY, FVector2D dimensions)
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
	GEngine->AddOnScreenDebugMessage(-1, 5.5f, FColor::Blue, FString::Printf(TEXT("left: %f, right: %f"), bottomLeftX, bottomLeftY));
	while (xDimension < 10)
	{
		int yDimension = 0;
		while (yDimension < 10)
		{
			float xOffset = xDimension * dimensions.X * 9.5;
			float yOffset = yDimension * dimensions.Y * 9.5;

			FVector placement = FVector(xOffset + bottomLeftX, yOffset + bottomLeftY, 112.0f);
			FRotator rotation;
			rotation.Roll = 90.0f;

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

