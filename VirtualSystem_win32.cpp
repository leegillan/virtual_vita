#include "VirtualSystem.h"
#include "VirtualSystem_win32.h"
#include <input/keyboard.h>



VirtualSystem* VirtualSystem::Create ()
{
	return new VirtualSystemWin32 ();
}

VirtualSystemWin32::VirtualSystemWin32 ()
{

}

VirtualSystemWin32::~VirtualSystemWin32 ()
{

}


void VirtualSystemWin32::Init ( PrimitiveBuilder* primitive_builder )
{
	float deskLength = 2.0f;
	float deskWidth = 2.0f;
	float deskHeight = 0.1f;
	desk_ = new VirtualObject;
	desk_->position_ = gef::Vector4 ( 0.0f, 0.0f, 0.0f );
	desk_->scale_ = gef::Vector4 ( deskLength, deskWidth, deskHeight );
	desk_->set_mesh ( primitive_builder->GetDefaultCubeMesh () );

	vita_ = new VirtualVita ();
	vita_->position_ = gef::Vector4 ( 0.0f, 1.0f, 0.75f );
	vita_->scale_ = gef::Vector4 ( 0.2f, 0.02f, 0.1f );
	vita_->set_mesh ( primitive_builder->GetDefaultCubeMesh () );

	const int num_markers = 6;

	for (int i = 0; i < num_markers; i++)
	{
		VirtualMarker *marker = new VirtualMarker;
		marker->active = i == 0;
		marker->markerID = i;
		marker->position_ = gef::Vector4 ( -0.5f + (0.2f * i), 0.0f, 0.05f );
		marker->scale_ = gef::Vector4 ( 0.059f, 0.059f, 0.01f );
		marker->set_mesh ( primitive_builder->GetDefaultCubeMesh () );
		markers_.push_back ( marker );
	}

	controlObject_ = vita_;
	primitive_builder_ = primitive_builder;
}


void VirtualSystemWin32::CleanUp ()
{

	delete desk_;
	delete vita_;
	for (int i = 0; i < markers_.size (); i++)
	{
		delete markers_[i];
	}
}


bool VirtualSystemWin32::Update ( float frame_time )
{
	// calculate the inverse view matrix from the vita
	vita_->Update ( frame_time );

	// then update the other objects - calculating a world matrix and a 
	desk_->Update ( frame_time );

	for (int i = 0; i < markers_.size (); i++)
	{
		if (markers_[i]->active)
		{
			markers_[i]->Update ( frame_time );
		}
	}

	return true;
}

void VirtualSystemWin32::Render ( gef::Renderer3D* renderer_3d )
{

	gef::Matrix44 view_matrix;

	if (useWideCamera)
	{
		gef::Vector4 camera_eye = gef::Vector4 ( 1.5f, 1.5f, 1.0f );
		gef::Vector4 camera_lookat = gef::Vector4 ( 0.0f, 0.0f, 0.0f );
		gef::Vector4 camera_up = gef::Vector4 ( 0.0f, 0.0f, 1.0f );
		view_matrix.LookAt ( camera_eye, camera_lookat, camera_up );
		renderer_3d->set_view_matrix ( view_matrix );
	}
	else
	{
		renderer_3d->set_view_matrix ( vita_->camera_lookAt );
	}


	// draw 3d stuff here
	renderer_3d->DrawMesh ( *desk_ );

	renderer_3d->set_override_material ( vita_ == controlObject_ ? &primitive_builder_->red_material () : &primitive_builder_->blue_material () );
	renderer_3d->DrawMesh ( *vita_ );
	renderer_3d->set_override_material ( NULL );

	for (int i = 0; i < markers_.size (); i++)
	{
		if (markers_[i]->active)
		{
			renderer_3d->set_override_material ( markers_[i] == controlObject_ ? &primitive_builder_->red_material () : &primitive_builder_->blue_material () );
			renderer_3d->DrawMesh ( *markers_[i] );
			renderer_3d->set_override_material ( NULL );
		}
	}

}



void VirtualSystemWin32::AdvanceControl ()
{
	if (controlObject_ == vita_)
	{
		// find the first active marker
		for (int i = 0; i < markers_.size (); i++)
		{
			if (markers_[i]->active)
			{
				controlObject_ = markers_[i];
				break;
			}
		}
	}
	else
	{
		// find the control marker, advance to the next. If not, switch to vita
		int controlIdx = -1;
		bool controlAdvanced = false;

		for (int i = 0; i < markers_.size (); i++)
		{
			if (controlIdx == -1)
			{
				if (markers_[i] == controlObject_)
				{
					controlIdx = i;
				}
			}
			else
			{
				if (markers_[i]->active)
				{
					controlObject_ = markers_[i];
					controlAdvanced = true;
					break;
				}
			}
		}
		if (!controlAdvanced)
		{
			controlObject_ = vita_;
		}
	}
}


void VirtualSystemWin32::ProcessKeyboardInput ( gef::Keyboard* keyboard, float frame_time )
{
	if (keyboard)
	{
		float accel = 1.0f;
		if (keyboard->IsKeyDown ( gef::Keyboard::KC_W ))
		{
			gef::Keyboard::KC_LSHIFT;
			controlObject_->velocity_ += gef::Vector4 ( 0.0f, -accel, 0.0f ) * frame_time;
		}
		if (keyboard->IsKeyDown ( gef::Keyboard::KC_A ))
		{
			controlObject_->velocity_ += gef::Vector4 ( accel, 0.0f, 0.0f ) * frame_time;
		}
		if (keyboard->IsKeyDown ( gef::Keyboard::KC_S ))
		{
			controlObject_->velocity_ += gef::Vector4 ( 0.0f, accel, 0.0f ) * frame_time;
		}
		if (keyboard->IsKeyDown ( gef::Keyboard::KC_D ))
		{
			controlObject_->velocity_ += gef::Vector4 ( -accel, 0.0f, 0.0f ) * frame_time;
		}
		if (keyboard->IsKeyDown ( gef::Keyboard::KC_Q ))
		{
			if (controlObject_ == vita_)
			{
				controlObject_->velocity_ += gef::Vector4 ( 0.0f, 0.0f, accel ) * frame_time;
			}
			else
			{
				VirtualMarker *marker = (VirtualMarker*)controlObject_;
				marker->rotationalAccelaration = 0.05f;
			}
		}
		if (keyboard->IsKeyDown ( gef::Keyboard::KC_E ))
		{
			if (controlObject_ == vita_)
			{
				controlObject_->velocity_ += gef::Vector4 ( 0.0f, 0.0f, -accel ) * frame_time;
			}
			else
			{
				VirtualMarker *marker = (VirtualMarker*)controlObject_;
				marker->rotationalAccelaration = -0.05f;
			}
		}

		if (keyboard->IsKeyPressed ( gef::Keyboard::KC_N ))
		{
			// add a new marker
			// find the first inactive marker
			for (int i = 0; i < markers_.size (); i++)
			{
				if (!markers_[i]->active)
				{
					markers_[i]->active = true;
					controlObject_ = markers_[i];
					break;
				}
			}

		}

		if (keyboard->IsKeyPressed ( gef::Keyboard::KC_M ))
		{
			// remove current marker
			for (int i = 0; i < markers_.size (); i++)
			{
				if (markers_[i] == controlObject_)
				{
					markers_[i]->active = false;
					AdvanceControl ();
					break;
				}
			}
		}

		useWideCamera = (keyboard->IsKeyDown ( gef::Keyboard::KC_LSHIFT ));

		if (keyboard->IsKeyPressed ( gef::Keyboard::KC_SPACE ))
		{
			AdvanceControl ();
		}
	}
}

bool  VirtualSystemWin32::IsMarkerFound ( int idx )
{
	return markers_[idx]->active;
}


void VirtualSystemWin32::GetMarkerTransform ( int idx, gef::Matrix44* mat )
{
	gef::Matrix44 trans = markers_[idx]->marker_transform;
	gef::Matrix44 vita = vita_->camera_lookAt;

	gef::Matrix44 matrix = trans * vita;
	*mat = matrix;

}