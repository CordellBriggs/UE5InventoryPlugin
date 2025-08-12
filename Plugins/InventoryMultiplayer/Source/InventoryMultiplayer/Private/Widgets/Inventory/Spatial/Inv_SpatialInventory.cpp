// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"
#include "InventoryMultiplayer.h"

void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Equipment->OnClicked.AddDynamic(this, &ThisClass::ShowEquipment);
	Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::ShowConsumables);
	Button_Materials->OnClicked.AddDynamic(this, &ThisClass::ShowMaterials);
	Button_QuestItems->OnClicked.AddDynamic(this, &ThisClass::ShowQuestItems);


	ShowEquipment();
	
}

FInv_SlotAvailabilityResult UInv_SpatialInventory::HasRoomForItem(UInv_ItemComponent* ItemComponent) const
{
	switch (UInv_InventoryStatics::GetItemCategoryFromItemComp(ItemComponent))
	{
		case EInv_ItemCategory::Equipment:
			UE_LOG(LogInventory, Error, TEXT("ItemCategory is set to Equipment!"));
			return Grid_Equipment->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::Consumables:
			UE_LOG(LogInventory, Error, TEXT("ItemCategory is set to Consumables!"));
			return Grid_Consumables->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::Materials:
			UE_LOG(LogInventory, Error, TEXT("ItemCategory is set to Materials!"));
			return Grid_Materials->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::QuestItems:
			UE_LOG(LogInventory, Error, TEXT("ItemCategory is set to QuestItems!"));
			return Grid_QuestItems->HasRoomForItem(ItemComponent);
		default:
			UE_LOG(LogInventory, Error, TEXT("ItemComponent doesn't have a valid Item Category!"));
			return FInv_SlotAvailabilityResult();
	}
}

void UInv_SpatialInventory::ShowEquipment()
{
	SetActiveGrid(Grid_Equipment, Button_Equipment);
}

void UInv_SpatialInventory::ShowConsumables()
{
	SetActiveGrid(Grid_Consumables, Button_Consumables);
}

void UInv_SpatialInventory::ShowMaterials()
{
	SetActiveGrid(Grid_Materials, Button_Materials);
}

void UInv_SpatialInventory::ShowQuestItems()
{
	SetActiveGrid(Grid_QuestItems, Button_QuestItems);
}

void UInv_SpatialInventory::DisableButton(UButton* Button)
{
	Button_Equipment->SetIsEnabled(true);
	Button_Consumables->SetIsEnabled(true);
	Button_Materials->SetIsEnabled(true);
	Button_QuestItems->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button)
{
	DisableButton(Button);
	Switcher->SetActiveWidget(Grid);
}