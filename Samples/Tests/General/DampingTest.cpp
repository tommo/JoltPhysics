// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#include <TestFramework.h>

#include <Tests/General/DampingTest.h>
#include <Physics/Collision/Shape/SphereShape.h>
#include <Physics/Body/BodyCreationSettings.h>
#include <Layers.h>

JPH_IMPLEMENT_RTTI_VIRTUAL(DampingTest) 
{ 
	JPH_ADD_BASE_CLASS(DampingTest, Test) 
}

void DampingTest::Initialize()
{
	// Floor
	CreateFloor();

	RefConst<Shape> sphere = new SphereShape(2.0f);

	// Bodies with increasing damping
	for (int i = 0; i <= 10; ++i)
	{
		Body &body = *mBodyInterface->CreateBody(BodyCreationSettings(sphere, Vec3(-50.0f + i * 10.0f, 2.0f, -80.0f), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING));
#ifdef _DEBUG
		body.SetDebugName(StringFormat("LinearDamping%d", i));
#endif
		body.GetMotionProperties()->SetAngularDamping(0.0f);
		body.GetMotionProperties()->SetLinearDamping(0.1f * i);
		body.SetLinearVelocity(Vec3(0, 0, 10));
		mBodyInterface->AddBody(body.GetID(), EActivation::Activate);
	}

	for (int i = 0; i <= 10; ++i)
	{
		Body &body = *mBodyInterface->CreateBody(BodyCreationSettings(sphere, Vec3(-50.0f + i * 10.0f, 2.0f, -90.0f), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING));
#ifdef _DEBUG
		body.SetDebugName(StringFormat("AngularDamping%d", i));
#endif
		body.GetMotionProperties()->SetLinearDamping(0.0f);
		body.GetMotionProperties()->SetAngularDamping(0.1f * i);
		body.SetAngularVelocity(Vec3(0, 10, 0));
		mBodyInterface->AddBody(body.GetID(), EActivation::Activate);
	}
}