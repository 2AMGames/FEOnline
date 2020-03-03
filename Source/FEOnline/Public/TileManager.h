// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperSceneTile.h"
#include "TileType.h"
#include "TileManager.generated.h"


UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class FEONLINE_API UTileManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTileManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	float SpriteSize; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	AActor* StaticMeshActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	TSubclassOf<class APaperSceneTile> SceneTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	FIntVector TileDimensions;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void CreateTiles(float bottomLeft, float bottomRight);

	UFUNCTION(BlueprintCallable)
	void CheckValidTile(APaperSceneTile* currentTile, int movesLeft);

	UFUNCTION(BlueprintCallable)
	APaperSceneTile* GetTile(const FIntVector& tileIndex);
		
private:
	
	TArray<APaperSceneTile*> SceneTiles;

	void CheckValidTileInternal(TSet<APaperSceneTile*>& tilesVisited, APaperSceneTile* currentTile, int movesLeft);

	APaperSceneTile* GetTileUp(const FIntVector& tileIndex);

	APaperSceneTile* GetTileDown(const FIntVector& tileIndex);

	APaperSceneTile* GetTileRight(const FIntVector& tileIndex);

	APaperSceneTile* GetTileLeft(const FIntVector& tileIndex);
};
