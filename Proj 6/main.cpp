#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>    // std::reverse

#include "graph.h"
#include "util.h"
#include "minqueue.h"

using namespace std;


//
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;

  cout << "**Edges: ";

  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }

  cout << endl;
}

void outputVectors(string prefix, vector<char> v){
	cout << prefix << ": ";
	for(unsigned int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	
	cout << endl;
}

vector<char> outputPreds(vector<char> Dijk, map<char, char> Pred, char startV, int index){
	 int pushin = index;
// 	 stack<char> PredStack;
	 vector<char> PredVector;
	 //Push back first index
	 //PredVector.push_back(startV);
	 //make a copy index because the pushbacks will be in reverse order'
	 vector<char> copyVec;
// 	cout << "the index before the while loop is " << index << endl;
	 while(index > 0){
// 		 (Pred.at(Dijk[index])) != startV
// 		 cout << "in while loop this is " << index << endl;
		 copyVec.push_back(Pred.at(Dijk[index]));
		 //cout << "Pred at " << index << " is " << Pred.at(Dijk[index]) << endl;
		 index--;
	 }
	//reverse copy index, now in right order
	reverse(copyVec.begin(), copyVec.end());
	//copy vector in predvect
	for(unsigned int x = 0; x < copyVec.size(); x++){
		PredVector.push_back(copyVec[x]);
	}
	//push back last index into predvect
	PredVector.push_back(Dijk[pushin]);
	//erase duplicates
	PredVector.erase(unique( PredVector.begin(), PredVector.end() ), PredVector.end() );
// 	cout << "reached" << endl;
// 	vector<char> LastVector;
// 	for(int buh; buh < PredVector.size(); buh++){
// 		cout << "big tiddies"<<endl;
// 		cout << PredVector[buh] << endl;
// 		if(isalpha(PredVector[buh])){
// 			cout << "this is a letter bitch fuck you notheruckdedr e" << endl;
// 			LastVector.push_back(PredVector[buh]);		
// 		}
// 	}
// 	return LastVector;
    return PredVector;
}

void outputLast(vector<char> Last){
// 	while (!Last.empty()) { 
//         cout << ' ' << Last.top(); 
//         Last.pop(); 
//     } 
//     cout << "you fucking bitch" << endl;
    for(unsigned int i = 0; i < Last.size(); i++){
		if(isalpha(Last[i])){
			cout << Last[i] << " ";
		}
	}
}

	
int main()
{
  graph  g;
  string filename;
  char   startV;
  map<char, int> Distance;
  map<char, char> Predecessors;
	  
  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
  outputGraph(g);

  //
  // now ask user for a starting vertex, and run BFS as well as
  // strongly-connected algorithms:
  //
  cout << endl;
  cout << "Enter a starting vertex or #> ";
  cin >> startV;
  
	vector<char> AllVerts = g.vertices();
  while (startV != '#')
  {
	
	if((std::find(AllVerts.begin(), AllVerts.end(), startV) == AllVerts.end())){
		cout << "Not a vertex in the graph, ignored..." << endl;
	}
	else{
	    outputVectors("Neighbors", g.neighbors(startV));
		outputVectors("BFS", BFS(g, startV));
		outputVectors("DFS", DFS(g, startV));

		vector<char> DijkVector = DijkstraShortestPath(g, startV, Distance, Predecessors);
		outputVectors("Dijkstra", DijkVector);
		//cout distances
		//int i = 0;
		cout << DijkVector[0] << ": " << Distance.at(DijkVector[0]) << " via " << startV << endl;
	// 	cout << "first" << endl;
		for(unsigned i = 1; i < DijkVector.size(); i++){
	//  		cout << "this is " << i << endl;
			cout << DijkVector[i] << ": " << Distance.at(DijkVector[i]) << " via ";
	// 	    cout << "this is after distance" << endl;
			vector<char> Preddd = outputPreds(DijkVector, Predecessors, startV, i);
			outputLast(Preddd);
			cout << endl;
		}
	}
	//output vectors
    
	//cout predecessors
	//stack<char> Preddd = outputPreds(DijkVector, Predecessors, startV, 5);
// 	for(unsigned int i = 0; i < Preddd.size(); i++){
// 		cout << Preddd[i] << " ";
// 	}
    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }

  //
  // done:
  //
  return 0;
}
