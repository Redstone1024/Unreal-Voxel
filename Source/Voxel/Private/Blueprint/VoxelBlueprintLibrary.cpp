#include "Blueprint/VoxelBlueprintLibrary.h"

#include "VoxelSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UVoxelBlueprintLibrary::AddBlockType(const UObject* WorldContextObject, const FName& Name, const FVoxelBlockType& BlockType)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);

	check(GameInstance);

	UVoxelSubsystem* VoxelSubsystem = GameInstance->GetSubsystem<UVoxelSubsystem>();
	
	check(VoxelSubsystem);

	VoxelSubsystem->BlockTypes.Add(Name, BlockType);
}
