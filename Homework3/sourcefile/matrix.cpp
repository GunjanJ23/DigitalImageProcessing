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

//Function to create laws  filter
 
vector<double> matrix::lawFilter(vector<double> vectorA, vector<double>vectorB,int n){
	
	
	vector<double> temp;
	double value;
	
	for(int filter1 = 0; filter1 <n; filter1++){
		for(int filter2 =0; filter2<n ; filter2++){
			 value = vectorA[filter1] * vectorB[filter2];
			 temp.push_back(value);
			 
		}
	}	
	
	return temp;
}

//Function to compute all filter of laws filter for imageClassification
vector<vector<double> > matrix::lawFilterBank(){
	
	double e[] = { -1/6.0,-2/6.0,0,2/6.0,1/6.0 };	
	vector<double> edge (e, e + sizeof(e) / sizeof(e[0]) );
	double s[] = { -1/4.0,0,2/4.0,0,-1/4.0 };
	vector<double> spot(s, s + sizeof(s) / sizeof(s[0]) );
	double w[]  = { -1/6.0,2/6.0,0,-2/6.0,1/6.0 };
	vector<double> wave(w, w + sizeof(w) / sizeof(w[0]) );
	vector<vector<double> > matEdgeFilter;
	
	matEdgeFilter.push_back(lawFilter(edge,edge,5));
	matEdgeFilter.push_back(lawFilter(edge,spot,5));
	matEdgeFilter.push_back(lawFilter(edge,wave,5));
	matEdgeFilter.push_back(lawFilter(wave,wave,5));
	matEdgeFilter.push_back(lawFilter(wave,edge,5));
	matEdgeFilter.push_back(lawFilter(wave,spot,5));
	matEdgeFilter.push_back(lawFilter(spot,spot,5));
	matEdgeFilter.push_back(lawFilter(spot,edge,5));
	matEdgeFilter.push_back(lawFilter(spot,wave,5));
	
	
	
	return matEdgeFilter;
	
}

//Function to compute all filter of laws filter for imageSegmentation
vector<vector<double> > matrix::lawFilterBankSegmentation(){
	
	double e[] = {-1.0/2,0,1.0/2};	
	vector<double> edge (e, e + sizeof(e) / sizeof(e[0]) );
	double s[] = {-1.0/6,2.0/6,-1.0/6};
	vector<double> spot(s, s + sizeof(s) / sizeof(s[0]) );
	double l[]  = {1.0/6,2.0/6,1.0/6};
	vector<double> level(l, l + sizeof(l) / sizeof(l[0]) );
	vector<vector<double> > matEdgeFilter;
	
	matEdgeFilter.push_back(lawFilter(edge,edge,3));
	matEdgeFilter.push_back(lawFilter(edge,spot,3));
	matEdgeFilter.push_back(lawFilter(edge,level,3));
	matEdgeFilter.push_back(lawFilter(spot,spot,3));
	matEdgeFilter.push_back(lawFilter(spot,edge,3));
	matEdgeFilter.push_back(lawFilter(spot,level,3));
	matEdgeFilter.push_back(lawFilter(level,edge,3));
	matEdgeFilter.push_back(lawFilter(level,spot,3));
	matEdgeFilter.push_back(lawFilter(level,level,3));
	
	
	return matEdgeFilter;
	
}


