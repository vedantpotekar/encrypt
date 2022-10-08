#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>
using namespace std;

class Node{
    public:
        char data;
        Node* lchild;
        Node* rchild;
}*root=NULL;


class Queue{
    private:
        int front;
        int rear;
        int size;
        Node** Q;
    public:
        Queue(){front=-1;rear=-1;size=10;Q=new Node*[size];};
        Queue(int n){front=-1;rear=-1;size=n;Q=new Node*[size];};
        void enqueue(Node* x);
        Node* dequeue();
        void display();
        int isempty();
};

void Queue::enqueue(Node* x){
    if(rear==size-1)
        cout<<"queue full"<<rear<<" "<<size-1<<"\n";
    else{
        rear++;
        Q[rear]=x;
    }
}

Node* Queue::dequeue(){
    Node* x=0;
    if(front==rear)
        cout<<"queue is empty\n";
    else{
        x=Q[front+1];
        front++;
    }
    return x;
};

void Queue::display(){
    for(int i=front+1;i<=rear;i++)
        cout<<Q[i]->data<<" ";
};

int Queue::isempty(){
    return front==rear;
};

void create(){
    Node *p,*t;
    string s;
    cin>>s;
    int traversestring=0;
    char x;
    Queue q(100000);
    // cout<<"enter value of root:-    ";
    // cin>>x;
    x=s[traversestring++];
    root=new Node;
    root->data=x;
    root->lchild=root->rchild=NULL;
    q.enqueue(root);

    while(!q.isempty()){
        p=q.dequeue();
        // cout<<"enter left child of  "<<p->data<<":-  ";
        // cin>>x;
        if(s[traversestring+1]=='\0')
            x='?';
        else
            x=s[traversestring++];
        if(x!='?'){
            t=new Node;
            t->data=x;
            t->lchild=t->rchild=NULL;
            p->lchild=t;
            q.enqueue(t);
        }
        // cout<<"enter right child of "<<p->data<<":-  ";
        // cin>>x;
        if(s[traversestring+1]=='\0')
            x='?';
        else
            x=s[traversestring++];
        if(x!='?'){
            t=new Node;
            t->data=x;
            t->lchild=t->rchild=NULL;
            p->rchild=t;
            q.enqueue(t);
        }
    }
};

void preorder(Node* p){
    if(p){
        cout<<p->data;
        preorder(p->lchild);
        preorder(p->rchild);
    }
};

void inorder(Node* p){
    if(p){
        preorder(p->lchild);
        cout<<p->data;
        preorder(p->rchild);
    }
};

void levelorder(Node* p){
    Queue qq(100000);
    cout<<p->data;
    qq.enqueue(p);
    while(!qq.isempty()){
        p=qq.dequeue();
        if(p->lchild){
            cout<<p->lchild->data;
            qq.enqueue(p->lchild);
        }
        if(p->rchild){
            cout<<p->rchild->data;
            qq.enqueue(p->rchild);
        }
    }
}

int search(vector<char> inord, int start, int end, int curr){
    for(int i=start;i<=end;i++){
        if(inord[i]==curr) return i;
    }
    return -1;
}

Node* buildtree(vector<char> preord,vector<char> inord, int start, int end){
    static int idx = 0;
    if(start>end) return NULL;
    char curr=preord[idx];
    idx++;
    Node* node=new Node;
    node->data=curr;
    node->lchild=node->rchild=NULL;
    if(start==end) return node;
    int pos=search(inord,start,end,curr);

    node->lchild=buildtree(preord,inord,start,pos-1);
    node->rchild=buildtree(preord,inord,pos+1,end);
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("preord.txt","w",stdout);
    create();
    preorder(root);

    freopen("inord.txt","w",stdout);
    inorder(root);

    freopen("output.txt","w",stdout);
    levelorder(root);


    return 0;
}
