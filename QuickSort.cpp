#include<iostream>
#include<cstdlib>
#include<fstream>
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

int partitionAroundPivot(int a[],int start,int end){

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
void quickSort(int a[],int start,int end,int &c){
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

	int* arr = new int[10000];
    int i = 0;
    int line;
    ifstream myfile;
    myfile.open("FileForQuickSort.txt");
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
    int c=0;
    quickSort(arr,0,9999,c);
	cout<<c<<endl;
	//for(int i=0;i<10000;i++) cout<<arr[i]<<" ";

	return 0;
}

