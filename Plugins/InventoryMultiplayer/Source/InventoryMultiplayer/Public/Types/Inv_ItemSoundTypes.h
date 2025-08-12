#pragma once

#include "Inv_ItemSoundTypes.generated.h"

UENUM(BlueprintType)
enum class EBaseSoundCategory : uint8
{
	Wood        UMETA(DisplayName = "Wood"),
	Stone       UMETA(DisplayName = "Stone"),
	Metallic    UMETA(DisplayName = "Metallic"),
	Cloth       UMETA(DisplayName = "Cloth"),
	Leather     UMETA(DisplayName = "Leather"),
	Glass     UMETA(DisplayName = "Glass"),
	Plastic     UMETA(DisplayName = "Plastic"),
	Organic     UMETA(DisplayName = "Organic"),
	None        UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EAccentSoundCategory : uint8
{
	None        UMETA(DisplayName = "None"),
	Gadgetry    UMETA(DisplayName = "Gadgetry"),
	Arcane      UMETA(DisplayName = "Arcane"),
	Crystalline UMETA(DisplayName = "Crystalline"),
	Wet         UMETA(DisplayName = "Wet"),
	Fire        UMETA(DisplayName = "Fire"),
	Electrical  UMETA(DisplayName = "Electrical"),
	Ghostly     UMETA(DisplayName = "Ghostly"),
	Corrupted   UMETA(DisplayName = "Corrupted"),
	
};