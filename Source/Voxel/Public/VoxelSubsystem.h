#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VoxelSubsystem.generated.h"

struct FVoxelBlockType;

UCLASS()
class UVoxelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UVoxelSubsystem(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Subsystem")
	int32 ChunkLoadDistance = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Subsystem")
	int32 ChunkUnloadBuffer = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Subsystem")
	TArray<UMaterial*> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Subsystem")
	TMap<FName, FVoxelBlockType> BlockTypes;

	UFUNCTION(BlueprintCallable, Category = "Voxel|Subsystem")
	const FVoxelBlockType& GetBlockType(const FName& Name) const;

};
