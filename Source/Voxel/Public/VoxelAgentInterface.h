#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VoxelAgentInterface.generated.h"

UINTERFACE(MinimalAPI)
class UVoxelAgentInterface : public UInterface
{
	GENERATED_BODY()
};

class VOXEL_API IVoxelAgentInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Voxel|Agent")
	FIntVector GetAgentLocation() const;
	FIntVector GetAgentLocation_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Voxel|Agent")
	FVector GetAgentPartialLocation() const;
	FVector GetAgentPartialLocation_Implementation() const;

};
