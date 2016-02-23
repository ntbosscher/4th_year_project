#define HEIGHT 		500
#define WIDTH 		480
#define MAJORXS 	24
#define MAXREADING 	(255*24)
#define xSpacing	(WIDTH/MAJORXS)

#include <vector>
#include <iostream>
#include <string>
#include <dlib\pixel.h>
#include <dlib\array2d.h>
#include <dlib\image_io.h>
#include <dlib\image_transforms.h>



using namespace std;
using namespace dlib;


class ImageProcessor {
	private:
		int currentX;
		int rowLength;
		int *lastY;
		int *currentY;
		bool first;
		int currentXCompile;
		array2d<hsi_pixel> img;
		double sensorData[HEIGHT][WIDTH];
		void yCompile();
		void xCompileTo(int botY);
	
		
		
	
	public:
		ImageProcessor(int i);
		void addData (int value, int y);
		void displayData ();
		array2d<hsi_pixel>& compileImage();
		array2d<hsi_pixel>& getImage();
		

};