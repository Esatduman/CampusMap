// graph.h <Starter Code>
// < Esat Duman >
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Spring 2023
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:

  struct vData{
  map<VertexT, WeightT> mapVw;
  set<VertexT> setV;
  };

  map<VertexT, vData> Vertices; //map for the vertices 
  int numberOfEdges;
  
  // come up with something here 

 public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  graph() { // replaced with constructor 

    this->numberOfEdges = 0;
  }

  graph(const graph &other) 
    {
        this->Vertices = other.Vertices;
        this->numberOfEdges = other.numberOfEdges;
    }

    graph &operator=(const graph &other) // operator function needed
    {
        this->Vertices = other.Vertices;
        this->numberOfEdges = other.numberOfEdges;

        return *this;
    }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {

    return this->Vertices.size(); // all we do here is return the size of the vertices 
    
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    
    return this->numberOfEdges;  // number of edges 
    
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
   
    if (Vertices.find(v) != Vertices.end()) {
        return false;
    }

    // Add the new vertex to the graph
    Vertices.emplace(v, vData{}); 

    // Return true to indicate the vertex was added successfully
    return true; 
    
    
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    // Find the vertex corresponding to the starting point of the edge
    auto it = Vertices.find(from);
    if (it == Vertices.end()) {
        // Vertex not found, so return false
        return false;
    }

    // Check if the edge already exists
    auto found = it->second.mapVw.find(to);
    if (found != it->second.mapVw.end()) {
        // If value is found replace with newer weight
        found->second = weight;
        return true;

    } else {
        // Add the new edge
        auto itEdge = Vertices.find(to);
        if (itEdge == Vertices.end()) {
            // Vertex not found, so return false
            return false;
        }
        // Insert the new edge and update the set of adjacent vertices
        it->second.mapVw.emplace(to, weight); // I am using emplace here since it increases the size of the container 
        it->second.setV.emplace(to); // Also inserts the new edge. 
        numberOfEdges++;
        return true;
    }
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
       // Check if 'from' vertex exists
    auto it = Vertices.find(from);
    if (it == Vertices.end()) {
        return false;
    }

    // Check if 'to' vertex exists
    if (Vertices.count(to) == 0) {
        return false;
    }

    // Find the weight of the edge between 'from' and 'to'
    auto found = it->second.mapVw.find(to);
    if (found != it->second.mapVw.end()) {
        weight = found->second;
        return true;
    } else {
        return false;
    }
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    

     // Find the position of the vertex in the Vertices map
      auto it = this->Vertices.find(v);
      if (it == this->Vertices.end()) {
    // If the vertex is not found, return an empty set
      return set<VertexT>{};
      }

    // Otherwise, return the set of vertices adjacent to the vertex
      return it->second.setV;

  }
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    vector<VertexT> v;

    for (auto i : this->Vertices) {
    v.push_back(i.first);// returns a copy:
    }
    return v;
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
      auto begin = this->Vertices.begin();
    for (int i = 0; i < this->NumVertices(); ++i) {
      output << " " << i << ". " << this->Vertices[i] << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (int row = 0; row < this->NumVertices(); ++row) {
      output << " row " << row << ": ";
      auto inside = this->Vertices.begin();
      
      for (int col = 0; col < this->NumVertices(); ++col) {
        auto method = begin->second.mapVw.find(inside->first);
        if (method == begin->second.mapvW.end()) {
          output << "F ";
        } else {
          output << "(T,"
            << method->second
            << ") ";
            inside++;
        }
      }
      output << endl;
    }
    output << "**************************************************" << endl;
  }
};
