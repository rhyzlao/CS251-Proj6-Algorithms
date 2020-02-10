/*util.h*/

#pragma once

#include <iostream>
#include <string>
#include <map>

#include "graph.h"
#include "minqueue.h"

using namespace std;

void buildGraph(string filename, graph& g);
vector<char> DFS(graph& g, char startV);
vector<char> BFS(graph& g, char startV);
vector<char> DijkstraShortestPath(graph& g, char startV, map<char, int> &Distance, map<char, char> &Predecessors);
