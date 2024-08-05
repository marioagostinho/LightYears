#include <box2D/b2_body.h>
#include <box2D/b2_polygon_shape.h>
#include <box2D/b2_fixture.h>
#include <box2D/b2_contact.h>

#include "framework/Actor.h"
#include "framework/MathUtility.h"

#include "framework/PhysicsSystem.h"

namespace ly
{
	unique<PhysicsSystem> PhysicsSystem::physicsSystem(nullptr);

	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld(b2Vec2(0.f, 0.f)),
		mPhysicsScale(0.01f),
		mVelocityIterations(8),
		mPositionIterations(3),
		mContactListener(),
		mPendingRemoveListeners()
	{
		mPhysicsWorld.SetContactListener(&mContactListener);
		mPhysicsWorld.SetAllowSleeping(false);
	}

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!physicsSystem)
		{
			physicsSystem = std::move(unique<PhysicsSystem>(new PhysicsSystem));
		}

		return *physicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingdDestroy())
			return nullptr;

		// Body definition
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		// Shape
		auto bound = listener->GetActorGlobalBounds();

		b2PolygonShape shape;
		shape.SetAsBox(bound.width/2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

		// Fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		// Body creation
		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		mPendingRemoveListeners.insert(bodyToRemove);
	}

	// Contact Listener
	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingdDestroy())
		{
			ActorA->OnActorBeginOverlap(ActorB);
		}

		if (ActorB && !ActorB->IsPendingdDestroy())
		{
			ActorB->OnActorBeginOverlap(ActorA);
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (ActorA && !ActorA->IsPendingdDestroy())
		{
			ActorA->OnActorEndOverlap(ActorB);
		}

		if (ActorB && !ActorB->IsPendingdDestroy())
		{
			ActorB->OnActorEndOverlap(ActorA);
		}
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : mPendingRemoveListeners)
		{
			mPhysicsWorld.DestroyBody(listener);
		}

		mPendingRemoveListeners.clear();
	}

	void PhysicsSystem::Cleanup()
	{
		physicsSystem = std::move(unique<PhysicsSystem>(new PhysicsSystem));
	}
}