// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Types/Inv_ItemSoundTypes.h"
#include "Items/Manifest/Inv_ItemManifest.h"

#include "Inv_InventoryItem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemAudioProfile
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Audio")
	EBaseSoundCategory BaseSoundCategory = EBaseSoundCategory::None; // e.g., "Metallic, "wooden", "organic"

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Audio")
	EAccentSoundCategory AccentSoundCategory = EAccentSoundCategory::None; // e.g., "Gadget, weapon, tool, armor, clothing
};

UCLASS()
class INVENTORYMULTIPLAYER_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }

	void SetItemManifest(const FInv_ItemManifest& Manifest);
	
	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); }
	FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); }
	bool IsStackable() const;
	int32 GetTotalStackCount() const { return TotalStackCount; }
	void SetTotalStackCount(int32 Count) { TotalStackCount = Count; }
	
	// AUDIO SECTION //
	// Returns the audio profile for this item, which contains sound categories for base and accent sounds.
	// This can be used to play appropriate sounds when the item is picked up, used, or interacted with.
	UFUNCTION(BlueprintCallable, Category = "Inventory|Audio")
	const FItemAudioProfile& GetAudioProfile() const { return AudioProfile; }

	UFUNCTION(BlueprintCallable, Category = "Inventory|Audio")
	EBaseSoundCategory GetBaseSoundCategory() const { return AudioProfile.BaseSoundCategory; }

	UFUNCTION(BlueprintCallable, Category = "Inventory|Audio")
	EAccentSoundCategory GetAccentSoundCategory() const { return AudioProfile.AccentSoundCategory; }

	UPROPERTY(EditAnywhere, Category = "Inventory|Audio")
	FItemAudioProfile AudioProfile;


private:

	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/InventoryMultiplayer.Inv_ItemManifest"), Replicated)
	FInstancedStruct ItemManifest;

	UPROPERTY(Replicated)
	int32 TotalStackCount{0};
	
};


template <typename FragmentType>
const FragmentType* GetFragment(const UInv_InventoryItem* Item, const FGameplayTag& Tag)
{
	if (!IsValid(Item)) return nullptr;

	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	return Manifest.GetFragmentOfTypeWithTag<FragmentType>(Tag);
	
}