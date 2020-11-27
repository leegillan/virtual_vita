#pragma once

#include "VirtualSystem.h"
#include "GameObject.h"
#include "VirtualObject.h"
#include "VirtualVita.h"
#include "VirtualMarker.h"
#include "primitive_builder.h"
#include <vector>
#include <input/keyboard.h>
#include <graphics/renderer_3d.h>


class VirtualSystemWin32 : public VirtualSystem
{
public:
	VirtualSystemWin32 ();
	~VirtualSystemWin32 ();

	virtual void Init ( PrimitiveBuilder* primitive_builder );
	virtual void CleanUp ();
	virtual bool Update ( float frame_time );
	virtual void Render ( gef::Renderer3D* renderer_3d );
	void AdvanceControl ();
	virtual void ProcessKeyboardInput ( gef::Keyboard* keyboard, float frame_time );

	virtual bool IsMarkerFound ( int idx );
	virtual void GetMarkerTransform ( int idx, gef::Matrix44* mat );

protected:

	GameObject* controlObject_;

	VirtualObject* desk_;
	VirtualVita* vita_;
	std::vector<VirtualMarker*> markers_;

	PrimitiveBuilder* primitive_builder_;

	bool useWideCamera = false;

};

