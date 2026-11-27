#pragma once
#ifndef SIEGE_LAB_LIBRARY_PHYSICS_REGISTRATION_H_
#define SIEGE_LAB_LIBRARY_PHYSICS_REGISTRATION_H_

#include "cyclone/body.h"
#include "cyclone/collide_fine.h"

#include "entity_id.h"

namespace siege_lab
{
	enum class ShapeKind
	{
		kSphere,
		kBox
	};

	struct PhysicsRegistration
	{
		EntityId id{};
		cyclone::RigidBody* body = nullptr;
		cyclone::CollisionPrimitive* collider = nullptr;
		ShapeKind kind = ShapeKind::kSphere;
	};
}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_PHYSICS_REGISTRATION_H_