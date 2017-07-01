#include<iostream>
#include<string>
#include<cmath>
#include "graph.h"

mits::Graph::Graph(const int nv, const int ne, std::vector<std::string> &vn, std::vector<std::string> &en, 
                   const int* adjcMat, RepType t){
    // 1. check if nv > MAX_VERTICES
    if(nv > MAX_VERTICES)
        throw mits::UnsupportedGraphSize();
    // 2. set the class members
    this->nvertex=nv;
    this->nedge=ne;
    this->vnames=vn;
    this->enames=en;
    this->repType=t;
        
    //3. use the adjcMat to set the bit map
    this->bmm=mits::BitMapMatrix(this->nvertex);
    
    for(int i=0;i<this->nvertex;i++){
        for(int j=0;j<this->nvertex;j++){
            if(*(adjcMat+i*this->nvertex+j) == 1)/* if the adjacency is 1 then set the bit */
                bmm.setBit(i,j);
            else /* else reset it */
                bmm.resetBit(i,j);
        }
    }
}

mits::Graph::Graph(mits::Graph &g){
    
    this->nvertex=g.getVertexCount();
    this->nedge=g.getEdgeCount();
    this->vnames=g.getVertexNames();
    this->enames=g.getEdgeNames();
    this->repType=g.getRepType();
        
    //3. use the adjcMat to set the bit map
    this->bmm=mits::BitMapMatrix(this->nvertex);

    for(int i=0;i<this->nvertex;i++){
        for(int j=0;j<this->nvertex;j++){
            if(g.isAdjacent(i+1,j+1))/* if the adjacency is 1 then set the bit */
                bmm.setBit(i,j);
            else /* else reset it */
                bmm.resetBit(i,j);
        }
    }
}

void mits::Graph::printAdjcMat(){

    int bitpos=0, byteloc=0, bitoffset=0;
    int mask;
    
    for(int i=0;i<this->nvertex;i++){
        for(int j=0;j<this->nvertex;j++){
            if(bmm.getBit(i,j))
                std::cout<<1<<' ';
            else
                std::cout<<0<<' ';
        }
        std::cout<<std::endl;
    }
}

bool mits::Graph::isAdjacent(int v1, int v2){
    return bmm.getBit(v1-1, v2-1);
}

int mits::Graph::getVertexCount(){
    return this->nvertex;
}

int mits::Graph::getEdgeCount(){
    return this->nedge;
}

mits::RepType mits::Graph::getRepType(){
    return this->repType;
}

std::vector<std::string> mits::Graph::getVertexNames(){
    return this->vnames;
}

std::vector<std::string> mits::Graph::getEdgeNames(){
    return this->enames;
}

std::string mits::Graph::getVertexName(int v){
    return this->vnames[v-1];
}

/* NOTE: The (i,i) entry is not changed to 0 after the ORing */
void mits::Graph::fuseV(int v1, int v2){
    
    if(v2<v1){
        v1=v1+v2;
        v2=v1-v2;
        v1=v1-v2;
    }
    // 1. OR rows v1 and v2 
    int r1=v1-1, r2=v2-1;
    for(int c=0;c<this->nvertex;c++){
        (bmm.getBit(r1,c)|bmm.getBit(r2,c))?bmm.setBit(r1,c):bmm.resetBit(r1,c);
    }
    // 2. OR cols v1 and v2
    int c1=v1-1, c2=v2-1;
    for(int r=0;r<this->nvertex;r++){
        (bmm.getBit(r,c1)|bmm.getBit(r,c2))?bmm.setBit(r,c1):bmm.resetBit(r,c1);
    }
    bmm.deleteEntry(v2-1);
    this->nvertex-=1;
    this->vnames.erase(this->vnames.begin()+v2-1);
}

/* NOTE: self loops are not counted */
int mits::Graph::getDegree(int v){
    
    int degree=0;
    int r=v-1;
    for(int c=0;c<this->nvertex;c++){
        // self loops not counted
        if(c!=r && bmm.getBit(r,c))
            degree++;
    }
    return degree;
}

int mits::Graph::getVertexWithMaxDegree(){

    int maxDegree=0,maxV=1;
    for(int v=1;v<=this->nvertex;v++){
        int d=getDegree(v);
        if(maxDegree<d){
            maxDegree=d;
            maxV=v;
        }
    }
    return maxV;
}

int mits::Graph::getNonAdjVertexCount(int v){

    int count=0;
    int r=v-1;
    for(int c=0;c<this->nvertex;c++){
        // nonadjancency with itself not counted
        if(c!=r && !bmm.getBit(r,c))
            count++;
    }
    return count;
}

void mits::Graph::deleteVertex(int v){
    
    bmm.deleteEntry(v-1);
    this->nvertex-=1;
    this->vnames.erase(this->vnames.begin()+v-1);
}

std::vector<mits::ComponentInfo> mits::Graph::getComponents(){
    
    Graph gtemp=*this;
    int count=0;
    std::vector<mits::ComponentInfo> compList;
    
    do{   
        count++;
        mits::ComponentInfo cInfo;
        cInfo.cId=count;
        int k=0;
        
        /* select vertex i in g */
        int v=gtemp.getVertexWithMaxDegree();
        
        /* fuse all vertices adjacent to i with i and call the new vertex i */
        int nonadj_v_count=gtemp.getNonAdjVertexCount(v);
        do{

            for(int i=1;i<=gtemp.getVertexCount();i++){
                if(v!=i && gtemp.isAdjacent(v,i)){
                    cInfo.vertices.push_back(gtemp.getVertexName(v>i?v:i));
                    gtemp.fuseV(v,i);
                    i--;
                    //v=gtemp.getVertexWithMaxDegree(); // get new v as vertex numbering changes
                }
            }
        /* Is the number of vertices nonadjacent to i same as before fusion?   */  
        }while(nonadj_v_count!=gtemp.getNonAdjVertexCount(v));
        
        /* delete from g vertex i (along with all vertices fused with i) 
           call the remaining subgraph as g */
        cInfo.vertices.push_back(gtemp.getVertexName(v));
        gtemp.deleteVertex(v);
        compList.push_back(cInfo);
    /* is there any vertex left in g? */  
    }while(gtemp.getVertexCount()>0);
    
    return compList;
}

mits::BitMapMatrix::BitMapMatrix(int nv){
    
    this->nvertex=nv;
    this->vbitmap=(char*)malloc((nvertex*nvertex)/NBITS);    
}

bool mits::BitMapMatrix::getBit(int i, int j){
    
    int bitpos=i*this->nvertex+j;   /* 2D (i,j) position to linear position */
    int byteloc=bitpos/NBITS;       /* find the byte in the array where the bit is set */
    int bitoffset=bitpos%NBITS;     /* find the offset of the bit to be set */

    int mask=pow(2, MAX_BIT_INDEX-bitoffset); /* build mask at required location */
    return (this->vbitmap[byteloc]&mask)!=0;
}

void mits::BitMapMatrix::setBit(int i, int j){
    
    int bitpos=i*this->nvertex+j;   /* 2D (i,j) position to linear position */
    int byteloc=bitpos/NBITS;       /* find the byte in the array where the bit is set */
    int bitoffset=bitpos%NBITS;     /* find the offset of the bit to be set */

    int mask=pow(2, MAX_BIT_INDEX-bitoffset); /* build mask at required location */
    this->vbitmap[byteloc]|=mask;
}

void mits::BitMapMatrix::resetBit(int i, int j){
    
    int bitpos=i*this->nvertex+j;   /* 2D (i,j) position to linear position */
    int byteloc=bitpos/NBITS;       /* find the byte in the array where the bit is set */
    int bitoffset=bitpos%NBITS;     /* find the offset of the bit to be set */

    int mask=pow(2, MAX_BIT_INDEX-bitoffset); /* build mask at required location */
    this->vbitmap[byteloc]&=(~mask);
}

void mits::BitMapMatrix::deleteEntry(int v){
    
    int r,c;
    r=c=v; // vertex counting starts from 1
    
    /* delete row first */
    int i1=r,j1=0,j2=0,i2=r+1;
    
    for(;i1<this->nvertex-1;i1++,i2=i1+1){
        for(j1=j2=0;j1<this->nvertex;j1++,j2++){     
            getBit(i2,j2) ? setBit(i1,j1): resetBit(i1,j1);
        }
    }
    
    for(int i=this->nvertex-1;i<this->nvertex;i++)
        for(int j=0;j<this->nvertex;j++)
            resetBit(i,j);

    /* delete column */
    i1=j1=i2=j2=0;
    for(;i1<this->nvertex-1;i1++){
        for(j1=0;j1<this->nvertex;j1++,j2++){
            if(j2==c)
                j2++;
            if(j2==this->nvertex){
                i2++;
                j2=(c!=0)?0:1;
            }
            getBit(i2,j2) ? setBit(i1,j1): resetBit(i1,j1);
        }
    }
    
    this->nvertex-=1; // reduce the vertex count
}