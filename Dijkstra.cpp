// pk.cpp : Defines the entry point for the console application.
//MINIMUM CUT GRAPH

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<conio.h>
#include<string>
#include <sstream>
#include <stdlib.h>
using namespace std;


struct node{
	int data;
	int dist;
	node *link;
};

class list{
	node* head;
	int tra;
public:
	list(){
		head=NULL;
		tra=1;
	}

	void insert_at_end_node(node* n){
		n->link=NULL;
		if(head==NULL){
			head=n;
		}else{
			node *temp=head;
			while(temp->link!=NULL){
				temp=temp->link;
			}
			temp->link=n;
		}
	}

	node* get_head(){
		if(this!=NULL)
			return head;
		else return NULL;
	}

	void show(){
		if(head==NULL) cout<<"Null"<<" ";
		else {
			node* temp=head;
			while(temp!=NULL){
				cout<<temp->data<<","<<temp->dist<<" ";
				if(temp==head) cout<<"->";
				temp=temp->link;
			}
		}
	}

	void set_tra(){
		if(this!=NULL)
			tra=1;
	}

	node* traverse(){
		if(this==NULL) return NULL;
		node* temp=head;
		if(temp==NULL) return NULL;
		for(int i=0;i<tra;i++)
			temp=temp->link;
		if(temp==NULL){
			set_tra();
		}else {
			tra++;
		}
		return temp;
	}

	int search(int d){
		int loc=0;
		if(head==NULL){
			cout<<"Nothing to search";
		}else{
			node* temp=head;
			//temp=temp->link;
			while(temp->link!=NULL){
				if(temp->data==d)
					return loc;
				temp=temp->link;
				loc++;
			}
			if(temp->data==d)
				return loc;
			return -1;
		}
	}

	void delete_node(int d){
		int loc=search(d);
		if(loc==-1){
			cout<<"Node not present";
		}else{
		    //cout<<loc<<endl;
			node* temp1=head;
			node* temp2;
			for(int i=0;i<loc;i++){
				temp2=temp1;
				temp1=temp1->link;
			}
			temp2->link=temp1->link;
			if(tra>1) tra--;
			delete temp1;
		}
	}
};

class graph{
	int vertices;
	int edges;
	list* g[201];
public:

	graph(int v){
		vertices=v;
		for(int i=1;i<=vertices;i++){
			g[i]=new list;
			node* temp=new node;
			temp->data=i;
			temp->dist=0;
			g[i]->insert_at_end_node(temp);
		}
	}

	void g_input(){
	    int i = 1;
        int line;
        string ch;
        ifstream myfile;
        myfile.open("FileForDijkstra.txt");
        if (myfile.is_open())
        {
            while ( myfile.good())
            {
              getline(myfile,ch);
              istringstream iss(ch);
              while(iss){
                  string sub,dist;
                  iss>>sub;
                  dist=sub.substr(sub.find(",")+1);
                  int v=atoi(sub.c_str());
                  int d=atoi(dist.c_str());
                  if(v==0) break;
                  if(v!=i){
                      node* temp=new node;
                      temp->data=v;
                      temp->dist=d;
                      temp->link=NULL;
                      g[i]->insert_at_end_node(temp);
                  }
              }
              i++;
            }
            myfile.close();
        }
	}

	void g_showall_adj(){
		for(int i=1;i<=vertices;i++){
			g[i]->show();  //
			cout<<endl;
		}
	}

	void g_show_adj(int i){
	    g[i]->show();
	}

	void g_set_tra(){
		for(int i=1;i<=vertices;i++)
			g[i]->set_tra();  //
	}

	node* g_adjacent(int n){
		return g[n]->traverse();  //
	}

	node* g_get_vertex(int d){
		node* temp;
		for(int i=1;i<=vertices;i++){
		    //if(g[i]!=NULL){
				temp=g[i]->get_head();  //
				if(temp!=NULL&&temp->data==d)
					return temp;
		    //}
		}
		return NULL;
	}

	node* g_max_deg(){
	    node* temp1;
	    node* temp2;
	    int max=0;
	    for(int i=1;i<=vertices;i++){
	        if(g[i]!=NULL){
	            int m=0;
	            g[i]->set_tra();
	            while(true){
	                temp2=g_adjacent(i);
	                if(temp2==NULL) break;
	                else m++;
	            }
	            if(m>max){
	                max=m;
	                temp1=g_get_vertex(i);
                }
	        }
	    }
	    return temp1;
	}

};

int X[200];
int A[201];

bool contain(int x,int n){
    for(int i=0;i<n;i++){
        if(X[i]==x) return true;
    }
    return false;
}

void dijkstra(graph gr){
    for(int j=0;j<200;j++) A[j]=1000000;
    A[1]=0;
    int i=1;
    X[0]=1;
    bool check=true;
    while(check && i<200){
        int min=1000000;
        int w;
        for(int j=0;j<i;j++){
            //cout<<"start";
            node* temp=gr.g_adjacent(X[j]);
            while(temp){
                //cout<<"reached"<<A[X[j]]<<X[j]<<A[X[j]]+temp->dist;
                if(min>(A[X[j]]+temp->dist) && !contain(temp->data,i)){
                    min=A[X[j]]+temp->dist;
                    w=temp->data;
                    //cout<<"min"<<min<<"w"<<w;
                }
                temp=gr.g_adjacent(X[j]);
            }
        }
        if(min!=1000000){
            X[i]=w;
            A[X[i]]=min;
            i++;
        }else check=false;
    }
    cout<<A[7]<<" "<<A[37]<<" "<<A[59]<<" "<<A[82]<<" "<<A[99]<<" "<<A[115]<<" "<<A[133]<<" "<<A[165]<<" "<<A[188]<<" "<<A[197]<<" ";

}

int main(){
    graph gr(200);
    gr.g_input();
    //gr.g_showall_adj();
    dijkstra(gr);
    return 0;
}
