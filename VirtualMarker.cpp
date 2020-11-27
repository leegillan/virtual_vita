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
	velocity_.set_z ( 0.0f );
	VirtualObject::Update ( frame_time );

	rotationalAccelaration *= 0.9f;
	rotation += rotationalAccelaration;

	gef::Matrix44 scale;
	scale.Scale ( scale_ );

	gef::Matrix44 rotate;
	rotate.RotationZ ( rotation );

	gef::Matrix44 transform = rotate;
	transform.SetTranslation ( position_ );
	marker_transform = transform;

	transform = scale * rotate;
	transform.SetTranslation ( position_ );
	set_transform ( transform );


	
	return true;
}