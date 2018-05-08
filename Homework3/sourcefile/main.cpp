//NAME: Gunjan Jhawar
//USC ID: 1857-5342-64
//E-mail: gunjanjh@usc.edu
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<fstream>
#include <string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<random>
#include<time.h>
#include "imageFrame.h"
#include "matrix.h"
using namespace std;

int main(int argc, char *argv[])

{
	
	 cout<<"Starting"<<endl;
	// string iFile = argv[1];
	// string oFile = argv[2];
	string iFile, oFile;
	vector<unsigned char> imageData;
	
	//Problem 1 
	int bytesPerPixel;
	int imageW;
	int imageH;
	
	// Check for proper syntax
	// if (argc < 3)
	// {
		// cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		// cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		// return 0;
	// }
	
	// // Check if image is grayscale or color
	// if (argc < 4)
	// {
		// bytesPerPixel = 1; // default is grey image
	// } 
	// else 
	// {
		bytesPerPixel = atoi(argv[1]);//3 otherwise
		// Check if size is specified
		// if (argc >= 5)
		// {
			imageW = atoi(argv[2]);//4 otherwise
			imageH= atoi(argv[3]);//5 otherwise
		// }
	// }
	// oFile = argv[4];

	//General
	
	imageFrame origImage(bytesPerPixel, imageW, imageH);
	// origImage.readImage(iFile.c_str());

			
int askQ;
cout<< "Choose one: 1. Color to Grayscale Conversion "<< '\n'<< "2. CMY conversion"<<'\n'<<"3. Bilinear interpolation"<<'\n'<<"4. Histogram equalization"<<'\n'<<"5. Image Filtering : Creating Oil Painting Effect"<<'\n';
cout<< "6. Image Filtering :Creating Film Special Effect "<< '\n'<< "7. Mix noise in color image along with PSNR"<<'\n'<<"8.Warping"<<'\n'<<"9. Reconstruction of Warped Image"<<'\n'<<"10.Homography Transformation"<<'\n';
cout<<"11.Stitching"<<'\n'<<"12.Dithering"<<'\n'<<"13. Dithering with four intensity values"<<'\n'<< "14. Error Diffusion"<< '\n'<<"15.Shrinking"<<'\n';
cout<<"16.Thinning/ Skeletonizing"<<'\n'<<"17. Counting Game"<<"\n"<<"18. Sobel Operator"<<'\n'<<"19. LoG Operator"<<"\n"<<"20. Texture Classification"<<"\n"<<"21. ImageSegmentation"<<"\n"<<endl;
cin>> askQ;
	
switch(askQ)
{
//Problem 1(a)



case 18:
{
	imageFrame outputImage(1,imageW, imageH);
	imageFrame binImage(1, imageW, imageH);
	binImage.average(origImage);
	binImage.sobel(binImage);
	outputImage.binary(binImage);
	outputImage.saveImage(oFile.c_str());
	
	
	break;
	
}

case 19:
{
	imageFrame outputImage(1, imageW, imageH);
	imageFrame binImage(1, imageW, imageH);
	binImage.luminosity(origImage);
	outputImage.log(binImage);
	bool hitorMiss;
	int index;
	vector<int> location;
	location.resize(1*imageW*imageH);
	for(int i = 1; i<imageH; i++){
		for(int j =1; j<imageW; j++){
	hitorMiss = outputImage.loGMorph(i,j);
	
	
	if(hitorMiss == true){
		index = i*imageW+j+0;
		// cout<<index<<endl;
		location[index] = 1;
	}
	
		}
	}
	// cout<<location.size()<<endl;
	for(int i =0; i< location.size(); i++){
		
			if(location[i] ==1){cout<< i<<endl;}
		
			
			}
	outputImage.saveImage(oFile.c_str());
}



case 20:
{
	
	vector<vector<double> > filterBank;
	matrix tempMat(100,100); 
	vector<double> featureVec[12];
	double feature;
	imageFrame textureImageFrame(1, imageW, imageH);
	imageFrame outputImage(1,imageW,imageH); //g++ -std=c++0x  -o test example.cpp use this to compile
	oFile = "final.raw";
	filterBank  = tempMat.lawFilterBank();
	for(int i=0; i<9; i++){
		for(int j=0; j<25; j++){
			cout<< filterBank[i][j]<<"\t";
		}
		cout<<endl;
	}
	for(int i =1 ; i<=12; i++){
	// cout<<"Image "<<i<<endl;
	iFile = "texture"+to_string(i)+".raw";
	textureImageFrame.readImage(iFile.c_str());
		for(int k =0; k< 9; k++){
			feature = textureImageFrame.featureEnergyExt(filterBank[k]);
			featureVec[i-1].push_back(feature);
			// cout<< feature<< "\t";
		}
		// cout<<endl;
	}
	
	double max[9], min[9],temp;
	
	for(int i=0; i<9; i++){
		max[i] = featureVec[0][i];
		min[i] = max[i];
		
	}
	
	for(int j=0; j<9;j++){
		for(int i=0; i<12; i++){
			temp = featureVec[i][j];
			if(max[j]<temp){max[j] = temp;}
			if(min[j]>temp){min[j] = temp;}
		}
	}
	
	
	vector<double> kmean[4];
	double random;
	int limit1, limit2;
	for(int i=0; i<4; i++){
		kmean[i]= featureVec[i*3+1];//i*3 +1
		
	}
	// srand(time(NULL)); 
	
	// for(int i =0; i<4; i++){
		// for(int j=0; j<9; j++){
			// int randNum;
			// int limit1 = max[j]; 
			// int limit2 = min[j];
			// randNum = rand() % (limit1 - limit2 + 1) + limit2;
			// kmean[i].push_back(randNum);
		
		// }
	// }
	
	for(int iteration =0; iteration<2; iteration++){
	vector<vector<double> > bin[4]; 
	vector<int> texture[4];
	double dist,distTemp;
	int assignBin;
	imageFrame uselessImage(1, imageW, imageH);
	cout<< "Sorting now"<<endl;
	for(int i=0; i<12; i++){
		dist = uselessImage.euclid(featureVec[i],kmean[0]);
		assignBin =0;
		for(int j =1; j<4; j++){
			distTemp = uselessImage.euclid(featureVec[i],kmean[j]);
			// cout<<dist<<"\t"<<distTemp<<"\t";
			if(dist > distTemp){assignBin = j; dist = distTemp;}
			
		}
		bin[assignBin].push_back(featureVec[i]);
		texture[assignBin].push_back(i);
	}
	for(int i =0; i<4; i++){
		cout<< i+1<<"\t";
		for(int j=0; j< texture[i].size(); j++)
		{
			cout<< texture[i][j] +1<<"\t";
		}
		cout<<"\n";
		texture[i].clear();
	}
	
	cout<<"Sorting done"<<endl;
	
	for(int i=0; i<4; i++){
		cout<< bin[i].size()<<endl;
	}
	cout<<"Updating K mean"<<endl;
	for(int kmeanIndex =0; kmeanIndex<4; kmeanIndex++){
		for(int elementIndex =0 ; elementIndex<9 ; elementIndex++){
			if(bin[kmeanIndex].size() != 0){
				kmean[kmeanIndex][elementIndex] = 0;
				for(int binIndex =0; binIndex< bin[kmeanIndex].size(); binIndex++){
					kmean[kmeanIndex][elementIndex] += (bin[kmeanIndex][binIndex][elementIndex]/ bin[kmeanIndex].size());
				}
			}
			else {continue;}
		}
	}
		
	
	}
	outputImage.saveImage(oFile.c_str());
	
}


case 21:
{
	//Function to do image segmentation
	
	//Creating filter bank
	vector<vector<double> > filterBank;
	matrix tempMat(100,100); 
	filterBank  = tempMat.lawFilterBankSegmentation();
	

	//Creating origImage
	imageFrame textureImageFrame(1, imageW, imageH);
	iFile = "comb.raw";
	
	textureImageFrame.readImage(iFile.c_str());
	// textureImageFrame.dcComponent();
	
	//Creating output Image
	imageFrame outputImage(1,imageW,imageH);
	
	//Creating vector which stores all convolved data
	vector<double> filteredImageData;
	filteredImageData.resize(9*imageW*imageH);
	
	//Doing filtering and storing filtered image value
	
	for(int i =0; i<9; i++){
		vector<double> tempVector;
		tempVector = textureImageFrame.convolve(filterBank[i]);
		for(int j =0; j< imageW*imageH; j++){
			int index = j*9 + i;
			filteredImageData[index] = tempVector[j];
				
	
		// cout<<filteredImageData[200+i]<<"\n";
		}
	}
	
	
	//Compute Energy 
	vector<double> energyVector;
	energyVector.resize(9*imageW*imageH);
	for(int filter =0; filter<9; filter++){		
		for(int row = 6; row< imageH-6; row++){
			for(int column = 6; column< imageW-6; column++){
				int value = 0;
				for(int i = row - 6 ; i<= row + 6 ;i++){
					for(int j = column- 6; j<= column + 6; j++){
						
						int index = i*imageW*9 + j*9 + filter;
						// cout<<index<<endl;
						value += pow(filteredImageData[index],2);	
						
					}
				}
				
				energyVector[row*imageW*9+column*9+filter] = value/13.0;
					
			}
		}
	}
	
	// // //Normalizing the convoluted result that we got by using the last vector
	
	vector<double> tempVector;
	tempVector = textureImageFrame.convolve(filterBank[8]);
	for(int i =0; i<9; i++){
			for(int j =0; j<imageW*imageH; j++){
				int index = j*9 +i;
				// cout<<index<<endl;
				energyVector[index] /= tempVector[j];
				// /cout<<filteredImageData[index]<<"\t"<<tempVector[j]<<"\n";
			}
			
		}
	

	
	// //Assign random values to kMean
	vector<double> kmean[6];
	srand(time(NULL)); 
	for(int i=0; i< 6; i++){
		int randomRow = rand()% imageH;
		// cout<<randomRow<<"\t";
		int randomColumn = rand()% imageW;
		// cout<< randomColumn<<"\t";
		// cout<<"\n";
		int index = randomRow *imageW *9 + randomColumn* 9;
		// cout<<index<<"\n";
		
		for(int j =0; j<8; j++){
				kmean[i].push_back(energyVector[index + j]);
		}
	}
	
	
	// //Calculating kMean and assigning bin
	imageFrame uselessImage(8, imageW, imageH);
	vector<double> randomVector;
	vector<double> bin[6];
	vector<vector<double> > correspondVec[6];
	for(int iteration =0; iteration<1; iteration++){
		
	for(int i=0; i<6;i++) {bin[i].clear();}
	
		for(int row=0; row< imageH; row++){
			for(int column =0; column< imageW; column++){
				
				int index = row*imageW*9+ column*9;
				
					for(int i=0; i<8;i++){
						randomVector.push_back(energyVector[index+i]);
					}
					
					
					int assignBin = 0;
					double distInitial = uselessImage.euclid(randomVector, kmean[0]);
					double dist;
					
					for(int count =1; count<6; count++){
						dist = uselessImage.euclid(randomVector, kmean[count]);
						if (dist< distInitial){
							assignBin = count;
							distInitial = dist;
						}
						
					}
					
				bin[assignBin].push_back(row);
				bin[assignBin].push_back(column);
				
				correspondVec[assignBin].push_back(randomVector);
				randomVector.clear();
				
			}
			// cout<<row<<"\t"<<endl;
		}
		
		
		// //Update K mean
		
		cout<<"Updating K mean"<<endl;
		for(int kmeanIndex =0; kmeanIndex<6; kmeanIndex++){
			for(int elementIndex =0 ; elementIndex<8 ; elementIndex++){
				if(correspondVec[kmeanIndex].size() != 0){
					kmean[kmeanIndex][elementIndex] = 0;
					for(int binIndex =0; binIndex< correspondVec[kmeanIndex].size(); binIndex++){
						kmean[kmeanIndex][elementIndex] += (correspondVec[kmeanIndex][binIndex][elementIndex]/ correspondVec[kmeanIndex].size());
					} 
				}
				else {continue;}
			}
		}
		// for(int i= 0; i<6; i++){
			// for(int j=0; j<correspondVec[i].size(); j++){
			// correspondVec[i][j].clear();
			// }
		// }
	
	
}
		
		
for(int i =0; i<6; i++){
	cout<<bin[i].size()<<"\t";
}
		
	for(int count =0; count<6; count++){
		for(int k=0; k<bin[count].size()/2; k++){
		int row = bin[count][k*2];
		int column = bin[count][k*2+1];
		int value[6] = {0,51,102,153,204,255};
		outputImage.setPixelValue(value[count],row,column,0);
			
		}
			
		
	}
	oFile = "final.raw";
	outputImage.saveImage(oFile.c_str());	
		
}




default:
{
	break;
}
}

cout<<"End";
return 0;
}






