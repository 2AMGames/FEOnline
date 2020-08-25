// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileType.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PaperSpriteActor.h"
#include "PaperSceneTile.generated.h"

UCLASS()
class FEONLINE_API APaperSceneTile : public APaperSpriteActor
{
	GENERATED_BODY()

public:

	APaperSceneTile();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Components")
	FLinearColor MovableColor;

	UPROPERTY(EditAnywhere, Category = "Components")
	FLinearColor NonMovableColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* MaterialInterfaceObject;

	FIntVector TileIndex;
	
public:

	UFUNCTION(BlueprintCallable)
	void SetTileIndex(int xIndex, int yIndex);

	UFUNCTION(BlueprintCallable)
	void SetMaterialColor(ETileType tileType);

	UFUNCTION(BlueprintCallable)
	FIntVector GetTileIndex();
};
