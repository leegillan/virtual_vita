#include "VirtualObject.h"

bool VirtualObject::Update ( float frame_time )
{
	// slow the object down
	velocity *= 0.9f;
	position += velocity * frame_time;

	return GameObject::Update(frame_time);
}
