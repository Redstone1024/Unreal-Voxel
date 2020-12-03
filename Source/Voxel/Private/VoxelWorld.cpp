#include "VoxelWorld.h"

#include "VoxelLog.h"
#include "VoxelBlock.h"
#include "VoxelChunk.h"
#include "VoxelHelper.h"
#include "VoxelSubsystem.h"
#include "VoxelAgentInterface.h"

const TArray<FIntPoint> ChunkLoadOrder =
{ 
	{   0,   0 },
	{   0,  -1 }, {  -1,   0 }, {   0,   1 }, {   1,   0 }, {  -1,  -1 }, {   1,  -1 }, {  -1,   1 }, {   1,   1 },
	{   2,   0 }, {  -2,   0 }, {   0,  -2 }, {   0,   2 }, {  -2,   1 }, {   1,   2 }, {   1,  -2 }, {  -1,  -2 },
	{   2,   1 }, {   2,  -1 }, {  -1,   2 }, {  -2,  -1 }, {  -2,  -2 }, {   2,   2 }, {   2,  -2 }, {  -2,   2 },
	{   0,  -3 }, {   3,   0 }, {  -3,   0 }, {   0,   3 }, {   3,  -1 }, {  -3,   1 }, {   1,  -3 }, {  -1,  -3 },
	{  -1,   3 }, {   1,   3 }, {   3,   1 }, {  -3,  -1 }, {   3,  -2 }, {   2,  -3 }, {  -3,   2 }, {  -3,  -2 },
	{   3,   2 }, {  -2,  -3 }, {  -2,   3 }, {   2,   3 }, {   4,   0 }, {   0,   4 }, {  -4,   0 }, {   0,  -4 },
	{   4,   1 }, {  -1,   4 }, {  -4,   1 }, {   4,  -1 }, {   1,  -4 }, {   1,   4 }, {  -4,  -1 }, {  -1,  -4 },
	{   3,  -3 }, {  -3,   3 }, {  -3,  -3 }, {   3,   3 }, {   4,  -2 }, {  -2,   4 }, {  -2,  -4 }, {  -4,  -2 },
	{  -4,   2 }, {   2,   4 }, {   2,  -4 }, {   4,   2 }, {   3,  -4 }, {  -5,   0 }, {   0,   5 }, {  -3,   4 },
	{   4,  -3 }, {  -4,   3 }, {   5,   0 }, {   4,   3 }, {  -4,  -3 }, {   0,  -5 }, {   3,   4 }, {  -3,  -4 },
	{  -5,  -1 }, {  -5,   1 }, {   5,  -1 }, {   5,   1 }, {  -1,   5 }, {  -1,  -5 }, {   1,  -5 }, {   1,   5 },
	{   5,  -2 }, {   5,   2 }, {   2,  -5 }, {  -2,  -5 }, {  -5,   2 }, {  -5,  -2 }, {   2,   5 }, {  -2,   5 },
	{  -4,   4 }, {   4,   4 }, {  -4,  -4 }, {   4,  -4 }, {  -5,  -3 }, {  -3,   5 }, {   5,   3 }, {   3,   5 },
	{  -5,   3 }, {   3,  -5 }, {   5,  -3 }, {  -3,  -5 }, {  -6,   0 }, {   0,   6 }, {   6,   0 }, {   0,  -6 },
	{   6,  -1 }, {  -6,  -1 }, {  -6,   1 }, {  -1,   6 }, {  -1,  -6 }, {   1,  -6 }, {   1,   6 }, {   6,   1 },
	{   2,  -6 }, {  -6,  -2 }, {   6,   2 }, {   2,   6 }, {  -6,   2 }, {  -2,   6 }, {  -2,  -6 }, {   6,  -2 },
	{   4,  -5 }, {   5,  -4 }, {  -5,   4 }, {   5,   4 }, {  -5,  -4 }, {  -4,  -5 }, {   4,   5 }, {  -4,   5 },
	{  -6,  -3 }, {   3,  -6 }, {  -3,  -6 }, {  -6,   3 }, {   6,   3 }, {   3,   6 }, {   6,  -3 }, {  -3,   6 },
	{   0,   7 }, {   0,  -7 }, {   7,   0 }, {  -7,   0 }, {   5,  -5 }, {   1,   7 }, {  -7,  -1 }, {  -7,   1 },
	{   1,  -7 }, {  -1,  -7 }, {  -5,  -5 }, {   7,   1 }, {   5,   5 }, {  -1,   7 }, {   7,  -1 }, {  -5,   5 },
	{   6,  -4 }, {  -4,  -6 }, {  -6,   4 }, {  -6,  -4 }, {   6,   4 }, {   4,   6 }, {   4,  -6 }, {  -4,   6 },
	{  -2,   7 }, {   7,   2 }, {  -2,  -7 }, {  -7,  -2 }, {   2,  -7 }, {   2,   7 }, {   7,  -2 }, {  -7,   2 },
	{  -7,   3 }, {   7,   3 }, {  -7,  -3 }, {  -3,  -7 }, {  -3,   7 }, {   7,  -3 }, {   3,   7 }, {   3,  -7 },
	{   6,  -5 }, {  -5,   6 }, {   6,   5 }, {  -6,  -5 }, {  -5,  -6 }, {   5,  -6 }, {   5,   6 }, {  -6,   5 },
	{   0,  -8 }, {   0,   8 }, {  -8,   0 }, {   8,   0 }, {   7,   4 }, {  -4,  -7 }, {   7,  -4 }, {   1,   8 },
	{  -1,  -8 }, {   1,  -8 }, {   4,  -7 }, {   4,   7 }, {  -7,  -4 }, {  -7,   4 }, {  -8,   1 }, {  -8,  -1 },
	{  -1,   8 }, {   8,   1 }, {   8,  -1 }, {  -4,   7 }, {   2,  -8 }, {  -2,   8 }, {  -2,  -8 }, {  -8,  -2 },
	{   8,   2 }, {   2,   8 }, {  -8,   2 }, {   8,  -2 }, {  -6,   6 }, {  -6,  -6 }, {   6,   6 }, {   6,  -6 },
	{   8,  -3 }, {   3,   8 }, {  -3,   8 }, {   8,   3 }, {   3,  -8 }, {  -8,  -3 }, {  -8,   3 }, {  -3,  -8 },
	{  -5,  -7 }, {   5,   7 }, {   7,  -5 }, {  -7,  -5 }, {   7,   5 }, {  -7,   5 }, {  -5,   7 }, {   5,  -7 },
	{   4,   8 }, {  -4,   8 }, {  -8,   4 }, {  -8,  -4 }, {   4,  -8 }, {   8,  -4 }, {   8,   4 }, {  -4,  -8 },
	{   0,  -9 }, {   0,   9 }, {  -9,   0 }, {   9,   0 }, {  -1,  -9 }, {   1,   9 }, {   9,  -1 }, {  -1,   9 },
	{   1,  -9 }, {  -9,   1 }, {  -9,  -1 }, {   9,   1 }, {   6,   7 }, {  -7,   6 }, {  -9,  -2 }, {   2,   9 },
	{  -2,  -9 }, {  -2,   9 }, {   9,   2 }, {  -6,  -7 }, {   7,  -6 }, {  -6,   7 }, {   7,   6 }, {   6,  -7 },
	{   2,  -9 }, {   9,  -2 }, {  -9,   2 }, {  -7,  -6 }, {   8,  -5 }, {  -5,   8 }, {  -8,  -5 }, {   5,   8 },
	{  -5,  -8 }, {   8,   5 }, {   5,  -8 }, {  -8,   5 }, {  -3,   9 }, {  -9,   3 }, {  -9,  -3 }, {   9,  -3 },
	{   3,   9 }, {  -3,  -9 }, {   3,  -9 }, {   9,   3 }, {  -4,   9 }, {  -9,  -4 }, {  -4,  -9 }, {   4,   9 },
	{   9,   4 }, {   4,  -9 }, {  -9,   4 }, {   9,  -4 }, {   7,   7 }, {  -7,   7 }, {  -7,  -7 }, {   7,  -7 },
	{  -6,  -8 }, {  10,   0 }, {   8,  -6 }, {  -8,  -6 }, {   8,   6 }, {   6,  -8 }, {  -6,   8 }, {   0, -10 },
	{   0,  10 }, {  -8,   6 }, {   6,   8 }, { -10,   0 }, {  10,  -1 }, { -10,  -1 }, {  -1, -10 }, { -10,   1 },
	{  -1,  10 }, {  10,   1 }, {   1,  10 }, {   1, -10 }, {   2,  10 }, { -10,   2 }, { -10,  -2 }, {  -2,  10 },
	{   2, -10 }, {  10,  -2 }, {  -2, -10 }, {  10,   2 }, {  -9,  -5 }, {  -9,   5 }, {  -5,  -9 }, {   9,  -5 },
	{   9,   5 }, {   5,   9 }, {   5,  -9 }, {  -5,   9 }, {   3,  10 }, { -10,   3 }, {   3, -10 }, {  -3,  10 },
	{  10,  -3 }, { -10,  -3 }, {  10,   3 }, {  -3, -10 }, {   8,  -7 }, {   8,   7 }, {   7,   8 }, {  -7,   8 },
	{  -7,  -8 }, {   7,  -8 }, {  -8,   7 }, {  -8,  -7 }, {   4, -10 }, {  10,   4 }, {  -4, -10 }, { -10,  -4 },
	{  10,  -4 }, {  -4,  10 }, {   4,  10 }, { -10,   4 }, {  -6,  -9 }, {   6,  -9 }, {   6,   9 }, {  -9,  -6 },
	{  -9,   6 }, {   9,  -6 }, {   9,   6 }, {  -6,   9 }, {   0,  11 }, {  11,   0 }, {   0, -11 }, { -11,   0 },
	{   1,  11 }, {  -1, -11 }, {  -1,  11 }, { -11,  -1 }, {  11,   1 }, {  11,  -1 }, {   1, -11 }, { -11,   1 },
	{  -5, -10 }, {  -2, -11 }, {  11,   2 }, { -10,  -5 }, {   2,  11 }, {  10,  -5 }, {   5, -10 }, {  11,  -2 },
	{  -5,  10 }, { -11,   2 }, {  10,   5 }, {   5,  10 }, {   2, -11 }, { -11,  -2 }, { -10,   5 }, {  -2,  11 },
	{  -8,  -8 }, {  -8,   8 }, {   8,   8 }, {   8,  -8 }, {   7,   9 }, { -11,   3 }, { -11,  -3 }, {  11,  -3 },
	{   9,   7 }, {  -3, -11 }, {   3, -11 }, {   7,  -9 }, {  -9,   7 }, {  -7,  -9 }, {  -9,  -7 }, {  11,   3 },
	{   9,  -7 }, {  -7,   9 }, {  -3,  11 }, {   3,  11 }, {  10,  -6 }, {  10,   6 }, { -10,  -6 }, {  -6, -10 },
	{  -6,  10 }, { -10,   6 }, {   6, -10 }, {   6,  10 }, {  -4,  11 }, { -11,   4 }, {  -4, -11 }, { -11,  -4 },
	{  11,  -4 }, {  11,   4 }, {   4, -11 }, {   4,  11 }, {  12,   0 }, {   0,  12 }, {   0, -12 }, { -12,   0 },
	{  12,  -1 }, {   8,  -9 }, { -12,  -1 }, {   1,  12 }, {  -1, -12 }, { -12,   1 }, {  12,   1 }, {   9,  -8 },
	{  -1,  12 }, {   1, -12 }, {  -9,   8 }, {  -8,  -9 }, {  -9,  -8 }, {  -8,   9 }, {   9,   8 }, {   8,   9 },
	{ -11,  -5 }, {   5, -11 }, {  11,   5 }, {  -5,  11 }, {  -5, -11 }, {   5,  11 }, { -11,   5 }, {  11,  -5 },
	{  12,  -2 }, {  12,   2 }, {  -2,  12 }, { -12,  -2 }, { -12,   2 }, {  -2, -12 }, {   2, -12 }, {   2,  12 },
	{   7,  10 }, {   7, -10 }, { -10,   7 }, {  10,  -7 }, {  -7, -10 }, {  10,   7 }, {  -7,  10 }, { -10,  -7 },
	{  12,  -3 }, {  12,   3 }, {  -3,  12 }, {   3, -12 }, { -12,   3 }, { -12,  -3 }, {  -3, -12 }, {   3,  12 },
	{  -6,  11 }, { -11,  -6 }, { -11,   6 }, {   6,  11 }, {  11,   6 }, {  -6, -11 }, {   6, -11 }, {  11,  -6 },
	{  12,  -4 }, {  12,   4 }, { -12,   4 }, {   4, -12 }, {  -4, -12 }, { -12,  -4 }, {  -4,  12 }, {   4,  12 },
	{   9,  -9 }, {  -9,  -9 }, {   9,   9 }, {  -9,   9 }, { -10,  -8 }, {   8, -10 }, { -10,   8 }, {  10,  -8 },
	{  -8,  10 }, {  10,   8 }, {  -8, -10 }, {   8,  10 }, {  12,  -5 }, {   5, -12 }, {   0, -13 }, {  13,   0 },
	{  -5,  12 }, {   5,  12 }, { -12,   5 }, {   0,  13 }, {  -5, -12 }, {  12,   5 }, { -12,  -5 }, { -13,   0 },
	{ -11,  -7 }, {   7, -11 }, {  11,  -7 }, { -13,  -1 }, { -13,   1 }, {  13,  -1 }, {  13,   1 }, {  11,   7 },
	{  -1, -13 }, {  -7,  11 }, {  -7, -11 }, {  -1,  13 }, {   1,  13 }, {   1, -13 }, {   7,  11 }, { -11,   7 },
	{  -2,  13 }, {   2,  13 }, { -13,   2 }, {   2, -13 }, {  -2, -13 }, {  13,  -2 }, { -13,  -2 }, {  13,   2 },
	{ -13,   3 }, {   3,  13 }, {   3, -13 }, { -13,  -3 }, {  -3,  13 }, {  -3, -13 }, {  13,  -3 }, {  13,   3 },
	{   6, -12 }, { -12,   6 }, {  12,  -6 }, {  -6, -12 }, { -12,  -6 }, {  -6,  12 }, {   6,  12 }, {  12,   6 },
	{  10,  -9 }, { -10,   9 }, {  -9, -10 }, {   9, -10 }, {   9,  10 }, {  -9,  10 }, { -10,  -9 }, {  10,   9 },
	{   8,  11 }, {   8, -11 }, {  11,  -8 }, {  13,   4 }, {  -8,  11 }, {  -8, -11 }, {   4,  13 }, {  -4, -13 },
	{  -4,  13 }, {  11,   8 }, {  13,  -4 }, { -11,  -8 }, { -13,   4 }, { -11,   8 }, {   4, -13 }, { -13,  -4 },
	{  12,  -7 }, {  12,   7 }, { -12,  -7 }, {   7, -12 }, {   7,  12 }, { -12,   7 }, {  -7,  12 }, {  -7, -12 },
	{  13,   5 }, {  -5,  13 }, { -13,  -5 }, {   5, -13 }, { -13,   5 }, {   5,  13 }, {  13,  -5 }, {  -5, -13 },
	{ -14,   0 }, {   0,  14 }, {   0, -14 }, {  14,   0 }, { -14,   1 }, {   1, -14 }, { -14,  -1 }, {  -1,  14 },
	{  -1, -14 }, {   1,  14 }, {  14,  -1 }, {  14,   1 }, {  -2, -14 }, {   2, -14 }, {   2,  14 }, { -10, -10 },
	{ -14,   2 }, {  10,  10 }, { -14,  -2 }, {  10, -10 }, {  -2,  14 }, { -10,  10 }, {  14,  -2 }, {  14,   2 },
	{  11,   9 }, {  11,  -9 }, { -11,  -9 }, { -11,   9 }, {   9,  11 }, {  -9,  11 }, {  -9, -11 }, {   9, -11 },
	{   6, -13 }, { -13,  -6 }, { -14,   3 }, {  -6,  13 }, {   6,  13 }, {   3, -14 }, {  -3,  14 }, { -14,  -3 },
	{  13,   6 }, {  14,  -3 }, {  13,  -6 }, {   3,  14 }, {  -6, -13 }, { -13,   6 }, {  -3, -14 }, {  14,   3 },
	{  -8, -12 }, {   8,  12 }, {  -8,  12 }, { -12,   8 }, {  12,  -8 }, { -12,  -8 }, {   8, -12 }, {  12,   8 },
	{   4,  14 }, { -14,   4 }, {  14,   4 }, {  14,  -4 }, {  -4, -14 }, {   4, -14 }, {  -4,  14 }, { -14,  -4 },
	{   7,  13 }, {  -7, -13 }, { -13,   7 }, { -13,  -7 }, {  13,  -7 }, {  -7,  13 }, {   7, -13 }, {  13,   7 },
	{ -10, -11 }, {   5, -14 }, { -11, -10 }, {   5,  14 }, { -11,  10 }, {  14,  -5 }, { -14,   5 }, { -14,  -5 },
	{  10, -11 }, {  10,  11 }, {  11, -10 }, {  11,  10 }, {  -5,  14 }, {  -5, -14 }, { -10,  11 }, {  14,   5 },
	{   0,  15 }, {   9,  12 }, { -12,   9 }, {  -9,  12 }, {  15,   0 }, {  12,  -9 }, {  12,   9 }, {   0, -15 },
	{ -15,   0 }, { -12,  -9 }, {   9, -12 }, {  -9, -12 }, {   1,  15 }, {  15,   1 }, { -15,  -1 }, {  -1,  15 },
	{  -1, -15 }, {  15,  -1 }, { -15,   1 }, {   1, -15 }, { -15,  -2 }, {   2, -15 }, {  15,   2 }, {  -2, -15 },
	{   2,  15 }, {  15,  -2 }, {  -2,  15 }, { -15,   2 }, {  -6,  14 }, {  14,  -6 }, { -14,   6 }, {  -6, -14 },
	{   6,  14 }, { -14,  -6 }, {   6, -14 }, {  14,   6 }, {   8,  13 }, {  13,   8 }, {  -8, -13 }, {  13,  -8 },
	{ -13,  -8 }, {  -8,  13 }, { -13,   8 }, {   8, -13 }, {   3,  15 }, {  15,   3 }, {  -3, -15 }, { -15,  -3 },
	{  -3,  15 }, { -15,   3 }, {   3, -15 }, {  15,  -3 }, {  15,   4 }, {   4, -15 }, {  -4, -15 }, {   4,  15 },
	{  -4,  15 }, {  15,  -4 }, { -15,   4 }, { -15,  -4 }, { -11, -11 }, {  11, -11 }, { -11,  11 }, {  11,  11 },
	{  12,  10 }, { -12,  10 }, { -10, -12 }, { -10,  12 }, {  10, -12 }, {  10,  12 }, { -12, -10 }, {  12, -10 },
	{   7, -14 }, {  14,   7 }, { -14,   7 }, {  14,  -7 }, {   7,  14 }, { -14,  -7 }, {  -7, -14 }, {  -7,  14 },
	{ -15,   5 }, { -13,  -9 }, {  -5, -15 }, {  13,  -9 }, {  -9, -13 }, {   9, -13 }, {   5,  15 }, {  -9,  13 },
	{   9,  13 }, {  13,   9 }, {  -5,  15 }, { -13,   9 }, {   5, -15 }, {  15,   5 }, { -15,  -5 }, {  15,  -5 },
	{   0,  16 }, { -16,   0 }, {   0, -16 }, {  16,   0 }, { -16,   1 }, { -16,  -1 }, {   1,  16 }, {  -1,  16 },
	{   1, -16 }, {  -1, -16 }, {  16,  -1 }, {  16,   1 }, {   2, -16 }, { -14,   8 }, {  -2,  16 }, {   8,  14 },
	{  14,   8 }, {  -2, -16 }, {  -8, -14 }, {  -8,  14 }, { -14,  -8 }, {  16,   2 }, {  16,  -2 }, {   2,  16 },
	{  14,  -8 }, { -16,   2 }, { -16,  -2 }, {   8, -14 }, {   6,  15 }, {   6, -15 }, {  -6, -15 }, {  15,  -6 },
	{ -15,   6 }, {  15,   6 }, { -15,  -6 }, {  -6,  15 }, {  -3,  16 }, {   3,  16 }, {  11,  12 }, {  12, -11 },
	{  12,  11 }, { -11,  12 }, {  16,  -3 }, {  16,   3 }, { -16,   3 }, { -16,  -3 }, {  -3, -16 }, { -12, -11 },
	{  11, -12 }, { -11, -12 }, { -12,  11 }, {   3, -16 }, { -10, -13 }, { -10,  13 }, { -13,  10 }, {  13, -10 },
	{  10, -13 }, {  10,  13 }, {  13,  10 }, { -13, -10 }, {  16,  -4 }, {  -4, -16 }, {  16,   4 }, {   4,  16 },
	{   4, -16 }, {  -4,  16 }, { -16,  -4 }, { -16,   4 }, {   7, -15 }, {  15,  -7 }, {  -7,  15 }, {  15,   7 },
	{   7,  15 }, {  -7, -15 }, { -15,   7 }, { -15,  -7 }, { -14,   9 }, {  -9, -14 }, {   9, -14 }, {  -9,  14 },
	{  14,   9 }, {  14,  -9 }, {   9,  14 }, { -14,  -9 }, { -16,  -5 }, {  -5, -16 }, {   5,  16 }, {  16,  -5 },
	{   5, -16 }, {  -5,  16 }, { -16,   5 }, {  16,   5 }, { -12,  12 }, {  12,  12 }, {  12, -12 }, { -12, -12 },
	{ -15,  -8 }, {   8,  15 }, {   8, -15 }, {  -8,  15 }, {  -8, -15 }, {  15,  -8 }, {  15,   8 }, { -15,   8 },
	{  13, -11 }, {  11, -13 }, { -11,  13 }, { -11, -13 }, {  11,  13 }, {  13,  11 }, { -13,  11 }, { -13, -11 },
	{  16,  -6 }, {  -6,  16 }, {   6, -16 }, { -16,   6 }, {  16,   6 }, { -16,  -6 }, {   6,  16 }, {  -6, -16 },
	{  14,  10 }, { -10,  14 }, {  14, -10 }, { -10, -14 }, {  10, -14 }, { -14,  10 }, { -14, -10 }, {  10,  14 },
	{ -16,  -7 }, {  16,  -7 }, {  -7, -16 }, {  -7,  16 }, {  16,   7 }, {   7,  16 }, { -16,   7 }, {   7, -16 },
	{   9, -15 }, {  15,  -9 }, {   9,  15 }, {  15,   9 }, { -15,   9 }, { -15,  -9 }, {  -9, -15 }, {  -9,  15 },
	{  13, -12 }, { -12,  13 }, { -12, -13 }, {  13,  12 }, {  12, -13 }, { -13, -12 }, {  12,  13 }, { -13,  12 },
	{ -14,  11 }, {  14, -11 }, { -14, -11 }, { -11, -14 }, { -11,  14 }, {  11, -14 }, {  14,  11 }, {  11,  14 },
	{ -16,  -8 }, { -16,   8 }, {  -8,  16 }, {   8, -16 }, {  16,  -8 }, {   8,  16 }, {  -8, -16 }, {  16,   8 },
	{  15,  10 }, { -10, -15 }, { -15,  10 }, { -15, -10 }, {  10,  15 }, {  10, -15 }, {  15, -10 }, { -10,  15 },
	{   9,  16 }, {  -9, -16 }, {  16,  -9 }, { -16,  -9 }, {  -9,  16 }, {   9, -16 }, { -16,   9 }, {  16,   9 },
	{ -13, -13 }, { -13,  13 }, {  13,  13 }, {  13, -13 }, {  12,  14 }, { -12,  14 }, { -12, -14 }, {  14,  12 },
	{  12, -14 }, {  14, -12 }, { -14, -12 }, { -14,  12 }, {  11, -15 }, { -11, -15 }, { -15, -11 }, { -11,  15 },
	{  15,  11 }, {  15, -11 }, { -15,  11 }, {  11,  15 }, { -10,  16 }, { -16, -10 }, { -10, -16 }, {  16, -10 },
	{  10, -16 }, {  10,  16 }, {  16,  10 }, { -16,  10 }, {  14, -13 }, {  13,  14 }, {  14,  13 }, {  13, -14 },
	{ -13, -14 }, { -14, -13 }, { -13,  14 }, { -14,  13 }, { -15, -12 }, {  15, -12 }, { -12, -15 }, { -15,  12 },
	{ -12,  15 }, {  12, -15 }, {  12,  15 }, {  15,  12 }, { -11,  16 }, {  16, -11 }, {  11, -16 }, { -11, -16 },
	{ -16,  11 }, { -16, -11 }, {  11,  16 }, {  16,  11 }, {  14,  14 }, { -14, -14 }, {  14, -14 }, { -14,  14 },
	{  15, -13 }, { -13, -15 }, { -15,  13 }, { -13,  15 }, {  15,  13 }, { -15, -13 }, {  13, -15 }, {  13,  15 },
	{  16, -12 }, {  12, -16 }, { -12, -16 }, {  12,  16 }, { -12,  16 }, { -16, -12 }, { -16,  12 }, {  16,  12 },
	{ -15,  14 }, {  14, -15 }, { -15, -14 }, { -14,  15 }, {  14,  15 }, { -14, -15 }, {  15, -14 }, {  15,  14 },
	{  16, -13 }, {  13, -16 }, { -16,  13 }, {  13,  16 }, { -16, -13 }, { -13, -16 }, { -13,  16 }, {  16,  13 },
	{ -15,  15 }, { -15, -15 }, {  15, -15 }, {  15,  15 }, {  16, -14 }, { -16,  14 }, {  14, -16 }, { -16, -14 },
	{ -14, -16 }, { -14,  16 }, {  14,  16 }, {  16,  14 }, {  16, -15 }, { -15, -16 }, { -16,  15 }, { -15,  16 },
	{ -16, -15 }, {  15, -16 }, {  15,  16 }, {  16,  15 }, { -16, -16 }, { -16,  16 }, {  16, -16 }, {  16,  16 },
};

AVoxelWorld::AVoxelWorld(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVoxelWorld::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GameInstance = GetGameInstance();
	VoxelSubsystem = GameInstance->GetSubsystem<UVoxelSubsystem>();
}

void AVoxelWorld::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ManageChunk();

	FlushMeshs();

}

void AVoxelWorld::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TArray<FIntPoint> ChunksToUnload;
	Chunks.GetKeys(ChunksToUnload);

	for (const FIntPoint& Chunk : ChunksToUnload)
		UnloadChunk(Chunk);

	Super::EndPlay(EndPlayReason);
}

const FVoxelBlock & AVoxelWorld::GetBlockByWorldLocation(const FIntVector & Location) const
{
	FIntPoint ChunkLocation;
	FIntVector RelativeLocation;

	UVoxelHelper::WorldToRelativeLocation(Location, ChunkLocation, RelativeLocation);

	if (!Chunks.Contains(ChunkLocation))
	{
		UE_LOG(LogVoxel, Warning, TEXT("The Chunk %d, %d Is Not Loaded, Block %d, %d, %d Is Invalid"), ChunkLocation.X, ChunkLocation.Y, Location.X, Location.Y, Location.Z);
		return FVoxelBlock::InvalidBlock;
	}

	return Chunks[ChunkLocation]->GetBlockByRelativeLocation(RelativeLocation);
}

void AVoxelWorld::SetBlockByWorldLocation(const FIntVector& Location, const FVoxelBlock& NewBlock)
{
	FIntPoint ChunkLocation;
	FIntVector RelativeLocation;

	UVoxelHelper::WorldToRelativeLocation(Location, ChunkLocation, RelativeLocation);

	if (!Chunks.Contains(ChunkLocation))
	{
		UE_LOG(LogVoxel, Warning, TEXT("The Chunk %d, %d Is Not Loaded, Block %d, %d, %d Is Invalid"), ChunkLocation.X, ChunkLocation.Y, Location.X, Location.Y, Location.Z);
		return;
	}

	Chunks[ChunkLocation]->SetBlockByRelativeLocation(RelativeLocation, NewBlock);
}

void AVoxelWorld::LoadChunk(const FIntPoint & ChunkLocation)
{
	if (Chunks.Contains(ChunkLocation)) return;

	UWorld* World = GetWorld();

	check(World);

	AVoxelChunk* NewVoxelChunk = World->SpawnActor<AVoxelChunk>();
	NewVoxelChunk->VoxelWorld = this;
	NewVoxelChunk->ChunkLocation = ChunkLocation;
	NewVoxelChunk->SetActorLocation(FVector(ChunkLocation.X * 1600.0f, ChunkLocation.Y * 1600.0f, 0.0f));
	NewVoxelChunk->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	NewVoxelChunk->FlushMaterials();
	NewVoxelChunk->Load();
	AddChunkToMeshFlushBuffer(ChunkLocation);

	Chunks.Add(ChunkLocation, NewVoxelChunk);

	UE_LOG(LogVoxel, Log, TEXT("The Chunk %d, %d Is Loaded"), ChunkLocation.X, ChunkLocation.Y);
}

void AVoxelWorld::UnloadChunk(const FIntPoint & ChunkLocation)
{
	if (!Chunks.Contains(ChunkLocation)) return;

	Chunks[ChunkLocation]->Unload();
	Chunks[ChunkLocation]->Destroy();

	Chunks.Remove(ChunkLocation);

	UE_LOG(LogVoxel, Log, TEXT("The Chunk %d, %d Is Unload"), ChunkLocation.X, ChunkLocation.Y);
}

void AVoxelWorld::FlushMaterials()
{
	for (const TPair<FIntPoint, AVoxelChunk*>& Chunk : Chunks)
	{
		Chunk.Value->FlushMaterials();
	}
}

void AVoxelWorld::ManageChunk()
{
	FIntPoint RootChunk;
	FIntVector RLocation;
	UVoxelHelper::WorldToRelativeLocation(IVoxelAgentInterface::Execute_GetAgentLocation(CenterAgent.GetObject()), RootChunk, RLocation);

	// Load
	for (const FIntPoint& Chunk : ChunkLoadOrder)
	{
		const FIntPoint WorldLocation = Chunk + RootChunk;
		const FIntPoint RelativeLocation = Chunk;

		const bool bChunkLoaded = Chunks.Contains(WorldLocation);
		const bool bInLoadDistance = FMath::Abs(RelativeLocation.X) < VoxelSubsystem->ChunkLoadDistance && FMath::Abs(RelativeLocation.Y) < VoxelSubsystem->ChunkLoadDistance;

		if (!bChunkLoaded && bInLoadDistance)
		{
			LoadChunk(WorldLocation);
			break;
		}
	}
	
	// Unload
	int32 ChunkUnloadDistance = VoxelSubsystem->ChunkLoadDistance + VoxelSubsystem->ChunkUnloadBuffer;
	for (const TPair<FIntPoint, AVoxelChunk*>& Chunk : Chunks)
	{
		const FIntPoint WorldLocation = Chunk.Key;
		const FIntPoint RelativeLocation = WorldLocation - RootChunk;

		const bool bInUnloadDistance = FMath::Abs(RelativeLocation.X) > ChunkUnloadDistance && FMath::Abs(RelativeLocation.Y) > ChunkUnloadDistance;

		if (bInUnloadDistance)
		{
			UnloadChunk(WorldLocation);
			break;
		}
	}
}

void AVoxelWorld::FlushMeshs()
{
	QUICK_SCOPE_CYCLE_COUNTER(STAT_VoxelWorld_FlushMeshs);

	for (const FIntPoint& ChunkLocation : MeshFlushBuffer)
	{
		if (!Chunks.Contains(ChunkLocation))
			continue;

		AVoxelChunk* ChunkActor = Chunks[ChunkLocation];

		if (!IsValid(ChunkActor))
			continue;

		ChunkActor->FlushMeshs();
	}

	MeshFlushBuffer.Reset();
}
