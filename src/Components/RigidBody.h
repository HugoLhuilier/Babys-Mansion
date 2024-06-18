#pragma once

#include "box2d/box2d.h"
#include "Component.h"

/*
* class to make an object rigid with box2D
*/
class RigidBody : public Component {
public:
	using Component::Component;

	/*
	* Function creating a body with box2d
	*/
	void createBody(b2BodyType type);

	/*
	* Function adding fixture for dynamic objects
	*/
	void addFixture(b2FixtureDef& fixtureDef);

	/*
	* Function adding fixture for static objects
	*/
	void addFixture(b2PolygonShape&);

	/*
	* Function adding a force on the rigidBody
	*/
	void addForce(b2Vec2& force);

	/*
	* Function reseting the speed of the body
	*/
	void resetSpeed();

	/*
	* Function updating the body
	*/
	void update() override;

	/*
	* Function returning a pointer to the body
	*/
	b2Body* getBody() const { return body; }

private:
	b2Body* body = nullptr;	// Not unique_ptr because the body is automatically freed when the world is deleted.
};