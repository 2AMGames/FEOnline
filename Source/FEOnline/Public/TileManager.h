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
		
private:
	
	TArray<APaperSceneTile*> SceneTiles;

};
