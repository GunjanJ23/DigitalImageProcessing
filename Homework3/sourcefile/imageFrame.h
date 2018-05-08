#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H
#include<vector>
#include<fstream>
#include "matrix.h"
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
		
		
		//Function to get Pixel Value directly in the imageVector
		unsigned char getPixelValue(int index);
		
		//Function to setPixelValue 
		void setPixelValue(unsigned char pixelValue,int index);
		
		
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
		
		//Problem 2
		
		
		//2.1 Warping
		
		//Decompose image into separate channel
		vector<imageFrame> sepChannel(imageFrame origImage);
		
		//Image to Cartesian 
		vector<double> imgToCart(int row, int column);
		
		//Cartesian to Image
		vector<double> carToImg(double crow, double ccolumn);
		
		
		//Cartesian to polar
		vector<double> sqToDisc(double X, double Y);
		
		
		//Polar to Cart
		vector<double> discToSq(double u, double v);
	
		//Transform one image to middle 
		vector<double> transToMid(double row, double column);
		
		//Transform image back to its original viewpoint
		vector<double> midtoTrans(double row, double column);
		
		//Function to homography
		vector<double> homography(imageFrame origImage);
		
		//Function to make transformed matrix
		void transform(imageFrame origImage, double sizeX, double sizeY, double minX, double minY);
		
		
		//Function to stitch 
		void stitch(imageFrame origImage, imageFrame midImage, imageFrame rightImage);
		
		//Index value to threshold matrix conversion 
		vector<double> bayerMatrix(int size);
		
		//Fucntion to dither 
		void dithering(imageFrame origImage,int size);
		
		//Fucntion to dither (2)
		void ditheringIntensity(imageFrame origImage,int size);
		
		//Function to perform normalization
		void normalize(imageFrame origImage);
		
		//Function to perform error diffusion: Floyd
		void errorDiffF(imageFrame origImage);
		
		//Function to perform error diffusion: Stucki
		void errorDiffS(imageFrame normalization);
		
		//Function to perform error diffusion: Jarvis
		void errorDiffJ(imageFrame normalization);
		
		//Function to do morphological processing
		vector<int> getWindow(int row,int column);
		
		//Function to perform conditional matching
		bool conditionalMatching(string operation,int count, int bitStream);
					
		//Function to perform unconditionalMatching
		bool unconditionalMatching(string operation, int bitStream);
		
		//Function to calculate star sizes
		bool countMatching(int bitStream);
		
		//Compare input and output vector
		bool compare(imageFrame frame,imageFrame finalImage);

		//Function to make binary image
		void binary(imageFrame origImage);
		
		//Function to invert image
		void invert(imageFrame binaryImage);

		//Function to do Counting Game
		void count(imageFrame binaryImage);
		
		//Function to counting game(Unique element)
		vector <int> uniqueElement();
		
		//Homework 3
		
		//Function to implement Sobel Operator 
		void sobel(imageFrame binaryImage);
		
		//Function to extend image
		void extendImage(imageFrame origImage);
		
		//Function to implement Sobel Operator 
		void log(imageFrame binImage);
		
		//Function to perform morphological on the image for loG
		bool loGMorph(int i, int j);
		
		//Function to texture classification 
		double featureEnergyExt(vector<double> temp);
	
		//Function to compute Euclidean Distance
		double euclid(vector<double> featureVec, vector<double> kmean);
		
		//Function to texture segmentation 
		vector<double> convolve(vector<double> filter);
		
		//Function to remove DC Component
		void dcComponent(); 
		
	
		
private:
		int bytesPerPixel;
		int imageW;
		int imageH;
		vector<unsigned char> imageData;
		
};

#endif

