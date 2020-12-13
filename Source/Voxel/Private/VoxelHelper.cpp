#include "VoxelHelper.h"

#include "VoxelWorld.h"
#include "Kismet/GameplayStatics.h"

AVoxelWorld * UVoxelHelper::CreateVoxelWorld(UObject* WorldContextObject, const FVoxelWorldSetting& WorldSetting)
{
	if (!IsWorldSettingValid(WorldContextObject, WorldSetting)) return nullptr;

	UWorld* World = WorldContextObject->GetWorld();

	if (!World) return nullptr;
	
	AVoxelWorld* VoxelWorld = Cast<AVoxelWorld>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(
			World,
			AVoxelWorld::StaticClass(),
			FTransform(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
			nullptr
		)
	);

	VoxelWorld->WorldSetting = WorldSetting;

	UGameplayStatics::FinishSpawningActor(VoxelWorld, FTransform());

	return VoxelWorld;
}

bool UVoxelHelper::IsWorldSettingValid(UObject * WorldContextObject, const FVoxelWorldSetting & WorldSetting)
{
	FString TestFilePath = WorldSetting.ArchiveFolder / TEXT("TestFile");

	if (!FFileHelper::SaveStringToFile(TEXT(""), *TestFilePath))
		return false;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.DeleteFile(*TestFilePath);

	return true;
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
