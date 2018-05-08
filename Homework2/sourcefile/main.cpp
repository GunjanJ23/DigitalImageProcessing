//NAME: Gunjan Jhawar
//USC ID: 1857-5342-64
//E-mail: gunjanjh@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include<vector>
#include<math.h>
#include<algorithm>
#include "imageFrame.h"
#include "matrix.h"
using namespace std;

int main(int argc, char *argv[])

{
	
	 cout<<"Starting"<<endl;
	string iFile = argv[1];
	string oFile = argv[2];
	
	vector<unsigned char> imageData;
	
	//Problem 1 
	int bytesPerPixel;
	int imageW;
	int imageH;
	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4)
	{
		bytesPerPixel = 1; // default is grey image
	} 
	else 
	{
		bytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5)
		{
			imageW = atoi(argv[4]);
			imageH= atoi(argv[5]);
		}
	}

	//General
	
	imageFrame origImage(bytesPerPixel, imageW, imageH);
	origImage.readImage(iFile.c_str());

			
int askQ;
cout<< "Choose one: 1. Color to Grayscale Conversion "<< '\n'<< "2. CMY conversion"<<'\n'<<"3. Bilinear interpolation"<<'\n'<<"4. Histogram equalization"<<'\n'<<"5. Image Filtering : Creating Oil Painting Effect"<<'\n';
cout<< "6. Image Filtering :Creating Film Special Effect "<< '\n'<< "7. Mix noise in color image along with PSNR"<<'\n'<<"8.Warping"<<'\n'<<"9. Reconstruction of Warped Image"<<'\n'<<"10.Homography Transformation"<<'\n';
cout<<"11.Stitching"<<'\n'<<"12.Dithering"<<'\n'<<"13. Dithering with four intensity values"<<'\n'<< "14. Error Diffusion"<< '\n'<<"15.Shrinking"<<'\n';
cout<<"16.Thinning/ Skeletonizing"<<'\n'<<"17. Counting Game"<<endl;
cin>> askQ;
	
switch(askQ)
{
//Problem 1(a)
case 1:	
	int part1;
	cout<< "Choose one: 1. Lightness"<< ""<< "2. Average"<< ""<<" 3. Luminosity"<<endl;
	cin>> part1;
	
	switch(part1)
	{
			
			case 1:
			{
				imageFrame bwLightnessImage(1, imageW, imageH);
				bwLightnessImage.lightness(origImage);
				bwLightnessImage.saveImage(oFile.c_str());
			break;
			}
			
			case 2:
			{
				imageFrame bwAverageImage(1, imageW , imageH);
				bwAverageImage.average(origImage);
				bwAverageImage.saveImage(oFile.c_str());
			break;
			}
			
			case 3:
			{
				imageFrame bwLuminosityImage(1, imageW , imageH);
				bwLuminosityImage.luminosity(origImage);
				bwLuminosityImage.saveImage(oFile.c_str());
			break;
			}
			
			default:
			{
			break;
			}
	}
break;

//Problem 1(b)
case 2:	
	int part2;
	cout<< "Choose one: 1. Cyan"<< ""<< "2. Magenta"<< ""<<" 3. Yellow"<<endl;
	cin>> part2;
	
	switch(part2)
	{
		case 1:
		{
		imageFrame cyanColorImage(1,imageW, imageH);
		cyanColorImage.cyan(origImage);
		cyanColorImage.saveImage(oFile.c_str());
		break;
		}
		
		case 2:
		{
		imageFrame magentaColorImage(1,imageW, imageH);
		magentaColorImage.magenta(origImage);
		magentaColorImage.saveImage(oFile.c_str());
		break;
		}
		
		case 3:
		{
		imageFrame yellowColorImage(1,imageW, imageH);
		yellowColorImage.yellow(origImage);
		yellowColorImage.saveImage(oFile.c_str());
		break;
		}
		
		default:
		{
		break;
		}
	
	}
break;

//Problem 1(c)
case 3:	
	{
		int imageWNew = 650;
		int imageHNew = 650;
		int bytesPerPixelNew = 3;
		imageFrame biLinNew(bytesPerPixelNew, imageWNew, imageHNew);
		biLinNew.biLin(origImage);
		biLinNew.saveImage(oFile.c_str());
		break;
	}
	
//Problem 2(a)
case 4:	
	int part4;
	cout<< "Choose one: 1. Transfer Function "<< ""<< "2. CDF"<<endl;
	cin>> part4;
	
	switch(part4)
	{
		case 1:
		{
		imageFrame histEqImage(3, imageW, imageH);
		histEqImage.hist(origImage);
		histEqImage.saveImage(oFile.c_str());
		break;
		}
		case 2:
		{
		imageFrame histEqImage(3, imageW, imageH);
		histEqImage.histCdf(origImage);
		histEqImage.saveImage(oFile.c_str());
		break;
		}
		
		default:
		{
			break;
		}
	}
break;
	
//Problem 2(b)
case 5:	
	int part5;
	cout<< "Choose one: 1. Step 1"<<" "<< "2. Step2"<<""<< " 3.Step3"<<endl;
	cin>> part5;
	
	switch(part5)
	{
		case 1:
		{
		
		imageFrame histEqImage(3, imageW, imageH);
		histEqImage.oilPaint(origImage);
		histEqImage.saveImage(oFile.c_str());
		break;
		}
		
		case 2:
		{
		imageFrame histEqImage(3, imageW, imageH);
		histEqImage.oilPaint2(origImage);
		histEqImage.saveImage(oFile.c_str());
		break;
		}
		
		case 3:
		imageFrame histEqImage(3, imageW, imageH);
		histEqImage.oilPaintgeneral(origImage);
		histEqImage.saveImage(oFile.c_str());
		break;
	}
break;

case 6:
{
	
//Problem 2(c)
	imageFrame filterImage(3, imageW, imageH);
	filterImage.filter(origImage);
	filterImage.saveImage(oFile.c_str());
	break;
}
	

case 7:
{
//Problem 3(a)	
	imageFrame psnrImage(3, imageW, imageH);
	psnrImage.psnr(origImage);
	psnrImage.psnrCas(origImage);
	psnrImage.saveImage(oFile.c_str());
	string baseFile = argv[6];
	imageFrame baseImage(bytesPerPixel, imageW, imageH);
	baseImage.readImage(baseFile.c_str());
	
	float psnrValue[3] ={0.0,0.0,0.0};
	float psnr[3] = {0.0,0.0,0.0};
	float MSE[3] = {0.0,0.0,0.0};
	
	for(int row = 0; row< imageH; row++)
		{
		for(int column= 0; column< imageW; column++)
			{
	
			
				psnrValue[0] = pow((baseImage.getPixelValue(row,column, 0) - psnrImage.getPixelValue(row, column, 0)), 2) + psnrValue[0];
				psnrValue[1] = pow((baseImage.getPixelValue(row,column, 1) - psnrImage.getPixelValue(row, column, 1)), 2) + psnrValue[1];
				psnrValue[2] = pow((baseImage.getPixelValue(row,column, 2) - psnrImage.getPixelValue(row, column, 2)), 2) + psnrValue[2];
				
				
			}
		}
		MSE[0] = psnrValue[0]/ (imageW*imageH);
		MSE[1] = psnrValue[1]/ (imageW*imageH);
		MSE[2] = psnrValue[2]/ (imageW*imageH);
		psnr[0] = 10* log10(pow(255,2)/ MSE[0]);
		psnr[1] = 10* log10(pow(255,2)/ MSE[1]);
		psnr[2] = 10* log10(pow(255,2)/ MSE[2]);
		cout<<psnr[0]<<endl;
		cout<<psnr[1]<<endl;
		cout<<psnr[2]<<endl;
		
	
	break;
}


case 8:
{
//Problem set 2
//Warping 

imageFrame warpImage(3, imageW, imageH);
double carOX, carOY, polarX, polarY, carX, carY, imageOX, imageOY;
 
vector<double> discCoor;
vector<double> sqCoor;
vector<double> sqCarCoor;
unsigned char pixelValue;
for(int colorChannel =0; colorChannel<3; colorChannel++)
{
for( int row  =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		discCoor = warpImage.imgToCart(row,column);
		carX = discCoor[0];
		carY = discCoor[1];
		
		
		carX += -imageW/2;
		carY += -imageH/2;
		
		carX /= imageW/2;
		carY /= imageH/2;
			
	
		
		if((pow(carX,2)+ pow(carY,2)) > 1)
		{
			warpImage.setPixelValue(0,row,column,colorChannel);
			continue;
		}
		
		
		sqCoor = warpImage.discToSq(carX, carY);
		carOX = sqCoor[0];
		carOY = sqCoor[1];
		
		carOX *= imageW/2;
		carOY *= imageH/2;
		
		carOX += imageW/2;
		carOY += imageH/2;
		
		
		sqCarCoor = warpImage.carToImg(carOX,carOY);
		imageOX = sqCarCoor[0];
		imageOY = sqCarCoor[1];
		
		
		pixelValue = origImage.getPixelValue(floor(imageOX), floor(imageOY), colorChannel);
		
		warpImage.setPixelValue(pixelValue, row, column,colorChannel);
		
		
	}
}
}
warpImage.saveImage(oFile.c_str());
break;

}

case 9:
{
//Reconstruction of image

imageFrame warpImage(3, imageW, imageH);

double carOX, carOY, polarX, polarY, carX, carY, imageOX, imageOY;
 
vector<double> discCoor;
vector<double> sqCoor;
vector<double> sqCarCoor;
unsigned char pixelValue;

for(int colorChannel =0; colorChannel<3; colorChannel++)
{
for( int row  =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		discCoor = warpImage.imgToCart(row,column);
		carX = discCoor[0];
		carY = discCoor[1];
		
		
		carX += -imageW/2;
		carY += -imageH/2;
		
		carX /= imageW/2;
		carY /= imageH/2;
			
		
		// if((pow(carX,2)+ pow(carY,2)) > 1)
		// {
			// continue;
		// }
		
		
		sqCoor = warpImage.sqToDisc(carX, carY);
		carOX = sqCoor[0];
		carOY = sqCoor[1];
		
		carOX *= imageW/2;
		carOY *= imageH/2;
		
		carOX += imageW/2;
		carOY += imageH/2;
		
		
		sqCarCoor = warpImage.carToImg(carOX,carOY);
		imageOX = sqCarCoor[0];
		imageOY = sqCarCoor[1];
		
		
		pixelValue = origImage.getPixelValue(floor(imageOX), floor(imageOY), colorChannel);
		
		warpImage.setPixelValue(pixelValue, row, column,colorChannel);
		
		
	}
}
}
warpImage.saveImage(oFile.c_str());
break;

}


case 10:
{
// Problem 1(2)
int sizeX, sizeY;
double minX, minY;
vector<double> param;
param = origImage.homography(origImage);
sizeX = param[0];
sizeY = param[1];
minX = param[2];
minY = param[3];

cout<<sizeX<<"\t"<<sizeY<<endl;
imageFrame outputImage(3,sizeX, sizeY);
outputImage.transform(origImage, sizeX, sizeY, minX, minY);
outputImage.saveImage(oFile.c_str());
break;

}


case 11:
{

//Perform Stitching
string iFile = argv[1];
string midFile = argv[2];
string rightFile = argv[3];
string oFile = argv[4];	

		vector<unsigned char> imageData;
		
		//Problem 1 
		int bytesPerPixel;
		int imageWI;
		int imageHI;
		int imageWM, imageWR;
		int imageHM, imageHR;
		
		
	
		bytesPerPixel = atoi(argv[5]);
		// Check if size is specified
		
		imageWI = 638;//for left 
		imageHI = 849;//for left
		imageWM = 480; //for middle
		imageHM = 640; //for middle
		imageWR  = 558; //for right 
		imageHR = 758; //for right
		
	
imageFrame origImage(bytesPerPixel, imageWI, imageHI);
origImage.readImage(iFile.c_str());
	
imageFrame midImage(bytesPerPixel, imageWM, imageHM);
midImage.readImage(midFile.c_str());

	
imageFrame rightImage(bytesPerPixel, imageWR, imageHR);
rightImage.readImage(rightFile.c_str());


int  imageWO = imageWI + imageWM + imageWR;//1676
int imageHO = 1500;

imageFrame outputImage(bytesPerPixel, imageWO, imageHO);
outputImage.stitch(origImage, midImage,rightImage);
outputImage.saveImage(oFile.c_str());
break;
}


case 12:

//Dithering
int option;
cout<<"Enter the operation that you need to perform: 1. Fixed thresholding 2.Random thresholding 3.Dithering matrix";
cin>> option;

switch(option)
{
case 1:
{
//Fixed Thresholding

imageFrame outputImage(1, imageW, imageH);
unsigned char pixel;

	
for(int row =0; row<imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
		pixel = origImage.getPixelValue(row, column, 0);
		if (pixel <70)
		{
			outputImage.setPixelValue(0, row, column, 0);
		}
		
		else 
		{
			outputImage.setPixelValue(255, row, column, 0);
		}
	}
}

outputImage.saveImage(oFile.c_str());
break;
}


case 2:
// Random Thresholding
{
imageFrame outputImage(1, imageW, imageH);
unsigned char pixel;
int random;

	
for(int row =0; row<imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
		random = rand() % 256;
		pixel = origImage.getPixelValue(row, column, 0);
		if (pixel <=random)
		{
			outputImage.setPixelValue(0, row, column, 0);
		}
		
		else 
		{
			outputImage.setPixelValue(255, row, column, 0);
		}
	}
}


outputImage.saveImage(oFile.c_str());
break;
}

case 3:
//Dithering Matrix
{
	
int size;
cout<<"Enter size of Dithering Matrix";
cin>> size;

imageFrame outputImage(1, imageW, imageH);
outputImage.dithering(origImage,size);
outputImage.saveImage(oFile.c_str());
break;
}

default:
{
	break;
}

}

break;

case 13:
{
//Dithering Intensity Matrix

imageFrame outputImage(1, imageW, imageH);
int size;

cout<<"Enter size of Dithering Matrix";
cin>> size;

outputImage.ditheringIntensity(origImage,size);
outputImage.saveImage(oFile.c_str());
break;
}

case 14:
{
//Function to perform error diffusion

int option;
cout<< "Enter the option: 1. Floyd 2.Jarvis 3.Stucki 4.Color Halftoning with Error Diffusion";
cin>>option;

switch(option)
{
case 1:
{
imageFrame outputImage(1, imageW, imageH);
imageFrame normalization(1, imageW, imageH);

normalization.normalize(origImage);
normalization.errorDiffF(origImage);
normalization.saveImage(oFile.c_str());
break;
}

case 2:
{
imageFrame outputImage(1, imageW, imageH);
imageFrame normalization(1, imageW, imageH);

normalization.normalize(origImage);
normalization.errorDiffJ(origImage);
normalization.saveImage(oFile.c_str());
break;
}

case 3:
{
imageFrame outputImage(1, imageW, imageH);
imageFrame normalization(1, imageW, imageH);

normalization.normalize(origImage);
normalization.errorDiffS(origImage);
normalization.saveImage(oFile.c_str());
break;
}

case 4:
{
	imageFrame outputImage(3,imageW, imageH);
	imageFrame cyan(1,imageW, imageH);
	imageFrame magenta(1,imageW, imageH);
	imageFrame yellow(1,imageW, imageH);
	
	cyan.cyan(origImage);
	cyan.errorDiffF(cyan);
	
	magenta.magenta(origImage);
	magenta.errorDiffF(magenta);
	
	yellow.yellow(origImage);
	yellow.errorDiffF(yellow);
	
	for(int row=0; row<imageH; row++)
	{
		for(int column=0; column<imageW; column++)
		{
			outputImage.setPixelValue(255 - cyan.getPixelValue(row,column,0), row,column,0);
			outputImage.setPixelValue(255 - magenta.getPixelValue(row,column,0), row,column,1);
			outputImage.setPixelValue(255 - yellow.getPixelValue(row,column,0), row,column,2);
		}
	}

outputImage.saveImage(oFile.c_str());	
	
	
break;
}

default:
{
break;
}

}

break;
}

case 15:

{
// //Function to convert binary image
imageFrame temp(1,imageW, imageH);
imageFrame initial(1,imageW, imageH);
imageFrame middle(1, imageW, imageH);
imageFrame last(1,imageW, imageH);
imageFrame result(1, imageW, imageH);

unsigned char pixel;


//Convert image to binary
for(int row =0; row<imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
		pixel = origImage.getPixelValue(row, column, 0);
		
		if (pixel <140)
		{
			temp.setPixelValue(0, row, column, 0);
			
		}
		
		else 
		{
			temp.setPixelValue(1, row, column, 0);
		}
	}
}
// temp.saveImage(oFile.c_str());

for(int row =0; row<imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
		pixel = temp.getPixelValue(row, column, 0);
		
		if(pixel ==1)
		{
			initial.setPixelValue(1,row,column,0);
		}
		else if (pixel ==0)
		{
			initial.setPixelValue(0,row,column,0);
		}
	}
}

					
// initial.saveImage(oFile.c_str());


// //Function to do morphological processing
int iteration =0;
int count =0;
vector<int> starSize;
starSize.push_back(0);

while(iteration <40)
{	
//Pass 1
for(int i =1; i< imageH; i++)
{
	for(int j = 1 ; j<imageW; j++)
	{
		
		if(initial.getPixelValue(i,j,0) == 0)
		{
			
			
			middle.setPixelValue(0,i,j,0);
			continue;
		}
		
		else
		{
			
								vector<int> allVectorValue;
								int hitOrMiss;
								int bitStream = 0x000;
								int bitSetter = 0x100;
								unsigned char pixel;
								int x;
								
								allVectorValue = initial.getWindow(i,j);
								int count = 0;
								//Find count for the vector
								for (int h =0; h< allVectorValue.size(); h++)
								{
									if (h == 4)
									{
										continue;
									}
									else if(h%2 ==0)
									{	
					
										count+=  allVectorValue[h];
										
									}
									
									else if (h%2 ==1)
									{
					
										count += 2*allVectorValue[h];
									}
					
								}
								
								//Convert Vector to binary
								for (int k =0; k< allVectorValue.size(); k++)
								{
									
								if(allVectorValue[k]==0)
									{
										bitSetter = bitSetter>> 1;
									}
				
								else if (allVectorValue[k] ==1)
									{
									bitStream |= bitSetter;
									bitSetter = bitSetter>>1;
									}
			
								}
								
								string operation = "Shrinking";
								
								hitOrMiss =  initial.conditionalMatching(operation,count,bitStream);
								
								if(hitOrMiss == true)
								{
									
									middle.setPixelValue(1,i, j, 0);
								}
								else
								{
								
									middle.setPixelValue(0,i, j, 0);
								}
								
	}
}
}


							//Function to use unconditional mask
							
							for(int i =1; i< imageH; i++)
							{
								for(int j = 1 ; j<imageW; j++)
									
								{
									if(middle.getPixelValue(i,j,0) == 0)
										{
											
											last.setPixelValue(initial.getPixelValue(i,j,0),i,j,0);
											continue;
										}
										
										else
										{
									
											int n =3;
											int kernel = n/2;
											vector<int> allVectorValue;
											int hitOrMiss;
											unsigned char pixel;

										
											
														allVectorValue = middle.getWindow(i,j);
														int bitStream = 0x000;
														int bitSetter = 0x100;
									
														for (int k =0; k< allVectorValue.size(); k++)
														{
															
															if(allVectorValue[k]==0)
															{
																	bitSetter = bitSetter>> 1;
															}
											
															else if (allVectorValue[k] ==1)
															{
																bitStream |= bitSetter;
																bitSetter = bitSetter>>1;
															}
										
														}
												
									
													string operation = "Shrinking";
													
													hitOrMiss =  middle.unconditionalMatching(operation,bitStream);
													
													if(hitOrMiss == true)
													{	
														pixel = initial.getPixelValue(i,j,0);
														last.setPixelValue(pixel,i, j, 0);
														
													}
													else
													{
														last.setPixelValue(0,i, j, 0);
													}
													
													
													
								}						
								
							}
							}

for(int row =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		
		pixel = last.getPixelValue(row,column,0);
		initial.setPixelValue(pixel,row,column,0);
	}
}

//Count the star size 

count =0;

for(int i =1; i< imageH-1; i++)
{
	
	for(int j =1; j< imageW-1; j++)
	{
		
		if(last.getPixelValue(i,j,0) == 0)
			{
											
				continue;
			}
										
		else
			{
									
					int n =3;
					int kernel = n/2;
					vector<int> allVectorValue;
					int hOrM;
					unsigned char pixel;

										
											
					allVectorValue = last.getWindow(i,j);
					
					int bitStream = 0x000;
					int bitSetter = 0x100;
									
					for (int k =0; k< allVectorValue.size(); k++)
						{
															
							if(allVectorValue[k]==0)
								{
									bitSetter = bitSetter>> 1;
								}
											
							else if (allVectorValue[k] ==1)
							{
								bitStream |= bitSetter;
								bitSetter = bitSetter>>1;
							}
										
						}
										
									
													
						// cout<<bitStream<<endl;						
						hOrM =  last.countMatching(bitStream);
													
							if(hOrM == true)
								{	
									count++;
														
								}
												
													
													
			}
	}
}	
starSize.push_back(count);				
	
// }							
				
iteration++;

}

for(int k=1;k<13; k++)
{
	cout<<"The number of stars for"<<k<<"is"<< starSize[k]- starSize[k-1]<<endl;
}

cout<< "Total number of stars"<< count<<endl;

for(int row =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		
		pixel = last.getPixelValue(row,column,0);
		result.setPixelValue(pixel*255,row,column,0);
		
	}
}

										
result.saveImage(oFile.c_str());
break;
}


case 16:
{
//Function to convert binary image

imageFrame temp(1,imageW, imageH);
imageFrame initial(1,imageW, imageH);
imageFrame middle(1, imageW, imageH);
imageFrame last(1,imageW, imageH);
imageFrame result(1, imageW, imageH);

unsigned char pixel;


//Convert image to binary
for(int row =0; row<imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
		pixel = origImage.getPixelValue(row, column, 0);
		
		if (pixel <127)
		{
			temp.setPixelValue(0, row, column, 0);
			
		}
		
		else 
		{
			temp.setPixelValue(1, row, column, 0);
		}
	}
}
// temp.saveImage(oFile.c_str());

for(int row =0; row<imageH; row++)
{
	for(int column = 0; column< imageW; column++)
	{
		pixel = temp.getPixelValue(row, column, 0);
		
		if(pixel ==1)
		{
			initial.setPixelValue(0,row,column,0);
		}
		else if (pixel ==0)
		{
			initial.setPixelValue(1,row,column,0);
		}
	}
}

int option;

cout<<"Enter option: 1. Thinning 2. Skeletonizing";
cin>>option;

switch(option)
{
case 1:
{
// //Function to do morphological processing
int iteration =0;
while(iteration <40)
{	
//Pass 1
for(int i =1; i< imageH; i++)
{
	for(int j = 1 ; j<imageW; j++)
	{
		
		if(initial.getPixelValue(i,j,0) == 0)
		{
			
			middle.setPixelValue(0,i,j,0);
			continue;
		}
		
		else
		{
			
								vector<int> allVectorValue;
								int hitOrMiss;
								int bitStream = 0x000;
								int bitSetter = 0x100;
								unsigned char pixel;
								int x;
								
								allVectorValue = initial.getWindow(i,j);
								int count = 0;
								//Find count for the vector
								for (int h =0; h< allVectorValue.size(); h++)
								{
									if (h == 4)
									{
										continue;
									}
									else if(h%2 ==0)
									{	
					
										count+=  allVectorValue[h];
										
									}
									
									else if (h%2 ==1)
									{
					
										count += 2*allVectorValue[h];
									}
					
								}
								
								//Convert Vector to binary
								for (int k =0; k< allVectorValue.size(); k++)
								{
									
								if(allVectorValue[k]==0)
									{
										bitSetter = bitSetter>> 1;
									}
				
								else if (allVectorValue[k] ==1)
									{
									bitStream |= bitSetter;
									bitSetter = bitSetter>>1;
									}
			
								}
								
								string operation = "Thinning";
								
								hitOrMiss =  initial.conditionalMatching(operation,count,bitStream);
								
								if(hitOrMiss == true)
								{
									
									middle.setPixelValue(1,i, j, 0);
								}
								else
								{
								
									middle.setPixelValue(0,i, j, 0);
								}
								
	}
}
}


							//Function to use unconditional mask
							
							for(int i =1; i< imageH; i++)
							{
								for(int j = 1 ; j<imageW; j++)
									
								{
									if(middle.getPixelValue(i,j,0) == 0)
										{
											
											last.setPixelValue(initial.getPixelValue(i,j,0),i,j,0);
											continue;
										}
										
										else
										{
									
											int n =3;
											int kernel = n/2;
											vector<int> allVectorValue;
											int hitOrMiss;
											unsigned char pixel;

										
											
														allVectorValue = middle.getWindow(i,j);
														int bitStream = 0x000;
														int bitSetter = 0x100;
									
														for (int k =0; k< allVectorValue.size(); k++)
														{
															
															if(allVectorValue[k]==0)
															{
																	bitSetter = bitSetter>> 1;
															}
											
															else if (allVectorValue[k] ==1)
															{
																bitStream |= bitSetter;
																bitSetter = bitSetter>>1;
															}
										
														}
												
									
													string operation = "Thinning";
													
													hitOrMiss =  middle.unconditionalMatching(operation,bitStream);
													
													if(hitOrMiss == true)
													{	
														pixel = initial.getPixelValue(i,j,0);
														last.setPixelValue(pixel,i, j, 0);
														
													}
													else
													{
														last.setPixelValue(0,i, j, 0);
													}
													
													
													
								}						
								
							}
							}

for(int row =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		
		pixel = last.getPixelValue(row,column,0);
		initial.setPixelValue(pixel,row,column,0);
	}
}


// }							
				
iteration++;

}

for(int row =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		
		pixel = last.getPixelValue(row,column,0);
		result.setPixelValue(pixel*255,row,column,0);
		
		
	}
}

										
result.saveImage(oFile.c_str());
break;
}


case 2:
{
int iteration =0;

while(iteration <40)
{	
//Pass 1
for(int i =1; i< imageH; i++)
{
	for(int j = 1 ; j<imageW; j++)
	{
		
		if(initial.getPixelValue(i,j,0) == 0)
		{
			
			middle.setPixelValue(0,i,j,0);
			continue;
		}
		
		else
		{
			
								vector<int> allVectorValue;
								int hitOrMiss;
								int bitStream = 0x000;
								int bitSetter = 0x100;
								unsigned char pixel;
								int x;
								
								allVectorValue = initial.getWindow(i,j);
								int count = 0;
								//Find count for the vector
								for (int h =0; h< allVectorValue.size(); h++)
								{
									if (h == 4)
									{
										continue;
									}
									else if(h%2 ==0)
									{	
					
										count+=  allVectorValue[h];
										
									}
									
									else if (h%2 ==1)
									{
					
										count += 2*allVectorValue[h];
									}
					
								}
								
								//Convert Vector to binary
								for (int k =0; k< allVectorValue.size(); k++)
								{
									
								if(allVectorValue[k]==0)
									{
										bitSetter = bitSetter>> 1;
									}
				
								else if (allVectorValue[k] ==1)
									{
									bitStream |= bitSetter;
									bitSetter = bitSetter>>1;
									}
			
								}
								
								string operation = "Skeletonizing";
								
								hitOrMiss =  initial.conditionalMatching(operation,count,bitStream);
								
								if(hitOrMiss == true)
								{
									
									middle.setPixelValue(1,i, j, 0);
								}
								else
								{
								
									middle.setPixelValue(0,i, j, 0);
								}
								
	}
}
}


							//Function to use unconditional mask
							
							for(int i =1; i< imageH; i++)
							{
								for(int j = 1 ; j<imageW; j++)
									
								{
									if(middle.getPixelValue(i,j,0) == 0)
										{
											
											last.setPixelValue(initial.getPixelValue(i,j,0),i,j,0);
											continue;
										}
										
										else
										{
									
											int n =3;
											int kernel = n/2;
											vector<int> allVectorValue;
											int hitOrMiss;
											unsigned char pixel;

										
											
														allVectorValue = middle.getWindow(i,j);
														int bitStream = 0x000;
														int bitSetter = 0x100;
									
														for (int k =0; k< allVectorValue.size(); k++)
														{
															
															if(allVectorValue[k]==0)
															{
																	bitSetter = bitSetter>> 1;
															}
											
															else if (allVectorValue[k] ==1)
															{
																bitStream |= bitSetter;
																bitSetter = bitSetter>>1;
															}
										
														}
												
									
													string operation = "Skeletonizing";
													
													hitOrMiss =  middle.unconditionalMatching(operation,bitStream);
													
													if(hitOrMiss == true)
													{	
														pixel = initial.getPixelValue(i,j,0);
														last.setPixelValue(pixel,i, j, 0);
														
													}
													else
													{
														last.setPixelValue(0,i, j, 0);
													}
													
													
													
								}						
								
							}
							}

for(int row =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		
		pixel = last.getPixelValue(row,column,0);
		initial.setPixelValue(pixel,row,column,0);
	}
}


// }							
				
iteration++;

}

for(int row =0; row< imageH; row++)
{
	for(int column =0; column< imageW; column++)
	{
		
		pixel = last.getPixelValue(row,column,0);
		result.setPixelValue(pixel*255,row,column,0);
		
		
	}
}

										
result.saveImage(oFile.c_str());
break;
}
}
break;
}

case 17:
{
//Function to perform counting game

imageFrame binaryImage(1,imageW, imageH);
unsigned char pixel;
matrix mat(imageW, imageH);

binaryImage.binary(origImage);
binaryImage.invert(binaryImage);

for(int row=0; row<imageH; row++)
{
	for(int column=0; column<imageW; column++)
	{
		mat.setMatrixValue(0,row,column);
	}
		
}	

binaryImage.count(binaryImage);
binaryImage.saveImage(oFile.c_str());




//Function to count the number of pieces

// vector<int> Frequency;
// Frequency = origImage.uniqueElement();

break;
}

default:
{
	break;
}
}

cout<<"End";
return 0;
}






