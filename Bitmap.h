////////////////////////////////////////
// Bitmap.h
////////////////////////////////////////

#ifndef CSE168_BITMAP_H
#define CSE168_BITMAP_H
#define DEFAULT_XRES 800;
#define DEFAULT_YRES 600;
#include "Core.h"

////////////////////////////////////////////////////////////////////////////////

class Bitmap {
public:
	Bitmap() {
		XRes = DEFAULT_XRES; 
		YRes = DEFAULT_YRES
		Pixel = new int[XRes*YRes]; 
	}
	Bitmap(int x,int y)						{XRes=x; YRes=y; Pixel=new int[XRes*YRes];}
	~Bitmap()								{delete []Pixel;}
	void Resize(int XRes, int YRes) {
		if (this->XRes == XRes && this->YRes == YRes) {
			return;
		}
		delete[] Pixel;
		Pixel = new int[XRes * YRes];
		this->XRes = XRes;
		this->YRes = YRes;
	}
	bool SaveBMP(const char *filename);

	int GetXRes() const						{return XRes;}
	int GetYRes() const						{return YRes;}
	int &GetPixel(int x,int y)				{return Pixel[y*XRes+x];}
	void SetPixel(int x,int y,int pix)		{Pixel[y*XRes+x]=pix;}

private:
	int XRes;
	int YRes;
	int *Pixel;
};

////////////////////////////////////////////////////////////////////////////////

#endif
