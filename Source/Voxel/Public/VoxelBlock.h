#pragma once

#include "CoreMinimal.h"
#include "VoxelMesh.h"
#include "UObject/Object.h"
#include "VoxelBlock.generated.h"

class AVoxelWorld;

USTRUCT(BlueprintType)
struct VOXEL_API FVoxelBlock
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FName Type;

	FVoxelBlock() : FVoxelBlock(FName(TEXT("Air"))) { }

	FVoxelBlock(FName InType) : Type(InType) { }

	const static FVoxelBlock InvalidBlock;

	bool IsValidBlock() const { return Type != NAME_None; }
};

UENUM(BlueprintType)
enum class EVoxelBlockShape : uint8
{
	Invalid,
	Air,
	Cube,
};

USTRUCT(BlueprintType)
struct VOXEL_API FVoxelBlockType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	EVoxelBlockShape Shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FVector2D CustomTopFaceUV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FVector2D CustomBottomFaceUV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FVector2D CustomFrontFaceUV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FVector2D CustomBackFaceUV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FVector2D CustomLeftFaceUV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Block")
	FVector2D CustomRightFaceUV;

	FVoxelBlockType() : FVoxelBlockType(EVoxelBlockShape::Air) { }

	FVoxelBlockType(EVoxelBlockShape InShape) : Shape(InShape) { }

	const static FVoxelBlockType InvalidBlockType;
};
