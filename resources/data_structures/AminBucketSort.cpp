// Author:	Amin Allam
// Program:	Bucket Sort

#include <iostream>
#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////

int ElemToBucket(double x)
{
	int t=(int)(x*10); // This transformation depends on the distribution of data
	return t;
}

void InsertionSort(vector<double>& a)
{
	int i,j,k,n=a.size();
	for(i=1;i<n;i++)
	{
		double t=a[i];
		for(j=i-1;j>=0;j--)
			if(a[j]<=t)
				break;
		k=j+1;
		for(j=i;j>k;j--)
			a[j]=a[j-1];
		a[k]=t;
	}
}

void BucketSort(double* a, int n)
{
	int i;
	const int num_buckets=10; // depends on problem
	vector<double> B[num_buckets];

	for(i=0;i<n;i++)
	{
		int t=ElemToBucket(a[i]);
		if(t<0 || t>=num_buckets) {cout<<"Error in ElemToBucket"; return;}
		B[t].push_back(a[i]);
	}

	int k, p=0;
	for(k=0;k<num_buckets;k++)
	{
		// sort elements in B[k] using insertion sort
		InsertionSort(B[k]);
		for(i=0;i<(int)B[k].size();i++)
			a[p++]=B[k][i];
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int i;
	double a[]={0.75,0.31,0.34,0.94,0.21,0.63,0.14,0.13,0.26};
	int n=sizeof(a)/sizeof(a[0]);
	BucketSort(a, n);
	for(i=0;i<n;i++) cout<<a[i]<<" "; cout<<endl;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
