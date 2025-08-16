#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_ItemFragment.generated.h"

class APlayerController;

USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()


	FInv_ItemFragment() {}
	FInv_ItemFragment(const FInv_ItemFragment&) = default;
	//copy assignment operator
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	//move constructor
	FInv_ItemFragment( FInv_ItemFragment&&) = default;
	//move assignment operator
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	// Deconstructor
	virtual ~FInv_ItemFragment() {}

	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragmentTag( FGameplayTag Tag) { FragmentTag = Tag; }
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories="FragmentTags"))
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};

USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FIntPoint GetGridSize() const { return GridSize; }
	void SetGridSize(FIntPoint Size) { GridSize = Size; }
	float GetGridPadding() const { return GridPadding; }
	void SetGridPadding(float Padding) { GridPadding = Padding; }
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Grid")
	FIntPoint GridSize{1, 1};

	UPROPERTY(EditAnywhere, Category = "Inventory|Grid")
	float GridPadding{0.f};

	
};

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
	
	UTexture2D* GetIcon() const { return Icon; }
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Image")
	TObjectPtr<UTexture2D> Icon {nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory|Image")
	FVector2D IconDimensions{44.f, 44.f};
	
};

USTRUCT(BlueprintType)
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
	
	int32 GetMaxStackSize() const { return MaxStackSize; }
	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(int32 Count) { StackCount = Count; }
	
private:

	UPROPERTY(EditAnywhere, Category = "Inventory|Stackable")
	int32 MaxStackSize{1};

	UPROPERTY(EditAnywhere, Category = "Inventory|Stackable")
	int32 StackCount{1};
	
};

USTRUCT(BlueprintType)
struct FInv_ConsumableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	//OnConsume is designed to be overriden 
virtual void OnConsume(APlayerController* PC) {};
	
};

USTRUCT(BlueprintType)
struct FInv_HealthPotionFragment : public FInv_ConsumableFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory|Consumable")
	float HealAmount = 20.f;
	
	//Here we are Overriding the OnConsume function we derived above!
	virtual void OnConsume(APlayerController* PC) override;
	
};

USTRUCT(BlueprintType)
struct FInv_ManaPotionFragment : public FInv_ConsumableFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory|Consumable")
	float ManaAmount = 20.f;
	
	//Here we are Overriding the OnConsume function we derived above!
	virtual void OnConsume(APlayerController* PC) override;
	
};