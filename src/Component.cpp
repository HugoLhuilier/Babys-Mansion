#include "Component.h"
#include "Object.h"
using namespace std;


Component::Component(Object* nObject)
{
	object = nObject;
	init();
}
