#include "ContactListener.h"
#include "Components/RigidBody.h"
#include "Object.h"
#include <iostream>
#include "Components/PlayerController.h"

using namespace std;

void ContactListener::BeginContact(b2Contact* contact) {
	RigidBody* rbA = reinterpret_cast<RigidBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	RigidBody* rbB = reinterpret_cast<RigidBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

	Object* player;
	Object* other;

	if (rbA->getObject()->hasTag(Tag::Player)) {
		player = rbA->getObject();
		other = rbB->getObject();
	} else if (rbB->getObject()->hasTag(Tag::Player)) {
		player = rbB->getObject();
		other = rbA->getObject();
	} else
		return;

	if (other->hasTag(Tag::Baby)) {
		player->getGame()->lose();
		return;
	}

	if (other->hasTag(Tag::Finnish)) {
		player->getGame()->winning();
		return;
	}

	if (other->hasTag(Tag::Lantern)) {
		if (PlayerController* p = player->getComponent<PlayerController>())
			p->triggerBonus();
		else
			cerr << "PlayerController component not found" << endl;
		return;
	}
}