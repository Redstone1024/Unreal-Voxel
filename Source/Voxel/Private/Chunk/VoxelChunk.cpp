#include "Chunk/VoxelChunk.h"

#include "VoxelLog.h"
#include "VoxelWorld.h"
#include "VoxelSubsystem.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

bool FVoxelChunkData::Serialize(FArchive & Slot)
{
	UScriptStruct* VoxelBlockStruct = FVoxelBlock::StaticStruct();

	for (int32 X = 0; X < 16; ++X)
	{
		for (int32 Y = 0; Y < 16; ++Y)
		{
			for (int32 Z = 0; Z < 256; ++Z)
			{
				VoxelBlockStruct->SerializeItem(Slot, &Blocks[X][Y][Z], nullptr);
			}
		}
	}

	return true;
}

AVoxelChunk::AVoxelChunk(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MeshComponents.SetNum(16);
	for (int32 i = 0; i < 16; ++i)
	{
		FString ComponentName = FString::Printf(TEXT("MeshComponent_%d"), i);
		MeshComponents[i] = CreateDefaultSubobject<UProceduralMeshComponent>(FName(ComponentName));
		MeshComponents[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

	FlushMeshFlags = -1;
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = GetGameInstance();
	VoxelSubsystem = GameInstance->GetSubsystem<UVoxelSubsystem>();

	AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
	FlushMaterials();

	ArchiveFile = VoxelWorld->GetWorldSetting().ArchiveFolder / FString::Printf(TEXT("%08X%08X"), ChunkLocation.X, ChunkLocation.Y);

	FSaveStructLoadDelegate OnLoaded;
	OnLoaded.BindUFunction(this, TEXT("OnDataLoaded"));
	Data = MakeShared<FSaveStructPtr<FVoxelChunkData>>(GetGameInstance()->GetSubsystem<UAutoSaveSubsystem>(), ArchiveFile, OnLoaded);
	
	check(Data->IsValid());
}

void AVoxelChunk::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Data = nullptr;

	Super::EndPlay(EndPlayReason);
}

const FVoxelBlock & AVoxelChunk::GetBlockByRelativeLocation(const FIntVector & Location) const
{
	checkCode(
		if (!Data->IsLoaded()
			|| !FMath::IsWithin(Location.X, 0, 16)
			|| !FMath::IsWithin(Location.Y, 0, 16)
			|| !FMath::IsWithin(Location.Z, 0, 256))
		{
			UE_LOG(LogVoxel, Warning, TEXT("The Block %d, %d, %d Is Invalid In Chunk %d, %d"), Location.X, Location.Y, Location.Z, ChunkLocation.X, ChunkLocation.Y);
			return FVoxelBlock::InvalidBlock;
		}
	);

	return (*Data)->Blocks[Location.X][Location.Y][Location.Z];
}

void AVoxelChunk::SetBlockByRelativeLocation(const FIntVector& Location, const FVoxelBlock& NewBlock)
{
	checkCode(
		if (!Data->IsLoaded()
			|| !FMath::IsWithin(Location.X, 0, 16)
			|| !FMath::IsWithin(Location.Y, 0, 16)
			|| !FMath::IsWithin(Location.Z, 0, 256))
		{
			UE_LOG(LogVoxel, Warning, TEXT("The Block %d, %d, %d Is Invalid In Chunk %d, %d"), Location.X, Location.Y, Location.Z, ChunkLocation.X, ChunkLocation.Y);
			return;
		}
	);

	(*Data)->Blocks[Location.X][Location.Y][Location.Z] = NewBlock;

	FlushMeshFlags |= 1 << (Location.Z / 16);

	if (Location.Z % 16 == 0 && Location.Z / 16 != 0)
		FlushMeshFlags |= 1 << (Location.Z / 16 - 1);

	if (Location.Z % 16 == 15 && Location.Z / 16 != 15)
		FlushMeshFlags |= 1 << (Location.Z / 16 + 1);

	const TMap<FIntPoint, AVoxelChunk*>& Chunks = VoxelWorld->GetChunks();

	if (Location.X == 15)
	{
		FIntPoint NeighborLocation = FIntPoint(ChunkLocation.X + 1, ChunkLocation.Y);

		if (Chunks.Contains(NeighborLocation))
		{
			AVoxelChunk* Neighbor = Chunks[NeighborLocation];
			Neighbor->FlushMeshFlags |= 1 << (Location.Z / 16);
			VoxelWorld->AddChunkToMeshFlushBuffer(NeighborLocation);
		}
	}

	if (Location.X == 0) 
	{
		FIntPoint NeighborLocation = FIntPoint(ChunkLocation.X - 1, ChunkLocation.Y);

		if (Chunks.Contains(NeighborLocation))
		{
			AVoxelChunk* Neighbor = Chunks[NeighborLocation];
			Neighbor->FlushMeshFlags |= 1 << (Location.Z / 16);
			VoxelWorld->AddChunkToMeshFlushBuffer(NeighborLocation);
		}
	}

	if (Location.Y == 15)
	{
		FIntPoint NeighborLocation = FIntPoint(ChunkLocation.X, ChunkLocation.Y + 1);

		if (Chunks.Contains(NeighborLocation))
		{
			AVoxelChunk* Neighbor = Chunks[NeighborLocation];
			Neighbor->FlushMeshFlags |= 1 << (Location.Z / 16);
			VoxelWorld->AddChunkToMeshFlushBuffer(NeighborLocation);
		}
	}

	if (Location.Y == 0)
	{
		FIntPoint NeighborLocation = FIntPoint(ChunkLocation.X, ChunkLocation.Y - 1);

		if (Chunks.Contains(NeighborLocation))
		{
			AVoxelChunk* Neighbor = Chunks[NeighborLocation];
			Neighbor->FlushMeshFlags |= 1 << (Location.Z / 16);
			VoxelWorld->AddChunkToMeshFlushBuffer(NeighborLocation);
		}
	}

	VoxelWorld->AddChunkToMeshFlushBuffer(ChunkLocation);
}

void AVoxelChunk::FlushMeshs()
{
	if (!FlushMeshFlags) return;

	for (int32 i = 0; i < 16; ++i)
	{
		int32 FlushMeshFlag = 1 << i;

		if (!(FlushMeshFlags & FlushMeshFlag))
			continue;

		FlushMeshSection(i);
	}

	FlushMeshFlags = 0;
}

void AVoxelChunk::FlushMaterials()
{
	for (int32 i = 0; i < 16; ++i)
	{
		for (int32 j = 0; j < VoxelSubsystem->Materials.Num(); ++j)
		{
			MeshComponents[i]->SetMaterial(j, VoxelSubsystem->Materials[j]);
		}
	}
}

void AVoxelChunk::FlushMeshSection(int32 SectionIndex)
{
	if (!Data->IsLoaded()) return;

	static FVoxelMeshData CubeTopFaceBuffer = FVoxelMeshData::CubeTopFace;
	static FVoxelMeshData CubeBottomFaceBuffer = FVoxelMeshData::CubeBottomFace;
	static FVoxelMeshData CubeFrontFaceBuffer = FVoxelMeshData::CubeFrontFace;
	static FVoxelMeshData CubeBackFaceBuffer = FVoxelMeshData::CubeBackFace;
	static FVoxelMeshData CubeLeftFaceBuffer = FVoxelMeshData::CubeLeftFace;
	static FVoxelMeshData CubeRightFaceBuffer = FVoxelMeshData::CubeRightFace;

	MeshSectionBuffer.Reset();

	FIntPoint FrontChunkLocation = FIntPoint(ChunkLocation.X + 1, ChunkLocation.Y);
	FIntPoint BackChunkLocation  = FIntPoint(ChunkLocation.X - 1, ChunkLocation.Y);
	FIntPoint RightChunkLocation = FIntPoint(ChunkLocation.X, ChunkLocation.Y + 1);
	FIntPoint LeftChunkLocation  = FIntPoint(ChunkLocation.X, ChunkLocation.Y - 1);

	const TMap<FIntPoint, AVoxelChunk*>& Chunks = VoxelWorld->GetChunks();
	AVoxelChunk* FrontChunk = Chunks.Contains(FrontChunkLocation) ? Chunks[FrontChunkLocation] : nullptr;
	AVoxelChunk* BackChunk  = Chunks.Contains(BackChunkLocation)  ? Chunks[BackChunkLocation]  : nullptr;
	AVoxelChunk* RightChunk = Chunks.Contains(RightChunkLocation) ? Chunks[RightChunkLocation] : nullptr;
	AVoxelChunk* LeftChunk  = Chunks.Contains(LeftChunkLocation)  ? Chunks[LeftChunkLocation]  : nullptr;

	for (int32 X = 0; X < 16; ++X)
	{
		for (int32 Y = 0; Y < 16; ++Y)
		{
			for (int32 Z = 0 + SectionIndex * 16; Z < 16 + SectionIndex * 16; ++Z)
			{
				const FVoxelBlockType& CurrentVoxelBlock = VoxelSubsystem->GetBlockType((*Data)->Blocks[X][Y][Z].Type);

				if (CurrentVoxelBlock.Shape != EVoxelBlockShape::Cube) continue;
				
				const FVoxelBlockType& TopVoxelBlock    = VoxelSubsystem->GetBlockType(Z + 1 < 256 ? (*Data)->Blocks[X][Y][Z + 1].Type : TEXT("Air"));
				const FVoxelBlockType& BottomVoxelBlock = VoxelSubsystem->GetBlockType(Z - 1 >= 0 ? (*Data)->Blocks[X][Y][Z - 1].Type : TEXT("Air"));
				const FVoxelBlockType& FrontVoxelBlock  = VoxelSubsystem->GetBlockType(X + 1 < 16 ? (*Data)->Blocks[X + 1][Y][Z].Type : (FrontChunk ? FrontChunk->GetBlockByRelativeLocation(FIntVector(0, Y, Z)).Type : TEXT("Air")));
				const FVoxelBlockType& BackVoxelBlock   = VoxelSubsystem->GetBlockType(X - 1 >= 0 ? (*Data)->Blocks[X - 1][Y][Z].Type : (BackChunk  ? BackChunk->GetBlockByRelativeLocation(FIntVector(15, Y, Z)).Type : TEXT("Air")));
				const FVoxelBlockType& LeftVoxelBlock   = VoxelSubsystem->GetBlockType(Y - 1 >= 0 ? (*Data)->Blocks[X][Y - 1][Z].Type : (LeftChunk  ? LeftChunk->GetBlockByRelativeLocation(FIntVector(X, 15, Z)).Type : TEXT("Air")));
				const FVoxelBlockType& RightVoxelBlock  = VoxelSubsystem->GetBlockType(Y + 1 < 16 ? (*Data)->Blocks[X][Y + 1][Z].Type : (RightChunk ? RightChunk->GetBlockByRelativeLocation(FIntVector(X, 0, Z)).Type : TEXT("Air")));
				
				if (TopVoxelBlock.Shape != EVoxelBlockShape::Cube)
				{
					for (FVector2D& UV3 : CubeTopFaceBuffer.UV3)
						UV3 = CurrentVoxelBlock.CustomTopFaceUV;

					MeshSectionBuffer.Append(CubeTopFaceBuffer, FVector(X, Y, Z) * 100.0f);
				}

				if (BottomVoxelBlock.Shape != EVoxelBlockShape::Cube)
				{
					for (FVector2D& UV3 : CubeBottomFaceBuffer.UV3)
						UV3 = CurrentVoxelBlock.CustomBottomFaceUV;

					MeshSectionBuffer.Append(CubeBottomFaceBuffer, FVector(X, Y, Z) * 100.0f);
				}

				if (FrontVoxelBlock.Shape != EVoxelBlockShape::Cube)
				{
					for (FVector2D& UV3 : CubeFrontFaceBuffer.UV3)
						UV3 = CurrentVoxelBlock.CustomFrontFaceUV;

					MeshSectionBuffer.Append(CubeFrontFaceBuffer, FVector(X, Y, Z) * 100.0f);
				}

				if (BackVoxelBlock.Shape != EVoxelBlockShape::Cube)
				{
					for (FVector2D& UV3 : CubeBackFaceBuffer.UV3)
						UV3 = CurrentVoxelBlock.CustomBackFaceUV;

					MeshSectionBuffer.Append(CubeBackFaceBuffer, FVector(X, Y, Z) * 100.0f);
				}

				if (LeftVoxelBlock.Shape != EVoxelBlockShape::Cube)
				{
					for (FVector2D& UV3 : CubeLeftFaceBuffer.UV3)
						UV3 = CurrentVoxelBlock.CustomLeftFaceUV;

					MeshSectionBuffer.Append(CubeLeftFaceBuffer, FVector(X, Y, Z) * 100.0f);
				}

				if (RightVoxelBlock.Shape != EVoxelBlockShape::Cube)
				{
					for (FVector2D& UV3 : CubeRightFaceBuffer.UV3)
						UV3 = CurrentVoxelBlock.CustomRightFaceUV;

					MeshSectionBuffer.Append(CubeRightFaceBuffer, FVector(X, Y, Z) * 100.0f);
				}
			}
		}
	}
	
	MeshComponents[SectionIndex]->CreateMeshSection_LinearColor
	(
		0,
		MeshSectionBuffer.Vertices,
		MeshSectionBuffer.Triangles,
		MeshSectionBuffer.Normals, 
		MeshSectionBuffer.UV0,
		MeshSectionBuffer.UV1,
		MeshSectionBuffer.UV2, 
		MeshSectionBuffer.UV3,
		MeshSectionBuffer.VertexColors,
		TArray<FProcMeshTangent>(),
		true
	);
}

void AVoxelChunk::OnDataLoaded(const FString & Filename)
{
	VoxelWorld->AddChunkToMeshFlushBuffer(ChunkLocation);
}
