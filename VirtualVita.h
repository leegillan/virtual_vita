#pragma once
#include "VirtualObject.h"
#include "maths/matrix44.h"

class VirtualVita : public VirtualObject
{
public:
	virtual bool Update ( float frame_time );
	
	gef::Matrix44 camera_lookAt;
	gef::Matrix44 inv_camera_lookAt;
};

