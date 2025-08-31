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
	virtual void Manifest(){}
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories="FragmentTags"))
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};

/*
 *Item fragment meant specifically for assimilation into a widget.
 */
class UInv_CompositeBase;

USTRUCT(BlueprintType)
struct FInv_InventoryItemFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UInv_CompositeBase* Composite) const;
protected:
	bool MatchesWidgetTag(const UInv_CompositeBase* Composite) const;
	
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
struct FInv_ImageFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	
	UTexture2D* GetIcon() const { return Icon; }
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Image")
	TObjectPtr<UTexture2D> Icon {nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory|Image")
	FVector2D IconDimensions{44.f, 44.f};
	
};

USTRUCT(BlueprintType)
struct FInv_TextFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	
	FText GetText() const { return FragmentText; }
	void SetText(const FText& Text) { FragmentText = Text; }
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Text")
	FText FragmentText;
	
};

USTRUCT(BlueprintType)
struct FInv_LabeledNumberFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
	virtual void Manifest() override;

	// When Manifesting for the first time, this fragment will randomize. However, once equipped and dropped, an item should retain the same value, so randomization should not occur.
	bool bRandomizeOnManifest{true};
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	FText Text_Label{};
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory|Label")
	float Value{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	float Min{0};
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	float Max{0};

	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	bool bCollapseLabel{false};
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	bool bCollapseValue{false};
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	int32 MinFractionDigits{1};
	
	UPROPERTY(EditAnywhere, Category = "Inventory|Label")
	int32 MaxFractionDigits{1};
	
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