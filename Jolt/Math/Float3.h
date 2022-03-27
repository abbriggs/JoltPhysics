// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Jolt/Core/HashCombine.h>

namespace JPH {

/// Class that holds 3 floats. Used as a storage class. Convert to Vec3 for calculations.
class [[nodiscard]] Float3
{
public:
				Float3() = default; ///< Intentionally not initialized for performance reasons
				Float3(const Float3 &inRHS) = default;
				Float3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) { }

	float		operator [] (int inCoordinate) const	
	{ 
		JPH_ASSERT(inCoordinate < 3); 
		return *(&x + inCoordinate); 
	}

	bool		operator == (const Float3 &inRHS) const
	{
		return x == inRHS.x && y == inRHS.y && z == inRHS.z;
	}

	bool		operator != (const Float3 &inRHS) const
	{
		return x != inRHS.x || y != inRHS.y || z != inRHS.z;
	}

	float		x;
	float		y;
	float		z;
};

using VertexList = vector<Float3>;

static_assert(is_trivial<Float3>(), "Is supposed to be a trivial type!");

} // JPH

// Create a std::hash for Float3
JPH_MAKE_HASHABLE(JPH::Float3, t.x, t.y, t.z)
