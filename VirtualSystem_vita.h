#pragma once

#include "VirtualSystem.h"
#include "primitive_builder.h"
#include <input/keyboard.h>
#include <graphics/renderer_3d.h>


class VirtualSystemVita : public VirtualSystem
{
public:
	VirtualSystemVita ();
	~VirtualSystemVita ();

	virtual void Init ( PrimitiveBuilder* primitive_builder ) {};
	virtual void CleanUp () {};
	virtual bool Update ( float frame_time ) { return true; }
	virtual void Render ( gef::Renderer3D* renderer_3d ) {};
	virtual void ProcessKeyboardInput ( gef::Keyboard* keyboard, float frame_time ) {};

	virtual bool IsMarkerFound ( int idx ) { return false; }
	virtual void GetMarkerTransform ( int idx, gef::Matrix44* mat ) {};
protected:
};

#pragma once
