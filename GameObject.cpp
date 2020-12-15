#include "GameObject.h"

GameObject::GameObject ()
{
	Init ();
}


void GameObject::Init ()
{
	position = gef::Vector4(0.0f, 0.0f, 0.0f);
	velocity = gef::Vector4(0.0f, 0.0f, 0.0f);
	scale = gef::Vector4(1.0f, 1.0f, 1.0f);
	rotation = gef::Vector4(0.0f, 0.0f, 0.0f);

	localTransform.SetIdentity();

	isStatic = false;
}

bool GameObject::Update ( float frame_time )
{
	if (!isStatic)
	{
		position += velocity * frame_time;
	}

	BuildTransform();
	return true;
}

bool GameObject::Update(float frame_time, gef::Matrix44 markerTransform)
{
	if (!isStatic)
	{
		position += velocity * frame_time;
	}

	BuildTransform(markerTransform);

	return true;
}

void GameObject::BuildTransform()
{
	gef::Matrix44 scaleMat;
	gef::Matrix44 rotX;
	gef::Matrix44 rotY;
	gef::Matrix44 rotZ;
	gef::Matrix44 transform;

	scaleMat.SetIdentity();
	rotX.SetIdentity();
	rotY.SetIdentity();
	rotZ.SetIdentity();
	transform.SetIdentity();

	scaleMat.Scale(scale);
	rotX.RotationX(rotation.x());
	rotY.RotationY(rotation.y());
	rotZ.RotationZ(rotation.z());
	transform.SetTranslation(position);

	localTransform = scaleMat * (rotX * rotY * rotZ) * transform;

	set_transform(localTransform);
}

void GameObject::BuildTransform(gef::Matrix44 markerTransform)
{
	gef::Matrix44 scaleMat;
	gef::Matrix44 rotX;
	gef::Matrix44 rotY;
	gef::Matrix44 rotZ;
	gef::Matrix44 transform;

	scaleMat.SetIdentity();
	rotX.SetIdentity();
	rotY.SetIdentity();
	rotZ.SetIdentity();
	transform.SetIdentity();

	scaleMat.Scale(scale);
	rotX.RotationX(rotation.x());
	rotY.RotationY(rotation.y());
	rotZ.RotationZ(rotation.z());
	transform.SetTranslation(position);

	localTransform = scaleMat * (rotX * rotY * rotZ) * transform;

	localTransform = localTransform * markerTransform;

	set_transform(localTransform);
}