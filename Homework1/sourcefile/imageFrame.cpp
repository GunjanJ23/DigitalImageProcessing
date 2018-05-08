//NAME: Gunjan Jhawar
//USC ID: 1857-5342-64
//E-mail: gunjanjh@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<algorithm>
#include<math.h>
#include "imageFrame.h"

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

		


	


