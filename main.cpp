#include<iostream>
#include<vector>
#include<string>
#include "graph.h"
#define MAX_EDGENAME_LEN 10

using namespace std;

int main(void){
    /*int adjcMat[][6]={\
                        {0, 1, 0, 0, 1, 1},\
                        {1, 0, 0, 1, 1, 0},\
                        {0, 0, 0, 1, 0, 0},\
                        {0, 1, 1, 0, 1, 1},\
                        {1, 1, 0, 1, 0, 0},\
                        {1, 0, 0, 1, 0, 0}\
                    };
    int* pAdjcMat=(int*)adjcMat;
    std::vector<std::string> vnames(6), enames(8);
    char vn[][6]={"v1", "v2", "v3", "v4", "v5", "v6"};
    char en[][8]={"e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8"};
    
    vnames.assign(vn,vn+6);
    enames.assign(en, en+8);
    
    mits::Graph g(6, 8, vnames, enames, pAdjcMat, mits::ADJACENCY_MATRIX);
    g.printAdjcMat();
    cout<<endl;                
    */
    
    /*int adjcMat[][4]={\
                        {0, 1, 0, 0},\
                        {1, 0, 0, 1},\
                        {0, 0, 0, 0},\
                        {0, 1, 0, 0}
                    };
                        
    int* pAdjcMat=(int*)adjcMat;
    std::vector<std::string> vnames(4), enames(2);
    std::string vn[4]={"v1", "v2", "v3", "v4"};
    std::string en[2]={"e1", "e2"};
    
    
    vnames.assign(vn,vn+4);
    enames.assign(en,en+2);
    
    mits::Graph g(4, 2, vnames, enames, pAdjcMat, mits::ADJACENCY_MATRIX);
    g.printAdjcMat();
    cout<<endl; */              

    int adjcMat[][20]={\
                        {0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},\
                        {1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},\
                        {1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                        {1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},\
                        {0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,0,0,1,1},\
                        {0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,1},\
                        {0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0},\
                        {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0},\
                        {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,1,1},\
                        {1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},\
                        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},\
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},\
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},\
                        {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1},\
                        {0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},\
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},\
                        {0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,1},\
                        {0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,0,1,0}\
                    };
                        
    int* pAdjcMat=(int*)adjcMat;
    std::vector<std::string> vnames(20), enames(2);
    std::string vn[20]={"v1", "v2", "v3", "v4", "v5","v6", "v7", "v8", "v9", "v10","v11", "v12", "v13", "v14", "v15","v16", "v17", "v18", "v19", "v20"};
    std::string en[2]={"e1", "e2"};
    
    
    vnames.assign(vn,vn+20);
    enames.assign(en,en+2);
    
    mits::Graph g(20, 2, vnames, enames, pAdjcMat, mits::ADJACENCY_MATRIX);
    g.printAdjcMat();
    cout<<endl;                

    vector<mits::ComponentInfo> cInfoList=g.getComponents();
    for(int i=0;i<cInfoList.size();i++){
        cout<<"COMP "<<cInfoList[i].cId<<"; VERT: ";
        for(int j=0;j<cInfoList[i].vertices.size();j++){
            cout<<cInfoList[i].vertices[j]<<" ";
        }
        cout<<endl;
    }
        
    
    /*Delete Vertex
    g.deleteVertex(1);
    g.printAdjcMat();*/
    
    
    /* Fuse vertices
    g.fuseV(1,2);
    g.printAdjcMat();
    */
    
    /* BitMapMatrix related functions
    mits::BitMapMatrix bmm(3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            adjcMat[i][j]==1 ? bmm.setBit(i,j) : bmm.resetBit(i,j);
        }
    }
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<" "<<bmm.getBit(i,j);
        }
        cout<<endl;
    }

    bmm.deleteEntry(2);
    
    cout<<endl;
    
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cout<<" "<<bmm.getBit(i,j);
        }
        cout<<endl;
    }*/
    
}