#ifndef GRAPH_H__
#define GRAPH_H__
#include<string>
#include<vector>

// Why use std::Vector instead of std::List?
// TODO: Desctructors to be created
namespace mits{
    /* Graph to support only 1000 vertices and 1000 edges */
    #define MAX_VERTICES 1000
    #define MAX_EDGES 1000
    #define NBITS 8
    #define MAX_BIT_INDEX 7
    
    enum RepType{
        ADJACENCY_MATRIX=1,
        INCIDENCE_MATRIX=2
    } ;
  
    struct ComponentInfo{
        int cId;
        std::vector<std::string> vertices;
    };
    
    class BitMapMatrix{
        private:
            char* vbitmap;
            int nvertex;
        public:
            BitMapMatrix(){
            }

            /* constructor creates a bit map of required size based on number of vertex */
            BitMapMatrix(int nv);
        
            /* get bit value stored in a 2D array */
            bool getBit(int i, int j);
        
            /* set bit at given position on 2D array */
            void setBit(int i, int j); 
        
            /* reset bit at given position on 2D array */
            void resetBit(int i, int j);
        
            /* delete rth row */
            void deleteEntry(int v);
    };
    
    // NOTE: Vertices are assigned numbers from 1 to n
    class Graph{
        private:
            int nvertex, /* number of vertices */
                nedge;   /* number of edges */
            std::vector<std::string> vnames,  /*  names of vertices */
                                    enames; /* names of edges */
            
            RepType repType; 
        
            mits::BitMapMatrix bmm;
        
        public:
            /* empty constructor */
            Graph(){
            }

            /* init graph using adjacency matrix */
            Graph(const int nv, const int ne, std::vector<std::string> &vn, std::vector<std::string> &en, 
                  const int* adjcMat, RepType t);
            
            /* copy constructor */
            Graph(mits::Graph &g);
        
            /* get number of vertices */
            int getVertexCount();
        
            std::string getVertexName(int v);
        
            /* get number of edges */
            int getEdgeCount();
        
            /* get representation type */
            RepType getRepType();
            
            /* get vertex names */
            std::vector<std::string> getVertexNames();
            
            /* get edge names */
            std::vector<std::string> getEdgeNames();
            
            /* check if vertices are adjacent */
            bool isAdjacent(int v1, int v2);
        
            /* get the degree of the vertex */
            int getDegree(int v);
        
            /* get the vertex with max degree */
            int getVertexWithMaxDegree();
            
            /* get the number of nonadjacent vertice */
            int getNonAdjVertexCount(int v);    
        
            /* print the adjancency matrix */
            void printAdjcMat();
        
            /* fuse vertices v1 and v2 */
            void fuseV(int v1, int v2);
        
            void deleteVertex(int v);    
        
            /* get the component count in the graph */
            std::vector<ComponentInfo> getComponents();
    };
    
    class UnsupportedGraphSize{};
}
#endif