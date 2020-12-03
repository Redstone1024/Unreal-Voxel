#include "Blueprint/VoxelBlueprintLibrary.h"

#include "VoxelSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UVoxelBlueprintLibrary::AddBlockType(const UObject* WorldContextObject, const FName& Name, const FVoxelBlockType& BlockType)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UVoxelSubsystem* LockstepSubsystem = GameInstance->GetSubsystem<UVoxelSubsystem>();
	LockstepSubsystem->BlockTypes.Add(Name, BlockType);
}
