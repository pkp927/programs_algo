#include<iostream>
#include<fstream>
#include<conio.h>
#include<set>
using namespace std;

void selSort(int a[],int size);
void swap(int &x,int &y);
int partitionAroundPivot(int a[],int start,int end);
void quickSort(int a[],int start,int end);

void selSort(int a[],int size){
	int min=0;
	for(int i=0;i<size;i++){
		for(int j=i;j<size;j++){
			if(a[min]>a[j]) min=i;
		}
		swap(a[min],a[i]);
	}
}
void swap(int &x,int &y){
	int temp=x;
	x=y;
	y=temp;
}

int partitionAroundPivot(long long a[],int start,int end){

	//int r=rand()%17;
	//int p;
	//if(r>=start&&r<=end) p=r;
	//else p=r%(end-start)+start;
	//cout<<p<<endl;
	int m=start+(end-start)/2;
	int p;
	if((a[start]>=a[m] && a[start]<=a[end] )|| (a[start]<=a[m] && a[start]>=a[end]) ){
        p=start;
	}else if((a[m]>=a[start] && a[m]<=a[end]) || (a[m]<=a[start] && a[m]>=a[end])){
	    p=m;
	}else {
	    p=end;
	}

	swap(a[start],a[p]);
	int i=start+1;
	int size=end-start+1;
	for(int j=start+1;j<=end;j++){
		if(a[j]<a[start]){
			swap(a[i],a[j]);
			i++;
		}
	}
	swap(a[start],a[i-1]);
	return i;
}
void quickSort(long long a[],int start,int end,int &c){
	int index=partitionAroundPivot(a,start,end);
	//for(int i=start;i<=end;i++) cout<<a[i]<<" ";
	//cout<<endl;
    int cp=end-start;
    c+=cp;
	if((index-1-start)>1){
		quickSort(a,start,index-2,c);
	}

	if((end+1-index)>1){
		quickSort(a,index,end,c);
	}

}

int main(){
    ifstream myfile;
    long i=0;
    long long z;
    long long* arr=new long long[1000000];
    myfile.open("sum2.txt");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
          myfile>>z;
          arr[i]=z;
          i++;
        }
        myfile.close();
    }
    int c=0;
    quickSort(arr,0,1000000,c);
    set<long long> s;
    long ct=0;
    for(int k=0;k<1000000;k++){
        for(int j=k+1;j<1000000;j++){
            if((arr[k]<0 && arr[j]>0) || (arr[k]>0 && arr[j]<0)){
                if(((arr[k]+arr[j]) <= 10000) && ((arr[k]+arr[j]) >= -10000)){
                    cout<<arr[k]+arr[j]<<" ";
                    s.insert(arr[k]+arr[j]);
                    ct++;
                }
            }
        }
    }
    cout<<"hiii"<<ct<<" "<<s.size();
    return 0;
}
