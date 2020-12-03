#pragma once

#include "CoreMinimal.h"
#include "VoxelBlock.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelBlueprintLibrary.generated.h"

struct FVoxelBlockType;

UCLASS()
class UVoxelBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Voxel|Subsystem", meta = (WorldContext = "WorldContextObject"))
	static void AddBlockType(const UObject* WorldContextObject, const FName& Name, const FVoxelBlockType& BlockType);

};
