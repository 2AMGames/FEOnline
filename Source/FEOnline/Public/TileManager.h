// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperSceneTile.h"
#include "TileType.h"
#include "TileManager.generated.h"

USTRUCT(Blueprintable)
struct FEONLINE_API FPlaceableSceneTile
{
	GENERATED_BODY();

	FPlaceableSceneTile();

	UPROPERTY(EditAnywhere)
	FVector WorldPosition;

	UPROPERTY(EditAnywhere)
	ETileType TileType;
};


UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class FEONLINE_API ATileManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ATileManager();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<FPlaceableSceneTile> PlacedSceneTiles;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	AActor* StaticMeshActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
	TSubclassOf<class APaperSceneTile> SceneTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	FIntVector TileDimensions;

	UPROPERTY(EditAnywhere)
	FVector DebugTileDrawSize;

	UPROPERTY(EditAnywhere)
	FRotator DebugTileRotation;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override { return true; }

	UFUNCTION(BlueprintCallable)
	void CreateTiles(FVector& StartingPosition);

	UFUNCTION(BlueprintCallable)
	void CheckValidTile(APaperSceneTile* currentTile, int movesLeft);

	UFUNCTION(BlueprintCallable)
	APaperSceneTile* GetTile(const FIntVector& tileIndex);
		
private:
	
	UPROPERTY()
	TArray<APaperSceneTile*> SceneTiles;

	void CheckValidTileInternal(TSet<APaperSceneTile*>& tilesVisited, APaperSceneTile* currentTile, int movesLeft);

	APaperSceneTile* GetTileUp(const FIntVector& tileIndex);

	APaperSceneTile* GetTileDown(const FIntVector& tileIndex);

	APaperSceneTile* GetTileRight(const FIntVector& tileIndex);

	APaperSceneTile* GetTileLeft(const FIntVector& tileIndex);
};
