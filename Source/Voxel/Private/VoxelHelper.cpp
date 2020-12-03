#include "VoxelHelper.h"

#include "VoxelWorld.h"

AVoxelWorld * UVoxelHelper::CreateVoxelWorld(UObject* WorldContextObject, const FVoxelWorldSetting& WorldSetting)
{
	UWorld* World = WorldContextObject->GetWorld();

	if (!World) return nullptr;

	AVoxelWorld* VoxelWorld = World->SpawnActor<AVoxelWorld>();

	VoxelWorld->WorldSetting = WorldSetting;

	return VoxelWorld;
}

void UVoxelHelper::WorldToRelativeLocation(const FIntVector & InWorldLocation, FIntPoint & OutChunkLocation, FIntVector & OutRelativeLocation)
{
	OutChunkLocation.X = InWorldLocation.X / 16;
	OutChunkLocation.Y = InWorldLocation.Y / 16;

	OutRelativeLocation.X = InWorldLocation.X % 16;
	OutRelativeLocation.Y = InWorldLocation.Y % 16;
	OutRelativeLocation.Z = InWorldLocation.Z;

	if (OutRelativeLocation.X < 0)
	{
		OutRelativeLocation.X += 16;
		OutChunkLocation.X -= 1;
	}

	if (OutRelativeLocation.Y < 0)
	{
		OutRelativeLocation.Y += 16;
		OutChunkLocation.Y -= 1;
	}
}
