#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <stdlib.h>
using namespace std;


struct node{
	string color;
	int f;
	node* p;
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
				//if(temp==NULL) cout<<"null";
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

	void rename_heads(){
	    head->data=head->f;
	}

	void rename_nodes_to_finishtime(int arr[]){
	    node* temp=head->link;
	    while(temp!=NULL){
	        temp->data=arr[temp->data];
	        temp=temp->link;
	    }
	}
};



class graph{
	int vertices;
	int edges;
	list** g;
public:
	graph(int v){
	    g=new list*[v+1];
		vertices=v;
		for(int i=1;i<=vertices;i++){
			g[i]=new list;
			node* temp=new node;
			temp->data=i;
			//temp->color=" ";
			//temp->f=-1;
            temp->color="white";
            temp->f=98654321;
			temp->p=NULL;
			g[i]->insert_at_end_node(temp);
		}
	}
	~graph(){
	    delete g;
	}
	void g_input(){
		int i=0,num1=0,num2=0;
        string ch;
        ifstream myfile;
        myfile.open("SCC.txt");
        if (myfile.is_open())
        {
            while ( myfile.good())
            {
              getline(myfile,ch);
              istringstream iss(ch);
              i=0;
              while(iss){
                  i++;
                  string sub;
                  iss>>sub;
                  int v=atoi(sub.c_str());
                  if(v==0) break;
                  if(i==1){num1=v;}
                  if(i==2){num2=v;}
              }
              node* temp=new node;
              temp->data=num1;
              temp->color=" ";
              temp->f=-1;
              temp->link=NULL;
              temp->p=NULL;
              g[num2]->insert_at_end_node(temp);
            }
            myfile.close();
        }
	}
	void g_showall_adj(){
		for(int i=1;i<=vertices;i++){
			g[i]->show();
			cout<<endl;
		}
	}
	void g_set_tra(){
		for(int i=1;i<=vertices;i++)
			g[i]->set_tra();
	}
	node* g_adjacent(int n){
		return g[n]->traverse();
	}
	node* g_get_node(int d){
		node* temp;
		for(int i=1;i<=vertices;i++){
				temp=g[i]->get_head();
				if(temp!=NULL && temp->data==d)
					return temp;
		}
		return NULL;
	}
	void g_rename_nodes(){
	    int arr[vertices+1];
	    arr[0]=0;
	    for(int i=1;i<=vertices;i++){
			g[i]->rename_heads();
			arr[i]=g[i]->get_head()->data;
		}
		for(int i=1;i<=vertices;i++){
			g[i]->rename_nodes_to_finishtime(arr);
		}
	}
	void reverse_graph(){
	    cout<<"reversing";
	    //g_set_tra();
	    list* gtemp[vertices+1];
	    for(int i=1;i<=vertices;i++){
			gtemp[i]=new list;
			node* temp=new node;
			temp->data=i;
			//temp->color="";
			//temp->f=-1;
            temp->color="white";
            temp->f=98654321;
			temp->p=NULL;
			gtemp[i]->insert_at_end_node(temp);
		}
	    node* temp1;
	    for(int i=1;i<=vertices;i++){
	        while(true){
                temp1=g[i]->traverse();
                if(temp1==NULL) break;
                node* temp2=new node;
                temp2->data=g[i]->get_head()->data;
                temp2->color=" ";
                temp2->f=-1;
                temp2->link=NULL;
                temp2->p=NULL;
                gtemp[temp1->data]->insert_at_end_node(temp2);
	        }
		}
	    for(int i=1;i<=vertices;i++){
	        g[i]=gtemp[i];
	    }
	}
};

long DFSVisit(graph* g,node* u,int* time){
    long ct=0;
	node* v;
	u->color="gray";
	while(true){
            //cout<<"a";
			v=g->g_adjacent(u->data);
			if(v==NULL) break;
			v=g->g_get_node(v->data);
			if(v->color=="white"){
			    //ct++;
				v->p=u;
				DFSVisit(g,v,time);
				//ct+=DFSVisit(g,v,time);
                //cout<<ct<<"  ";
			}
	}
	u->color="black";
	*time=*time+1;
	u->f=*time;
	return ct;
}

void DFS(graph* g,int n){
    long* scc=new long[n/2];
	node* u;
	int i=n;
	int time=0;
	/*
	while(true){
		u=g->g_get_node(i);
		if(u==NULL || i==0) break;
		u->p=NULL;
		u->color="white";
		u->f=98654321;
		i--;
	}
	*/
	cout<<" start dfs ";
	//i=n;
	int j=0;
	long check=0;
	while(true){
		u=g->g_get_node(i);
		if(u==NULL || i==0) break;
		if(u->color=="white"){
			check=DFSVisit(g,u,&time);
			if(check!=0){
			    //scc[j]=check+1;
			    //cout<<scc[j]<<"scc  ";
                j++;
			}
		}
		i--;
	}
	cout<<" no of scc: "<<j<<endl;
	//for(int m=0;m<j;m++){
        //cout<<scc[m]<<" ";
	//}
}

int main(){
    graph gr(875714);
	gr.g_input();
	//gr.g_showall_adj();

	//node* temp;
    /*
    cout<<"All nodes are: ";
	for(int i=1;i<=875714;i++){
		temp=gr.g_get_node(i);
		if(temp==NULL) break;
		cout<<temp->data<<" ";
	}
    */
	//cout<<endl;
	//gr.g_set_tra();
	DFS(&gr,875714);
	/*
	for(int i=1;i<=875714;i++){
			temp=gr.g_get_node(i);
			cout<<"node:"<<temp->data<<" color:"<<temp->color<<" finish time:"<<temp->f;
			if(temp->p!=NULL) cout<<" parent:"<<temp->p->data<<endl;
			else cout<<" parent: null"<<endl;
	}
    */
	gr.g_rename_nodes();
	gr.reverse_graph();
	//gr.g_showall_adj();
	DFS(&gr,875714);

	return 0;
}
