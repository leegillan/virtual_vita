#include "VirtualObject.h"

bool VirtualObject::Update ( float frame_time )
{
	// slow the object down
	velocity_ *= 0.9f;
	position_ += velocity_ * frame_time;

	return GameObject::Update(frame_time);
}
