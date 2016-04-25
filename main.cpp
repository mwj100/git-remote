//
//  main.cpp
//  shiyan
//YKCW6-BPFPF-BT8C9-7DCTH-QXGWC
//  Created by wjmiao on 4/16/16.
//  Copyright © 2016 wjmiao. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <tuple>


using namespace std;

void PrintState(int state[][3][3]);
int HValue(int state[][3][3],int target[][3][3]);


typedef struct Node{
    int state[3][3][3];
    int h;
    tuple<int, int, int> zero;
    int depth;
    struct Node* parent;
}Node;

struct cmp{
    bool operator()(Node* a, Node* b){
        return a->h + a->depth > b->h + b->depth;
    }
};

struct Hash_Node{
    size_t operator()(const Node* &A) const{
        int b = 378551;
        int a = 63689;
        long hash = 0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    hash = hash * a + A->state[i][j][k];
                    a = a * b;
                }
            }
        }
        return size_t(hash);
    }
};

struct Equal_Node{
    bool operator()(const Node* &a, const Node* &b) const{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    if(a->state[i][j][k] != b->state[i][j][k])
                        return false;
                }
            }
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    ifstream source("./source.txt");
    if(!source){
        cout<<"Open file error!";
        return 0;
    }
    int initstate[3][3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            source>>initstate[i][j][0];
            source>>initstate[i][j][1];
            source>>initstate[i][j][2];
        }
    }
    ifstream target("./target.txt");
    if(!target){
        cout<<"Open file error!";
        return 0;
    }
    int endstate[3][3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            target>>endstate[i][j][0];
            target>>endstate[i][j][1];
            target>>endstate[i][j][2];
        }
    }
    
    Node root;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                root.state[i][j][k] = initstate[i][j][k];
                if(initstate[i][j][k] == 0)
                    root.zero = make_tuple(i,j,k);
            }
        }
    }
    root.h = HValue(root.state, endstate);
    root.depth = 1;
    root.parent = nullptr;

    priority_queue <Node*,vector<Node*>,cmp> queue;
    queue.push(&root);
    
    unordered_set<const Node*, Hash_Node, Equal_Node> hashtable;
    
    while(queue.size()){
        Node* minh = queue.top();
        queue.pop();
        if(!HValue(minh->state,endstate)){
            //到达最终
            break;
        }
        hashtable.insert(minh);
        //遍历所有孩子
        int i = get<0>(minh->zero),j = get<1>(minh->zero),k = get<2>(minh->zero);
        if(i-1>=0 && minh->state[i-1][j-1][k-1]!=-1){
            Node* child = new Node;
            for(int i1=0;i1<2;i1++){
                for(int i2=0;i2<2;i2++){
                    for(int i3=0;i3<2;i3++){
                        child->state[i1][i2][i3] = minh->state[i1][i2][i3];
                    }
                }
            }
            child->state[i][j][k] = minh->state[i-1][j][k];
            child->state[i-1][j][k] = minh->state[i][j][k];
            const Node* hehe = child;
            auto search = hashtable.find(hehe);
          //  if(search != hashtable.end()){
                
            //}
            
        }
    
        
    }

    
    
    
}

int HValue(int state[][3][3],int target[][3][3]){
    int count = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                if(state[i][j][k]!=0 && state[i][j][k]!= -1 && state[i][j][k] != target[i][j][k])
                    count++;
            }
        }
    }
    return count;
}

//tuple<int,int,int> FindZero(Node* a)

void PrintState(int state[][3][3]){
    //print out the state;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                cout<<state[i][j][k];
                cout<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}