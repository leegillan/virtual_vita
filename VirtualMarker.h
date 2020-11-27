#pragma once
#include "VirtualObject.h"
#include "maths/matrix44.h"

class VirtualMarker : public VirtualObject
{
public:
	VirtualMarker ();
	virtual bool Update ( float frame_time );
	bool active;
	int markerID;
	gef::Matrix44 marker_transform;
	float rotation;
	float rotationalAccelaration;
};

#pragma once
