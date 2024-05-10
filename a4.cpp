#include <bits/stdc++.h>
using namespace std;

// Function to find the vertex with minimum key value
int minKey( vector<int> &key,  vector<bool> &inMST, int V)
{
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; ++v)
    {
        if (!inMST[v] && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the MST
void printMST(vector<int> &parent, vector<vector<int>> &graph, unordered_map<int, string> &indexToCity)
{
    cout << "Edge \tWeight" << endl;
    for (int i = 1; i < parent.size(); ++i)
    {
        cout << indexToCity.at(parent[i]) << " - " << indexToCity.at(i) << "\t" << graph[i][parent[i]] << endl;
    }
}

// Function to perform Prim's algorithm and print the MST
void primMST(vector<vector<int>> &graph, int V, unordered_map<int, string> &indexToCity)
{
    vector<int> parent(V, -1);    // Array to store constructed MST
    vector<int> key(V, INT_MAX);  // Key values used to pick minimum weight edge in cut
    vector<bool> inMST(V, false); // To represent vertices not yet included in MST

    // Start with the first vertex
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always the root of MST

    // Construct MST with V vertices
    for (int count = 0; count < V - 1; ++count)
    {
        int u = minKey(key, inMST, V); // Pick the minimum key vertex not yet included in MST
        if (u == -1)
        {
            break; // If no vertex left to include, break
        }

        inMST[u] = true; // Include the picked vertex in MST

        // Update key values and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < V; ++v)
        {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the MST
    printMST(parent, graph, indexToCity);
}

int main()
{
    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    unordered_map<string, int> cityToIndex;
    unordered_map<int, string> indexToCity;
    vector<vector<int>> graph(numCities, vector<int>(numCities, 0));

    // Input city names and build cityToIndex and indexToCity maps
    cin.ignore(); // Ignore newline character in buffer
    for (int i = 0; i < numCities; ++i)
    {
        string cityName;
        cout << "Enter name of city " << i + 1 << ": ";
        getline(cin, cityName);

        cityToIndex[cityName] = i;
        indexToCity[i] = cityName;
    }

    // Input road costs between cities to build the adjacency matrix (graph)
    for (int i = 0; i < numCities; ++i)
    {
        for (int j = i + 1; j < numCities; ++j)
        {
            int cost;
            cout << "Enter road cost between " << indexToCity[i] << " and " << indexToCity[j] << ": ";
            cin >> cost;
            graph[i][j] = cost;
            graph[j][i] = cost; // Assuming undirected roads
        }
    }

    // Function call to find and print MST using Prim's algorithm
    primMST(graph, numCities, indexToCity);

    return 0;
}
