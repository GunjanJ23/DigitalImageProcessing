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
// origImage.saveImage(oFile.c_str());
		
int askQ;
cout<< "Choose one: 1. Color to Grayscale Conversion "<< '\n'<< "2. CMY conversion"<<'\n'<<"3. Bilinear interpolation"<<'\n'<<"4. Histogram equalization"<<'\n'<<"5. Image Filtering : Creating Oil Painting Effect"<<'\n';
cout<< "6. Image Filtering :Creating Film Special Effect "<< '\n'<< "7. Mix noise in color image along with PSNR"<<'\n'<<endl;
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

//Problem 2(c)
case 6:
{
	imageFrame filterImage(3, imageW, imageH);
	filterImage.filter(origImage);
	filterImage.saveImage(oFile.c_str());
	break;
}
	
//Problem 3(a)
case 7:
{
	
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

		
cout<<"End";
return 0;
}
}





