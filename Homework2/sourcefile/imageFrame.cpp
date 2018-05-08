//NAME: Gunjan Jhawar
//USC ID: 1857-5342-64
//E-mail: gunjanjh@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<algorithm>
#include<math.h>
#include "imageFrame.h"
#define PI 3.14159265
#include "matrix.h"

using namespace std;

//Create constructor 
imageFrame::imageFrame(int bytesPerPixel_i,int imageW_i, int imageH_i)
{
	bytesPerPixel = bytesPerPixel_i;
	imageW = imageW_i;
	imageH = imageH_i;
	imageData.resize(bytesPerPixel*imageH*imageW,0);
}
	 
//Create destructor
imageFrame::~imageFrame()
{
}


void imageFrame::changeImageFrame(int bytesPerPixel_i,int imageW_i, int imageH_i)
{
	bytesPerPixel = bytesPerPixel_i;
	imageW = imageW_i;
	imageH = imageH_i;
	imageData.resize(bytesPerPixel*imageH*imageW,0);
}

//Function to read input file
void imageFrame::readImage(const char* iFile) 
{
	FILE *inputFile;
	
		if (!(inputFile=fopen(iFile,"rb"))) 
		{
		cout << "Cannot open file: " << iFile<<endl;
		exit(1);
	    }
	
	fread(&imageData[0], sizeof(unsigned char), imageW*imageH*bytesPerPixel, inputFile);
	
	fclose(inputFile);	
}

//Function to save output file 

void imageFrame::saveImage(const char* oFile)
{
	FILE *outputFile;
	
		if (!(outputFile=fopen(oFile,"wb"))) 
		{
		cout << "Cannot open file: " << oFile<< endl;
		exit(1);
	    }
	fwrite(&imageData[0], sizeof(unsigned char), imageW*imageH*bytesPerPixel, outputFile);
	fclose(outputFile);	
	
	
}

//Function to set pixel value for a given location 
unsigned char imageFrame::getPixelValue(int row ,int column,int colorChannel)
{
	int index = getIndex(row,column,colorChannel);
	return(imageData[index]);
	
}


//Function to set pixel value for a given location 
void imageFrame::setPixelValue(unsigned char pixelValue, int row ,int column,int colorChannel)
{
	int index = getIndex(row,column,colorChannel);
	imageData[index] = pixelValue ;	
}

//Function to get index from row,column, colorchannel
int imageFrame::getIndex(int row,int column, int colorChannel)
{
	int index = row*bytesPerPixel*imageW+ column*bytesPerPixel+colorChannel;
	return(index);
}

//Function to get Pixel Value directly in the imageVector
unsigned char imageFrame::getPixelValue(int index)
{
	return imageData[index];
}

//Function to setPixelValue 
void imageFrame::setPixelValue(unsigned char pixelValue,int index)
{
	imageData[index] = pixelValue;
}




//Function lightness method
void imageFrame::lightness(imageFrame origImage)
{
	unsigned char color[3];
	unsigned char bwColor;
	
	for(int row = 0; row<origImage.imageH; row++)
	{
		for(int column = 0; column<origImage.imageW; column++)
		{
			color[0]= origImage.getPixelValue(row,column,0);
			color[1]= origImage.getPixelValue(row,column,1);
			color[2]= origImage.getPixelValue(row,column,2);
			bwColor = (max(max(color[0],color[1]),color[2]) + min(min(color[0],color[1]), color[2]))/2;
			setPixelValue(bwColor, row,column,0);
		}
	}
		
}

//Function for average method 
void imageFrame::average(imageFrame origImage)
{
	unsigned char color[3];
	unsigned char bwColor;
	for(int row = 0; row < imageH; row++)
	{
		for(int column =0; column < imageW; column++)
		{
			
			color[0] = origImage.getPixelValue(row,column,0);
			color[1]= origImage.getPixelValue(row,column,1);
			color[2]= origImage.getPixelValue(row,column,2);
			bwColor = (color[0] +color[1] +color[2])/3;
			setPixelValue(bwColor, row, column, 0);
		}
	}
}

//Function for luminosity method 
void imageFrame::luminosity(imageFrame origImage)
{
	unsigned char color[3];
	unsigned char bwColor;
	for( int row = 0; row< origImage.imageH; row++)
	{
		for(int column=0; column< origImage.imageW; column++)
		{
			color[0] = origImage.getPixelValue(row,column,0);
			color[1] = origImage.getPixelValue(row,column,1);
			color[2] = origImage.getPixelValue(row,column,2);
			bwColor = 0.21*color[0] + 0.72*color[1] + 0.07*color[2];
			setPixelValue(bwColor, row, column, 0);
		}
	}
}

//Function to convert to cyan channel
void imageFrame::cyan(imageFrame origImage)
{
	unsigned char color;
	unsigned char cyanColor;
	for( int row = 0; row< origImage.imageH; row++)
	{
		for(int column=0; column< origImage.imageW; column++)
		{
			color= origImage.getPixelValue(row,column,0);
			cyanColor = 255 *color;
			setPixelValue(cyanColor, row, column, 0);
		}
	}
}

//Function to convert to magenta channel
void imageFrame::magenta(imageFrame origImage)
{
	unsigned char color;
	unsigned char magnetaColor;
	for( int row = 0; row< origImage.imageH; row++)
	{
		for(int column=0; column< origImage.imageW; column++)
		{
			color= origImage.getPixelValue(row,column,1);
			// magnetaColor = (1 - (color/255)) *255;
			magnetaColor = 255 - color;
			setPixelValue(magnetaColor, row, column, 0);
		}
	}
}

//Function to convert to yellow channel
void imageFrame::yellow(imageFrame origImage)
{
	unsigned char color;
	unsigned char yellowColor;
	for( int row = 0; row< origImage.imageH; row++)
	{
		for(int column=0; column< origImage.imageW; column++)
		{
			color= origImage.getPixelValue(row,column,2);
			yellowColor = 255 - color;
			setPixelValue(yellowColor, row, column, 0);
		}
	}
}

//Function to do bilinear interpolation
void imageFrame::biLin(imageFrame origImage)
{
	
	
	float scalingFactor = (511.0/649.0);
	int row;
	int column;
	
	for(row = 0 ; row<imageW; row++)
	{
		for(column=0 ; column<imageH; column++)
		{
			for (int colorChannel = 0; colorChannel < 3; colorChannel++)
			{
				float xValue = row*scalingFactor;
				float yValue = column*scalingFactor;
				
				int x1Value = static_cast<int>(xValue);
				int y1Value = static_cast<int>(yValue);
				
				int x2Value = x1Value + 1;
				int y2Value = y1Value + 1;
				
				float xdiff = xValue - x1Value;
				float ydiff = yValue - y1Value;
				unsigned char bpixel;
				
				
					bpixel= ((1 - xdiff)*(1 - ydiff)*origImage.getPixelValue(x1Value,y1Value,colorChannel) + 
					(xdiff)*(1 - ydiff)*origImage.getPixelValue(x1Value,y2Value,colorChannel)+
					(1 - xdiff)*(ydiff) * origImage.getPixelValue(x2Value,y1Value,colorChannel) +
					(xdiff)*(ydiff)* origImage.getPixelValue(x2Value, y2Value, colorChannel));
					
					setPixelValue(bpixel, row,column,colorChannel);
					
			}
		}
		
	}
	
}

//Function to create histogram
void imageFrame::hist(imageFrame origImage)
{
	vector <int> rFrequency;
	rFrequency.resize(256);
	unsigned char rcolor = 0;
	int r = 0;
	vector <int> gFrequency;
	gFrequency.resize(256);
	unsigned char gcolor = 0;
	int g = 1;
	vector <int> bFrequency;
	bFrequency.resize(256);
	unsigned char bcolor = 0;
	int b = 2;
	
	
	for(int row = 0; row < imageH; row++)
		{
		for(int column = 0; column< imageW; column++)
			{
			rcolor = origImage.getPixelValue(row, column,r);
			rFrequency[rcolor]++;
			gcolor = origImage.getPixelValue(row, column,g);
			gFrequency[gcolor]++;
			bcolor = origImage.getPixelValue(row, column,b);
			bFrequency[bcolor]++;
			
			}
		}

char *csvFile = new char[512];
cout<<"Enter the csv file"<<endl;
cin>> csvFile;
ofstream saveFile;
saveFile.open(csvFile);
	
saveFile<< "Color Value"<<","<< "Red"<<","<<"Green"<<","<<"Blue"<<endl;
	
	
	for(int i=0; i<256; i++)
	{
		
		saveFile<< i<<","<<rFrequency[i]<<","<<gFrequency[i]<<","<<bFrequency[i]<<endl;
	}
saveFile.close();
		
	
	vector <float> rProb;
	vector<float> rCumu;
	vector<int> rCumuProb;
	rProb.resize(256);
	rCumu.resize(256);
	rCumuProb.resize(256);
	float rCount = 0.0;
	
	vector <float> gProb;
	vector<float> gCumu;
	vector<int> gCumuProb;
	gProb.resize(256);
	gCumu.resize(256);
	gCumuProb.resize(256);
	float gCount = 0.0;
	
	vector <float> bProb;
	vector<float> bCumu;
	vector<int> bCumuProb;
	bProb.resize(256);
	bCumu.resize(256);
	bCumuProb.resize(256);
	float bCount = 0.0;
	
	
	
	for(int i = 0; i<256; i++)
	{
		rProb[i] = rCount + ((float)rFrequency[i]/(imageH*imageW));
		rCount = rProb[i];
		rCumu[i] = rProb[i]*255;
		rCumuProb[i] = static_cast<int>(rCumu[i]);
		gProb[i] = gCount + ((float)gFrequency[i]/(imageH*imageW));
		gCount = gProb[i];
		gCumu[i] = gProb[i]*255;
		gCumuProb[i] = static_cast<int>(gCumu[i]);
		bProb[i] = bCount + ((float)bFrequency[i]/(imageH*imageW));
		bCount = bProb[i];
		bCumu[i] = bProb[i]*255;
		bCumuProb[i] = static_cast<int>(bCumu[i]);
	}
		
		
	
	unsigned char rnewColor;
	unsigned char gnewColor;
	unsigned char bnewColor;
	for(int row = 0; row < imageH; row++)
		{
		for(int column = 0; column< imageW; column++)
			{
			rcolor = origImage.getPixelValue(row, column,r);
			gcolor = origImage.getPixelValue(row, column,g);
			bcolor = origImage.getPixelValue(row, column,b);
			rnewColor = rCumuProb[rcolor];
			gnewColor = gCumuProb[gcolor];
			bnewColor = bCumuProb[bcolor];
			setPixelValue(rnewColor, row, column, r);
			setPixelValue(gnewColor, row, column, g);
			setPixelValue(bnewColor, row, column, b);
			
			}
		}
		


char *csvFile1 = new char[512];
cout<<"Enter the csv file"<<endl;
cin>> csvFile1;
ofstream saveFile1;
saveFile1.open(csvFile1);
	
saveFile1<< "Color Value"<<","<< "Red"<<","<<"Green"<<","<<"Blue"<<endl;
	
	for(int i=0; i<256; i++)
	{
		
		saveFile1<< i<<","<<rCumuProb[i]<<","<<gCumuProb[i]<<","<<bCumuProb[i]<<endl;
	}
saveFile1.close();


}

//Function to create cdf 
void imageFrame::histCdf(imageFrame origImage)
{
	unsigned char pixR;
	unsigned char pixG;
	unsigned char pixB;
	vector <int> locR;
	vector <int> locG;
	vector <int> locB;
	int intensity;
	for(int intensity =0; intensity< 256; intensity++)
	{
		
		for (int row=0; row< imageH; row++)
		{
			for(int column =0; column< imageW; column++)
			{
				pixR = origImage.getPixelValue(row,column,0);
				pixG = origImage.getPixelValue(row,column,0);
				pixB = origImage.getPixelValue(row,column,0);
				if (intensity ==(int)pixR)
				{
					locR.push_back(getIndex(row,column,0));
				}
				if (intensity ==(int)pixG)
				{
					locG.push_back(getIndex(row,column,1));
				}
				if (intensity ==(int)pixB)
				{
					locB.push_back(getIndex(row,column,2));
				}
			}
		}
		
	}
	
	

int increment =0;
int breaker =0;
int location;

for(int i= 0; i< imageH*imageW*1; i++)
{
	if( breaker == (int)(imageW*imageH*1)/256)
	{
		breaker =0;
		increment++;
		
		continue;
	}
	else if (breaker <(int)(imageW*imageH*1)/256)
	{
		imageData[locR[i]] = increment;
		imageData[locG[i]] = increment;
		imageData[locB[i]] = increment;
		breaker++;
	}
	
}

unsigned char cdfValueR;
unsigned char cdfValueG;
unsigned char cdfValueB;
vector<int> cdfHistR;
vector<int> cdfHistG;
vector<int> cdfHistB;
cdfHistR.resize(256);
cdfHistG.resize(256);
cdfHistB.resize(256);


for(int row = 0; row < imageH; row++)
		{
		for(int column = 0; column< imageW; column++)
			{
				cdfValueR = getPixelValue(row, column,0);
				cdfHistR[(int)cdfValueR]++;
				cdfValueG = getPixelValue(row, column,1);
				cdfHistG[(int)cdfValueG]++;
				cdfValueB = getPixelValue(row, column,2);
				cdfHistB[(int)cdfValueB]++;
			}
		}


char *csvFile = new char[512];
cout<<"Enter the csv file"<<endl;
cin>> csvFile;
ofstream saveFile;
saveFile.open(csvFile);

saveFile<< "Color Value"<<","<< "Red"<<","<<"Green"<<","<<"Blue"<<endl;
	
	for(int i=0; i<256; i++)
	{
		
		saveFile<< i<<","<<cdfHistR[i]<<","<<cdfHistG[i]<<","<<cdfHistB[i]<<endl;
	}
saveFile.close();



}

//Function to create oil paint effect	
void imageFrame::oilPaint(imageFrame origImage)
{
	vector <int> rFrequency;
	rFrequency.resize(256,0);
	unsigned char rcolor = 0;
	int r = 0;
	vector <int> gFrequency;
	gFrequency.resize(256,0);
	unsigned char gcolor = 0;
	int g = 1;
	vector <int> bFrequency;
	bFrequency.resize(256,0);
	unsigned char bcolor = 0;
	int b = 2;
	
	
	for(int row = 0; row < imageH; row++)
		{
		for(int column = 0; column< imageW; column++)
			{
			rcolor = origImage.getPixelValue(row, column,r);
			rFrequency[rcolor]++;
			gcolor = origImage.getPixelValue(row, column,g);
			gFrequency[gcolor]++;
			bcolor = origImage.getPixelValue(row, column,b);
			bFrequency[bcolor]++;
			
			}
		}
		
		
	


float rValue = 0.0;
float gValue = 0.0;
float bValue = 0.0;
vector <int> rBin;
vector<int> gBin;
vector<int> bBin;

for(int i = 0; i<256;i++)
{
	rValue = rFrequency[i] + rValue;
	gValue = gFrequency[i] + gValue;
	bValue = bFrequency[i] + bValue;
	
			if(rValue >= (float)(imageW*imageH)/4)
			{
				
				rBin.push_back(i);
				rValue = 0;
			}
			
			if(gValue >= (float)(imageW*imageH)/4)
			{
				gBin.push_back(i);
				gValue = 0;
			}
			
			if(bValue >= (float)(imageW*imageH)/4)
			{
				bBin.push_back(i);
				bValue = 0;
			}
}


int rAverage[4] = {0,0,0,0};
int gAverage[4] = {0,0,0,0};
int bAverage[4] = {0,0,0,0};

rAverage[0] = (0 +rBin[0])/2;
rAverage[1] = (rBin[0]+1 + rBin[1])/2;
rAverage[2] = (rBin[1]+1 + rBin[2])/2;
rAverage[3] = (rBin[2]+1 + 255)/2;

gAverage[0] = (0 +gBin[0])/2;
gAverage[1] = (gBin[0]+1 + gBin[1])/2;
gAverage[2] = (gBin[1]+1 + gBin[2])/2;
gAverage[3] = (gBin[2]+1 + 255)/2;

bAverage[0] = (0 +bBin[0])/2;
bAverage[1] = (bBin[0]+1 + bBin[1])/2;
bAverage[2] = (bBin[1]+1 + bBin[2])/2;
bAverage[3] = (bBin[2]+1 + 255)/2;

	


for(int row =0; row< imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
	if( origImage.getPixelValue(row,column,0) <= rBin[0])
		{
		setPixelValue((rAverage[0]), row,column,0);
		}
	else if( origImage.getPixelValue(row,column,0) > rBin[0]&& origImage.getPixelValue(row,column,0) <= rBin[1])
		{
		setPixelValue((rAverage[1]), row,column,0);	
		}
	else if( origImage.getPixelValue(row,column,0) > rBin[1] && origImage.getPixelValue(row,column,0) <= rBin[2])
		{
		
		setPixelValue((rAverage[2]), row,column,0);	
		}
	else if( origImage.getPixelValue(row,column,0) > rBin[2] && origImage.getPixelValue(row,column,0) <= 255)
		{
		setPixelValue((rAverage[3]), row,column,0);	
		}
	}
}

for(int row =0; row< imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
	if( origImage.getPixelValue(row,column,1) <= gBin[0])
		{
		setPixelValue((gAverage[0]), row,column,1);
		}
	else if( origImage.getPixelValue(row,column,1) > gBin[0]&& origImage.getPixelValue(row,column,1) <= gBin[1])
		{
		setPixelValue((gAverage[1]), row,column,1);	
		}
	else if( origImage.getPixelValue(row,column,1) > gBin[1] && origImage.getPixelValue(row,column,1) <= gBin[2])
		{
		
		setPixelValue((gAverage[2]), row,column,1);	
		}
	else if( origImage.getPixelValue(row,column,1) > gBin[2] && origImage.getPixelValue(row,column,1) <= 255)
		{
		setPixelValue((gAverage[3]), row,column,1);	
		}
	}
}

for(int row =0; row< imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
	if( origImage.getPixelValue(row,column,2) <= bBin[0])
		{
		setPixelValue((bAverage[0]), row,column,2);
		}
	else if( origImage.getPixelValue(row,column,2) > bBin[0]&& origImage.getPixelValue(row,column,2) <= bBin[1])
		{
		setPixelValue((bAverage[1]), row,column,2);	
		}
	else if( origImage.getPixelValue(row,column,2) > bBin[1] && origImage.getPixelValue(row,column,2) <= bBin[2])
		{
		
		setPixelValue((bAverage[2]), row,column,2);	
		}
	else if( origImage.getPixelValue(row,column,2) > bBin[2] && origImage.getPixelValue(row,column,2) <= 255)
		{
		setPixelValue((bAverage[3]), row,column,2);	
		}
	}
}

}


//Function for step 2 oil paint

void imageFrame::oilPaint2(imageFrame origImage)
{
int n = 3;
int setNewValue;
int kernel = n/2;
for(int colorChannel =0; colorChannel<3; colorChannel++)
{
	for(int row = kernel; row< imageH; row++)
	{
		for(int column= kernel; column< imageW; column++)
		{
			
			setNewValue = origImage.window(origImage,row,column,colorChannel,n);
			setPixelValue(setNewValue,row,column,colorChannel);
		}
	}
}





}

//Function to create window
int imageFrame::window(imageFrame origImage,int row, int column, int colorChannel, int n)
{
	vector<int> vec_sort;
	int loc;
	int kernel = n/2;
	for(int i = row - kernel ; i<= row+ kernel; i++)
	{
		for(int j=column - kernel ; j<= column+ kernel; j++)
		{
			
			loc = getIndex(i,j,colorChannel);
			vec_sort.push_back(imageData[loc]);
		}
	}
	
	//Reference: https://stackoverflow.com/questions/19920542/c-calculating-the-mode-of-a-sorted-array
	int count = 1, mode = 0, m = 0, i = 1;
	while(i != vec_sort.size()+1)
		{
			if(vec_sort[i-1] != vec_sort[i]) 
			{
				if(count > m)
					{
					mode = vec_sort[i-1];
					m = count;
					count = 1;
					}
			}
			else
				++count;
				++i;
		}
		
	return(mode);
	
	
}

//Function to generalize

void imageFrame::oilPaintgeneral(imageFrame origImage)
{
	vector <int> rFrequency;
	rFrequency.resize(256,0);
	unsigned char rcolor = 0;
	int r = 0;
	vector <int> gFrequency;
	gFrequency.resize(256,0);
	unsigned char gcolor = 0;
	int g = 1;
	vector <int> bFrequency;
	bFrequency.resize(256,0);
	unsigned char bcolor = 0;
	int b = 2;
	
	
	for(int row = 0; row < imageH; row++)
		{
		for(int column = 0; column< imageW; column++)
			{
			rcolor = origImage.getPixelValue(row, column,r);
			rFrequency[rcolor]++;
			gcolor = origImage.getPixelValue(row, column,g);
			gFrequency[gcolor]++;
			bcolor = origImage.getPixelValue(row, column,b);
			bFrequency[bcolor]++;
			
			}
		}
		
		
	


float rValue = 0.0;
float gValue = 0.0;
float bValue = 0.0;
vector <int> rBin;
vector<int> gBin;
vector<int> bBin;
rBin.push_back(0);
gBin.push_back(0);
bBin.push_back(0);
int n = 8;

for(int i = 0; i<256;i++)
{
	rValue = rFrequency[i] + rValue;
	gValue = gFrequency[i] + gValue;
	bValue = bFrequency[i] + bValue;
	
			if(rValue >= (float)(imageW*imageH)/n)
			{
				
				rBin.push_back(i);
				rValue = 0;
			}
			
			if(gValue >= (float)(imageW*imageH)/n)
			{
				gBin.push_back(i+1);
				gValue = 0;
			}
			
			if(bValue >= (float)(imageW*imageH)/n)
			{
				bBin.push_back(i+1);
				bValue = 0;
			}
}

rBin.push_back(255);
gBin.push_back(255);
bBin.push_back(255);

vector<int> rAverage;
vector<int> gAverage;
vector<int> bAverage;



for( int i =0; i<n; i++)
{
	rAverage.push_back((rBin[i] +rBin[i+1])/2);
	
	gAverage.push_back((gBin[i] +gBin[i+1])/2);
	
	bAverage.push_back((bBin[i] +bBin[i+1])/2);
	

}


for(int i =0; i<rBin.size()-2; i++)
{
for(int row =0; row< imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
	if( origImage.getPixelValue(row,column,0) <= rBin[1])
		{
		setPixelValue((rAverage[0]), row,column,0);
		}
	else if( origImage.getPixelValue(row,column,0) > rBin[i+1]&& origImage.getPixelValue(row,column,0) <= rBin[i+2])
		{
		setPixelValue((rAverage[i+1]), row,column,0);	
	
		}
	}
}
}

for(int i =0; i<gBin.size()-2; i++)
{
for(int row =0; row< imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
	if( origImage.getPixelValue(row,column,1) <= gBin[1])
		{
		setPixelValue((gAverage[0]), row,column,1);
		}
	else if( origImage.getPixelValue(row,column,1) > gBin[i+1]&& origImage.getPixelValue(row,column,1) <= gBin[i+2])
		{
		setPixelValue((gAverage[i+1]), row,column,1);	
	
		}
	}
}
}

for(int i =0; i<bBin.size()-2; i++)
{
for(int row =0; row< imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
	if( origImage.getPixelValue(row,column,1) <= bBin[1])
		{
		setPixelValue((bAverage[0]), row,column,2);
		}
	else if( origImage.getPixelValue(row,column,2) > bBin[i+1]&& origImage.getPixelValue(row,column,1) <= bBin[i+2])
		{
		setPixelValue((bAverage[i+1]), row,column,2);	
	
		}
	}
}
}

}



//Function to do filtering 
void imageFrame::filter(imageFrame origImage)
{
	
	unsigned char rValue;
	unsigned char gValue;
	unsigned char bValue;
	for(int row =0; row< imageH; row++)
	{
		for(int column = 0; column< imageW; column++)
		{
			
				rValue = (double)(180.0/255)*(255 - origImage.getPixelValue(row, imageW - column,0))+70;	
				gValue = (double)(205.0/255)*(255 - origImage.getPixelValue(row, imageW - column,1));
				bValue = (double)(192.0/255)*(255 - origImage.getPixelValue(row, imageW - column,2));
				
				setPixelValue(rValue, row, column,0);
				setPixelValue(gValue, row, column,1);
				setPixelValue(bValue, row, column,2);
			
		}
		
	}
}

//Function to do PSNR

void imageFrame::psnr(imageFrame origImage)
{

	
int setNewValue1;
int n =3;
int kernel = n/2;

for(int colorChannel =0; colorChannel<3; colorChannel++)
{
	for(int row = kernel; row< imageH; row++)
	{
		for(int column= kernel; column< imageW; column++)
		{
			
		
			setNewValue1 = origImage.medianWindow(origImage,row,column,colorChannel,n);
			setPixelValue(setNewValue1,row,column,colorChannel);
			
		}
	}

}
}

void imageFrame::psnrCas(imageFrame origImage)
{

	
int setNewValue;
int n =3;
int kernel = n/2;

for(int colorChannel =0; colorChannel<3; colorChannel++)
{
	for(int row = kernel; row< imageH; row++)
	{
		for(int column= kernel; column< imageW; column++)
		{		
				setNewValue = origImage.meanWindow(origImage,row,column,colorChannel,n);
				setPixelValue(setNewValue,row,column,colorChannel);
		}
	}
}

}


//Function to create mean window
int imageFrame::meanWindow(imageFrame origImage,int row, int column, int colorChannel, int n)
{
	
	vector<int> vec_sort;
	int loc;
	int kernel = n/2;
	
	for(int i = row - kernel ; i<= row+ kernel; i++)
	{
		for(int j=column - kernel ; j<= column+ kernel; j++)
		{
			
			loc = getIndex(i,j,colorChannel);
			vec_sort.push_back(imageData[loc]);
			
		}
	}

	
int count = 0, value =0, mean=0, i=0;
for(int i=0; i < vec_sort.size();i++)
	{
			count = vec_sort[i] + value;
			value = count;
	}
	
mean = count/vec_sort.size();
return(mean);
	
	
}


//Function to create median window
int imageFrame::medianWindow(imageFrame origImage,int row, int column, int colorChannel,int n)
{
	
	vector<int> vec_sort;
	int loc;
	int kernel = n/2;
	
	for(int i = row - kernel ; i<= row+ kernel; i++)
	{
		for(int j=column - kernel ; j<= column+ kernel; j++)
		{
			
			loc = getIndex(i,j,colorChannel);
			vec_sort.push_back(imageData[loc]);
			
		}
	}


int median, indexM;	
std::sort(vec_sort.begin(), vec_sort.end());
indexM = (n*n)/2;
median = vec_sort[indexM +1];

return(median);
	
	
}


//Problem 2


//Decompose image into separate channel
vector<imageFrame> imageFrame::sepChannel(imageFrame origImage)
{
	imageFrame redChannel(1, imageW, imageH);
	imageFrame greenChannel(1, imageW, imageH);
	imageFrame blueChannel(1, imageW, imageH);
	vector<imageFrame> allChannel;
	
	for(int i =0; i<imageW*imageH; i++)
	{
		redChannel.setPixelValue(imageData[3*i],i);
		greenChannel.setPixelValue(imageData[3*i+1],i);
		blueChannel.setPixelValue(imageData[3*i+2],i);
	}
	
	allChannel.push_back(redChannel);
	allChannel.push_back(greenChannel);
	allChannel.push_back(blueChannel);
	
return(allChannel);
	
}

//2.1 Warping

//Image to Cartesian 
vector<double> imageFrame::imgToCart(int row, int column)
{
	
	double convMat[] = {0.0, 1.0, 0.5, -1, 0.0, imageH-0.5,0.0, 0.0, 1.0};
	matrix imageCoordinate(3,1);
	double a[] = {row,column,1};
	imageCoordinate.setMatVec(a,3);
	matrix carCoordinate(3,1);
	carCoordinate.multiply(convMat,9,imageCoordinate);
	return carCoordinate.getMatrixVec();
		
	
}	

//Cartesian to Image

vector<double> imageFrame::carToImg (double row, double column)
{
	
	
	double convMat[] = {0.0, -1.0, imageH-0.5, 1, 0.0,-0.5,0.0, 0.0, 1.0};
	matrix imageCoordinate(3,1);
	double a[] = {row,column,1};
	imageCoordinate.setMatVec(a,3);
	matrix carCoordinate(3,1);
	carCoordinate.multiply(convMat,9,imageCoordinate);
	return carCoordinate.getMatrixVec();
		
	
	
	
}



//Cartesian to polar
vector<double> imageFrame::sqToDisc(double X, double Y)
{
	vector<double> outputLoc;
	double polarX = X * sqrt(1 - (pow(Y,2)/2));
	double polarY = Y * sqrt(1 - (pow(X,2)/2));
	outputLoc.push_back(polarX);
	outputLoc.push_back(polarY);
	return outputLoc;	
}


//Polar to Cart
vector<double> imageFrame::discToSq(double u, double v)
{
	vector<double> outputLoc;
	double carX = 0.5* (sqrt(2 + pow(u,2) - pow(v,2) + (2 *sqrt(2) * u)) - (sqrt(2 + pow(u,2) - pow(v,2) - (2 *sqrt(2) * u))));
	double carY = 0.5 *(sqrt(2 - pow(u,2) + pow(v,2) + (2 *sqrt(2) * v)) - (sqrt(2 - pow(u,2) + pow(v,2) - (2 *sqrt(2) * v))));
	outputLoc.push_back(carX);
	outputLoc.push_back(carY);
	return outputLoc;
}
		
		
//Transform one image to middle 
vector<double> imageFrame::transToMid(double row, double column)
{
	
	double convMat[] = {1.5794 ,-0.0152, -412.7608,0.3499 , 1.4739, -127.3254,0.0011  ,0.0002 ,1.0000};//left and middle
	//double convMat[] = {0.7833 ,0.0252, 202.5533, -0.1735 ,0.9688, 19.3485,-0.0005, 0.0001, 1 };//right and middle
	matrix imageCoordinate(3,1);
	double a[] = {row,column,1};
	imageCoordinate.setMatVec(a,3);
	matrix carCoordinate(3,1);
	carCoordinate.multiply(convMat,9,imageCoordinate);
	return carCoordinate.getMatrixVec();
		
	
}	

//Transform image back to its original viewpoint

vector<double> imageFrame::midtoTrans(double row, double column)
{
	
	
	double convMat[] = { 0.4972 ,  -0.0223 , 202.3644,-0.1625   , 0.6742 ,  18.7915, -0.0005  , -0.0001 ,   0.7736};//left and middle         
	//double convMat[] = {0.791746266448185,	-0.112872304605566	,26.0463915426255,0.0278612994471332,0.571262546627447,198.650543023901,5.96717170318252e-05,-0.000411171013099770,0.863549259037532};
	//double convMat[] = {1.12941455970986	,-0.00577596812850329,	-228.654889817945, 0.191368141984834	,1.03329171362663,	-58.75489339500150,.000545570465656446	,-0.000106217155426915	,0.891548044430528};//right and middle
	matrix imageCoordinate(3,1);
	double a[] = {row,column,1};
	imageCoordinate.setMatVec(a,3);
	matrix carCoordinate(3,1);
	carCoordinate.multiply(convMat,9,imageCoordinate);
	return carCoordinate.getMatrixVec();
		
	
}	


//Function to homography

vector<double> imageFrame::homography(imageFrame origImage)
{
vector <double> car, facX, facY, img, mid;
unsigned char pixel;
double minX, minY, maxX, maxY, minNewX, maxNewX, minNewY, maxNewY;
double sizeX, sizeY;
vector<double> size;

//Translate value for X axis
car = origImage.imgToCart(0,0);
img = origImage.transToMid(car[0],car[1]);
facX.push_back(img[0]/img[2]);
car = origImage.imgToCart(imageH-1, imageW-1);
img = origImage.transToMid(car[0],car[1]);
facX.push_back(img[0]/img[2]);
car = origImage.imgToCart(0,imageW-1);
img = origImage.transToMid(car[0],car[1]);
facX.push_back(img[0]/img[2]);
car = origImage.imgToCart(imageH-1 ,0);
img = origImage.transToMid(car[0],car[1]);
facX.push_back(img[0]/img[2]);

//Translate value for Y axis
car = origImage.imgToCart(0,0);
img = origImage.transToMid(car[0],car[1]);
facY.push_back(img[1]/img[2]);

car = origImage.imgToCart(imageH-1, imageW-1);
img = origImage.transToMid(car[0],car[1]);
facY.push_back(img[1]/img[2]);

car = origImage.imgToCart(0,imageW-1);
img = origImage.transToMid(car[0],car[1]);
facY.push_back(img[1]/img[2]);

car = origImage.imgToCart(imageH-1 ,0);
img = origImage.transToMid(car[0],car[1]);
facY.push_back(img[1]/img[2]);



minX = facX[0];

for(int i=1; i< facX.size(); i++)
{
	if (facX[i]< minX)
	{
		minX = facX[i];
	}
}


minY = facY[0];


for(int i=1; i< facY.size(); i++)
{
	if (facY[i]< minY)
	{
		minY= facY[i];
	}
}


//Translation 
for(int i = 0; i<4; i++)
{
	facX[i] = facX[i] - minX;
	facY[i] = facY[i] - minY;
	facX.push_back(facX[i]);
	facY.push_back(facY[i]);
}
//To find image size 
minNewX = facX[0];
maxNewX = facX[0];
for(int i=1; i< facX.size(); i++)
{
	if (facX[i]< minNewX)
	{
		minNewX = facX[i];
	}
}

for(int i=1; i< facX.size(); i++)
{
	if (facX[i]> maxNewX)
	{
		maxNewX = facX[i];
	}
}
// cout<< minX<<endl;

minNewY = facY[0];
maxNewY = facY[0];

for(int i=1; i< facY.size(); i++)
{
	if (facY[i]< minNewY)
	{
		minNewY= facY[i];
	}
}
for(int i=1; i< facY.size(); i++)
{
	if (facY[i]> maxNewY)
	{
		maxNewY = facY[i];
	}
}

sizeX = maxNewX - minNewX +1 ;
sizeY = maxNewY - minNewY+ 1;
// cout<< sizeY<<endl;

size.push_back(sizeX);
size.push_back(sizeY);
size.push_back(minX);
size.push_back(minY);

return size;

}


//Function to make transformed matrix
void imageFrame::transform(imageFrame origImage, double sizeX, double sizeY, double minX, double minY)
{
imageFrame interImage(3, floor(sizeX), floor(sizeY));
double X,Y;
vector<double> mid, img, cart;
double convX, convY;
unsigned char pixel;


for(int row =0; row< sizeY; row++)
{
	for(int column =0; column< sizeX; column++)
	{
		cart = imgToCart(row,column);
		
		X = cart[0] + minX -0.5;
		Y = cart[1] + minY -0.5;
		
		
		mid = midtoTrans(X,Y);
		convX = mid[0]/mid[2];
		convY = mid[1]/mid[2];
		// cout<<convX;
		img = origImage.carToImg(convX, convY);
		if(img[0] <0.0 || img[0]> origImage.imageH-1 || img[1]<0.0 || img[1]> origImage.imageW-1)
		{
			continue;
		}
		// cout<<floor(img[0])<<"\t"<<floor(img[1])<<endl;
		for(int colorChannel =0; colorChannel<3; colorChannel++)
{
		pixel = origImage.getPixelValue(floor(img[0]), floor(img[1]), colorChannel);
		setPixelValue(pixel, row,column,colorChannel);
	}
	}
}


}

//Function to stitch 
void imageFrame::stitch(imageFrame origImage,imageFrame midImage, imageFrame rightImage)
{
	unsigned char pixel;
	for(int colorChannel=0; colorChannel<3; colorChannel++)
	{
	for(int i = 0; i< origImage.imageH; i++)
	{
		for(int j=0; j< origImage.imageW; j++)
		{
			
			pixel = origImage.getPixelValue(i,j,colorChannel);
			setPixelValue(pixel, i+50+264,j+224,colorChannel);
		}
	}
	
	
	
	for(int i = 0; i< rightImage.imageH; i++)
	{
		for(int j=0; j<rightImage.imageW; j++)
		{
			// cout<<i+origImage.imageH<<endl;
			pixel = rightImage.getPixelValue(i,j,colorChannel);
			setPixelValue(pixel, i+300+64 ,j+origImage.imageW+midImage.imageW -274,colorChannel);
		}
	}
	
	for(int i = 0; i< midImage.imageH; i++)
	{
		for(int j=0; j<midImage.imageW; j++)
		{
			// cout<<i+origImage.imageH<<endl;
			pixel = midImage.getPixelValue(i,j,colorChannel);
			setPixelValue(pixel, i+400 ,j+origImage.imageW ,colorChannel);
		}
	}
	}
	
}


//Index value to threshold matrix conversion 

vector<double> imageFrame::bayerMatrix(int size)
{
	matrix bayer(size,size);
	matrix basic(2,2);
	double b[] = {0,2,3,1};
	basic.setMatVec(b,4);
	 double matValue;
	
	
	if(size == 2)
	{
		bayer = basic;
	}
	else{
		
	vector<double> temp;
	temp = bayerMatrix(size/2);
	
	matrix returnMat(size/2,size/2);
	int count =0;
	for(int i=0; i<size/2; i++)
	{
		for(int j=0; j<size/2; j++)
		{
			returnMat.setMatrixValue(temp[count], i,j);
			count++;
		}
	}
	
	for (int row =0; row< size/2; row++)
	{
		for(int column =0; column<size/2; column++)
		{
			matValue = 4* returnMat.getMatrixValue(row, column);
			bayer.setMatrixValue(matValue,row,column);
			
		}
	}
	
	for (int row =0; row< size/2; row++)
	{
		for(int column =0; column<size/2; column++)
		{
			matValue = 4* returnMat.getMatrixValue(row, column) +2;
			bayer.setMatrixValue(matValue,row,column + size/2);
			
		}
	}
	
	for (int row =0; row< size/2; row++)
	{
		for(int column =0; column<size/2; column++)
		{
			matValue = 4* returnMat.getMatrixValue(row, column) +3;
			bayer.setMatrixValue(matValue,row +size/2,column);
			
		}
	}
	
	for (int row =0; row< size/2; row++)
	{
		for(int column =0; column<size/2; column++)
		{
			matValue = 4* returnMat.getMatrixValue(row, column) +1;
			bayer.setMatrixValue(matValue,row +size/2,column+ size/2);
			
		}
	}
	
	}
	return bayer.getMatrixVec();
}

//Fucntion to dither 

void imageFrame::dithering(imageFrame origImage,int size)
{
	vector<double> bayer;
	bayer = bayerMatrix(size);
	//Thresholding Matrix
	matrix threshold(size,size);
	double value =0;
	int count =0;
	for(int i=0; i< size; i++)
	{
		for(int j=0; j<size; j++)
		{
			value = (bayer[count]+0.5) /pow(size,2) ;
			count++;
			threshold.setMatrixValue(value, i,j);
		}
	}
	double pixelValue;
	for(int row =0; row< imageH; row++)
	{
		for(int column =0; column< imageW; column++)
		{
			pixelValue = origImage.getPixelValue(row,column,0);
			pixelValue /= 255.0;
			
			if(pixelValue >= threshold.getMatrixValue(row%size, column%size))
			{
				setPixelValue(255,row,column,0);
			}
			else
			{
				setPixelValue(0,row,column,0);
			}
		}
	}
}

//Fucntion to dither(2)

void imageFrame::ditheringIntensity(imageFrame origImage,int size)
{
	vector<double> bayer;
	bayer = bayerMatrix(size);
	//Thresholding Matrix
	matrix threshold(size,size);
	double value =0;
	int count =0;
	for(int i=0; i< size; i++)
	{
		for(int j=0; j<size; j++)
		{
			value = (bayer[count]+0.5) /pow(size,2) ;
			count++;
			threshold.setMatrixValue(value, i,j);
		}
	}
	double pixelValue;
	for(int row =0; row< imageH; row++)
	{
		for(int column =0; column< imageW; column++)
		{
			pixelValue = origImage.getPixelValue(row,column,0);
			pixelValue /= 255.0;
			
			if(0<= pixelValue <= (threshold.getMatrixValue(row%size, column%size))/2)
			{
				setPixelValue(0,row,column,0);
			}
			else if((threshold.getMatrixValue(row%size, column%size))/2< pixelValue <= threshold.getMatrixValue(row%size, column%size))
			{
				setPixelValue(85,row,column,0);
			}
			
			else if((threshold.getMatrixValue(row%size, column%size))< pixelValue <= 0.5+ (threshold.getMatrixValue(row%size, column%size))/2)
			{
				setPixelValue(170,row,column,0);
			}
			else if(0.5+(threshold.getMatrixValue(row%size, column%size))/2< pixelValue <= 1)
			{
				setPixelValue(255,row,column,0);
			}
			
		}
	}
}

//Function to perform normalization
void imageFrame::normalize(imageFrame origImage)
{
	unsigned char pixel;
	for(int row=0; row< imageH; row++)
	{
		for(int column = 0; column< imageW; column++)
		{
			pixel = origImage.getPixelValue(row,column,0);
			setPixelValue(pixel, row, column,0);
			// cout<<(double)pixel<<endl;
		}
	}
}


//Function to perform error diffusion: Floyd
void imageFrame::errorDiffF(imageFrame origImage)
{
	
	// imageFrame errorMat(1,imageW, imageH);
	unsigned char value;
	unsigned char oldPixel, newPixel;
	double quant_error;
	// int n =3;
	// int kernel = n/2;
	
for(int row= 2; row < imageH-1; row+=2)
{
	//row++;
	// cout<<row<<endl;
	for(int column = 1; column< imageW-1; column++)
	{
		
		oldPixel = getPixelValue(row,column,0);
		
		if(oldPixel< 127)
		{
			newPixel =0;
			setPixelValue(0,row,column,0);
			
		}
		else
		{
			newPixel = 255;
			setPixelValue(255,row,column,0);
			
		}
		
		
		quant_error = oldPixel - newPixel;
		
		value = getPixelValue(row,column+1,0) + (quant_error* (7.0/16));
		setPixelValue(value,row,column+1,0);
		
		value = getPixelValue(row+1,column-1,0) + (quant_error* (3.0/16));
		setPixelValue(value,row+1,column-1,0);
		
		value = getPixelValue(row+1,column,0) + (quant_error* (5.0/16));
		setPixelValue(value,row+1,column,0);
		
		value = getPixelValue(row+1,column+1,0) + (quant_error* (1.0/16));
		setPixelValue(value,row+1,column+1,0);
		}
		
}


for(int row= 1; row < imageH-1; row+=2)
{
	//row++;
	
	for(int column = imageW-1; column< 1; column--)
	{
		
		
		oldPixel = getPixelValue(row,column,0);
		
		if(oldPixel< 127)
		{
			newPixel =0;
			setPixelValue(0,row,column,0);
			
		}
		else
		{
			newPixel = 255;
			setPixelValue(255,row,column,0);
			
		}
		
		quant_error = oldPixel - newPixel;
		
		value = getPixelValue(row,column+1,0) + (quant_error* (7.0/16));
		setPixelValue(value,row,column+1,0);
		
		value = getPixelValue(row+1,column-1,0) + (quant_error* (3.0/16));
		setPixelValue(value,row+1,column-1,0);
		
		value = getPixelValue(row+1,column,0) + (quant_error* (5.0/16));
		setPixelValue(value,row+1,column,0);
		
		value = getPixelValue(row+1,column+1,0) + (quant_error* (1.0/16));
		setPixelValue(value,row+1,column+1,0);
		}
		
}
}



//Function to perform error diffusion: Jarvis
void imageFrame::errorDiffJ(imageFrame origImage)
{
	
	// imageFrame errorMat(1,imageW, imageH);
	unsigned char value;
	unsigned char oldPixel, newPixel;
	double quant_error;
	// int n =3;
	// int kernel = n/2;
	
for(int row= 4; row < imageH-2; row+=2)
{
	//row++;
	// cout<<row<<endl;
	for(int column = 3; column< imageW-2; column++)
	{
		
		oldPixel = getPixelValue(row,column,0);
		
		if(oldPixel< 127)
		{
			newPixel =0;
			setPixelValue(0,row,column,0);
			
		}
		else
		{
			newPixel = 255;
			setPixelValue(255,row,column,0);
			
		}
		
		
		quant_error = oldPixel - newPixel;
		
		value = getPixelValue(row,column+1,0) + (quant_error* (7.0/48));
		setPixelValue(value,row,column+1,0);
		
		value = getPixelValue(row,column+2,0) + (quant_error* (5.0/48));
		setPixelValue(value,row,column+2,0);
		
		value = getPixelValue(row+1,column-2,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+1,column-2,0);
		
		value = getPixelValue(row+1,column-1,0) + (quant_error* (5.0/48));
		setPixelValue(value,row+1,column-2,0);

		value = getPixelValue(row+1,column,0) + (quant_error* (7.0/48));
		setPixelValue(value,row+1,column,0);

		value = getPixelValue(row+1,column+1,0) + (quant_error* (5.0/48));
		setPixelValue(value,row+1,column+1,0);

		value = getPixelValue(row+1,column+2,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+1,column+2,0);

		value = getPixelValue(row+2,column-2,0) + (quant_error* (1.0/48));
		setPixelValue(value,row+2,column-2,0);

		value = getPixelValue(row+2,column-1,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+2,column-1,0);

		value = getPixelValue(row+2,column,0) + (quant_error* (5.0/48));
		setPixelValue(value,row+2,column,0);

		value = getPixelValue(row+2,column+1,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+2,column+1,0);

		value = getPixelValue(row+2,column+2,0) + (quant_error* (1.0/48));
		setPixelValue(value,row+2,column+2,0);

		}
		

}


for(int row= 3 ; row < imageH-2; row+=2)
{
	//row++;
	// cout<<row<<endl;
	for(int column = imageW-2; column< 3; column--)
	{
		
		
		oldPixel = getPixelValue(row,column,0);
		
		if(oldPixel< 127)
		{
			newPixel =0;
			setPixelValue(0,row,column,0);
			
		}
		else
		{
			newPixel = 255;
			setPixelValue(255,row,column,0);
			
		}
		
	
		quant_error = oldPixel - newPixel;
		
		value = getPixelValue(row,column+1,0) + (quant_error* (7.0/48));
		setPixelValue(value,row,column+1,0);
		
		value = getPixelValue(row,column+2,0) + (quant_error* (5.0/48));
		setPixelValue(value,row,column+2,0);
		
		value = getPixelValue(row+1,column-2,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+1,column-2,0);
		
		value = getPixelValue(row+1,column-1,0) + (quant_error* (5.0/48));
		setPixelValue(value,row+1,column-2,0);

		value = getPixelValue(row+1,column,0) + (quant_error* (7.0/48));
		setPixelValue(value,row+1,column,0);

		value = getPixelValue(row+1,column+1,0) + (quant_error* (5.0/48));
		setPixelValue(value,row+1,column+1,0);

		value = getPixelValue(row+1,column+2,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+1,column+2,0);

		value = getPixelValue(row+2,column-2,0) + (quant_error* (1.0/48));
		setPixelValue(value,row+2,column-2,0);

		value = getPixelValue(row+2,column-1,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+2,column-1,0);

		value = getPixelValue(row+2,column,0) + (quant_error* (5.0/48));
		setPixelValue(value,row+2,column,0);

		value = getPixelValue(row+2,column+1,0) + (quant_error* (3.0/48));
		setPixelValue(value,row+2,column+1,0);

		value = getPixelValue(row+2,column+2,0) + (quant_error* (1.0/48));
		setPixelValue(value,row+2,column+2,0);

		
}
}
}

//Function to perform error diffusion: Stucki
void imageFrame::errorDiffS(imageFrame origImage)
{
	
	// imageFrame errorMat(1,imageW, imageH);
	unsigned char value;
	unsigned char oldPixel, newPixel;
	double quant_error;
	// int n =3;
	// int kernel = n/2;
	
for(int row= 4; row < imageH-2; row+=2)
{
	//row++;
	// cout<<row<<endl;
	for(int column = 3; column< imageW-2; column++)
	{
		
		oldPixel = getPixelValue(row,column,0);
		
		if(oldPixel< 127)
		{
			newPixel =0;
			setPixelValue(0,row,column,0);
			
		}
		else
		{
			newPixel = 255;
			setPixelValue(255,row,column,0);
			
		}
		
		
		quant_error = oldPixel - newPixel;
		
		value = getPixelValue(row,column+1,0) + (quant_error* (8.0/42));
		setPixelValue(value,row,column+1,0);
		
		value = getPixelValue(row,column+2,0) + (quant_error* (4.0/42));
		setPixelValue(value,row,column+2,0);
		
		value = getPixelValue(row+1,column-2,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+1,column-2,0);
		
		value = getPixelValue(row+1,column-1,0) + (quant_error* (4.0/42));
		setPixelValue(value,row+1,column-2,0);

		value = getPixelValue(row+1,column,0) + (quant_error* (8.0/42));
		setPixelValue(value,row+1,column,0);

		value = getPixelValue(row+1,column+1,0) + (quant_error* (4.0/42));
		setPixelValue(value,row+1,column+1,0);

		value = getPixelValue(row+1,column+2,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+1,column+2,0);

		value = getPixelValue(row+2,column-2,0) + (quant_error* (1.0/42));
		setPixelValue(value,row+2,column-2,0);

		value = getPixelValue(row+2,column-1,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+2,column-1,0);

		value = getPixelValue(row+2,column,0) + (quant_error* (4.0/42));
		setPixelValue(value,row+2,column,0);

		value = getPixelValue(row+2,column+1,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+2,column+1,0);

		value = getPixelValue(row+2,column+2,0) + (quant_error* (1.0/42));
		setPixelValue(value,row+2,column+2,0);

		
		}
		
}


for(int row= 3 ; row < imageH-2; row+=2)
{
	//row++;
	// cout<<row<<endl;
	for(int column = imageW-2; column< 3; column--)
	{
		
		
		oldPixel = getPixelValue(row,column,0);
		
		if(oldPixel< 127)
		{
			newPixel =0;
			setPixelValue(0,row,column,0);
			
		}
		else
		{
			newPixel = 255;
			setPixelValue(255,row,column,0);
			
		}
		
	
		quant_error = oldPixel - newPixel;
		
		value = getPixelValue(row,column+1,0) + (quant_error* (8.0/42));
		setPixelValue(value,row,column+1,0);
		
		value = getPixelValue(row,column+2,0) + (quant_error* (4.0/42));
		setPixelValue(value,row,column+2,0);
		
		value = getPixelValue(row+1,column-2,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+1,column-2,0);
		
		value = getPixelValue(row+1,column-1,0) + (quant_error* (4.0/42));
		setPixelValue(value,row+1,column-2,0);

		value = getPixelValue(row+1,column,0) + (quant_error* (8.0/42));
		setPixelValue(value,row+1,column,0);

		value = getPixelValue(row+1,column+1,0) + (quant_error* (4.0/42));
		setPixelValue(value,row+1,column+1,0);

		value = getPixelValue(row+1,column+2,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+1,column+2,0);

		value = getPixelValue(row+2,column-2,0) + (quant_error* (1.0/42));
		setPixelValue(value,row+2,column-2,0);

		value = getPixelValue(row+2,column-1,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+2,column-1,0);

		value = getPixelValue(row+2,column,0) + (quant_error* (4.0/42));
		setPixelValue(value,row+2,column,0);

		value = getPixelValue(row+2,column+1,0) + (quant_error* (2.0/42));
		setPixelValue(value,row+2,column+1,0);

		value = getPixelValue(row+2,column+2,0) + (quant_error* (1.0/42));
		setPixelValue(value,row+2,column+2,0);

		
		
}
}


}

//Function to do morphological processing

vector<int> imageFrame::getWindow(int row,int column)
{
int kernel = 1;
vector<int> vec_sort;
int loc;
for(int i = row - kernel ; i<= row+ kernel; i++)
	{
		for(int j = column - kernel ; j<= column+ kernel; j++)
		{
			
			loc = getIndex(i,j,0);
			vec_sort.push_back(imageData[loc]);
			
		}
	}
return vec_sort;
}

//Function to perform conditional matching

bool imageFrame::conditionalMatching(string operation,int count, int bitStream)
{
	
    int s1[4] = {0b001010000,0b100010000,0b000010100,0b000010001};//
	int s2[4] = {0b000011000,0b010010000,0b000110000,0b000010010};//
	int s3[8] = {0b001011000,0b011010000,0b110010000,0b100110000,0b000110100,0b000010110,0b000010011,0b000011001};//
	int s4[4] = {0b001011001,0b111010000,0b100110100,0b000010111};//
	int s5[8] = {0b110011000,0b010011001,0b011110000,0b001011010,0b011011000,0b110110000,0b000110110,0b000011011};//
	int s6[10] = {0b110011001,0b011110100,0b111011000,0b011011001,0b111110000,0b110110100,0b100110110,0b000110111,0b000011111,0b001011011};//
	int s7[4] = {0b111011001,0b111110100,0b100110111,0b001011111};
	int s8[4] = {0b011011011,0b111111000,0b110110110,0b000111111};
	int s9[8] = {0b111011011,0b011011111,0b111111100,0b111111001,0b111110110,0b110110111,0b100111111,0b001111111};
	int s10[4] = {0b111011111,0b111111101,0b111110111,0b101111111};
	
	int t4[8] = {0b010011000,0b010110000,0b000110010,0b000011010,0b001011001,0b111010000,0b100110100,0b000010111};
	int t5[8] = {0b110011000,0b010011001,0b011110000,0b001011010,0b011011000,0b110110000,0b000110110,0b000011011};
	int t6[10] = {0b110011001,0b011110100,0b111011000,0b011011001,0b111110000,0b110110100,0b100110110,0b000110111,0b000011111,0b001011011};
	int t7[4] = {0b111011001,0b111110100,0b100110111,0b001011111};
	int t8[4] = {0b011011011,0b111111000,0b110110110,0b000111111};
	int t9[8] = {0b111011011,0b011011111,0b111111100,0b111111001,0b111110110,0b110110111,0b100111111,0b001111111};
	int t10[4] = {0b111011111,0b111111101,0b111110111,0b101111111};
	
	
	int sk4[8] = {0b010011000,0b010110000,0b000110010,0b000011010,0b001011001,0b111010000,0b100110100,0b000010111};
	int sk6[8] = {0b111011000,0b011011001,0b111110000,0b110110100,0b100110110,0b000110111,0b000011111,0b001011011};
	int sk7[4] = {0b111011001,0b111110100,0b100110111,0b001011111};
	int sk8[4] = {0b011011011,0b111111000,0b110110110,0b000111111};
	int sk9[8] = {0b111011011,0b011011111,0b111111100,0b111111001,0b111110110,0b110110111,0b100111111,0b001111111};
	int sk10[4] = {0b111011111,0b111111101,0b111110111,0b101111111};
	int sk11[4] = {0b111111011,0b111111110,0b110111111,0b011111111};
	
	int x = 10;
	int b[x];
	
	
	
		if (operation ==  "Shrinking")
		{
	
			switch(count)
				{
						case 1:
						
						x = sizeof(s1);
						memcpy(b, s1, sizeof(s1));
						break;
    
						case 2:
						
						x = sizeof(s2);
						memcpy(b, s2, sizeof(s2));
						break;
    
						case 3:
						
						x = sizeof(s3);
						memcpy(b, s3, sizeof(s3));
						break;
    
						case 4:
						
						x = sizeof(s4);
						memcpy(b, s4, sizeof(s4)); 
						break;
   
						case 5:
						
						x = sizeof(s5);
						memcpy(b, s5, sizeof(s5));
						break;
    
						case 6:
						
						x = sizeof(s6);
						memcpy(b, s6, sizeof(s6)); 
						break;
    
						case 7:
						
						x = sizeof(s7);
						memcpy(b, s7, sizeof(s7)); 
						break;
    
						case 8:
						
						x = sizeof(s8);
						memcpy(b, s8, sizeof(s8)); 
						break;

						case 9:
						
						x = sizeof(s9);
						memcpy(b, s9, sizeof(s9)); 
						break;
  
						case 10:
						
						x = sizeof(s10);
						memcpy(b, s10, sizeof(s10));
						break;
						
						default:
						return false;
						break;
						
				}
		}
	
		else if  (operation ==  "Thinning")
		{
			switch(count)
			{
				
					case 4:
					
					x = sizeof(t4);
					memcpy(b, t4, sizeof(t4));
					break;
    
					case 5:
					
					x = sizeof(t5);
					memcpy(b, t5, sizeof(t5));
					break;
					
    
					case 6:
					
					x = sizeof(t6);
					memcpy(b, t6, sizeof(t6));
					break;
    
					case 7:
					
					x = sizeof(t7);
					memcpy(b, t7, sizeof(t7));
					break;
    
					case 8:
					
					x = sizeof(t8);
					memcpy(b, t8, sizeof(t8));
					break;

					case 9:
					
					x = sizeof(t9);
					memcpy(b, t9, sizeof(t9));
					break;
  
					case 10:
					
					x = sizeof(t10);
					memcpy(b, t10, sizeof(t10));
					break;
					
					default:
					return false;
					break;
				}
		}

		else if  (operation == "Skeletonizing")
		{
			switch(count)
			{
					case 4:
					
					x = sizeof(sk4);
					memcpy(b, sk4, sizeof(sk4));
					break; 
					
    
					case 6:
					
					x = sizeof(sk6);
					memcpy(b, sk6, sizeof(sk6));
					break;
					

					case 7:
					
					x = sizeof(sk7);
					memcpy(b, sk7, sizeof(sk7));
					break;
					
    
					case 8:
					
					x = sizeof(sk8);
					memcpy(b, sk8, sizeof(sk8));
					break;
					

					case 9:
					
					x = sizeof(sk9);
					memcpy(b, sk9, sizeof(sk9));
					break;
  
					case 10:
					
					x = sizeof(sk10);
					memcpy(b, sk10 , sizeof(sk10));
					break;
					
					case 11:
					
					x = sizeof(sk11);
					memcpy(b, sk11, sizeof(sk11));
					break;
					
					default:
					return false;
					break;
				}
		}
int n =(sizeof(b)/sizeof(*b));


for (int i = 0; i < n; i++)
{
	if( bitStream == b[i])
	{
		return true;
	}
}
return false;
}
		
		
//Function to perform unconditionalMatching
bool imageFrame::unconditionalMatching(string operation, int bitStream)
{
						
int uncond_thin[28]={0b001010000,0b100010000, // Spur
0b000010010,0b000011000, // Single 4-connection
0b001011000,0b011010000,0b110010000,0b100110000, //LCluster
0b000110100,0b000010110,0b000010011,0b000011001,
0b011110000,0b110011000,0b010011001,0b001011010, // 4-connected offset
// 0b011011100,0b001011100,0b011010100, // Spur corner Cluster
// 0b110110001,0b100110001,0b110010001,
// 0b001110110,0b001110100,0b001010110,
// 0b100011011,0b100011001,0b100010011
0b011011100,0b110110001,0b001110110,0b100011011,// Spur corner Cluster
0b001011100,0b110010001,0b001010110,0b100011001,
0b011010100,0b100110001,0b001110100,0b100010011};  



int uncond_shrink[20]={0b001010000,0b100010000, // Spur
0b000010010,0b000011000, // Single 4-connection
0b011110000,0b110011000,0b010011001,0b001011010, // 4-connected offset
0b011011100,0b110110001,0b001110110,0b100011011,// Spur corner Cluster
0b001011100,0b110010001,0b001010110,0b100011001,
0b011010100,0b100110001,0b001110100,0b100010011}; 
// 0b011011100,0b001011100,0b011010100, // Spur corner Cluster
// 0b110110001,0b100110001,0b110010001,
// 0b001110110,0b001110100,0b001010110,
// 0b100011011,0b100011001,0b100010011};                       
                                

int uncond_WithD[41]={0b110110000,// Corner Cluster
                             0b010111000,// TeeBranch
                             0b010111000,
                             0b000111010,
                             0b000111010,
                             0b010110010,
                             0b010110010,
                             0b010011010,
                             0b010011010,
							 0b101010100,0b101010010,0b101010001,0b101010110,0b101010101,0b101010011,0b101010111,// VeeBranch 
                             0b100010101,0b100011100,0b101010100,0b100011101,0b101010101,0b101011100,0b101011101,
							 0b001010101,0b010010101,0b001010101,0b011010101,0b101010101,0b110010101,0b111010101,
							 0b101010001,0b010110001,0b001010101,0b101110001,0b101010101,0b001110101,0b101110101,							 
                             0b010011100,// DiagonalBranch  
                             0b010110001, 
                             0b001110010,
                             0b100011010};

int uncond_mask_WithD[41] = {0b110110000,// Corner Cluster
0b011111011, // TeeBranch
0b110111110,
0b110111110,
0b011111010,
0b010111111,
0b111111010,
0b111111010,
0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,
0b101011101,0b101011101,0b101011101,0b101011101,0b101011101,0b101011101,0b101011101,
0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,
0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,
0b011111110,
0b110111011,
0b011111110,
0b110111011// DiagonalBranch 
};

    

int uncond_skel[12]={0b000010001,0b000010100,0b001010000,0b100010000, // Spur
                   0b000010010,0b000011000,0b000110000,0b010010000, // Single 4-connection
                   0b010011000,0b010110000,0b000011010,0b000110010// LCorner
    };

int uncond_skel_WithD[38]={
            0b110110000,// Corner Cluster
            0b000011011,
            0b010111000,
            0b010110010,
            0b000111010,
            0b010011010,// Tee Branch
            0b101010100,0b101010010,0b101010001,0b101010110,0b101010101,0b101010011,0b101010111,// VeeBranch 
            0b100010101,0b100011100,0b101010100,0b100011101,0b101010101,0b101011100,0b101011101,
			0b001010101,0b010010101,0b001010101,0b011010101,0b101010101,0b110010101,0b111010101,
			0b101010001,0b010110001,0b001010101,0b101110001,0b101010101,0b001110101,0b101110101,
            0b010011100,// Diagonal Branch
            0b010110001,
            0b001110010,
            0b100011010,
    };
	
		
int uncond_skel_mask_WithD[38] = {0b110110000,// Corner Cluster
            0b000011011,
            0b010111000,
            0b010110010,
            0b000111010,
            0b010011010,
0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,//VeeBranch
0b101011101,0b101011101,0b101011101,0b101011101,0b101011101,0b101011101,0b101011101,
0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,
0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,
 0b010011100,// Diagonal Branch
            0b010110001,
            0b001110010,
            0b100011010,// Diagonal Branch
};


if (operation == "Thinning")

{
	for(int i=0; i<28; i++)
	{
		if(bitStream == uncond_thin[i])
		{
			return true;
			break;
		}
	}
	
	for(int i =0; i<41 ; i++)
	{
		if((bitStream & uncond_mask_WithD[i]) == uncond_WithD[i])
		{
			return true;
			break;
		}
	}
	return false;
}		
		
 
else if (operation == "Shrinking")

{
	for(int i=0; i<20; i++)
	{
		if(bitStream == uncond_shrink[i])
		{
			return true;
			break;
		}
	}
	
	for(int i =0; i<41; i++)
	{
		if((bitStream &  uncond_mask_WithD[i]) == uncond_WithD[i])
		{
			return true;
			break;
		}
	}
	return false;
}		
		
		
else if (operation == "Skeletonizing")

{
	for(int i=0; i<12; i++)
	{
		
		if(bitStream == uncond_skel[i])
		{
			return true;
			break;
		}
	}
	
	for(int i =0; i< 38; i++)
	{
		
		if((bitStream &  uncond_mask_WithD[i]) == uncond_skel_WithD[i])
		{
			return true;
			break;
		}
	}

	return false;
	
}		
		
	


    
}	


//Function to calculate star sizes
bool imageFrame::countMatching(int bitStream)
{
	
	
	if(bitStream == 0b000010000)
	{
		return true;
	}
	else 
		return false;
}


//Compare input and output vector
bool imageFrame::compare(imageFrame frame,imageFrame finalImage)
{
	unsigned char pixel;
	for(int row=0; row<imageH; row++)
	{
		for(int column =0; column< imageW; column++)
		{
			if(frame.getPixelValue(row,column,0)  == finalImage.getPixelValue(row,column,0))
			{
				
				pixel = finalImage.getPixelValue(row,column,0);
				setPixelValue(pixel,row,column,0);
				continue;
			}
			
			else
			{
				for(int row =0; row< imageH; row++)
				{
					for(int column =0; column<imageW; column++)
					{
						pixel = finalImage.getPixelValue(row,column,0);
						frame.setPixelValue(pixel*255, row, column,0);
					}
				}
				
				return false;
			}	
			
		}
}

return true;
}


//Function to invert image
void imageFrame::invert(imageFrame binaryImage)
{
unsigned char pixel;
for(int row=0; row< imageH; row++)
{
	for(int column=0; column<imageW; column++)
	{
		pixel = binaryImage.getPixelValue(row,column,0);
		
		if(pixel == 0)
		{
			setPixelValue(1,row,column,0);
		}
		else if (pixel ==1)
		{
			setPixelValue(0,row,column,0);
		}
		
	}
}
} 

//Function to make binary image

void imageFrame::binary(imageFrame origImage)
{
	unsigned char pixel;
for(int row=0; row< imageH; row++)
{
	for(int column=0; column<imageW; column++)
	{
		pixel = origImage.getPixelValue(row,column,0);
		
		if(pixel< 150)
		{
			setPixelValue(0,row,column,0);
		}
		else if (pixel>=150)
		{
			setPixelValue(1,row,column,0);
		}
		
	}
}
}

//Function to do Counting Game
void imageFrame::count(imageFrame binaryImage)
{
vector<double> array;
int labelCount =0;
unsigned char pixel;
matrix labelData(imageW, imageH);
int iteration =0;
while(iteration <10)
{	
for (int row=1; row<imageH-1; row++)
{
	for(int column=1; column<imageW-1; column++)
	{
		pixel = binaryImage.getPixelValue(row,column,0);
		
		if(pixel ==0)
		{
			continue;
		}
		
		else if(pixel ==1)
		{
			array = labelData.getNeighbor(row,column);
			
			double label = 0;
			
			for(int i=0; i< array.size(); i++)
			{
				if(array[i]!=0)
				{
					if(label ==0)
					{
						label = array[i];
					}
					
					if(label >array[i])
					{
						label = array[i];
					}
					
				}
			}
				
			if(label ==0)
				{
					label = labelCount;
					labelCount++;
					labelData.setMatrixValue(label, row,column);
				}
				
			else
				{
					labelData.setMatrixValue(label, row,column);
				}
		}
		
	}
}

double labelAssign;

for(int i=0; i< imageH; i++)
{
	for(int j=0; j<imageW; j++)
	{
		if(labelData.getMatrixValue(i,j) ==0)
		{
			labelData.setMatrixValue(0,i,j);
			continue;
		}
		else
		{
				array = labelData.getNeighbor(i,j);
				labelAssign = labelData.getMatrixValue(i,j);
				
				for(int k=0; k<array.size(); k++)
				{	
					if(array[k]< labelAssign && array[k]!=0)
					{
						labelAssign = array[k];
					}
				
				}
		labelData.setMatrixValue(labelAssign,i,j);	
		}
	}
}
iteration++;
}

vector<double> temp;
temp = labelData.getMatrixVec();

for(int i=0; i<temp.size();i++)
{
	imageData[i] = temp[i];
}

}



//Function to counting game(Unique element)
vector <int> imageFrame::uniqueElement() 
{
vector <int> Frequency;
Frequency.resize(256);
unsigned char count;
	
	for(int row = 0; row < imageH; row++)
		{
		for(int column = 0; column< imageW; column++)
			{
			count = getPixelValue(row, column,0);
			
			Frequency[(int)count]++;

			}
		}
return Frequency;
}


