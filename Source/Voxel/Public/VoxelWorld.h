#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "VoxelWorld.generated.h"

struct FVoxelBlock;

class AVoxelChunk;
class UVoxelHelper;
class UVoxelBlockType;
class UVoxelSubsystem;
class IVoxelAgentInterface;

USTRUCT(BlueprintType)
struct FVoxelWorldSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|World")
	FString ArchiveFolder;

};

UCLASS(BlueprintType)
class VOXEL_API AVoxelWorld : public AInfo
{
	GENERATED_BODY()

	friend UVoxelHelper;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|World")
	TScriptInterface<IVoxelAgentInterface> CenterAgent;

	AVoxelWorld(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Voxel|World")
	const FVoxelWorldSetting& GetWorldSetting() const { return WorldSetting; }

	UFUNCTION(BlueprintCallable, Category = "Voxel|World")
	const TMap<FIntPoint, AVoxelChunk*>& GetChunks() const { return Chunks; }

	UFUNCTION(BlueprintCallable, Category = "Voxel|World")
	const FVoxelBlock& GetBlockByWorldLocation(const FIntVector& Location) const;

	UFUNCTION(BlueprintCallable, Category = "Voxel|World")
	void SetBlockByWorldLocation(const FIntVector& Location, const FVoxelBlock& NewBlock);

	UFUNCTION(BlueprintCallable, Category = "Voxel|World")
	void AddChunkToMeshFlushBuffer(const FIntPoint& ChunkLocation) { MeshFlushBuffer.Add(ChunkLocation); }

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Voxel|World")
	void FlushMaterials();

public:

	void LoadChunk(const FIntPoint& ChunkLocation);
	void UnloadChunk(const FIntPoint& ChunkLocation);

private:

	UPROPERTY(EditAnywhere, Category = "Voxel|World")
	FVoxelWorldSetting WorldSetting;

	UPROPERTY()
	UVoxelSubsystem* VoxelSubsystem;

	UPROPERTY()
	TMap<FIntPoint, AVoxelChunk*> Chunks;

	UPROPERTY()
	TSet<FIntPoint> MeshFlushBuffer;

private:
	
	void ManageChunk();

	void FlushMeshs();

};
