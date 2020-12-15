#include "VirtualVita.h"

bool VirtualVita::Update ( float frame_time )
{
	// slow the object down
	velocity *= 0.9f;

	// don't allow the vita to go too low
	if (position.z() < 0.1f)
	{
		position.set_z ( 0.1f );
		velocity.set_z ( 0.0f );
	}

	gef::Vector4 camera_lookat = gef::Vector4 ( 0.0f, 0.0f, 0.0f );
	gef::Vector4 camera_up = gef::Vector4 ( 0.0f, 0.0f, 1.0f );
	camera_lookAt.LookAt (position, camera_lookat, camera_up );
	inv_camera_lookAt.AffineInverse ( camera_lookAt );

	return	VirtualObject::Update(frame_time);
}