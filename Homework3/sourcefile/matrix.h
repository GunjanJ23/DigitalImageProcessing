#ifndef MATRIX_H 
#define MATRIX_H
#include<vector>
#include<fstream>
#include"imageFrame.h"
using namespace std;

class matrix
{
public:

		//Create constructor of matrix 
		matrix(int width_i, int height_i);
		
		//Destructor
		~matrix(void);
		
		//Get matrix value
		double getMatrixValue(int row ,int column);
		
		//Function to set matrix value for a given location 
		void setMatrixValue(double matPixelLoc, int row ,int column);
		
		//Function to get index from row,column, colorchannel
		int getMatrixIndex(int row,int column);

		//Function to set vector in matrix vector
		void setMatVec(double a[], int length);
		
		//Function to get Matrix Value
		double getMatrixVal(int index);
		
		//Function to return the matrix vector
		vector<double> getMatrixVec();
		
		//Function to set Matrix Value
		void setMatrixValue(double value, int index);
			
		//Function to do matrix multiplication
		void multiply(double convMat[],int length, matrix inputMatrix);
		
		//Function to get neighboring pixel values
		vector<double> getNeighbor(int row,int column);
		
		//Function to create laws  filter
		vector<double> lawFilter(vector<double> vectorA, vector<double>vectorB,int n);
		
		//Function to compute all filter of laws filter
		vector<vector<double> > lawFilterBank();
		
		
		//Function to compute all filter of laws filter for imageSegmentation
		vector<vector<double> > lawFilterBankSegmentation();
	
		//Function to perform normalization for L3 filter
		double normalizeL(vector<double> filterL);
	
		
		
	
	
	
private:
	int matrixWidth;
	int matrixHeight;
	vector<double> matrixVec;
	
	
};

#endif 