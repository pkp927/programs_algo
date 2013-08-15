// pk.cpp : Defines the entry point for the console application.
//MINIMUM CUT GRAPH

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<conio.h>
#include<queue>
#include<string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;


struct node{
	int data;
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
		//node* temp=n;
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
				cout<<temp->data<<" ";
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
		//int d;
		for(int i=0;i<tra;i++)
			temp=temp->link;
		if(temp==NULL){
			set_tra();
			//d=-1;
		}else {
			tra++;
			//d=temp->data;
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
			g[i]=new list;                //
			node* temp=new node;
			temp->data=i;
			g[i]->insert_at_end_node(temp);  //
		}
	}
	void g_input(){
	    int i = 1;
        int line;
        string ch;
        ifstream myfile;
        myfile.open("FileForMinCut.txt");
        if (myfile.is_open())
        {
            while ( myfile.good())
            {
              getline(myfile,ch);
              istringstream iss(ch);
              while(iss){
                  string sub;
                  iss>>sub;
                  int v=atoi(sub.c_str());
                  if(v==0) break;
                  if(v!=i){
                      node* temp=new node;
                      temp->data=v;
                      temp->link=NULL;
                      g[i]->insert_at_end_node(temp);  //
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



	void merge_vertices(node* temp1,node* temp2){
		node* temp;
		int n1=temp1->data;
		int n2=temp2->data;
		g[n1]->set_tra(); //
		g[n2]->set_tra(); //
		while(true){
			temp=g_adjacent(n2);
			if(temp==NULL) break;
			if(temp->data!=n1){
				node* t=new node;
				t->data=temp->data;
				t->link=NULL;
				g[n1]->insert_at_end_node(t);  //
			}
		}
		g_set_tra();
		node* adj;
		for(int i=1;i<=vertices;i++){
			temp=g_get_vertex(i);
			if(temp!=NULL&&i!=n1){
				while(true){
					adj=g_adjacent(temp->data);
					if(adj==NULL) break;
					else if(adj->data==n2) adj->data=n1;
                }
			}
		}
		g[n1]->set_tra();
		while(true){
					adj=g_adjacent(n1);
					if(adj==NULL) break;
					else if(adj->data==n2) g[n1]->delete_node(n2);
        }

		g[n2] = NULL;
		g_set_tra();  // //
	}
};

void minCutGraph(graph* g){
	int ver[2];
	int ct;
	int n;
	node* temp1;
	node* temp2;
	int p=0;
	while(true){
		n=rand()%200+1;
		//temp1=g->g_max_deg();
		temp1=g->g_get_vertex(n);
		if(temp1!=NULL) temp2=g->g_adjacent(temp1->data);
		if(temp1!=NULL&&temp2!=NULL){
			//cout<<temp1->data<<" "<<temp2->data<<endl;
			g->merge_vertices(temp1,temp2);
		}
		ct=0;
		int j=0;node* temp;
		for(int i=1;i<=200;i++){
			temp=g->g_get_vertex(i);
			if(temp!=NULL){
				ver[j]=temp->data;
				ct++;
			}
			j=(j+1)%2;
		}
		if(ct==2) break;
        //p++;
        //if(p==200) break;
	}
	ct=0;
	for(int i=1;i<=200;i++){
		temp1=g->g_get_vertex(i);
		if(temp1!=NULL){
			while(g->g_adjacent(i)!=NULL)
				ct++;
			break;
		}
	}
	cout<<endl;
	//g->g_show_adj(ver[0]);
	cout<<endl;
	//g->g_show_adj(ver[1]);
	cout<<endl<<ct<<" "<<ver[0]<<" "<<ver[1];

}

int main(){
    for(int i=0;i<50;i++){
	graph gr(200);
	gr.g_input();
	//node* temp1=gr.g_get_vertex(200);
	//node* temp2=gr.g_get_vertex(155);
	//gr.merge_vertices(temp2,temp1);
    //gr.g_showall_adj();
	srand(time(0));
	minCutGraph(&gr);
    }
	getch();
	return 0;
}

