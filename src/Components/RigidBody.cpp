#include "RigidBody.h"
#include "Object.h"
#include <iostream>

using namespace std;


void RigidBody::createBody(b2BodyType type)
{
	if (body) {
		cerr << "A body has already been created." << endl;
		return;
	}

	b2BodyDef bodyDef;
	bodyDef.type = type;
	sf::Vector2f pos = getObject()->getPos();
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = true;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = getObject()->getGame()->getWorld()->CreateBody(&bodyDef);
}

// Used to create fixture for a dynamic object
void RigidBody::addFixture(b2FixtureDef& fixtureDef)
{
	if (!body) {
		cerr << "No body has been created yet." << endl;
		return;
	}

	body->CreateFixture(&fixtureDef);
}

// Used to create fixture for a static object
void RigidBody::addFixture(b2PolygonShape& shape)
{
	if (!body) {
		cerr << "No body has been created yet." << endl;
		return;
	}

	body->CreateFixture(&shape, 0);
}

void RigidBody::addForce(b2Vec2& force)
{
	if (!body) {
		cerr << "No body has been created yet." << endl;
		return;
	}

	body->ApplyForceToCenter(force, true);
}

void RigidBody::resetSpeed()
{
	body->SetLinearVelocity(b2Vec2_zero);
}

void RigidBody::update()
{
	// Update object position ever frame if rigidBody is dynamic (ie can move)
	if (body && body->GetType() == b2BodyType::b2_dynamicBody) {
		b2Vec2 bodyPos = body->GetTransform().p;
		sf::Vector2f nPos(bodyPos.x, bodyPos.y);
		getObject()->updatePos(nPos);
	}
}

