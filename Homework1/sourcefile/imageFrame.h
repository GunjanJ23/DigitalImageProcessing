#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H
#include<vector>
#include<fstream>
using namespace std;
class imageFrame
{
public:
		 //Create constructor 
		 imageFrame(int bytesPerPixel_i,int imageW_i, int imageH_i);
		 
		 
		//Create destructor
		~imageFrame(void);
		
		//Change variables
		void changeImageFrame(int bytesPerPixel_i,int imageW_i, int imageH_i);
		
		//Function to read input file
		void readImage(const char* iFile);

		//Function to write file 
		void saveImage(const char* oFile);
		
		//Function to set pixel value for a given location 
		unsigned char getPixelValue(int row ,int column,int colorChannel);
		
		//Function to set pixel value for a given location 
		void setPixelValue(unsigned char pixelValue, int row ,int column,int colorChannel);
		
		//Function to get index from row,column, colorchannel
		int getIndex(int row,int column, int colorChannel);
		
		//Function lightness method
		void lightness(imageFrame origImage);
		
		//Function for average method 
		void average(imageFrame origImage);
		
		//Function for luminosity method 
		void luminosity(imageFrame origImage);
		
		//Function to convert to cyan channel
		void cyan(imageFrame origImage);
		
		//Function to convert to cyan channel
		void magenta(imageFrame origImage);
		
		//Function to convert to cyan channel
		void yellow(imageFrame origImage);
		
		//Function to do bilinear interpolation
		void biLin(imageFrame origImage);
		
		//Function to create histogram and transfer function
		void hist(imageFrame origImage);
		
		//Function to create cdf 
		void histCdf(imageFrame origImage);
		
		//Function to create oil paint effect
		void oilPaint(imageFrame origImage);
		
		void oilPaint2(imageFrame origImage);
		
		//Function to try
		void oilPaintgeneral(imageFrame origImage);
		
		//Function to create window
		int window(imageFrame origImage, int row, int column, int colorChannel, int n);
		
		//Function to do filtering 
		void filter(imageFrame origImage);
		
		
		//Function to do PSNR
		void psnr(imageFrame origImage);
		
		void psnrCas(imageFrame origImage);
		
		
		//Function to do mean and median in a window
		int meanWindow(imageFrame origImage,int row, int column, int colorChannel, int n );

		int medianWindow(imageFrame origImage,int row, int column, int colorChannel, int n);
		
		
		
		
		
		
private:
		int bytesPerPixel;
		int imageW;
		int imageH;
		vector<unsigned char> imageData;
};

#endif

