#pragma once


struct MarkerData
{
	bool lost;
	int target;
};

struct CameraBuffer
{
	CameraBuffer* prev;
	CameraBuffer* next;
	void* buf;
	//	SceUID uID;
	//	SceCameraRead read;
	//	SceGxmTexture tex_yuv;

	int32_t volatile ref;

	//	SceMotionSensorState motion[SCE_MOTION_MAX_NUM_STATES];
};

struct AppData
{
	AppData* prev;
	AppData* next;

	unsigned int ref;
	CameraBuffer* currentImage;

	struct
	{
		gef::Matrix44 viewMat;
		gef::Matrix44 projMat;
	}world;

	struct
	{
		gef::Matrix44 transform[6];
	}transforms;

	struct
	{
		MarkerData marker[6];
	} markers;

};

void sampleInitialize ()
{
}

void smartInitialize ( void )
{
}


AppData* sampleUpdateBegin ()
{
	AppData* dat = new AppData;

	dat->currentImage = new CameraBuffer;

	return dat;
}


void smartTrackingReset ()
{
}

void sampleUpdateEnd ( AppData* dat )
{
	delete dat->currentImage;
	delete dat;
}

void smartRelease ( void )
{

}

void sampleRelease ()
{


}

void smartUpdate ( CameraBuffer* image )
{

}

AppData* sampleRenderBegin ()
{
	AppData* dat = nullptr;

	return dat;
}


void sampleRenderEnd ()
{
}
