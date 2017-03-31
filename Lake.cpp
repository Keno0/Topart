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
	void printAllPathsUtil(int, int, bool[], int[], int &);
public:
	Graph(int V); // Constructor

				  // function to add an edge to graph
	void addEdge(int u, int v, int weight);

	// Finds longest distances from given source vertex
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
		if (distance > bestDistance && distance <= maxDistance)
		{
			bestDistance = distance;
			bestPathIndex = path_index;
			for (int i = 0; i < path_index; i++)
			{
				bestPath[i] = path[i];
			}
		}			
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

	int s = 0, d = vertices-1;	
	g.printAllPaths(s, d);

	g.CheckNumberOfCompTravel();

	return 0;
}