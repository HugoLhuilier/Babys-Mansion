#pragma once

#include "box2d/box2d.h"
#include "Component.h"


class RigidBody : public Component {
public:
	using Component::Component;

	void createBody(b2BodyType type);
	void addFixture(b2FixtureDef& fixtureDef);
	void addFixture(b2PolygonShape&);
	void addForce(b2Vec2& force);
	void resetSpeed();

	void update() override;

	b2Body* getBody() const { return body; }

private:
	b2Body* body = nullptr;	// Not unique_ptr because the body is automatically freed when the world is deleted.
};