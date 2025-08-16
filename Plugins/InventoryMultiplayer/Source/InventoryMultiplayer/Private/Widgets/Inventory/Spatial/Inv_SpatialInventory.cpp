// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"

#include "AudioDevice.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"
#include "InventoryMultiplayer.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Widgets/ItemDescription/Inv_ItemDescription.h"

void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Equipment->OnClicked.AddDynamic(this, &ThisClass::ShowEquipment);
	Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::ShowConsumables);
	Button_Materials->OnClicked.AddDynamic(this, &ThisClass::ShowMaterials);
	Button_QuestItems->OnClicked.AddDynamic(this, &ThisClass::ShowQuestItems);

	Grid_Equipment->SetOwningCanvas(CanvasPanel);
	Grid_Consumables->SetOwningCanvas(CanvasPanel);
	Grid_Materials->SetOwningCanvas(CanvasPanel);
	Grid_QuestItems->SetOwningCanvas(CanvasPanel);

	ShowEquipment();
	
}

FReply UInv_SpatialInventory::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	ActiveGrid->DropItem();
	return FReply::Handled();
	
}

void UInv_SpatialInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(ItemDescription)) return;
	SetItemDescriptionSizeAndPosition(ItemDescription, CanvasPanel);
	
}

void UInv_SpatialInventory::SetItemDescriptionSizeAndPosition(UInv_ItemDescription* Description, UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* ItemDescriptionCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(Description);
	if (!IsValid(ItemDescriptionCPS)) return;

	const FVector2D ItemDescriptionSize = Description->GetBoxSize();
	ItemDescriptionCPS->SetSize(ItemDescriptionSize);

	FVector2D ClampedPosition = UInv_WidgetUtils::GetClampedWIdgetPosition(
		UInv_WidgetUtils::GetWidgetSize(Canvas),
		ItemDescriptionSize,
		UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));

	ItemDescriptionCPS->SetPosition(ClampedPosition);
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

void UInv_SpatialInventory::OnItemHovered(UInv_InventoryItem* Item)
{
	UInv_ItemDescription* DescriptionWidget = GetItemDescription();
	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);

	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(DescriptionTimer);

	FTimerDelegate DescriptionTimerDelegate;
	DescriptionTimerDelegate.BindLambda([this]()
	{
		GetItemDescription()->SetVisibility(ESlateVisibility::HitTestInvisible);
	});

	GetOwningPlayer()->GetWorldTimerManager().SetTimer(DescriptionTimer, DescriptionTimerDelegate, DescriptionTimerDelay, false);
}

void UInv_SpatialInventory::OnItemUnHovered()
{
	GetItemDescription()->SetVisibility(ESlateVisibility::Collapsed);
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(DescriptionTimer);
}

bool UInv_SpatialInventory::HasHoverItem() const
{
	if (Grid_Equipment->HasHoverItem()) return true;
	if (Grid_Consumables->HasHoverItem()) return true;
	if (Grid_Materials->HasHoverItem()) return true;
	if (Grid_QuestItems->HasHoverItem()) return true;
	return false;
	
}

UInv_ItemDescription* UInv_SpatialInventory::GetItemDescription()
{
	if (!IsValid(ItemDescription))
	{
		ItemDescription = CreateWidget<UInv_ItemDescription>(GetOwningPlayer(), ItemDescriptionClass);
		CanvasPanel->AddChild(ItemDescription);
	}
	return ItemDescription;
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
	if (ActiveGrid.IsValid()) ActiveGrid->HideCursor();
	ActiveGrid = Grid;
	if (ActiveGrid.IsValid()) ActiveGrid->ShowCursor();
	
	DisableButton(Button);
	Switcher->SetActiveWidget(Grid);
}

