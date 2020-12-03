#include "VoxelSubsystem.h"

#include "Block/VoxelBlock.h"

UVoxelSubsystem::UVoxelSubsystem(const class FObjectInitializer& ObjectInitializer)
{
	BlockTypes.Add(TEXT("Air"), FVoxelBlockType());
}

const FVoxelBlockType & UVoxelSubsystem::GetBlockType(const FName & Name) const
{
	if (BlockTypes.Contains(Name))
		return BlockTypes[Name];

	return FVoxelBlockType::InvalidBlockType;
}
