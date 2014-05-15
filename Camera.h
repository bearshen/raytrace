#ifndef CSE168_CAMERA_H
#define CSE168_CAMERA_H
#include <string>
#include "Scene.h"
#include "Vector3.h"
#include "Bitmap.h"
#include "Matrix34.h"
#include "Core.h"
using std::string;

#define DEFAULT_XRES 800;
#define DEFAULT_YRES 600;
#define DEFAULT_ASPECT_RATIO 1.333;
class Camera {
public:
	Camera() {};
	void SetFOV(float degrees) {
		VerticalFOV = degrees / 180.0f * PI;
	}
	void SetAspect(float Aspect) {
		this->Aspect = Aspect;
	}
	void SetResolution(int XRes, int YRes) {
		this->XRes = XRes;
		this->YRes = YRes;
		BMP.Resize(XRes, YRes);
	}
	void LookAt(Vector3 &pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 &target = Vector3(1.0f, 0.0f, 0.0f), Vector3 &up = Vector3(0.0f, 1.0f, 0.0f)) {
		WorldMatrix.d = pos;
		WorldMatrix.c = WorldMatrix.d - target;
		WorldMatrix.c.Normalize();
		WorldMatrix.a.Cross(up, WorldMatrix.c);
		WorldMatrix.a.Normalize();
		WorldMatrix.b.Cross(WorldMatrix.c, WorldMatrix.a);
	}

	void SetSuperSample(int samples){
		nSamples = samples;
	}
	void Render(Scene &s);
	Color RenderPixel(Ray &ray, Scene &s);
	bool SaveBitmap(char *filename) {
		bool ret = BMP.SaveBMP(filename);
		return ret;
	}
private:
	int XRes, YRes;
	int nSamples;
	Matrix34 WorldMatrix;
	float VerticalFOV;
	float Aspect;
	Bitmap BMP;
};
#endif 
