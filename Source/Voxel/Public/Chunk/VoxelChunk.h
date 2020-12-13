#pragma once

#include "CoreMinimal.h"
#include "SaveStruct.h"
#include "Block/VoxelBlock.h"
#include "GameFramework/Actor.h"
#include "VoxelChunk.generated.h"

class AVoxelWorld;
class UVoxelSubsystem;
class UProceduralMeshComponent;

USTRUCT()
struct FVoxelChunkData : public FSaveStruct
{
	GENERATED_BODY()

	FVoxelBlock Blocks[16][16][256];

	bool Serialize(FArchive& Slot);
};

template<>
struct TStructOpsTypeTraits<FVoxelChunkData> : public TStructOpsTypeTraitsBase2<FVoxelChunkData>
{
	enum
	{
		WithSerializer = true,
	};
};

UCLASS(BlueprintType)
class VOXEL_API AVoxelChunk : public AActor
{
	GENERATED_BODY()

	friend AVoxelWorld;

public:

	AVoxelChunk(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Voxel|Chunk")
	AVoxelWorld* GetVoxelWorld() const { return VoxelWorld; }

	UFUNCTION(BlueprintCallable, Category = "Voxel|Chunk")
	FIntPoint GetChunkLocation() const { return ChunkLocation; }

	UFUNCTION(BlueprintCallable, Category = "Voxel|Chunk")
	const FVoxelBlock& GetBlockByRelativeLocation(const FIntVector& Location) const;

	UFUNCTION(BlueprintCallable, Category = "Voxel|Chunk")
	void SetBlockByRelativeLocation(const FIntVector& Location, const FVoxelBlock& NewBlock);

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Voxel|Chunk")
	void FlushMeshs();

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Voxel|Chunk")
	void FlushMaterials();

private:

	UPROPERTY()
	UVoxelSubsystem* VoxelSubsystem;

	UPROPERTY()
	AVoxelWorld* VoxelWorld;

	UPROPERTY()
	TArray<UProceduralMeshComponent*> MeshComponents;

	FString ArchiveFile;

	FIntPoint ChunkLocation;

	uint16 FlushMeshFlags;

	TSharedPtr<FSaveStructPtr<FVoxelChunkData>> Data;

	FVoxelMeshData MeshSectionBuffer;

private:

	void FlushMeshSection(int32 SectionIndex);

	UFUNCTION()
	void OnDataLoaded(const FString& Filename);

};
