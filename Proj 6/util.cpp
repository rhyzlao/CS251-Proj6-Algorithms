/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include <limits>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;
const int Infinity = numeric_limits<int>::max();

vector<char> DijkstraShortestPath(graph& g, char startV, map<char, int> &Distance, map<char, char> &Predecessors){	
	vector<char> AllVertex;
	vector<char>  visited;
	vector<char>  neighborVect;
	minqueue<char, int> unvisitedQueue;
	
// 	map<char, int> Distance;
// 	map<char, char> Predecessors;
	
	AllVertex = g.vertices();
	
	for(unsigned int i = 0; i < AllVertex.size(); i++){
		Distance[AllVertex[i]] =  Infinity;
		Predecessors[AllVertex[i]] = -1;
		unvisitedQueue.pushinorder(AllVertex[i], Infinity);		
	}
	
	//Distance.emplace(startV, 0);
	Distance[startV] = 0;
	unvisitedQueue.pushinorder(startV, 0);
	
	while(!unvisitedQueue.empty()){
		char currentV = unvisitedQueue.minfront();
		unvisitedQueue.minpop();
		if(Distance.at(currentV) == Infinity){
			break;
		}
		visited.push_back(currentV);
		
		neighborVect = g.neighbors(currentV);
		for(unsigned int d = 0; d < neighborVect.size(); d++){
			int edgeWeight = g.getweight(currentV, neighborVect[d]);
			int alternativePathDist = (Distance.at(currentV)) + edgeWeight;
			
			int adjVDist = Distance.at(neighborVect[d]);
			if(alternativePathDist < adjVDist){
				//Distance.emplace(neighborVect[i], alternativePathDist);
				Distance[neighborVect[d]] = alternativePathDist;
				//Predecessors.emplace(neighborVect[i], currentV);
				Predecessors[neighborVect[d]] = currentV;
				unvisitedQueue.pushinorder(neighborVect[d], alternativePathDist);
			}
		}
	}
	
	return visited;
}
//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  vector<char>  neighborVect;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;

  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  
  while(!frontierQueue.empty()){
     char currentV = frontierQueue.front();
     frontierQueue.pop();
     visited.push_back(currentV);
     
     neighborVect = g.neighbors(currentV);
     for(unsigned int i = 0; i < neighborVect.size(); i++){
        if (discoveredSet.find(neighborVect[i]) == discoveredSet.end()) {  // then v is not an element of the set:
            frontierQueue.push(neighborVect[i]);
            discoveredSet.insert(neighborVect[i]);
        }
     }
  }
  
  return visited;
}

//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;
  vector<char>  neighborVect;

  frontierStack.push(startV);

  while(!frontierStack.empty()){
     char currentV = frontierStack.top();
     frontierStack.pop();
     if (visitedSet.find(currentV) == visitedSet.end()){
      visited.push_back(currentV);
      visitedSet.insert(currentV);
      neighborVect = g.neighbors(currentV);
        for(unsigned int i = 0; i < neighborVect.size(); i++){
               frontierStack.push(neighborVect[i]);
        }
     }
     
  }
  

  return visited;
}


//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  //
  // Now input edges:  Src Dest Weight ... #
  //
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}

