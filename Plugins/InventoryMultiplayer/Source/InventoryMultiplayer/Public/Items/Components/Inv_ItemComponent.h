// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_ItemComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYMULTIPLAYER_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInv_ItemComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FInv_ItemManifest GetItemManifest() const { return ItemManifest; }
	
	FString GetPickupMessage() const { return PickupMessage; }
	
	void PickedUp();

	// The Sound to play when the Item Is PickedUp in the world.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Audio")
	TObjectPtr<USoundBase> PickUpSound;

protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory|Item")
	void OnPickedUp();

private:

	UPROPERTY(Replicated, EditAnywhere, Category = "Inventory")
	FInv_ItemManifest ItemManifest;

	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FString PickupMessage;



};













