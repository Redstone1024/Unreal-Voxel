#pragma once

#include "CoreMinimal.h"
#include "VoxelMesh.generated.h"

USTRUCT(BlueprintType)
struct VOXEL_API FVoxelMeshData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<int32> Triangles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FVector> Normals;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FVector2D> UV0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FVector2D> UV1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FVector2D> UV2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FVector2D> UV3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Mesh")
	TArray<FLinearColor> VertexColors;

	const static FVoxelMeshData CubeTopFace;
	const static FVoxelMeshData CubeBottomFace;
	const static FVoxelMeshData CubeFrontFace;
	const static FVoxelMeshData CubeBackFace;
	const static FVoxelMeshData CubeLeftFace;
	const static FVoxelMeshData CubeRightFace;

	void Reset();

	void Append(const FVoxelMeshData& Source);

	void Append(const FVoxelMeshData& Source, const FVector& LocationOffset);
};
