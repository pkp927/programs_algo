
#include<iostream>
#include<conio.h>
#include<algorithm>
#include<vector>
#include<fstream>
#include<queue>
#include<string>
using namespace std;

int main(){
  int x;
  vector<int> v;
  vector<int> med;
  make_heap (v.begin(),v.end());
  priority_queue<int,vector<int>,greater<int> > q;
  ifstream myfile;
  myfile.open("FileForMedian.txt");
  int i=1;
  if (myfile.is_open())
  {
      while(myfile.good()){
      myfile >> x;
      if(i==1){
        //start with Hlow
        v.push_back(x);
        push_heap (v.begin(),v.end());
        //cout<<"v";
      }else{
        //fill in Hlow or Hhigh
        if(x<v.front()){
            v.push_back(x);
            push_heap (v.begin(),v.end());
            //cout<<"v";
        }else{
            q.push(x);
            //cout<<"q";
        }
        //check for size equality
        int vs=v.size();
        int qs=q.size();
        if(!q.empty() && ((qs-vs)>=2)){
            //cout<<" qs"<<qs-vs<<" "<<v.size()<<" "<<q.size();
            x=q.top();
            q.pop();
            v.push_back(x);
            push_heap (v.begin(),v.end());
            //cout<<" "<<v.size()<<" "<<q.size();
        }else if(!v.empty() && ((vs-qs)>=2)){
            //cout<<" vs"<<vs-qs<<" "<<v.size()<<" "<<q.size();
            x=v.front();
            pop_heap (v.begin(),v.end());
            v.pop_back();
            q.push(x);
            //cout<<" "<<v.size()<<" "<<q.size();
        }
      }
      //check the median
        if(i%2==0){
            if(v.size()==i/2) med.push_back(v.front());
            else med.push_back(q.top());
        }else{
            if(v.size()==(i+1)/2) med.push_back(v.front());
            else med.push_back(q.top());
        }
        //cout<<endl;
        i++;
      }
  }

  //cout<<endl<<"medians:";
  long long sum=0;
  for (int i=0; i<med.size(); i++)
    sum+=med[i];
  cout<<sum;
  return 0;
}
