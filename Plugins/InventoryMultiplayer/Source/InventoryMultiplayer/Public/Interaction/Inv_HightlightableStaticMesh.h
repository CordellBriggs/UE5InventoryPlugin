// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inv_Highlightable.h"
#include "Components/StaticMeshComponent.h"
#include "Inv_HightlightableStaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYMULTIPLAYER_API UInv_HightlightableStaticMesh : public UStaticMeshComponent, public IInv_Highlightable
{
	GENERATED_BODY()

public:
	virtual void Highlight_Implementation() override;
	virtual void UnHighlight_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category= "Inventory|Highlight")
	TObjectPtr<UMaterialInterface> HighlightMaterial;
};
