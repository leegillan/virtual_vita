#pragma once

#include <graphics/mesh_instance.h>

class GameObject : public gef::MeshInstance
{
public:
	GameObject ();
	
	void Init ();
	virtual bool Update ( float frame_time );
	void BuildTransform ();

	gef::Vector4 position_;
	gef::Vector4 scale_;
	gef::Vector4 velocity_;
};

