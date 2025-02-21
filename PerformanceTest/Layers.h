// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Physics/Collision/ObjectLayer.h>
#include <Physics/Collision/BroadPhase/BroadPhaseLayer.h>

/// Layer that objects can be in, determines which other objects it can collide with
namespace Layers
{
	static constexpr uint8 NON_MOVING = 0;
	static constexpr uint8 MOVING = 1;
	static constexpr uint8 NUM_LAYERS = 2;
};

/// Function that determines if two object layers can collide
inline bool ObjectCanCollide(ObjectLayer inObject1, ObjectLayer inObject2)
{
	switch (inObject1)
	{
	case Layers::NON_MOVING:
		return inObject2 == Layers::MOVING; // Non moving only collides with moving
	case Layers::MOVING:
		return true; // Moving collides with everything
	default:
		JPH_ASSERT(false);
		return false;
	}
};

/// Broadphase layers
namespace BroadPhaseLayers
{
	static constexpr BroadPhaseLayer NON_MOVING(0);
	static constexpr BroadPhaseLayer MOVING(1);
};

/// Function that determines if two broadphase layers can collide
inline bool BroadPhaseCanCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2)
{
	switch (inLayer1)
	{
	case Layers::NON_MOVING:
		return inLayer2 == BroadPhaseLayers::MOVING;
	case Layers::MOVING:
		return true;	
	default:
		JPH_ASSERT(false);
		return false;
	}
}

/// Create mapping table from layer to broadphase layer
inline ObjectToBroadPhaseLayer GetObjectToBroadPhaseLayer()
{
	ObjectToBroadPhaseLayer object_to_broadphase;
	object_to_broadphase.resize(Layers::NUM_LAYERS);
	object_to_broadphase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
	object_to_broadphase[Layers::MOVING] = BroadPhaseLayers::MOVING;
	return object_to_broadphase;
}