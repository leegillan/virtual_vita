#include "VirtualMarker.h"

VirtualMarker::VirtualMarker () :
	VirtualObject (),
	active(false),
	markerID(0)
{
	marker_transform.SetIdentity ();
}
 
bool VirtualMarker::Update ( float frame_time )
{
	// clamp the markers to the table
	velocity_.set_z ( 0.0f );
	VirtualObject::Update ( frame_time );

	// create an unscaled transform
	gef::Matrix44 trans;
	trans.SetIdentity ();
	trans.SetTranslation ( position_ );
	marker_transform = trans ;
	return true;
}