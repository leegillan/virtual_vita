#pragma once
#include "GameObject.h"
#include "VirtualObject.h"
#include "VirtualVita.h"
#include "VirtualMarker.h"
#include "primitive_builder.h"
#include <vector>
#include <input/keyboard.h>
#include <graphics/renderer_3d.h>

class VirtualSystem
{
public:
	virtual ~VirtualSystem ();

	virtual void Init ( PrimitiveBuilder* primitive_builder ) = 0;
	virtual void CleanUp () = 0;
	virtual bool Update ( float frame_time ) = 0;
	virtual void Render ( gef::Renderer3D* renderer_3d ) = 0;
	virtual void ProcessKeyboardInput ( gef::Keyboard* keyboard, float frame_time ) = 0;

	virtual bool IsMarkerFound ( int idx ) = 0;
	virtual void GetMarkerTransform ( int idx, gef::Matrix44* mat ) = 0;

	static VirtualSystem* Create ();

protected:
	VirtualSystem ();

};


/*
	void Init ( PrimitiveBuilder* primitive_builder );
	void CleanUp ();
	bool Update ( float frame_time );
	void Render ( gef::Renderer3D* renderer_3d );
	void AdvanceControl ();
	void ProcessKeyboardInput ( gef::Keyboard* keyboard, float frame_time );

	GameObject* controlObject_;

	VirtualObject* desk_;
	VirtualVita* vita_;
	std::vector<VirtualMarker*> markers_;

	PrimitiveBuilder* primitive_builder_;

	bool useWideCamera = false;

};

*/