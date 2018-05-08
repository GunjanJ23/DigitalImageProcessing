#include<iostream>
#include "matrix.h"
#include"imageFrame.h"
#include<math.h>

using namespace std;

//Create constructor
matrix::matrix(int height_i,int  width_i)
{
		matrixWidth = width_i;
		matrixHeight = height_i;
		matrixVec.resize(matrixWidth*matrixHeight);
}

//Create Destructor
matrix::~matrix()
{
}


//Function to get index from row,column, colorchannel
int matrix::getMatrixIndex(int row,int column)
{
	int index = row*matrixWidth+ column;
	return(index);
}

//Set matrix value
double matrix::getMatrixValue(int row ,int column)
{
	int index = getMatrixIndex(row,column);
	return(matrixVec[index]);
	
}


//Function to set matrix value for a given location 
void matrix::setMatrixValue(double matPixelLoc, int row ,int column)
{
	int index = getMatrixIndex(row,column);
	matrixVec[index] = matPixelLoc ;	
}



//Function to get Matrix Value
double matrix::getMatrixVal(int index)
{
	return (matrixVec[index]);
}

//Function to return the matrix vector
		
vector<double>  matrix::getMatrixVec()
{
	return(matrixVec);
}


//Function to set Matrix Value
void matrix::setMatrixValue(double value, int index)
{
	matrixVec[index] = value;
}



//Function to set vector in matrix vector
void matrix::setMatVec(double a[], int length)
{
	for(int i=0; i<length; i++)
	{
		matrixVec[i] = a[i];
	}
	// for(int i=0; i<10 ;i++)
	// {
		// cout<<matrixVec[i]<<endl;
	// }
	
}

//Function to do matrix multiplication

void matrix::multiply(double convMat[],int length, matrix inputMatrix)
{
	int j=0, k=0;
	double opValue=0;
	while(k< length)
	{
	for(int i=0; i<3;i++)
	{
		//cout<<inputMatrix.getMatrixVal(i)<<endl;
		opValue += convMat[k] *inputMatrix.getMatrixVal(i);
		k++;
		
	}
	setMatrixValue(opValue,j,0);
	j++;
	opValue=0;
	}
}


//Function to get neighboring pixel values

vector<double> matrix::getNeighbor(int row,int column)
{
int kernel = 1;
vector<double> vec_sort;
int loc;
for(int i = row - kernel ; i<= row+ kernel; i++)
	{
		for(int j = column - kernel ; j<= column+ kernel; j++)
		{
			
			loc = getMatrixIndex(i,j);
			vec_sort.push_back(getMatrixVal(loc));
			
		}
	}
return vec_sort;
}

