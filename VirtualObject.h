#pragma once

#include "GameObject.h"
#include "maths/vector4.h"
#include "maths/matrix44.h"

class VirtualObject : public GameObject
{
public:
	virtual bool Update ( float frame_time );

};