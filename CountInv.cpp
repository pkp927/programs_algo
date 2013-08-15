#include<iostream>
#include<fstream>
using namespace std;

long countSplitInv(long a[],long l,long m,long r);
long count(long a[],long l,long r);

long countSplitInv(long a[],long l, long m,long r){
	long ct=0;
	long i=l;
	long j=m+1;
	long k=0;
	long* arr=new long[r-l+1];
	while(true){
		if((i>m)||(j>r)) break;
		if(a[i]<=a[j]) {
			arr[k]=a[i];
			i++;
		}
		else {
			arr[k]=a[j];
			ct=ct+m-i+1;
			j++;
		}
		k++;
	}
	while(i<=m){
		arr[k]=a[i];
		k++; i++;
	}
	while(j<=r){
		arr[k]=a[j];
		k++; j++;
	}
	for(i=0,k=l;k<=r;k++,i++){
		a[k]=arr[i];
	}
	return ct;
}
long count(long a[],long l,long r){
	long x=0,y=0,z=0;
	if(l<r){
		long m=(l+r)/2;
		x=count(a,l,m);
		y=count(a,m+1,r);
		z=countSplitInv(a,l,m,r);
	}
	return (x+y+z);
}
int main(){

    long* arr = new long[100000];
    long i = 0;
    long line;
    ifstream myfile;
    myfile.open("FileForCountInv.txt");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
          myfile >> line;
          arr[i] = line;
          i++;
        }
        myfile.close();
    }
	cout<<count(arr,0,i-1);

	return 0;
}
