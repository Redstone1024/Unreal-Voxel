#pragma once

#include "CoreMinimal.h"
#include "VoxelWorld.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelHelper.generated.h"

class AVoxelWorld;

UCLASS()
class VOXEL_API UVoxelHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Voxel|Helper", meta = (WorldContext = "WorldContextObject"))
	static AVoxelWorld* CreateVoxelWorld(UObject* WorldContextObject, const FVoxelWorldSetting& WorldSetting);

	UFUNCTION(BlueprintCallable, Category = "Voxel|Helper", meta = (WorldContext = "WorldContextObject"))
	static bool IsWorldSettingValid(UObject* WorldContextObject, const FVoxelWorldSetting& WorldSetting);
	
	UFUNCTION(BlueprintPure, Category = "Voxel|Helper")
	static void WorldToRelativeLocation(const FIntVector& InWorldLocation, FIntPoint& OutChunkLocation, FIntVector& OutRelativeLocation);

};
