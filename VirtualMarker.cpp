#include "VirtualMarker.h"

VirtualMarker::VirtualMarker () :
	VirtualObject (),
	active(false),
	markerID(0),
	rotation(0.0f),
	rotationalAccelaration(0.0f)
{
	marker_transform.SetIdentity ();
}
 
bool VirtualMarker::Update ( float frame_time )
{
	// clamp the markers to the table
	velocity.set_z ( 0.0f );
	VirtualObject::Update ( frame_time );

	rotationalAccelaration *= 0.9f;
	rotation += rotationalAccelaration;

	gef::Matrix44 scaleMat;
	scaleMat.Scale(scale);

	gef::Matrix44 rotate;
	rotate.RotationZ (rotation);

	gef::Matrix44 transform = rotate;
	transform.SetTranslation ( position );
	marker_transform = transform;

	transform = scaleMat * rotate;
	transform.SetTranslation (position);
	set_transform ( transform );

	return true;
}