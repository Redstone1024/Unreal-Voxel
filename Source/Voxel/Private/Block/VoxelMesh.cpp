#include "Block/VoxelMesh.h"

const FVoxelMeshData FVoxelMeshData::CubeTopFace =
{
	// Vertices
	{
		{ 0.0f, 0.0f, 100.0f },
		{ 100.0f, 0.0f, 100.0f },
		{ 0.0f, 100.0f, 100.0f },
		{ 100.0f, 100.0f, 100.0f },
	},

	// Triangles
	{
		2, 1, 0,
		2, 3, 1,
	},
	
	// Normals
	{
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
	},
	
	// UV0
	{
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
	},
	
	// UV1
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},
	
	// UV2
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},
	
	// UV3
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},
	
	// VertexColors
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	},
};

const FVoxelMeshData FVoxelMeshData::CubeBottomFace =
{
	// Vertices
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 100.0f, 0.0f, 0.0f },
		{ 0.0f, 100.0f, 0.0f },
		{ 100.0f, 100.0f, 0.0f },
	},

	// Triangles
	{
		0, 1, 2,
		1, 3, 2,
	},

	// Normals
	{
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
	},

	// UV0
	{
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
	},

	// UV1
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV2
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV3
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// VertexColors
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	},
};

const FVoxelMeshData FVoxelMeshData::CubeFrontFace =
{
	// Vertices
	{
		{ 100.0f, 0.0f, 0.0f },
		{ 100.0f, 0.0f, 100.0f },
		{ 100.0f, 100.0f, 0.0f },
		{ 100.0f, 100.0f, 100.0f },
	},

	// Triangles
	{
		0, 1, 2,
		1, 3, 2,
	},

	// Normals
	{
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
	},

	// UV0
	{
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
	},

	// UV1
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV2
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV3
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// VertexColors
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	},
};

const FVoxelMeshData FVoxelMeshData::CubeBackFace =
{
	// Vertices
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 100.0f },
		{ 0.0f, 100.0f, 0.0f },
		{ 0.0f, 100.0f, 100.0f },
	},

	// Triangles
	{
		2, 1, 0,
		2, 3, 1,
	},

	// Normals
	{
		{ -1.0f, 0.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
	},

	// UV0
	{
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
	},

	// UV1
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV2
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV3
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// VertexColors
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	},
};

const FVoxelMeshData FVoxelMeshData::CubeLeftFace =
{
	// Vertices
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 100.0f },
		{ 100.0f, 0.0f, 0.0f },
		{ 100.0f, 0.0f, 100.0f },
	},

	// Triangles
	{
		0, 1, 2,
		1, 3, 2,
	},

	// Normals
	{
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
	},

	// UV0
	{
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
	},

	// UV1
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV2
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV3
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// VertexColors
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	},
};

const FVoxelMeshData FVoxelMeshData::CubeRightFace =
{
	// Vertices
	{
		{ 0.0f, 100.0f, 0.0f },
		{ 0.0f, 100.0f, 100.0f },
		{ 100.0f, 100.0f, 0.0f },
		{ 100.0f, 100.0f, 100.0f },
	},

	// Triangles
	{
		2, 1, 0,
		2, 3, 1,
	},

	// Normals
	{
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
	},

	// UV0
	{
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
	},

	// UV1
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV2
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// UV3
	{
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
	},

	// VertexColors
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	},
};

void FVoxelMeshData::Reset()
{
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	UV0.Reset();
	UV1.Reset();
	UV2.Reset();
	UV3.Reset();
	VertexColors.Reset();
}

void FVoxelMeshData::Append(const FVoxelMeshData & Source)
{
	Vertices.Append(Source.Vertices);
	Triangles.Append(Source.Triangles);
	Normals.Append(Source.Normals);
	UV0.Append(Source.UV0);
	UV1.Append(Source.UV1);
	UV2.Append(Source.UV2);
	UV3.Append(Source.UV3);
	VertexColors.Append(Source.VertexColors);

	for (int32 i = -Source.Triangles.Num(); i < 0; ++i)
		Triangles[Triangles.Num() + i] += Vertices.Num() - Source.Vertices.Num();
}

void FVoxelMeshData::Append(const FVoxelMeshData & Source, const FVector & LocationOffset)
{
	Append(Source);

	for (int32 i = -Source.Vertices.Num(); i < 0; ++i)
		Vertices[Vertices.Num() + i] += LocationOffset;
}
