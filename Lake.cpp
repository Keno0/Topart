// A C++ program to find single source longest distances in a DAG
#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#include <string>
#define NINF INT_MIN
using namespace std;

// Graph is represented using adjacency list. Every node of adjacency list
// contains vertex number of the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode
{
	int v;
	int weight;
public:
	AdjListNode(int _v, int _w)
	{
		v = _v;
		weight = _w;
	}
	int getV()
	{
		return v;
	}
	int getWeight()
	{
		return weight;
	}
};

// Class to represent a graph using adjacency list representation
class Graph
{
	int distance = 0;
	int bestPath[10000];
	int bestPathIndex = 0;
	int maxDistance = 0;
	int bestDistance = 0;
	int compNumber = 0;
	bool **indexOfPairCompCity;
	string *city;

	int V; // No. of vertices’

		   // Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;

	// A function used by longestPath
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
	void printAllPathsUtil(int, int, bool[], int[], int &);
public:
	Graph(int V); // Constructor

				  // function to add an edge to graph
	void addEdge(int u, int v, int weight);

	// Finds longest distances from given source vertex
	void longestPath(int s);
	void printAllPaths(int s, int d);

	void PrintBestPathEndDistance();
	void ReadDatasFromConsole();
	void CheckNumberOfCompTravel();

};

void Graph::PrintBestPathEndDistance()
{
	cout << "Best distance: " << bestDistance << endl;
	cout << "Best Path: ";
	for (int i = 0; i < bestPathIndex; i++)
	{
		cout << bestPath[i] << " ";
	}
	cout << endl;
}

Graph::Graph(int V) // Constructor
{
	this->V = V;
	adj = new list<AdjListNode>[V];
	city = new string[V];
	indexOfPairCompCity = new bool*[V];
	for (int i = 0; i < V; i++)
	{
		indexOfPairCompCity[i] = new bool[V];
	}
}

void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode node(v, weight);
	adj[u].push_back(node); // Add v to u’s list
}

// A recursive function used by longestPath. See below link for details
// http://www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
	// Mark the current node as visited
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<AdjListNode>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		AdjListNode node = *i;
		if (!visited[node.getV()])
			topologicalSortUtil(node.getV(), visited, Stack);
	}

	// Push current vertex to stack which stores topological sort
	Stack.push(v);
}

// The function to find longest distances from a given vertex. It uses
// recursive topologicalSortUtil() to get topological sorting.
void Graph::longestPath(int s)
{
	stack<int> Stack;
	int *dist = new int[V];

	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to store Topological Sort
	// starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	// Initialize distances to all vertices as infinite and distance
	// to source as 0
	for (int i = 0; i < V; i++)
		dist[i] = NINF;
	dist[s] = 0;

	// Process vertices in topological order
	while (Stack.empty() == false)
	{
		// Get the next vertex from topological order
		int u = Stack.top();
		Stack.pop();

		// Update distances of all adjacent vertices
		list<AdjListNode>::iterator i;
		if (dist[u] != NINF)
		{
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
				if (dist[i->getV()] < dist[u] + i->getWeight())
					dist[i->getV()] = dist[u] + i->getWeight();
		}
	}

	// Print the calculated longest distances
	for (int i = 0; i < V; i++)
		(dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

	// Create an array to store paths
	int *path = new int[V];
	int path_index = 0; // Initialize path[] as empty

						// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	printAllPathsUtil(s, d, visited, path, path_index);
}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
	int path[], int &path_index)
{
	// Mark the current node and store it in path[]
	visited[u] = true;
	path[path_index] = u;
	path_index++;

	// If current vertex is same as destination, then print
	// current path[]
	if (u == d)
	{
		
		/*for (int i = 0; i < path_index; i++)
		{
			cout << path[i] << " ";
			
		}*/
		if (distance > bestDistance && distance <= maxDistance)
		{
			bestDistance = distance;
			bestPathIndex = path_index;
			for (int i = 0; i < path_index; i++)
			{
				bestPath[i] = path[i];
			}
		}
		//cout <<" "<<distance << endl;
		
		

	}
	else // If current vertex is not destination
	{
		// Recur for all the vertices adjacent to current vertex
		list<AdjListNode>::iterator i;
		
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (!visited[i->getV()])
			{
				distance += i->getWeight();
				printAllPathsUtil(i->getV(), d, visited, path, path_index);
				distance -= i->getWeight();
			}
		}
	}

	// Remove current vertex from path[] and mark it as unvisited
	
	path_index--;
	visited[u] = false;
}

void Graph::ReadDatasFromConsole()
{
	string distanceBetweenCities ="";
	string numberOfComps = "";
	int tempNumber = 0;
	int indexOfNumber = 0;
	getline(cin, city[0]);
	for (int i = 0; i < V-1; i++)
	{
		getline(cin, city[i]);
	}
	city[V - 1] = city[0];

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			indexOfPairCompCity[i][j] = false;
		}
	}

	getline(cin, distanceBetweenCities);
	for (int i = 0; i < distanceBetweenCities.length(); i++)
	{
		
		switch (distanceBetweenCities[i])
		{
		case ' ':
			addEdge(indexOfNumber, indexOfNumber + 1, tempNumber);
			indexOfNumber++;
			tempNumber = 0;
			break;
		case '0':
			tempNumber *= 10;
			break;
		case '1':
			tempNumber *= 10;
			tempNumber += 1;
			break;
		case '2':
			tempNumber *= 10;
			tempNumber += 2;
			break;
		case '3':
			tempNumber *= 10;
			tempNumber += 3;
			break;
		case '4':
			tempNumber *= 10;
			tempNumber += 4;
			break;
		case '5':
			tempNumber *= 10;
			tempNumber += 5;
			break;
		case '6':
			tempNumber *= 10;
			tempNumber += 6;
			break;
		case '7':
			tempNumber *= 10;
			tempNumber += 7;
			break;
		case '8':
			tempNumber *= 10;
			tempNumber += 8;
			break;
		case '9':
			tempNumber *= 10;
			tempNumber += 9;
			break;
		default:
			break;
		}
	}

	addEdge(indexOfNumber, indexOfNumber + 1, tempNumber);

	tempNumber = 0;
	//Number of comps
	getline(cin, numberOfComps);
	for (int i = 0; i < numberOfComps.length(); i++)
	{

		switch (numberOfComps[i])
		{
		case '0':
			tempNumber *= 10;
			break;
		case '1':
			tempNumber *= 10;
			tempNumber += 1;
			break;
		case '2':
			tempNumber *= 10;
			tempNumber += 2;
			break;
		case '3':
			tempNumber *= 10;
			tempNumber += 3;
			break;
		case '4':
			tempNumber *= 10;
			tempNumber += 4;
			break;
		case '5':
			tempNumber *= 10;
			tempNumber += 5;
			break;
		case '6':
			tempNumber *= 10;
			tempNumber += 6;
			break;
		case '7':
			tempNumber *= 10;
			tempNumber += 7;
			break;
		case '8':
			tempNumber *= 10;
			tempNumber += 8;
			break;
		case '9':
			tempNumber *= 10;
			tempNumber += 9;
			break;
		default:
			break;
		}
	}

	compNumber = tempNumber;
	string compDatas = "";
	//Store indexes comp city pairs
	for (int i = 0; i < compNumber; i++)
	{
		string firsCity = "";
		string secondCity = "";
		string comDistance = "";
		int indexOfFirstCity = 0;
		int indexOfSecondCity = 0;
		int compDis = 0;
		int tempIndex = 0;
		getline(cin, compDatas);
		//store comp data line by line
		for (int i = 0; i < compDatas.length(); i++)
		{
			if (compDatas[i] == ' ')
			{
				if (tempIndex == 0)
				{
					
						firsCity= compDatas.substr(tempIndex, i- tempIndex);

					

					tempIndex = i + 1;
				}
				else
				{
					
					secondCity = compDatas.substr(tempIndex, i - tempIndex);
					

					tempIndex = i + 1;
				}
				
			}
			if (i == (compDatas.length() - 1))
			{
				tempNumber = 0;
				for (int j = tempIndex; j < compDatas.length(); j++)
				{
					switch (compDatas[j])
					{
					case '0':
						tempNumber *= 10;
						break;
					case '1':
						tempNumber *= 10;
						tempNumber += 1;
						break;
					case '2':
						tempNumber *= 10;
						tempNumber += 2;
						break;
					case '3':
						tempNumber *= 10;
						tempNumber += 3;
						break;
					case '4':
						tempNumber *= 10;
						tempNumber += 4;
						break;
					case '5':
						tempNumber *= 10;
						tempNumber += 5;
						break;
					case '6':
						tempNumber *= 10;
						tempNumber += 6;
						break;
					case '7':
						tempNumber *= 10;
						tempNumber += 7;
						break;
					case '8':
						tempNumber *= 10;
						tempNumber += 8;
						break;
					case '9':
						tempNumber *= 10;
						tempNumber += 9;
						break;
					default:
						break;
					}
				}
			}

			compDis = tempNumber;
		}
		
		for (int i = 0; i < V; i++)
		{
			if (city[i].compare(firsCity) == 0)
			{
				indexOfFirstCity = i;
			}

			if (city[i].compare(secondCity) == 0)
			{
				indexOfSecondCity = i;
			}
		}

		addEdge(indexOfFirstCity, indexOfSecondCity, compDis);
		indexOfPairCompCity[indexOfFirstCity][indexOfSecondCity] = true;
		indexOfPairCompCity[indexOfSecondCity][indexOfFirstCity] = true;

		
	}
	//Store max distance
	string maxDistanceValue = "";
	getline(cin, maxDistanceValue);
	tempNumber = 0;
	for (int j = 0; j < maxDistanceValue.length(); j++)
	{
		switch (maxDistanceValue[j])
		{
		case '0':
			tempNumber *= 10;
			break;
		case '1':
			tempNumber *= 10;
			tempNumber += 1;
			break;
		case '2':
			tempNumber *= 10;
			tempNumber += 2;
			break;
		case '3':
			tempNumber *= 10;
			tempNumber += 3;
			break;
		case '4':
			tempNumber *= 10;
			tempNumber += 4;
			break;
		case '5':
			tempNumber *= 10;
			tempNumber += 5;
			break;
		case '6':
			tempNumber *= 10;
			tempNumber += 6;
			break;
		case '7':
			tempNumber *= 10;
			tempNumber += 7;
			break;
		case '8':
			tempNumber *= 10;
			tempNumber += 8;
			break;
		case '9':
			tempNumber *= 10;
			tempNumber += 9;
			break;
		default:
			break;
		}
	}

	maxDistance = tempNumber;

}

void Graph::CheckNumberOfCompTravel()
{
	int compCounter=0;
	for (int i = 0; i < bestPathIndex -1; i++)
	{
		if (indexOfPairCompCity[bestPath[i]][bestPath[i + 1]])
		{
			compCounter++;
		}
	}
	cout << compCounter << endl;
	for (int i = 0; i < bestPathIndex -1; i++)
	{
		if (indexOfPairCompCity[bestPath[i]][bestPath[i + 1]])
		{
			cout << city[bestPath[i]] << " " << city[bestPath[i + 1]] << endl;
		}
	}

}

// Driver program to test above functions
int main()
{
	// Create a graph given in the above diagram.  Here vertex numbers are
	// 0, 1, 2, 3, 4, 5 with following mappings:
	// 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
	int vertices = 0;
	cin >> vertices;
	vertices++;
	Graph g(vertices);
	g.ReadDatasFromConsole();
	//g.addEdge(0, 1, 30);
	//g.addEdge(1, 2, 15);
	//g.addEdge(2, 3, 60);
	//g.addEdge(3, 4, 45);
	//g.addEdge(4, 5, 60);
	//g.addEdge(2, 4, 30);

	//int s = 1;
	//cout << "Following are longest distances from source vertex " << s << " \n";
	//g.longestPath(s);
	int s = 0, d = vertices-1;
	//cout << "Following are all different paths from " << s	<< " to " << d << endl;
	g.printAllPaths(s, d);

	//g.PrintBestPathEndDistance();
	g.CheckNumberOfCompTravel();

	return 0;
}